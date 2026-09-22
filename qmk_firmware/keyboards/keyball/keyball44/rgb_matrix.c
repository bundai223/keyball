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

/*
 * The LED indices below follow the WS2812 serial order on each PCB, not a
 * row-major or visual-key order.  The two halves are concatenated globally:
 * left LED1..30 use indices 0..29 and right LED1..29 use indices 30..58;
 * index 59 is the unused split slot.
 *
 * Left PCB:
 *   LED1..20 and LED28..30 are keylights; LED21..27 are underglow.
 * Right PCB:
 *   LED1=R35 (inner thumb), LED2=R34, LED17=R31 (outer thumb),
 *   LED3..10 are underglow, and the main key columns are:
 *     R00: LED11..13, R01: LED14..16, R02: LED18..20,
 *     R03: LED21..23, R04: LED24..26, R05: LED27..29.
 *
 * LAYOUT_* expands the right-hand arguments as R00..R05 in matrix order,
 * while the keymap presents them visually as R05..R00.
 */
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
