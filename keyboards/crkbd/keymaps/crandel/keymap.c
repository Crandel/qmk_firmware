/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 Vitalii Drevenchuk <@Crandel>

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
#ifdef DEBUG_ENABLE
#include "print.h"
#endif

#include "crd_keycodes.h"


#ifdef OLED_ENABLE
#  include <stdio.h>
#  include "crd_oled.c"
#endif

#include "crd_helpers.c"

#ifdef LEADER_ENABLE
#  include "crd_leader.c"
#endif

#ifdef TAP_DANCE_ENABLE
#  include "crd_tapdance.c"
#endif


void set_lang(bool lng){
  if (lng) {
    tap_code(KC_CAPS);
  } else {
    tap_code16(S(KC_CAPS));
  }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  #ifdef DEBUG_ENABLE
  uprintf("current state in default_layer_state_set_user %d, biton %d\n", state, biton32(state));
  #endif // !NO_DEBUG
  switch (biton32(state)) {
    case COLMAK_L:
      set_indicators_state(CR_HSV_GREEN, "COLEMAK");
      break;
    case NUM_L:
      set_indicators_state(CR_HSV_BLUE, "NUMBERS");
      break;
    case CHARS_L:
      set_indicators_state(CR_HSV_GOLD, "CHARS");
      break;
    case MOUSE_L:
      set_indicators_state(CR_HSV_ORANGE, "MOUSE");
      break;
    case GAME_L:
      set_indicators_state(CR_HSV_RED, "GAMES");
      break;
  }
  return state;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
  #endif
  switch (keycode) {
  case TRM_COPY:
    if (record->event.pressed) {
      // when keycode TRM_COPY is pressed
      shifted_letters(KC_C);
    }
    break;
  case TRM_PSTE:
    if (record->event.pressed) {
      shifted_letters(KC_V);
    }
    break;
  case UML_SEQ:
    if (record->event.pressed) {
      // when keycode UML_SEQ is pressed
      tap_code(KC_PSCR);
      tap_code16(S(KC_QUOT));
    }
    break;
  case V_US:
    if (record->event.pressed) {
      set_lang(true);
    }
    break;
  case V_UK:
    if (record->event.pressed) {
      set_lang(false);
    }
    break;
  }
  #ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  #endif // oled_enable

  return true;
}

#ifdef COMBO_ENABLE
enum combo_events {
  UK_COMBO,
  UK_N_COMBO,
  US_COMBO,
  TAB_COMBO,
  TAB_N_COMBO,
  ESC_COMBO,
  ESC_N_COMBO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM uk_combo[]    = {KC_B,    KC_E,    COMBO_END};
const uint16_t PROGMEM uk_n_combo[]  = {KC_MINS, KC_HOME, COMBO_END};
const uint16_t PROGMEM us_combo[]    = {KC_D,    KC_N,    COMBO_END};
const uint16_t PROGMEM tab_combo[]   = {KC_G,    KC_M,    COMBO_END};
const uint16_t PROGMEM tab_n_combo[] = {KC_3,    KC_DOT,  COMBO_END};
const uint16_t PROGMEM esc_combo[]   = {KC_V,    KC_O,    COMBO_END};
const uint16_t PROGMEM esc_n_combo[] = {KC_F2,   KC_BTN4, COMBO_END};
combo_t key_combos[] = {
    [UK_COMBO]    = COMBO_ACTION(uk_combo), // keycodes with modifiers are possible too!
    [UK_N_COMBO]  = COMBO_ACTION(uk_n_combo),
    [US_COMBO]    = COMBO_ACTION(us_combo),
    [TAB_COMBO]   = COMBO_ACTION(tab_combo),
    [TAB_N_COMBO] = COMBO_ACTION(tab_n_combo),
    [ESC_COMBO]   = COMBO_ACTION(esc_combo),
    [ESC_N_COMBO] = COMBO_ACTION(esc_n_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
  case UK_COMBO:
  case UK_N_COMBO:
    if (pressed) {
      set_lang(false);
    }
    break;
  case US_COMBO:
    if (pressed) {
      set_lang(true);
    }
    break;
  case ESC_COMBO:
  case ESC_N_COMBO:
    if (pressed) {
      tap_code(KC_ESC);
    }
    break;
  case TAB_COMBO:
  case TAB_N_COMBO:
    if (pressed) {
      tap_code(KC_TAB);
    }
    break;
  }
}
#endif // COMBO_ENABLE


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COLMAK_L] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------.    ,------------------------------------------------------------------------.
     QK_GESC,    KC_Q, LALT_T(KC_W), LCTL_T(KC_F), LSFT_T(KC_P),       KC_B,       KC_E, LSFT_T(KC_I), LCTL_T(KC_U), RALT_T(KC_Y),    KC_SCLN,     KC_DEL,
  //|-------+--------+-------------+-------------+-------------+-----------|    |------+-------------+-------------+-------------+-----------+-----------|
  TD(TD_LNG),    KC_A,         KC_R,         KC_S,         KC_T,       KC_G,       KC_M,         KC_H,         KC_J,         KC_K,       KC_L, TD(TD_UKR),
  //|-------+--------+-------------+-------------+-------------+-----------|    |------+-------------+-------------+-------------+-----------+-----------|
     KC_LSFT,    KC_Z,         KC_X,         KC_C,         KC_D,       KC_V,       KC_O,         KC_N,      KC_COMM,       KC_DOT, TD(TD_SYM),    QK_LEAD,
  //|-------+--------+-------------+-------------+-------------+-----------|    |------+-------------+-------------+-------------+-----------+-----------|
                                          KC_LGUI,       KC_SPC, TD(TD_LAY),     KC_ENT,       KC_TAB,      KC_BSPC
                                          //`------------------------------'    `----------------------------------'
  ),

  [NUM_L] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.    ,------------------------------------------------------------------------------------.
      QK_GESC, KC_F5, LALT_T(KC_7), LCTL_T(KC_4), LSFT_T(KC_2),      KC_MINS,          KC_HOME, LSFT_T(KC_END), LCTL_T(KC_PGDN), RALT_T(KC_PGUP),  UML_SEQ,     KC_DEL,
  //|--------+------+-------------+-------------+-------------+-------------|    |------------+---------------+----------------+----------------+---------+-----------|
   TD(TD_LNG), KC_F4,         KC_8,         KC_5,         KC_1,         KC_3,           KC_DOT,        KC_LEFT,         KC_DOWN,           KC_UP, KC_RIGHT, TD(TD_UKR),
  //|--------+------+-------------+-------------+-------------+-------------|    |------------+---------------+----------------+----------------+---------+-----------|
        KC_F1, KC_F3,         KC_9,         KC_6,         KC_0,        KC_F2,          KC_BTN4,        KC_BTN1,         KC_BTN2,         KC_BTN3,  KC_BSLS,    KC_PSCR,
  //---------+------+-------------+-------------+-------------+-------------|    |------------+---------------+----------------+----------------+---------+-----------|
                                         KC_LGUI,       KC_SPC,   TD(TD_LAY),           KC_ENT,         KC_TAB,         KC_BSPC
                                         //`--------------------------------'    `---------------------------------------------'
  ),

  [CHARS_L] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.    ------------------------------------------------------------------------------------.
       QK_GESC,   KC_F7, LSFT(KC_7), LSFT(KC_4), LSFT(KC_2),           KC_F8,           KC_EQL, LSFT(KC_BSLS),        KC_GRV, LSFT(KC_GRV), LSFT(KC_SCLN),     KC_DEL,
  //|---------+--------+-----------+-----------+-----------+----------------|    |------------+--------------+--------------+-------------+--------------+-----------|
    TD(TD_LNG),TRM_COPY, LSFT(KC_8), LSFT(KC_5), LSFT(KC_1),      LSFT(KC_3),          KC_LCTL,       KC_LBRC,    LSFT(KC_9),   LSFT(KC_0),       KC_RBRC, TD(TD_UKR),
  //|---------+--------+-----------+-----------+-----------+----------------|    |------------+--------------+--------------+-------------+--------------+-----------|
       KC_LALT,TRM_PSTE,     KC_CUT, LSFT(KC_6),     KC_APP,         KC_PSTE,     LSFT(KC_EQL), LSFT(KC_LBRC), LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_RBRC),    KC_PSCR,
  //|---------+--------+-----------+-----------+-----------+----------------|    |------------+--------------+--------------+-------------+--------------+-----------|
                                        KC_LGUI,     KC_SPC,      TD(TD_LAY),           KC_ENT,        KC_TAB,       KC_BSPC
                                        //`---------------------------------'    `------------------------------------------'
  ),

  [MOUSE_L] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------.              ,--------------------------------------------------------.
      QK_GESC,  KC_BRID, KC_BRIU,  KC_VOLD, KC_VOLU,        KC_F9,                    KC_F10,  KC_F11, KC_WH_D, KC_WH_U, KC_PSCR, QK_BOOT,
  //|--------+---------+--------+---------+--------+-------------|              |-----------+--------+--------+--------+--------+--------|
   TD(TD_LNG), TRM_COPY, KC_BTN4,  KC_BTN2, KC_BTN1,      KC_BTN3,                    KC_F12, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  TO_GAM,
  //|--------+---------+--------+---------+--------+-------------|              |-----------+--------+--------+--------+-----------------|
      QK_BOOT, TRM_PSTE,  KC_CUT,  KC_COPY,  KC_APP,      KC_PSTE,                    KC_INS, KC_WBAK, KC_PGDN, KC_PGUP, KC_WFWD, XXXXXXX,
  //|--------+---------+--------+------------------+-------------|              |-----------+--------+--------+--------+--------+--------|
                                   KC_LGUI,  KC_SPC,   TD(TD_LAY),                    KC_ENT,  KC_TAB, KC_BSPC
                                   //`---------------------------'              `-----------------------------'
  ),

  [GAME_L] = LAYOUT_split_3x6_3(
  //,-------------------------------------------------.    ,------------------------------------------------------.
        QK_GESC,    KC_G, KC_Q,   KC_W,   KC_E,   KC_H,     XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|----------+--------+-----+-------+-------+-------|    |------+-----------+--------+--------+--------+--------|
     TD(TD_LNG), KC_LSFT, KC_A,   KC_S,   KC_D,   KC_F,       KC_1,       KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,
  //|----------+--------+-----+-------+-------+-------|    |------+-----------+--------+--------+--------+--------|
        XXXXXXX, KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_V,       KC_6,       KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|----------+--------+-----+-------+-------+-------|    |------+-----------+--------+--------+--------+--------|
                               KC_LALT, KC_TAB, KC_ENT,     KC_ENT, TD(TD_LAY), XXXXXXX
                               //`--------------------'    `---------------------------'
  ),
};

