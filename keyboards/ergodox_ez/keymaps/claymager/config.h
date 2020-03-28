/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 12

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 5

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 5

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_kc(                                                       \
    L00,L01,L02,L03,L04,L05,L06,           R00,R01,R02,R03,R04,R05,R06,  \
    L10,L11,L12,L13,L14,L15,L16,           R10,R11,R12,R13,R14,R15,R16,  \
    L20,L21,L22,L23,L24,L25,                   R21,R22,R23,R24,R25,R26,  \
    L30,L31,L32,L33,L34,L35,L36,           R30,R31,R32,R33,R34,R35,R36,  \
    L40,L41,L42,L43,L44,                           R42,R43,R44,R45,R46,  \
                            L55,L56,   R50,R51,                          \
                                L54,   R52,                              \
                        L53,L52,L51,   R55,R54,R53 )                     \
   LAYOUT_ergodox_pretty(                                           \
    KC_##L00,KC_##L01,KC_##L02,KC_##L03,KC_##L04,KC_##L05,KC_##L06,       KC_##R00,KC_##R01,KC_##R02,KC_##R03,KC_##R04,KC_##R05,KC_##R06,  \
    KC_##L10,KC_##L11,KC_##L12,KC_##L13,KC_##L14,KC_##L15,KC_##L16,       KC_##R10,KC_##R11,KC_##R12,KC_##R13,KC_##R14,KC_##R15,KC_##R16,  \
    KC_##L20,KC_##L21,KC_##L22,KC_##L23,KC_##L24,KC_##L25,                         KC_##R21,KC_##R22,KC_##R23,KC_##R24,KC_##R25,KC_##R26,  \
    KC_##L30,KC_##L31,KC_##L32,KC_##L33,KC_##L34,KC_##L35,KC_##L36,       KC_##R30,KC_##R31,KC_##R32,KC_##R33,KC_##R34,KC_##R35,KC_##R36,  \
    KC_##L40,KC_##L41,KC_##L42,KC_##L43,KC_##L44,                                           KC_##R42,KC_##R43,KC_##R44,KC_##R45,KC_##R46,  \
                            KC_##L55,KC_##L56,                      KC_##R50,KC_##R51,                     \
                                     KC_##L54,                      KC_##R52,                              \
                   KC_##L53,KC_##L52,KC_##L51,                      KC_##R55,KC_##R54,KC_##R53 )
