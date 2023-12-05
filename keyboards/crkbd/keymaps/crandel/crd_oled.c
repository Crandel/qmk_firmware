char keylog_str[24] = {};
char layer_str[34] = {};

void update_oled_layer(const char *data){
  // update layer_str
  snprintf(layer_str,
           sizeof(layer_str),
           "%s",
           data);
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode == TRM_COPY) {
    name = 'C';
  } else if (keycode == TRM_PSTE) {
    name = 'P';
  } else if (keycode == UML_SEQ) {
    name = 'U';
  } else if (keycode == V_US) {
    name = 'S';
  } else if (keycode == V_UK) {
    name = 'K';
  }

  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }
  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c\n",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
  oled_write(keylog_str, false);
}

void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  oled_write_ln(layer_str, true);
}

bool oled_task_user(void) {
  oled_render_layer_state();
  oled_render_keylog();
  return false;
}

void keyboard_post_init_user(void) {
  // Call the post init code.
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  // update layer_str
  update_oled_layer("Colemak");
}
