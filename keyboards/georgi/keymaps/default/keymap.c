#include QMK_KEYBOARD_H
#include "state.h"      // set_sticky
#include "mode.h"       // steno_mode,  USER_MACRO
#define IGNORE_SLOW_TRANS_TAP_INTERRUPT



/* Keyboard Layout
 * ,---------------------------------.    ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |    | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|    |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |    | ST4 | RR | RB | RG | RS | RZ |
 * `---------------------------------'    `------------------------------'
 *                   ,---------------,    .---------------.
 *                   | LNO | LA | LO |    | RE | RU | RNO |
 *                   `---------------'    `---------------'
 */



// Steno Layers.
//
// Each should be added three times in this section, plus in the main map
//
// Layers containing PWR are always available, even in Plover mode.
//
// Don't make two exclusive layers (PWR and LSD | LK) that OR to a third
// ( PWR | LSD | LK ); they will collide weirdly and confuse you.
#define FUNCT   ( LSD | LK | LP | LH )
#define MEDIA   ( LSD | LK | LW | LR )
#define MOUSE   ( PWR | LSD )
#define MOVE    ( LSD | LK)
#define NUM     ( PWR )
#define SYM     ( RZ )

// Order matters! In the event of a collision, stay on the earlier layer
const uint32_t steno_layers[] = {MOVE, MOUSE, MEDIA, FUNCT, RES2, SYM, NUM};

#define __x__ KC_NO
#define TRANSPARENT(chord, act) \
    KEY(chord, act) \
    KEY(FUNCT | chord, act) \
    KEY(MEDIA | chord, act) \
    KEY(MOUSE | chord, act) \
    KEY(MOVE | chord, act) \
    KEY(NUM | chord, act) \
    KEY(SYM | chord, act) \
    KEY(RES2 | chord, act)


// QMK Layers
#define STENO_LAYER   0
#define GAMING        1
#define GAMING_2      2

// Primary (non-qmk) layout
//
// This takes many of the basic QMK keycodes, but for anything more complex,
// see user_macros below.
//
// RIGHT_HAND, LEFT_HAND, and LETTER_KEYS are helper macros that cover the five internal
// columns (i.e. no thumb keys, and not the ones a pinky would stretch to)
//
// These are not QMK layers. KC_TRANS probably does not act how you would expect.
//
// Overrides go AT THE END of this keymap.
const mapping_t keymap[] PROGMEM = {

    // Thumb Chords and modifiers
    //
    TRANSPARENT( LNO | RNO | LA | RU,  LCTL(KC_LSFT))
    TRANSPARENT( LNO | LA | LO,        LSFT(KC_ESC))
    KEY( LA | LO | RE | RU,            LSFT(KC_ENT))

    TRANSPARENT( LA | LO,    KC_ESC)
    TRANSPARENT( LNO,        KC_LALT)
    TRANSPARENT( LA,         KC_ENT)
    TRANSPARENT( LO,         KC_LSFT)

    TRANSPARENT( RNO,        KC_RALT)
    TRANSPARENT( RE | RU,    KC_TAB)
    TRANSPARENT( RE,         KC_SPC)
    TRANSPARENT( RU,         KC_LGUI)

    TRANSPARENT( RD,         KC_LCTL)
    TRANSPARENT( PWR,        KC_BSPC)
    SLOW_KEY( PWR,           KC_BSPC)
    SLOW_KEY( RZ,            KC_DEL)
    KEY( PWR | RZ,           KC_BSPC)


/* Function layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     | NCTFUNCTF |     |    | xxx | F1  | F2  | F3  | F4  |     |
 * |     +     +     +     +     +     |    |     + F5  + F6  + F7  + F8  +     |
 * |     | FUNCTFUNC |     |     |     |    | xxx | F9  | F10 | F11 | F12 |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    RIGHT_HAND( FUNCT,
        __x__, KC_F1, KC_F2,  KC_F3,  KC_F4,
        __x__, KC_F5, KC_F6,  KC_F7,  KC_F8,
        __x__, KC_F9, KC_F10, KC_F11, KC_F12)


/* Movement layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     |     |     |     |    | xxx | <-  |  ↓  |  ↑  | ->  |     |
 * |     +     +     +     +     +     |    |     +     +     +     +     +     |
 * |     | MOVEMOVEM |     |     |     |    | xxx | Hm  | PgD | PgU | End |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    RIGHT_HAND( MOVE,
        __x__, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
        __x__, __x__,   __x__,   __x__,   __x__,
        __x__, KC_HOME, KC_PGDN, KC_PGUP, KC_END)

/* Mouse layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     |     |     |     |    | mb2 | w↓  | m↑  | w↑  | acc0|     |
 * |     +     +     +     +     +     |    | mb3 +     +     +     + acc1+     |
 * | MOUSEMOUS |     |     |     |     |    | mb1 | m<- | m↓  | PgU | acc2|     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    RIGHT_HAND( MOUSE,
        KC_MS_BTN2, KC_MS_WH_DOWN, KC_MS_UP,   KC_MS_WH_UP, KC_MS_ACCEL0,
        KC_MS_BTN3, __x__,         __x__,      __x__,       KC_MS_ACCEL1,
        KC_MS_BTN1, KC_MS_LEFT,    KC_MS_DOWN, KC_MS_RIGHT, KC_MS_ACCEL2)

    KEY( MOUSE | LO, KC_MS_BTN1 )
    KEY( MOUSE | LA, KC_MS_BTN2 )
    KEY( MOUSE | LA | LO, KC_MS_BTN3 )

/* Media Layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     |     |     |     |    | VolU|Prev |Play | PLY |Next |     |
 * |     +     +     +     +     +     |    | Mute+     +     +     +     +     |
 * |     | MEDIAMEDIAMEDIAMEDIAM |     |    | VolD| xxX | xxx | xxx | xxx |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    RIGHT_HAND( MEDIA,
        KC_VOLU, KC_MPRV, KC_MPLY, KC_MPLY, KC_MNXT,
        KC_MUTE, __x__,   __x__,   __x__,   __x__,
        KC_VOLD, __x__,   __x__,   __x__,   __x__)


/* Numbers
 * ,-----------------------------------,    ,-----------------------------------,
 * |     | xxx |  a  |  b  |  c  | xxx |    |  :  |  1  |  2  |  3  |  .  |     |
 * |     +     +     +     +     +     |    |  0  +  4  +  5  +  6  +  -  +     |
 * | NUM | xxx |  d  |  e  |  f  | xxx |    |     |  7  |  8  |  9  |  0  |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    LETTER_KEYS( NUM,
        __x__, KC_A,  KC_B,  KC_C,  __x__,     KC_COLON, KC_1, KC_2, KC_3, KC_DOT,
        __x__, __x__, __x__, __x__, __x__,     KC_0,     KC_4, KC_5, KC_6, KC_MINUS,
        __x__, KC_D,  KC_E,  KC_F,  __x__,     __x__,    KC_7, KC_8, KC_9, KC_0)


/* Symbols
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |  `  |  [  |  {  |  (  |  <  |    |  >  |  )  |  }  |  ]  |  ?  |     |
 * |     +  ~  +  -  +  '  +  :  +  _  |    |  \  +  =  +  "  +  +  +  ?  +     |
 * |     |  !  |  @  |  #  |  $  |  %  |    |  |  |  ^  |  &  |  *  |  ?  | SYM |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
    LETTER_KEYS( SYM,
        KC_GRV,  KC_LBRC, KC_LCBR,  KC_LPRN,  KC_LABK,    KC_RABK,   KC_RPRN,  KC_RCBR, KC_RBRC, KC_QUES,
        KC_TILD, KC_MINS, KC_QUOTE, KC_COLON, KC_UNDS,    KC_BSLASH, KC_EQUAL, KC_DQUO, KC_PLUS, KC_QUES,
        KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,    KC_PIPE,   KC_CIRC,  KC_AMPR, KC_ASTR, KC_QUES)


/* Letters
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |  Q  |  W  |  E  |  R  |  T  |    |  Y  |  U  |  I  |  O  |  L  | ctl |
 * +-----+- A -+- S -+- D -+- F -+- G -|    |- H -+- J -+- K -+- L -+- ' -+-----|
 * | bsp |  Z  |  X  |  C  |  V  |  B  |    |  N  |  M  |  ,  |  .  |  /  | del |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
 *                   ,-----------------,    .-----------------.
 *                   | alt |enter|shift|    | spc | gui |altGr|
 *                   `-----------------'    `-----------------'
*/
    LETTER_KEYS( 0,
        KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,     KC_H, KC_J, KC_K,    KC_L,   KC_QUOTE,
        KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH)

    // Overrides
    //
    SLOW_KEY(LSD,   KC_Z)
    SLOW_KEY(PWR | LSD, __x__)
    KEY( PWR | LO,  LSFT(KC_BSPC))
    KEY( PWR | RD,  LCTL(KC_BSPC))


    // FAKE STENO
    //
    KEY( RES2 | LSU,    KC_Q)
    KEY( RES2 | LSD,    KC_A)
    KEY( RES2 | LFT,    KC_W)
    KEY( RES2 | LP,     KC_E)
    KEY( RES2 | LH,     KC_R)
    KEY( RES2 | LK,     KC_S)
    KEY( RES2 | LW,     KC_D)
    KEY( RES2 | LR,     KC_F)
    KEY( RES2 | ST1,    KC_T)
    KEY( RES2 | ST2,    KC_G)
    KEY( RES2 | LA,     KC_C)
    KEY( RES2 | LO,     KC_V)
    KEY( RES2 | RE,     KC_N)
    KEY( RES2 | RU,     KC_M)
    KEY( RES2 | ST3,    KC_Y)
    KEY( RES2 | ST4,    KC_H)
    KEY( RES2 | RF,     KC_U)
    KEY( RES2 | RP,     KC_I)
    KEY( RES2 | RL,     KC_O)
    KEY( RES2 | RT,     KC_P)
    KEY( RES2 | RD,     KC_LBRC)
    KEY( RES2 | RR,     KC_J)
    KEY( RES2 | RB,     KC_K)
    KEY( RES2 | RG,     KC_L)
    KEY( RES2 | RS,     KC_SCLN)
    KEY( RES2 | RZ,     KC_COMM)
    KEY( RES2 | LNO,    KC_1)
    KEY( RES2 | RNO,    KC_1)

};



// chordUp macros!
//
// Stick with USER_MACRO and chords with FN (which essentially overrides Plover momentaries)
// and RES1/RES2 unless you like getting your hands dirty.
bool user_macros(uint32_t chord) {

    // Key combos to notify the OS of mode change
    uint16_t notify_qwerty = 0; //LGUI(LCTL(LSFT(KC_Q)));
    uint16_t notify_plover = 0; //LGUI(LCTL(LSFT(KC_S)));

    // Lone FN press:
    // send notify_****, then proceed as normal (i.e. switch modes)
    if (chord == FN) {
        if (steno_mode)
            register_code16(notify_qwerty);
        else
            register_code16(notify_plover);
        clear_keyboard();
        return true;
    }


    // Sticky bits and QMK layers
    //
    USER_MACRO( FN | RES1,
        register_code16(notify_qwerty);
        STICKY_BITS = 0;
    )

    USER_MACRO( FN | RES2,
        register_code16(notify_qwerty);
        STICKY_BITS = 0;
    )

    // qmk layer switch
    USER_MACRO( FN | PWR | ST3 | ST4,
        layer_on(GAMING);
    )

    // sample text expansion mode
    USER_MACRO( FN | ST1,
        STICKY_BITS = RES1;
    )

    // fake steno mode: use plover through NKRO interface
    USER_MACRO( FN | PWR | ST1 | ST2,
        STICKY_BITS = RES2;
    )


    // Misc
    //
    USER_MACRO( RES1 | RR,
        SEND_STRING("username@email.com");
    )

    USER_MACRO( FN | LSU | LFT | LP,
        SEND_RAM_STRING("keymap length: %d", keymap_length);
    )

    /* Version
     * ,-----------------------------------,    ,-----------------------------------,
     * |#####|     |     |     |     |     |    |     |     |     |     |###########|
     * +-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+###########|
     * |     |     |     |     |     |     |    |     |     |     |     |###########|
     * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
     *                     ,---------------,    .---------------.
     *                     |     |    |    |    |    |    |     |
     *                     `---------------'    `---------------'
    */
    USER_MACRO( (FN | RT | RS | RD | RZ),
        SEND_STRING(VERSION " " __DATE__);
    )

    return false;
}



// QMK interface
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer, everything goes through here
    [STENO_LAYER] = LAYOUT_georgi(
        STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,       STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        STN_PWR, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,       STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
                                    STN_N1, STN_A,   STN_O,         STN_E,   STN_U,   STN_N7
    ),

    // Gaming layer with Numpad, Very limited
    [GAMING] = LAYOUT_georgi(
        KC_LSFT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DQUO,
                                   KC_LALT, KC_SPC,  LT(GAMING_2, KC_ENT),       KC_DEL,  KC_ASTR, TO(STENO_LAYER)
    ),

    [GAMING_2] = LAYOUT_georgi(
        KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT,
                                   KC_LALT, KC_SPC,  KC_ENT,        KC_DEL,  KC_ASTR, TO(STENO_LAYER)
    )
};



// Don't fuck with this, thanks.
const size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
const size_t n_steno_layers = sizeof(steno_layers)/sizeof(steno_layers[0]);
const size_t keymap_length  = sizeof(keymap)/sizeof(keymap[0]);
