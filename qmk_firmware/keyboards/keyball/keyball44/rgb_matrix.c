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

#ifdef RGB_MATRIX_ENABLE

// clang-format off
led_config_t g_led_config = {
    {
        /* Key matrix to LED index */
        { 17, 14, 10,  6,  3,  0 },
        { 18, 15, 11,  7,  4,  1 },
        { 19, 16, 12,  8,  5,  2 },
        { NO_LED, 13,  9, 27, 28, 29 },
        { 40, 43, 47, 50, 53, 56 },
        { 41, 44, 48, 51, 54, 57 },
        { 42, 45, 49, 52, 55, 58 },
        { NO_LED, 46, NO_LED, NO_LED, 31, 30 },
    },
    {
        /* LED index to physical position */
        { 100,  0 }, { 100, 21 }, { 100, 42 },
        {  80,  0 }, {  80, 21 }, {  80, 42 },
        {  60,  0 }, {  60, 21 }, {  60, 42 },
        {  60, 63 },
        {  40,  0 }, {  40, 21 }, {  40, 42 },
        {  40, 63 },
        {  20,  0 }, {  20, 21 }, {  20, 42 },
        {   0,  0 }, {   0, 21 }, {   0, 42 },
        {   0, 63 }, { 112, 63 }, { 124, 63 }, { 136, 63 }, { 148, 63 }, { 160, 63 }, { 172, 63 },
        {  80, 63 }, { 100, 63 }, { 120, 63 },

        { 140, 63 }, { 160, 63 },
        { 140, 63 }, { 148, 63 }, { 156, 63 }, { 164, 63 }, { 172, 63 }, { 180, 63 }, { 188, 63 }, { 196, 63 },
        { 224,  0 }, { 224, 21 }, { 224, 42 },
        { 220,  0 }, { 220, 21 }, { 220, 42 }, { 220, 63 },
        { 200,  0 }, { 200, 21 }, { 200, 42 },
        { 180,  0 }, { 180, 21 }, { 180, 42 },
        { 160,  0 }, { 160, 21 }, { 160, 42 },
        { 140,  0 }, { 140, 21 }, { 140, 42 },
        { 224, 63 },
    },
    {
        /* LED index to flag */
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,

        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_NONE,
    }
};
// clang-format on

#endif
