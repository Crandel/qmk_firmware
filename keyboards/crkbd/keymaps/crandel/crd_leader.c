#include QMK_KEYBOARD_H
void leader_end_user(void) {
  if (leader_sequence_one_key(KC_C)) {
    register_code(KC_LSFT);
    tap_code16(C(KC_C));
    unregister_code(KC_LSFT);
    return;
  }
  if (leader_sequence_one_key(KC_V)) {
    register_code(KC_LSFT);
    tap_code16(C(KC_V));
    unregister_code(KC_LSFT);
    return;
  }
  if (leader_sequence_one_key(KC_A)) {
    tap_code(KC_PSCR);
    tap_code16(S(KC_QUOT));
    tap_code(KC_A);
    return;
  }
  if (leader_sequence_one_key(KC_E)) {
    tap_code(KC_PSCR);
    tap_code16(S(KC_QUOT));
    tap_code(KC_E);
    return;
  }
  if (leader_sequence_one_key(KC_O)) {
    tap_code(KC_PSCR);
    tap_code16(S(KC_QUOT));
    tap_code(KC_O);
    return;
  }
  if (leader_sequence_one_key(KC_U)) {
    tap_code(KC_PSCR);
    tap_code16(S(KC_QUOT));
    tap_code(KC_U);
    return;
  }
  if (leader_sequence_one_key(KC_Q)) {
    tap_code(KC_SCLN);
    tap_code(KC_W);
    tap_code(KC_Q);
    return;
  }
  if (leader_sequence_one_key(KC_X)) {
    tap_code16(A(KC_X));
    return;
  }
}
