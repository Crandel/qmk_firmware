#pragma once

enum layers {
  COLMAK_L = 0,
  NUM_L = 1,
  CHARS_L = 2,
  MOUSE_L = 3,
  GAME_L = 4,
};

#define TO_CLM (1 << COLMAK_L)
#define TO_NMB (1 << NUM_L)
#define TO_CHR (1 << CHARS_L)
#define TO_MOS (1 << MOUSE_L)
#define TO_GAM (1 << GAME_L)

enum custom_keycodes {
  TRM_COPY = SAFE_RANGE,
  TRM_PSTE,
  UML_SEQ,
  V_US,
  V_UK,
};
