/*
Copyright 2026 bundai223

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#endif
#include "sync_timer.h"

#include "ripple_adapter.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t started_at;
    uint8_t hue;
} ripple_event_t;

static ripple_state_t ripple_state;

#ifdef SPLIT_KEYBOARD
static ripple_event_t pending_events[RIPPLE_MAX_WAVES];
static uint8_t        pending_event_count;
#endif

static void trigger_event(const ripple_event_t *event) {
    ripple_trigger(&ripple_state, event->x, event->y, event->started_at, event->hue);
}

static bool key_led_point(uint8_t row, uint8_t column, uint16_t *x, uint16_t *y) {
    if (row >= MATRIX_ROWS || column >= MATRIX_COLS) {
        return false;
    }

    uint8_t led = g_led_config.matrix_co[row][column];
    if (led == NO_LED || g_led_config.flags[led] == LED_FLAG_NONE) {
        return false;
    }

    *x = g_led_config.point[led].x;
    *y = g_led_config.point[led].y;
    return true;
}

void keyball_ripple_trigger_key(uint8_t row, uint8_t column) {
    uint16_t x;
    uint16_t y;
    if (!key_led_point(row, column, &x, &y)) {
        return;
    }

    ripple_event_t event = {
        .x          = x,
        .y          = y,
        .started_at = sync_timer_read(),
        .hue        = rgb_matrix_get_hue(),
    };
    trigger_event(&event);

#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        if (pending_event_count < RIPPLE_MAX_WAVES) {
            pending_events[pending_event_count++] = event;
        } else {
            pending_events[0] = event;
        }
    }
#endif
}

ripple_sample_t keyball_ripple_sample(uint16_t now, uint16_t x, uint16_t y) {
    return ripple_sample(&ripple_state, now, x, y);
}

#ifdef SPLIT_KEYBOARD
static void ripple_event_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    (void)in_buflen;
    (void)out_buflen;
    (void)out_data;
    trigger_event((const ripple_event_t *)in_data);
}
#endif

void keyboard_post_init_user(void) {
    ripple_state_init(&ripple_state);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_RIPPLE);
#endif
#ifdef SPLIT_KEYBOARD
    if (!is_keyboard_master()) {
        transaction_register_rpc(RIPPLE_EVENT_SYNC, ripple_event_handler);
    }
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    if (record->event.pressed) {
        keyball_ripple_trigger_key(record->event.key.row, record->event.key.col);
    }
    return true;
}

void housekeeping_task_user(void) {
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master() && pending_event_count > 0 && transaction_rpc_send(RIPPLE_EVENT_SYNC, sizeof(ripple_event_t), &pending_events[0])) {
        for (uint8_t index = 1; index < pending_event_count; index++) {
            pending_events[index - 1] = pending_events[index];
        }
        pending_event_count--;
    }
#endif
}
