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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 0
#define NUMB 1
#define SYMB 2
#define META 3
#define NAV  4

enum combos {
    L_TH, R_TH, QWFP
};

const uint16_t PROGMEM esc_combo[] = {KC_ENT, KC_LSFT, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_SPC, KC_LGUI, COMBO_END};
const uint16_t PROGMEM qwfp_combo[] = {KC_Q, KC_W, KC_F, KC_P, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [L_TH] = COMBO(esc_combo, KC_ESC),
    [R_TH] = COMBO(tab_combo, KC_TAB),
    [QWFP] = COMBO(qwfp_combo, RESET)
};

/* enum custom_keycodes { */
/*   QWERTY = SAFE_RANGE, */
/* }; */

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_RESET   RESET
#define KC_SYMB OSL(SYMB)
#define KC_NUMB OSL(NUMB)
#define KC_META OSL(META)
#define KC_NAV_Z LT(NAV, KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
       META,     Q,     W,     F,     P,     B,                      J,     L,     U,     Y,  SCLN,  RCTL,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       NUMB,     A,     R,     S,     T,     G,                      M,     N,     E,     I,     O,  SYMB,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       BSPC, NAV_Z,     X,     C,     D,     V,                      K,     H,  COMM,   DOT,  SLSH,   DEL,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    LALT,  ENT, LSFT,     SPC, LGUI, RALT
                              //`--------------------'  `--------------------'
  ),

  [NUMB] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____,     A,     B,     C, _____,                   COLN,     1,     2,     3,   DOT, _____,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____,     D,     E,     F, _____,                      0,     4,     5,     6, MINUS, _____,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____,     7,     8,     9,  SLSH, _____,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),

  [SYMB] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, GRAVE,  LBRC,  LCBR,  LPRN,  LABK,                   RABK,  RPRN,  RCBR,  RBRC,  SCLN, _____,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  TILD, MINUS, QUOTE,  COLN,  UNDS,                 BSLASH, EQUAL,  DQUO,  PLUS,  SCLN, _____,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  EXLM,    AT,  HASH,   DLR,  PERC,                   PIPE,  CIRC,  AMPR,  ASTR,  QUES, _____,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),


  [META] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, XXXXX,   F10,   F11,   F12, XXXXX,                  XXXXX,    F1,    F2,    F3, XXXXX, RESET,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX,   F13,   F14,   F15, XXXXX,                    F10,    F4,    F5,    F6, XXXXX, _____,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX,   F16,   F17,   F18, XXXXX,                  XXXXX,    F7,    F8,    F9, XXXXX, _____,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),

  [NAV] = LAYOUT_kc(
  //,-----------------------------------------.                             ,-----------------------------------------.
     XXXXX,      XXXXX, MS_WH_DOWN,   MS_UP, MS_WH_UP,       XXXXX,           XXXXX, PGDOWN,   UP,  PGUP, XXXXX, XXXXX,
  //|------+------+------+------+------+------|                             |------+------+------+------+------+------|
     XXXXX, MS_WH_LEFT,    MS_LEFT, MS_DOWN, MS_RIGHT, MS_WH_RIGHT,            HOME,  LEFT,  DOWN, RIGHT,   END, XXXXX,
  //|------+------+------+------+------+------|                             |------+------+------+------+------+------|
     XXXXX,      _____,    MS_BTN2, MS_BTN3,  MS_BTN1,       XXXXX,           XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,
  //|------+------+------+------+------+------+------|                  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      _____, _____, _____
                              //`--------------------'    `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    /* matrix_write_ln(matrix, read_keylogs()); */
    /* matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui)); */
    //matrix_write_ln(matrix, read_host_led_state());
    matrix_write_ln(matrix, read_timelog());
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
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    set_timelog();
  }

  return true;
}
