/* Copyright 2020 tominabox1
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

// Layers
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _SPCFN,
  _ADJUST
};

// Custom Keycodes
enum custom_keycodes {
    OCQUOTE,
    OCPAREN
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


// Combos
const uint16_t PROGMEM combo1[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_LCBR, KC_RCBR, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo1, KC_NO),
    COMBO(combo2, KC_NO),
	COMBO(combo3, KC_NO)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
  case 0:
	  if (pressed) {
        SEND_STRING("()");
		tap_code16(KC_LEFT);
      }
      break;
  case 1:
      if (pressed) {
        SEND_STRING("[]");
        tap_code16(KC_LEFT);     // go left
      }
      break;
  case 2:
	if (pressed) {
        SEND_STRING("{}");
        tap_code16(KC_LEFT);     // go left
      }
      break;
  }
}
// Combos end

// Tap Dance for open-close quotes
enum {
  DQUOTE,
  SQUOTE
};

// Double quote
void dance_doublequote(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
	case 1:
	  tap_code16(KC_AT);
	  reset_tap_dance(state);
	  break;
	case 2:
	  tap_code16(KC_AT);
	  tap_code16(KC_AT);
	  tap_code16(KC_LEFT);
	  reset_tap_dance(state);
	  break;
	case 3:
	  for (int i = 0; i < 3; i++) {
		tap_code16(KC_AT);
		tap_code16(KC_AT);
		tap_code16(KC_LEFT);
	  }
	  reset_tap_dance(state);
	  break;
	}
}

// Single quotes
void dance_singlequote(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
	case 1:
	  tap_code(KC_QUOT);
	  reset_tap_dance(state);
	  break;
	case 2:
	  tap_code(KC_QUOT);
	  tap_code(KC_QUOT);
	  tap_code16(KC_LEFT);
	  reset_tap_dance(state);
	  break;
	case 3:
	  for (int i = 0; i < 3; i++) {
		tap_code(KC_QUOT);
		tap_code(KC_QUOT);
		tap_code16(KC_LEFT);
	  }
	  reset_tap_dance(state);
	  break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [DQUOTE] = ACTION_TAP_DANCE_FN(dance_doublequote),
  [SQUOTE] = ACTION_TAP_DANCE_FN(dance_singlequote)
};
// Tap Dance end



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | ENTER|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHIFT|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | SHIFT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | ALT  | SUPER| META | LOWER|    SPACE    |RAISE | META | SUPER| ALT  | CTRL |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,          KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,            KC_BSPC,
    KC_TAB,          KC_A,         KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN,         KC_ENT,
    LSFT_T(KC_NUBS), RCTL_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,    KC_N,      KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), RSFT_T(KC_MINS),
    KC_LCTL,         KC_SLCK,      KC_LGUI, KC_LALT, LOWER,   LT(_SPCFN, KC_SPC), RAISE,   KC_LALT, KC_RGUI, KC_SLCK,         KC_LCTL
),

/* RAISE LAYER: SYMBOLS
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   "  |   &  |   *  |   =  |   {  |   }  |  F7  |  F8  |  F9  |  F10 | BSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   @  |   $  |   %  |   ^  |   (  |   )  |  F4  |  F5  |  F6  |  F11 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   _  |   !  |   @  |   #  |   [  |   ]  |  F1  |  F2  |  F3  |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_mit(
    KC_GRV,  TD(DQUOTE), KC_AMPR, KC_ASTR, KC_EQL,  KC_LCBR, KC_RCBR, KC_F7, KC_F8, KC_F9, KC_F10, KC_BSPC,
    _______, S(KC_QUOT), KC_DLR,  KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_F4, KC_F5, KC_F6, KC_F11, _______,
    KC_PIPE, KC_UNDS, KC_EXLM, S(KC_QUOT), KC_NUHS, KC_LBRC, KC_RBRC, KC_F1, KC_F2, KC_F3, KC_F12, _______,
    _______, _______, _______, _______,    _______, _______, _______, _______,    KC_MNXT, KC_VOLD, KC_VOLU
),

/* LOWER LAYER: NUMBERS
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |      |      |      |      |      |      |   7  |   8  |   9  |   0  |  ^   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |   '  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |   *  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
    S(KC_NUHS), _______, _______, _______,    _______,    _______, _______, KC_7,    KC_8,    KC_9,    KC_0,    KC_CIRC,
    _______,    _______, _______, _______,    _______,    _______, _______, KC_4,    KC_5,    KC_6,    TD(SQUOTE), KC_EQUAL,
    _______,    _______, _______, _______,    _______,    _______, _______, KC_1,    KC_2,    KC_3,    KC_ASTR, KC_PLUS,
    _______,    _______, _______, _______,    _______,    _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* SPACE FUNCTION LAYER: NAVIGATION ETC.
 * ,-----------------------------------------------------------------------------------.
 * |      |      | INS  | END  | BSPC |C-BSPC|      |      |  UP  | A-TAB| C-UP | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | HOME | PSCR | DEL  |      | C-DEL| C-LFT| LFT  | DOWN | RIGHT|C-RGHT|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | APP  |      |      |      | C-DWN|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SPCFN] = LAYOUT_planck_mit(
	_______, _______, KC_INS,  KC_END,  KC_BSPC, C(KC_BSPC), _______,    KC_CAPS,  KC_UP,    A(KC_TAB),  C(KC_UP), KC_DEL ,
    _______, KC_HOME, KC_PSCR, KC_DEL , _______, C(KC_DEL),  C(KC_LEFT), KC_LEFT,  KC_DOWN,  KC_RIGHT,   C(KC_RIGHT), _______,  
    _______, _______, KC_APP , _______, _______, _______,    C(KC_DOWN), _______,  _______,  _______,    _______,  _______,
    _______, _______, _______, _______, _______, _______,          _______,        _______,  _______,    _______,  _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | RESET| DEBUG| RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-| DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



