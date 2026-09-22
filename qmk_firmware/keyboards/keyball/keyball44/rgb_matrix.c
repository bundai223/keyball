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
        {  0,  1,  2,  3,  4,  5 },
        {  6,  7,  8,  9, 10, 11 },
        { 12, 13, 14, 15, 16, 17 },
        { NO_LED, 18, 19, 20, 21, 22 },
        { 35, 34, 33, 32, 31, 30 },
        { 41, 40, 39, 38, 37, 36 },
        { 47, 46, 45, 44, 43, 42 },
        { NO_LED, 48, NO_LED, NO_LED, 49, 50 },
    },
    {
        /* LED index to physical position */
        {   0,  0 }, {  20,  0 }, {  40,  0 }, {  60,  0 }, {  80,  0 }, { 100,  0 },
        {   0, 21 }, {  20, 21 }, {  40, 21 }, {  60, 21 }, {  80, 21 }, { 100, 21 },
        {   0, 42 }, {  20, 42 }, {  40, 42 }, {  60, 42 }, {  80, 42 }, { 100, 42 },
        {  20, 63 }, {  40, 63 }, {  60, 63 }, {  80, 63 }, { 100, 63 },
        {   0, 63 }, { 112, 63 }, { 124, 63 }, { 136, 63 }, { 148, 63 }, { 160, 63 }, { 172, 63 },

        { 140,  0 }, { 160,  0 }, { 180,  0 }, { 200,  0 }, { 220,  0 }, { 224,  0 },
        { 140, 21 }, { 160, 21 }, { 180, 21 }, { 200, 21 }, { 220, 21 }, { 224, 21 },
        { 140, 42 }, { 160, 42 }, { 180, 42 }, { 200, 42 }, { 220, 42 }, { 224, 42 },
        { 160, 63 }, { 200, 63 }, { 220, 63 },
        { 140, 63 }, { 148, 63 }, { 156, 63 }, { 164, 63 }, { 172, 63 }, { 180, 63 }, { 188, 63 }, { 196, 63 },
        { 224, 63 },
    },
    {
        /* LED index to flag */
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_NONE,
    }
};
// clang-format on

#endif
