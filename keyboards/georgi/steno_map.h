#ifndef STENO_MAP_H
#define STENO_MAP_H

#include QMK_KEYBOARD_H
#include "keycodes.h"


// Data
//
typedef struct {
    uint32_t chord;
    uint16_t delay;
    uint16_t key;
} mapping_t;

typedef struct map_results {
    mapping_t map;
    uint16_t  count;
} map_results_t;

extern const mapping_t  empty_map;
extern const mapping_t  keymap[];
extern const size_t     keymap_length;

extern const size_t     n_steno_layers;
extern const uint32_t   steno_layers[];


// Functions
//
bool            has_perfect_match(uint32_t chord);
map_results_t   matching_chords(uint32_t chord);


// Keymap helpers
//
#define NEW_ENTRY(chord, delay, keys) \
    {chord, delay, keys},

#define KEY(chord, keys)      NEW_ENTRY(chord, 25, keys)
#define SLOW_KEY(chord, keys) NEW_ENTRY(chord, 500, keys)

#define SEND_RAM_STRING(base, ...) \
    SRS_HELPER( CONCAT_W(tmp_str, __COUNTER__), base, __VA_ARGS__)

#define SRS_HELPER(unique_name, base, ...) \
    char unique_name[64]; \
    sprintf(unique_name, base, __VA_ARGS__); \
    send_string(unique_name)

#define CONCAT_W(a, b) CONCAT(a, b) // force args to be redefined

#define LEFT_HAND(layer, \
        lq, lw, le, lr, lt, \
        la, ls, ld, lf, lg, \
        lz, lx, lc, lv, lb) \
KEY(layer | LSU, lq) \
KEY(layer | LFT, lw) \
KEY(layer | LP, le) \
KEY(layer | LH, lr) \
KEY(layer | ST1, lt) \
KEY(layer | LSU | LSD, la) \
KEY(layer | LFT | LK, ls) \
KEY(layer | LP | LW, ld) \
KEY(layer | LH | LR, lf) \
KEY(layer | ST1 | ST2, lg) \
KEY(layer | LSD, lz) \
KEY(layer | LK, lx) \
KEY(layer | LW, lc) \
KEY(layer | LR, lv) \
KEY(layer | ST2, lb)

#define RIGHT_HAND(layer, \
        ry, ru, ri, ro, rp, \
        rh, rj, rk, rl, rL, \
        rn, rm, rC, rP, rS) \
KEY(layer | ST3, ry) \
KEY(layer | RF, ru) \
KEY(layer | RP, ri) \
KEY(layer | RL, ro) \
KEY(layer | RT, rp) \
KEY(layer | ST3 | ST4, rh) \
KEY(layer | RF | RR, rj) \
KEY(layer | RP | RB, rk) \
KEY(layer | RL | RG, rl) \
KEY(layer | RT | RS, rL) \
KEY(layer | ST4, rn) \
KEY(layer | RR, rm) \
KEY(layer | RB, rC) \
KEY(layer | RG, rP) \
KEY(layer | RS, rS)

#define LETTER_KEYS(layer, \
        lq, lw, le, lr, lt,   ry, ru, ri, ro, rp, \
        la, ls, ld, lf, lg,   rh, rj, rk, rl, rL, \
        lz, lx, lc, lv, lb,   rn, rm, rC, rP, rS) \
    LEFT_HAND(layer, \
        lq, lw, le, lr, lt, \
        la, ls, ld, lf, lg, \
        lz, lx, lc, lv, lb) \
    RIGHT_HAND(layer, \
        ry, ru, ri, ro, rp, \
        rh, rj, rk, rl, rL, \
        rn, rm, rC, rP, rS)

#endif /* STENO_MAP_H */
