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
#include "crd_keycodes.h"
#include QMK_KEYBOARD_H

// Tap dance enums
enum {
  TD_LAY,
  TD_LNG,
  TD_UKR,
  TD_SYM
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


// Create an instance of 'td_tap_t' for the 'TD_LAY' tap dance.
static td_tap_t state_lay = {
    .is_press_action = true,
    .state = TD_NONE
};

void finished_lay(tap_dance_state_t *state, void *user_data) {
    state_lay.state = cur_dance(state);
    switch (state_lay.state) {
        case TD_SINGLE_TAP:  register_code16(TO_CLM); break;
        case TD_SINGLE_HOLD: register_code16(TO_CHR); break;
        case TD_DOUBLE_TAP:  register_code16(TO_NMB); break;
        case TD_DOUBLE_HOLD: register_code16(TO_MOS); break;
        default: break;
    }
}

void reset_lay(tap_dance_state_t *state, void *user_data) {
    switch (state_lay.state) {
        case TD_SINGLE_TAP:  unregister_code16(TO_CLM); break;
        case TD_SINGLE_HOLD: unregister_code16(TO_CHR); break;
        case TD_DOUBLE_TAP:  unregister_code16(TO_NMB); break;
        case TD_DOUBLE_HOLD: unregister_code16(TO_MOS); break;
        default: break;
    }
    state_lay.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'TD_LNG' tap dance.
static td_tap_t state_lng = {
    .is_press_action = true,
    .state = TD_NONE
};

void finished_lng(tap_dance_state_t *state, void *user_data) {
    state_lng.state = cur_dance(state);
    switch (state_lng.state) {
        case TD_SINGLE_TAP:  register_code(KC_CAPS); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_CAPS)); break;
        case TD_DOUBLE_TAP:  register_code16(S(KC_CAPS)); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_CAPS)); break;
        default: break;
    }
}

void reset_lng(tap_dance_state_t *state, void *user_data) {
    switch (state_lng.state) {
        case TD_SINGLE_TAP:  unregister_code(KC_CAPS); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_CAPS)); break;
        case TD_DOUBLE_TAP:  unregister_code16(S(KC_CAPS)); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_CAPS)); break;
        default: break;
    }
    state_lng.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'TD_UKR' tap dance.
static td_tap_t state_ukr = {
    .is_press_action = true,
    .state = TD_NONE
};

void finished_ukr(tap_dance_state_t *state, void *user_data) {
    state_ukr.state = cur_dance(state);
    switch (state_ukr.state) {
        case TD_SINGLE_TAP:  register_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP:  register_code16(S(KC_SLSH)); break;
        case TD_DOUBLE_HOLD: register_code(KC_RBRC); break;
        default: break;
    }
}

void reset_ukr(tap_dance_state_t *state, void *user_data) {
    switch (state_ukr.state) {
        case TD_SINGLE_TAP:  unregister_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP:  unregister_code16(S(KC_SLSH)); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_RBRC); break;
        default: break;
    }
    state_ukr.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'TD_SYM' tap dance.
static td_tap_t state_sym = {
    .is_press_action = true,
    .state = TD_NONE
};

void finished_sym(tap_dance_state_t *state, void *user_data) {
    state_sym.state = cur_dance(state);
    switch (state_sym.state) {
        case TD_SINGLE_TAP:  register_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP:  register_code16(S(KC_SLSH)); break;
        case TD_DOUBLE_HOLD: register_code(KC_RBRC); break;
        default: break;
    }
}

void reset_sym(tap_dance_state_t *state, void *user_data) {
    switch (state_sym.state) {
        case TD_SINGLE_TAP:  unregister_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP:  unregister_code16(S(KC_SLSH)); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_RBRC); break;
        default: break;
    }
    state_sym.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, finished_lay, reset_lay),
    [TD_LNG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, finished_lng, reset_lng),
    [TD_UKR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, finished_ukr, reset_ukr),
    [TD_SYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, finished_sym, reset_sym)
};
