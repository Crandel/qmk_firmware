#pragma once

enum layers {
  COLMAK_L = 0,
  NUM_L = 1,
  CHARS_L = 2,
  MOUSE_L = 3,
  GAME_L = 4,
};

#define TO_CLM DF(COLMAK_L)
#define TO_NMB DF(NUM_L)
#define TO_CHR DF(CHARS_L)
#define TO_MOS DF(MOUSE_L)
#define TO_GAM DF(GAME_L)

enum custom_keycodes {
  TRM_COPY = SAFE_RANGE,
  TRM_PSTE,
  UML_SEQ,
  V_US,
  V_UK,
};
