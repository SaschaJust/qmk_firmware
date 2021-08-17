/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

// define custom keycodes
enum custom_keycodes {
    // used for windows snipping
    KC_SNIP = SAFE_RANGE,
};

// process the custom keycode events
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_SNIP:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LSFT)"s"SS_UP(X_LSFT)SS_UP(X_LGUI));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Physical keyboard layout:
     *
     *      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Home           Rotary(Mute)
     *      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Ins
     *      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 Del
     *      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgUp
     *      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       PgDn
     *      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
     *
     *
     * The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
     * this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
     * cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
     * if that's your preference.
     *
     * To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
     * it'll be back to normal when you plug it back in.
     */

    /*
     * Default Layer
     *
     * This layer is the default typing layer that is supposed to behave exactly as the physical keycaps suggest.
     *
     * Activation:
     *   default
     *
     * Layout specifics:
     *   ESC: ESC normally, GRAVE when used with GUI, TILDE when used with SHIFT.
     *   CAPS: CAPS when tapped, activates layer 2 when held.
     *   RIGHT_SHIFT: SHIFT when held, ENTER when tapped.
     *   Vertical keys have been remapped as I consider this more consistent.
     */
    [0] = LAYOUT(
        KC_GESC,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_HOME,          KC_MUTE,
        KC_GRV,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    KC_BSPC,          KC_INS,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,   KC_BSLS,          KC_DEL,
        LT(2, KC_CAPS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_SFTENT,          KC_UP,   KC_PGDN,
        KC_LCTL,          KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * Media Layer
     *
     * This layer brings media keys and inverse functionality (INS->DEL, HOME->END).
     *
     * Activation:
     *   by holding the FN key.
     *
     * Layout zones:
     *   F-keys are use for media control
     *   Vertical keys are inverted
     *   Arrow cluster is HOME, END, PGUP, PGDN
     *   ESC sends WIN+SHIFT+S for Windows snipping
     *   Backspace enables bootloader
     *
     * Lighting:
     *   Layer indicated by backlighting (side lighting) color: #FF0000 (red)
     */

    [1] = LAYOUT(
        KC_SNIP,          KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, _______, _______, _______, _______,   KC_END,           KC_PSCR,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_DEL,           KC_DEL,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,            KC_INS,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,          KC_PGDN,
        _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, KC_PGUP, KC_PGUP,
        _______,          _______, _______,                            _______,                            _______, _______, _______,   KC_HOME, KC_PGDN, KC_END
    ),

    /*
     * Ergonomic Layer
     *
     * This layer brings media keys and inverse functionality (INS->DEL, HOME->END).
     *
     * Activation:
     *   by holding the CAPS key.
     *
     * Layout zones:
     *   WASD acts as arrow cluster.
     *   F-Keys are second row (F13-F24)
     *
     * Lighting:
     *   Layer indicated by backlighting (side lighting) color: #00FFFF (cyan)
     */

    [2] = LAYOUT(
        KC_SNIP,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,    KC_END,           _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,          KC_DEL,
        _______,          _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,            KC_INS,
        _______,          KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,            _______,          KC_PGDN,
        _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, KC_PGUP,
        _______,          _______, _______,                            _______,                            _______, _______, _______,   _______, _______, _______
    ),
};


/*
 * Here, we replace the default  volume functionality with mouse
 * scrolling. On my setup, volume is controlled through
 * an external DAC and should never be changed in the OS.
 *
 * Additionally, the media layer lets you control volume
 * through F1 to F3.
 *
 * Using the ALT modifier will enable fast scrolling.
 * Using the SHIFT modifier will switch to horizontal scrolling.
 * Using the CTRL modifier will fall back to volume control.
 *
 * We can ignore the index as the GMMK PRO only has one encoder.
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Store which mods are held
    uint8_t mod_state = get_mods();

    if (mod_state & MOD_MASK_CTRL) {
        // If a CTRL is being held
        // Ignore the modifier and only send the keypress.
        del_mods(MOD_MASK_CTRL);
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
        set_mods(mod_state);
    } else if (mod_state & MOD_MASK_SHIFT) {
        // If a SHIFT is being held
        // Ignore the modifier and only send the keypress.
        del_mods(MOD_MASK_SHIFT);
        tap_code(clockwise ? KC_WH_R : KC_WH_L);
        set_mods(mod_state);
    } else {
        // If no modifiers or ALT are held
        tap_code(clockwise ? KC_WH_D : KC_WH_U);
    }

    return true;
}
