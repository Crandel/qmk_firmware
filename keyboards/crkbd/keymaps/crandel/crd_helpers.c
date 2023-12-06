#pragma once
void shifted_letters(uint8_t code){
  register_code(KC_LSFT);
  tap_code16(C(code));
  unregister_code(KC_LSFT);
}

void set_indicators_state(uint8_t hue, uint8_t sat, uint8_t val, const char *data){
  #ifdef OLED_ENABLE
  update_oled_layer(data);
  #endif // OLED_ENABLE
  #ifdef RGBLIGHT_ENABLE
  rgblight_sethsv(hue, sat, val);
  #endif // RGBLIGHT_ENABLE
}
