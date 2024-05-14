/* Copyright 2022 Dennis Kruyt (dennis@kruyt.org)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};
     
#define KC_CCED ALGR(KC_COMMA)
#define KC_LOWER LT(1, KC_DEL)
#define KC_RAISE LT(2, KC_BSPC)

// Tap Dances declarations
enum {
	ENT_SFT,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
	[ENT_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_RSFT),
}; 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,         KC_Q,    KC_W,    KC_E,    KC_R,    	KC_T,    KC_Y,    KC_U,		KC_I,    KC_O,     KC_P,       	KC_BSLS,
        KC_TAB,         KC_A,    KC_S,    KC_D,    KC_F,    	KC_G,    KC_H,    KC_J,		KC_K,    KC_L,     KC_SCLN,	KC_QUOT,
        KC_LSFT,	KC_Z,    KC_X,    KC_C,    KC_V,    	KC_B,    KC_N,    KC_M,		KC_COMM, KC_DOT,   KC_SLSH,    	TD(ENT_SFT),
        KC_LCTL,	MO(3),   KC_LGUI, KC_LALT, KC_LOWER,	KC_SPC,  KC_SPC,  KC_RAISE,	KC_LEFT, KC_DOWN,  KC_UP,      	KC_RGHT
    ),
    [_LOWER] = LAYOUT_ortho_4x12(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, S(KC_MINS), KC_EQL,
        KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_LCBR, KC_RCBR,    KC_GRV,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______,    _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,      KC_RGHT
    ),
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PMNS, KC_PPLS,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_LBRC, KC_RBRC, _______,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_CCED, _______,
        _______, _______, _______, _______, KC_BSPC, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
    [_ADJUST] = LAYOUT_ortho_4x12(
        _______, _______, G(KC_1), G(KC_2), G(KC_3), _______, _______, _______, _______, _______, KC_PSCR, C(KC_SCLN),
        _______, _______, G(KC_4), G(KC_5), G(KC_6), _______, _______, _______, _______, _______, _______, _______,
        KC_LSFT, _______, G(KC_7), G(KC_8), G(KC_9), _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, G(KC_0), _______, _______, _______, _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgb_matrix_sethsv(HSV_BLUE);
        break;
    case _LOWER:
        rgb_matrix_sethsv(HSV_RED);
        break;
    case _ADJUST:
        rgb_matrix_sethsv(HSV_YELLOW);
        break;
    default: //  for any other layers, or the default layer
        rgb_matrix_sethsv(HSV_GREEN);
        break;
    }
    return state;
}

