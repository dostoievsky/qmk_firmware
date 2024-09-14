/* Copyright 2022 Dennis Kruyt (dennis@kruyt.org) *
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
  _INSERT,
  _LOWER,
  _RAISE,
  _CONTROL
};

#define KC_LR LT(1, KC_DEL)
#define KC_RE LT(2, KC_BSPC)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_LGUI OSM(MOD_LGUI)
#define KC_CCED ALGR(KC_COMMA)
#define KC_GV ALGR(KC_GRV)
#define KC_DVTM C(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_INSERT] = LAYOUT_ortho_4x12(
        QK_GESC,    KC_Q,     KC_W,    KC_E,    KC_R,  KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_BSLS,
        KC_TAB,     KC_A,     KC_S,    KC_D,    KC_F,  KC_G,    KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,
        OSM_LSFT,   KC_Z,     KC_X,    KC_C,    KC_V,  KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_ENT,
        KC_LCTL,    KC_DVTM,  OSM_LGUI, KC_LALT, KC_LR, KC_SPC,  KC_SPC,  KC_RE, KC_RALT, KC_MENU,  KC_RCTL,  OSM_RSFT
    ),
    [_LOWER] = LAYOUT_ortho_4x12(
        KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        KC_GV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_LCBR, KC_RCBR, KC_GRV,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_EQUAL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_LBRC, KC_RBRC, _______,
        _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_CCED, _______,
        _______,   _______, _______, _______, KC_BSPC, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
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
    default: //  for any other layers, or the default layer
        rgb_matrix_sethsv(HSV_GREEN);
        break;
    }
    return state;
}


void oneshot_mods_changed_user(uint8_t mods) {
	if (mods) {
        	rgb_matrix_sethsv(HSV_WHITE);
	}
 	if (mods & MOD_MASK_GUI) {
        	rgb_matrix_sethsv(HSV_YELLOW);
      	}
	if (!mods) {
        	rgb_matrix_sethsv(HSV_GREEN);
	}
}


