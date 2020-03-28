#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0
#define NUMB 1
#define SYMB 2
#define META 3
#define NAV  4
#define STEN 5
#define EU4a 6
#define EU4b 7
#define ANKI 8

#define ____ KC_TRANSPARENT
#define _xx_ KC_NO
#define _LT_ KC_TRANSPARENT

#define KC_____ KC_TRANSPARENT
#define KC_TO(x) TO(x)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Colemak Mod-DH
 *
 * ,---------------------------------------------.           ,--------------------------------------------.
 * |TG(META) | F1  | F2  | F3  | F4  | F5  | F6  |           | F7  | F8  | F9  | F10 | F11 | F12 |TG(META)|
 * |---------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+--------|
 * |BkSp/LAlt|  Q  |  W  |  F  |  P  |  B  |     |           |     |  J  |  L  |  U  |  Y  |  ;  |  Del   |
 * |---------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+--------|
 * |osl NUM  |  A  |  R  |  S  |  T  |  G  |-----|           |-----|  M  |  N  |  E  |  I  |  O  |osl SYM |
 * |---------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+--------|
 * | BkSp/NUM|  Z  |  X  |  C  |  D  |  V  |     |           |     |  K  |  H  |  ,  |  .  |  /  | RCtrl  |
 * `---------+-----+-----+-----+-----+-----------'           `-----------+-----+-----+-----+-----+--------'
 *   |   <-  |  -> |     |L_Alt|Enter|                                   |Super|R_Alt|     |  ↓  |  ↑  |
 *   `-------------------------------'                                   `-----------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Prev | Next |       | Vol↑ | Mute |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Play |       | Vol↓ |        |      |
 *                                 |LShift|  Esc |------|       |------|  Tab/  |Space |
 *                                 |      |      | Ctrl |       | Ctrl | LT NAV |      |
 *                                 `--------------------'       `----------------------'
 */
  [BASE] = LAYOUT_ergodox(
      // left hand
      TG(META),           KC_F1,         KC_F2,  KC_F3,    KC_F4,     KC_F5,  KC_F6,
      LALT_T(KC_BSPACE),  KC_Q,          KC_W,   KC_F,     KC_P,      KC_B,   TO(BASE),
      OSL(NUMB),          KC_A,          KC_R,   KC_S,     KC_T,      KC_G,
      LT(NUMB,KC_BSPACE),  LT(NAV,KC_Z),  KC_X,   KC_C,     KC_D,      KC_V,   ____,
      KC_LEFT,            KC_RIGHT,      ____,   KC_LALT,  KC_ENTER,
      KC_MEDIA_PREV_TRACK,  KC_MEDIA_NEXT_TRACK,
      KC_MEDIA_PLAY_PAUSE,
      KC_LSHIFT,            KC_ESCAPE,            KC_LCTRL,

      // right hand
      KC_F7,  KC_F8,  KC_F9,  KC_F10,     KC_F11,  KC_F12,     TG(META),
      TO(BASE),   KC_J,   KC_L,   KC_U,       KC_Y,    KC_SCOLON,  KC_RCTL,
              KC_M,   KC_N,   KC_E,       KC_I,    KC_O,       OSL(SYMB),
      ____,   KC_K,   KC_H,   KC_COMMA,   KC_DOT,  KC_SLASH,   LT(SYMB,KC_DEL),
                      KC_LGUI,  KC_RALT,  ____,    KC_DOWN,    KC_UP,
      KC_AUDIO_VOL_UP,      KC_AUDIO_MUTE,
      KC_AUDIO_VOL_DOWN,
      KC_RCTRL,             LT(NAV,KC_TAB),         KC_SPACE
   ),

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
  [NUMB] = LAYOUT_kc(
     ____, ____, ____, ____, ____, ____, ____,            ____, ____, ____, ____, ____, ____, ____,
     ____, ____,    A,    B,    C, ____, ____,            ____, COLN,    1,    2,    3,  DOT, ____,
     ____, ____,    D,    E,    F, ____,                           0,    4,    5,    6,MINUS, ____,
     ____, ____, ____, ____, ____, ____, ____,            ____, ____,    7,    8,    9,SLASH, ____,
     ____, ____, ____, ____, ____,                                    ____, LPRN, RPRN, ____, ____,
                                       ____, ____,    ____, ____,
                                             ____,    ____,
                                 ____,TO(0), ____,    ____, ____, ____
  ),

       /* _____,   _____,   _____,   _____,   _____,   _____,   _____, */
      /* ____,  ____,  KC_A,  KC_B,  KC_C,  ____,  ____, */
      /* _LT_,  ____,  KC_D,  KC_E,  KC_F,  ____, */
      /* ____,  ____,  ____,  ____,  ____,  ____,  ____, */
      /* ____,  ____,  ____,  ____,  ____, */
      /* ____,  ____, */
      /* ____, */
      /* ____,  TO(BASE),  ____, */

      /* // right hand */
      /* ____,  ____,     ____,  ____,    ____,      ____,      ____, */
      /* ____,  KC_COLN,  KC_1,  KC_2,    KC_3,    KC_DOT,    ____, */
      /*        KC_0,     KC_4,  KC_5,    KC_6,    KC_MINUS,  ____, */
      /* ____,  ____,     KC_7,  KC_8,    KC_9,    KC_SLASH,  ____, */
      /*                  ____,  KC_LPRN, KC_RPRN,  ____,      ____, */
      /* ____,  ____, */
      /* ____, */
      /* ____,  ____,  ____ */
  /* ), */

  [SYMB] = LAYOUT_ergodox(
/* Keymap 2: Symbols
 *
 * ,----------------------------------------------.           ,--------------------------------------------.
 * |         |     |     |     |     |     |      |           |      |     |     |     |     |     |       |
 * |---------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+-------|
 * |         |  `  |  [  |  {  |  (  |  <  |  TO  |           |      |  >  |  )  |  }  |  ]  |  ;  |       |
 * |---------+-----+-----+-----+-----+-----| BASE |           |      |-----+-----+-----+-----+-----+-------|
 * |         |  ~  |  -  |  '  |  :  |  _  |------|           |------|  \  |  -  |  "  |  +  |  ;  | (osl) |
 * |---------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+-------|
 * |         |  !  |  @  |  #  |  $  |  %  |      |           |      |  |  |  ^  |  &  |  *  |  ?  |       |
 * `---------+-----+-----+-----+-----+------------'           `------------+-----+-----+-----+-----+-------'
 *   |       |     |     |     |     |                                     |     |     |     |     |     |
 *   `-------------------------------'                                     `-----------------------------'
                                         ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |  TO  |      |       |      |        |      |
 *                                 |      | BASE |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
      // left hand
      ____,  ____,      ____,         ____,      ____,     ____,     ____,
      ____,  KC_GRAVE,  KC_LBRACKET,  KC_LCBR,   KC_LPRN,  KC_LABK,  ____,
      ____,  KC_TILD,   KC_MINUS,     KC_QUOTE,  KC_COLN,  KC_UNDS,
      ____,  KC_EXLM,   KC_AT,        KC_HASH,   KC_DLR,   KC_PERC,  ____,
      ____,  ____,      ____,         ____,      ____,
      ____,  ____,
      ____,
      ____,  TO(BASE),  ____,

      // right hand
      ____,  ____,       ____,      ____,     ____,         ____,       ____,
      ____,  KC_RABK,    KC_RPRN,   KC_RCBR,  KC_RBRACKET,  KC_SCOLON,  ____,
             KC_BSLASH,  KC_EQUAL,  KC_DQUO,  KC_PLUS,      KC_SCOLON,  _LT_,
      ____,  KC_PIPE,    KC_CIRC,   KC_AMPR,  KC_ASTR,      KC_QUES,    ____,
                         ____,      ____,        ____,      ____,       ____,
      ____,  ____,
      ____,
      ____,  ____,  ____),



  [META] = LAYOUT_ergodox(
      // left hand
      _LT_,      ____,     ____,   ____,   ____,   ____,   ____,
      TO(STEN),  ____,     ____,   ____,   ____,   ____,  ____,
      TO(NUMB),  TO(ANKI), ____,   ____,   ____,   ____,
      ____,      ____,     ____,   ____,   ____,   ____,  ____,
      ____,      ____,     ____,   ____,   ____,
      ____,  ____,
      ____,
      ____,  ____,  ____,
      
      // right hand
      ____,    ____,  ____,      ____,  ____,  ____,  _LT_,
      ____,    ____,  ____,      ____,  ____,  ____,  ____,
               ____,  TO(EU4a),  ____,  ____,  ____,  ____,
      ____,    ____,  ____,      ____,  ____,  ____,  ____,
                      ____,      ____,  ____,  ____,  ____,
      ____,  ____,
      ____,
      ____,  ____,  ____),



  [NAV] = LAYOUT_ergodox(
      // left hand
      ____,  ____,           ____,           ____,        ____,         ____,            ____,
      ____,  _xx_,           KC_MS_WH_DOWN,  KC_MS_UP,    KC_MS_WH_UP,  _xx_,            ____,
      ____,  KC_MS_WH_LEFT,  KC_MS_LEFT,     KC_MS_DOWN,  KC_MS_RIGHT,  KC_MS_WH_RIGHT,
      ____,  _LT_,           KC_MS_BTN2,     KC_MS_BTN3,  KC_MS_BTN1,   _xx_,            ____,
      ____,  ____,           ____,           ____,        ____,
      ____,  ____,
      ____,
      ____,  TO(BASE),       ____,
      
      // right hand
      ____,  ____,     ____,       ____,     ____,      ____,    ____,
      ____,  _xx_,     KC_PGDOWN,  KC_UP,    KC_PGUP,   _xx_,    ____,
             KC_HOME,  KC_LEFT,    KC_DOWN,  KC_RIGHT,  KC_END,  ____,
      ____,  _xx_,     _xx_,       _xx_,     _xx_,      _xx_,    ____,
                       ____,       ____,     ____,      ____,    ____,
      ____,  ____,
      ____,
      ____,  _LT_,  ____),



  [STEN] = LAYOUT_ergodox(
      // left hand
      _xx_,  _xx_,  _xx_,  _xx_,  _xx_,  _xx_,  _xx_,
      _xx_,  _xx_,  _xx_,  _xx_,  _xx_,  _xx_,  ____,
      _xx_,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,
      _xx_,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  _xx_,
      _xx_,  _xx_,  _xx_,  _xx_,  KC_1,
      _xx_,  _xx_,
      _xx_,
      KC_C,  KC_V,  _xx_,
      
      // right hand
      _xx_,  _xx_,  _xx_,  _xx_,  _xx_,  _xx_,       _xx_,
      ____,  _xx_,  _xx_,  _xx_,  _xx_,  _xx_,       _xx_,
             KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,       KC_LBRACKET,
      _xx_,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCOLON,  KC_QUOTE,
                    KC_0,  _xx_,  _xx_,  _xx_,       _xx_,
      _xx_,  _xx_,
      _xx_,
      _xx_,  KC_N,  KC_M),



  [EU4a] = LAYOUT_ergodox(
      // left hand
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,
      ____,  ____,
      ____,
      ____,  ____,  ____,
      
      // right hand
      ____,      KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  ____,
      KC_PLUS,   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_ESCAPE,
                 KC_Z,  KC_X,  KC_C,  KC_H,  KC_N,  KC_SPACE,
      KC_MINUS,  KC_A,  KC_S,  KC_D,  KC_G,  LSFT(KC_K),  KC_ENTER,
                        KC_J,  KC_V,  ____,  ____,  KC_LCTRL,
      ____,  KC_LCTRL,
      KC_LSHIFT,
      KC_L,  LT(EU4b,KC_B),  LT(EU4b,KC_F1)),

  [EU4b] = LAYOUT_ergodox(
      // left hand
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,
      ____,  ____,
      ____,
      ____,  ____,  ____,
      
      // right hand
      ____,  ____,  KC_0,  KC_COMMA,  KC_DOT,  KC_QUOTE,  ____,
      ____,  ____,  KC_1,  KC_2,      KC_3,    ____,      ____,
             ____,  KC_4,  KC_5,      KC_6,    KC_LCTRL,  ____,
      ____,  ____,  KC_7,  KC_8,      KC_9,    ____,      ____,
                    ____,  KC_0,      ____,    ____,      KC_LCTRL,
      ____,  ____,
      ____,
      ____,  _LT_,  _LT_
  ),

  [ANKI] = LAYOUT_ergodox(
      // left hand
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  KC_4,  KC_3,  KC_2,  KC_1,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,
      ____,  ____,
      ____,
      ____,  ____,  ____,

      // right hand
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
             ____,  KC_1,  KC_2,  KC_3,  KC_4,  ____,
      ____,  ____,  ____,  ____,  ____,  ____,  ____,
      ____,  ____,  ____,  ____,  ____,
      ____,  ____,
      ____,
      ____,  ____,  ____
  ),

};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    };
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 4:
        ergodox_right_led_3_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
