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

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifndef RIPPLE_MAX_WAVES
#    define RIPPLE_MAX_WAVES UINT8_C(4)
#endif
#ifndef RIPPLE_DURATION_MS
#    define RIPPLE_DURATION_MS UINT16_C(1200)
#endif
#ifndef RIPPLE_MAX_RADIUS
#    define RIPPLE_MAX_RADIUS UINT16_C(240)
#endif
#ifndef RIPPLE_RING_WIDTH
#    define RIPPLE_RING_WIDTH UINT16_C(18)
#endif
#ifndef RIPPLE_TRAIL_OFFSET
#    define RIPPLE_TRAIL_OFFSET UINT16_C(30)
#endif
#ifndef RIPPLE_TRAIL_WIDTH
#    define RIPPLE_TRAIL_WIDTH UINT16_C(24)
#endif
#ifndef RIPPLE_TRAIL_INTENSITY
#    define RIPPLE_TRAIL_INTENSITY UINT8_C(64)
#endif
#ifndef RIPPLE_HUE_SHIFT_MS
#    define RIPPLE_HUE_SHIFT_MS UINT16_C(16)
#endif

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t started_at;
    uint8_t hue;
    bool active;
} ripple_wave_t;

typedef struct {
    ripple_wave_t waves[RIPPLE_MAX_WAVES];
    uint8_t next_wave;
} ripple_state_t;

typedef struct {
    uint8_t intensity;
    uint8_t hue;
} ripple_sample_t;

void ripple_state_init(ripple_state_t *state);
void ripple_trigger(ripple_state_t *state, uint16_t x, uint16_t y, uint16_t now, uint8_t hue);
ripple_sample_t ripple_sample(const ripple_state_t *state, uint16_t now, uint16_t x, uint16_t y);
