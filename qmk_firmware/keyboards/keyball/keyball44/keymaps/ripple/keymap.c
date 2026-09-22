/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Personal Keyball44 mapping captured from the Remap configuration.
  [0] = LAYOUT_universal(
    _______  , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , _______  ,
    _______  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , RALT_T(KC_SCLN), _______  ,
    _______  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , RSFT_T(KC_SLSH), _______  ,
              KC_LALT, KC_LGUI, SFT_T(KC_SPC),       LT(1, KC_BSPC), LCTL_T(KC_ESC),                  RCTL_T(KC_TAB), LT(2, KC_ENT), _______, _______, LSG(KC_4)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                       KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  ,
    _______  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                       KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______  ,
    _______  , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                       S(KC_6)  , S(KC_7)  , S(KC_8)  , KC_F11   , KC_F12   , _______  ,
              _______, _______, _______,              _______, _______,                     _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_F11   , KC_F12   , S(KC_9)  , S(KC_0)  , S(KC_GRV),                                      _______, _______, _______, _______, KC_BSLS  , _______  ,
    _______  , _______  , _______  , KC_LBRC  , KC_RBRC  , KC_MINS  ,                                      KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_QUOT  , _______  ,
    _______  , _______  , _______  , S(KC_LBRC), S(KC_RBRC), KC_EQL ,                                      S(KC_EQL), KC_GRV   , KC_BSLS  , _______, S(KC_MINS), _______  ,
              _______, _______, _______,              KC_DEL  , KC_ESC  ,                       _______, _______, _______, _______, _______
  ),

  [3] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                       _______, _______, _______, _______, _______, _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                       _______, KC_BTN1  , KC_BTN3  , KC_BTN2  , MO(4)    , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                       _______, _______, _______, _______, _______, _______  ,
              _______, 0x5C00   , _______,              _______, _______,                     _______, _______, _______, _______, 0x5C00
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Layer 3 is the personal mouse layer; scroll mode is controlled by
    // explicit pointing-device keycodes instead of layer state.
    (void)state;
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
