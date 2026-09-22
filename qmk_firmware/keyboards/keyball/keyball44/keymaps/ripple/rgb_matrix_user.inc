RGB_MATRIX_EFFECT(RIPPLE)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "ripple_adapter.h"

static uint8_t ripple_add(uint8_t first, uint8_t second) {
    uint16_t sum = (uint16_t)first + second;
    return sum > 255 ? 255 : (uint8_t)sum;
}

bool RIPPLE(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV background_hsv = rgb_matrix_config.hsv;
    background_hsv.v   = scale8(background_hsv.v, 32);
    RGB background      = rgb_matrix_hsv_to_rgb(background_hsv);
    uint16_t now        = (uint16_t)g_rgb_timer;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        ripple_sample_t sample = keyball_ripple_sample(now, g_led_config.point[i].x, g_led_config.point[i].y);
        HSV             wave_hsv = {
            .h = sample.hue,
            .s = rgb_matrix_config.hsv.s,
            .v = rgb_matrix_config.hsv.v,
        };
        RGB wave = rgb_matrix_hsv_to_rgb(wave_hsv);
        rgb_matrix_set_color(i,
                             ripple_add(background.r, scale8(wave.r, sample.intensity)),
                             ripple_add(background.g, scale8(wave.g, sample.intensity)),
                             ripple_add(background.b, scale8(wave.b, sample.intensity)));
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
