#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;
extern uint8_t is_master;

enum Layers {
    BASE = 0,
    NUMB,
    SYMB,
    META,
    NAV,
    SYMB2,
    _MACRO,
    NONE,
    // leave this here
    N_LAYERS
};

const char *layer_strings[N_LAYERS] = {
    "Default",
    "Numbers",
    "Symbols",
    "Meta",
    "Navigation",
    "Complex Symbols",
    "Macros",
    "None" };

enum tap_dance {
    TD_META = 0,
    TD_SYMB,
    TD_NUMB
};

/* void mo_toggle_layer(qk_tap_dance_state_t *state, uint8_t layer); */

void meta_finished (qk_tap_dance_state_t *state, void *user_data);
void meta_reset (qk_tap_dance_state_t *state, void *user_data);

void symb_finished (qk_tap_dance_state_t *state, void *user_data);
void numb_finished (qk_tap_dance_state_t *state, void *user_data);
void osl_2_reset(qk_tap_dance_state_t *state, void *user_data);
/* const uint16_t PROGMEM tab_combo[] = {KC_SPC, KC_LGUI, COMBO_END}; */

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_META] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, meta_finished, meta_reset),
    [TD_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, symb_finished, osl_2_reset),
    [TD_NUMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numb_finished, osl_2_reset)
};


enum custom_keycodes {
  SB_BIND = SAFE_RANGE,
};

#define _____ KC_TRNS
#define XXXXX KC_NO
#define SFT_ESC MT(MOD_LSFT, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    TD(TD_META),  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSL(NUMB),    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, TD(TD_SYMB),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_BSPC, LT(NAV,KC_Z),  KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LALT,    KC_ENT, SFT_ESC,     KC_SPC, MT(MOD_LGUI, KC_TAB), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [NUMB] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   _____,    KC_A,    KC_B,    KC_C,   _____,                      KC_COLN,    KC_1,    KC_2,    KC_3,  KC_DOT,   _____,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _____,   _____,    KC_D,    KC_E,    KC_F,   _____,                         KC_0,    KC_4,    KC_5,    KC_6,KC_MINUS,   _____,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _____,   _____,   _____,   _____,   _____,   _____,                        _____,    KC_7,    KC_8,    KC_9, KC_SLSH,   _____,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,      _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),

  [SYMB] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,KC_GRAVE, KC_LBRC, KC_LCBR, KC_LPRN, KC_LABK,                      KC_RABK, KC_RPRN, KC_RCBR, KC_RBRC, KC_SCLN,   _____,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _____, KC_TILD,KC_MINUS,KC_QUOTE, KC_COLN, KC_UNDS,                    KC_BSLASH,KC_EQUAL, KC_DQUO, KC_PLUS, KC_SCLN,   _____,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _____, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_PIPE, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES,   _____,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,      _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),


  [META] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   XXXXX,  KC_F10,  KC_F11,  KC_F12,   RESET,                        XXXXX,   KC_F1,   KC_F2,   KC_F3,   XXXXX,   _____,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TO(NUMB),   XXXXX,  KC_F13,  KC_F14,  KC_F15,   XXXXX,                       KC_F10,   KC_F4,   KC_F5,   KC_F6,   XXXXX, TO(SYMB),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(NAV), TO(NAV),  KC_F16,  KC_F17,  KC_F18,   XXXXX,                        XXXXX,   KC_F7,   KC_F8,   KC_F9,   XXXXX,   _____,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _____,   _____, LSFT(KC_ESC),    _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   XXXXX, KC_WH_D, KC_MS_U, KC_WH_U,   XXXXX,                        XXXXX, KC_PGDN,   KC_UP, KC_PGUP,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   _____, KC_BTN2, KC_BTN3, KC_BTN1,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,        _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),

  [SYMB2] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        SB_BIND,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,        _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),
  [_MACRO] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,        _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  ),

  [NONE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _____,   _____,   _____,        _____,   _____,   _____
                                      //`--------------------------'  `--------------------------'
  )
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}



//Functions that control what our tap dance key does
void meta_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
      case 1:
          /* mo_toggle_layer(state, META); */
          set_oneshot_layer(META, ONESHOT_START);
          break;
      case 2:
          layer_clear();
          break;
      case 3:
          set_oneshot_layer(_MACRO, ONESHOT_START);
          break;
      case 4:
          layer_invert(NONE);
  }
}

void meta_reset(qk_tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (state->count <= 3) {
      clear_oneshot_layer_state(ONESHOT_PRESSED);
  };
}

//Functions that control what our tap dance key does
void symb_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
      case 1:
          set_oneshot_layer(SYMB, ONESHOT_START);
          break;
      case 2:
          set_oneshot_layer(SYMB2, ONESHOT_START);
          break;
  }
}

void osl_2_reset(qk_tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (state->count <= 2) {
      clear_oneshot_layer_state(ONESHOT_PRESSED);
  };
}

void numb_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
      case 1:
          /* mo_toggle_layer(state, META); */
          set_oneshot_layer(NUMB, ONESHOT_START);
          break;
      case 2:
          set_oneshot_mods(MOD_LSFT | MOD_LALT | MOD_LCTL);
          set_oneshot_layer(NUMB, ONESHOT_START);
          break;
  }
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
/* const char *read_layer_state(void); */
const char *read_layer_state(void) {
  static char layer_state_str[24];
  char layer_name[17];
  uint8_t max_layer = biton32(layer_state);
  if (max_layer < N_LAYERS) {
      strcpy(layer_name, layer_strings[max_layer]);
  } else {
      snprintf(layer_name, sizeof(layer_name), "Undef-%ld", layer_state);
  };

  strcpy(layer_state_str, "Layer: ");

  strcat(layer_state_str, layer_name);
  strcat(layer_state_str, "");
  return layer_state_str;
}

const char *read_logo(void);
/* void set_keylog(uint16_t keycode, keyrecord_t *record); */
/* const char *read_keylog(void); */
/* const char *read_keylogs(void); */

/* const char *read_mode_icon(bool swap); */
// const char *read_host_led_state(void);
/* void set_timelog(void); */
/* const char *read_timelog(void); */

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    /* matrix_write_ln(matrix, read_keylog()); */
    /* matrix_write_ln(matrix, read_keylogs()); */
    /* matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui)); */
    //matrix_write_ln(matrix, read_host_led_state());
    /* matrix_write_ln(matrix, read_timelog()); */
  } else {
    matrix_write(matrix, read_logo());
  }
}


void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
      switch (keycode) {
          case SB_BIND:
              SEND_STRING(">>=");
              break;
      }
#ifdef SSD1306OLED
    /* set_keylog(keycode, record); */
#endif
    /* set_timelog(); */
  }


  return true;
}
