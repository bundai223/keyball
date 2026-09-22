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

#include "ripple.h"

static uint8_t ring_intensity(uint32_t distance_squared, uint16_t radius, uint16_t width) {
    uint16_t lower_radius = radius > width ? radius - width : 0;
    uint16_t upper_radius = radius + width;
    uint32_t lower_squared = (uint32_t)lower_radius * lower_radius;
    uint32_t radius_squared = (uint32_t)radius * radius;
    uint32_t upper_squared = (uint32_t)upper_radius * upper_radius;

    if (distance_squared < lower_squared || distance_squared > upper_squared) {
        return 0;
    }

    if (radius == 0) {
        return (uint8_t)(255 - (distance_squared * 255) / upper_squared);
    }

    if (distance_squared <= radius_squared) {
        uint32_t span = radius_squared - lower_squared;
        return (uint8_t)(((distance_squared - lower_squared) * 255) / span);
    }

    return (uint8_t)(((upper_squared - distance_squared) * 255) / (upper_squared - radius_squared));
}

static uint8_t add_intensity(uint8_t first, uint8_t second) {
    uint16_t sum = (uint16_t)first + second;
    return sum > 255 ? 255 : (uint8_t)sum;
}

static uint32_t distance_squared(const ripple_wave_t *wave, uint16_t x, uint16_t y) {
    int32_t dx = (int32_t)x - wave->x;
    int32_t dy = (int32_t)y - wave->y;

    return (uint32_t)(dx * dx + dy * dy);
}

void ripple_state_init(ripple_state_t *state) {
    state->next_wave = 0;
    for (uint8_t index = 0; index < RIPPLE_MAX_WAVES; index++) {
        state->waves[index].active = false;
    }
}

void ripple_trigger(ripple_state_t *state, uint16_t x, uint16_t y, uint16_t now, uint8_t hue) {
    ripple_wave_t *wave = &state->waves[state->next_wave];

    wave->x = x;
    wave->y = y;
    wave->started_at = now;
    wave->hue = hue;
    wave->active = true;
    state->next_wave = (uint8_t)((state->next_wave + 1) % RIPPLE_MAX_WAVES);
}

ripple_sample_t ripple_sample(ripple_state_t *state, uint16_t now, uint16_t x, uint16_t y) {
    ripple_sample_t result = {0, 0};
    uint8_t strongest_intensity = 0;

    for (uint8_t index = 0; index < RIPPLE_MAX_WAVES; index++) {
        ripple_wave_t *wave = &state->waves[index];
        uint16_t elapsed;

        if (!wave->active) {
            continue;
        }

        elapsed = (uint16_t)(now - wave->started_at);
        if (elapsed >= RIPPLE_DURATION_MS) {
            // Retire expired waves so a 16-bit timer wrap cannot replay them.
            wave->active = false;
            continue;
        }

        uint16_t radius = (uint16_t)(((uint32_t)RIPPLE_MAX_RADIUS * elapsed) / RIPPLE_DURATION_MS);
        uint32_t distance = distance_squared(wave, x, y);
        uint8_t intensity = ring_intensity(distance, radius, RIPPLE_RING_WIDTH);
        uint16_t trail_radius = radius > RIPPLE_TRAIL_OFFSET ? radius - RIPPLE_TRAIL_OFFSET : 0;
        uint8_t trail = ring_intensity(distance, trail_radius, RIPPLE_TRAIL_WIDTH);

        trail = (uint8_t)(((uint16_t)trail * RIPPLE_TRAIL_INTENSITY) / 255);
        intensity = add_intensity(intensity, trail);
        if (intensity > strongest_intensity) {
            strongest_intensity = intensity;
            result.hue = (uint8_t)(wave->hue + elapsed / RIPPLE_HUE_SHIFT_MS);
        }
        result.intensity = add_intensity(result.intensity, intensity);
    }

    return result;
}
