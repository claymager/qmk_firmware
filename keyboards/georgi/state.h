#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include "steno_map.h"


// Data
//
struct best_guess {
    mapping_t map;
    uint16_t  time;
} best_map;

uint32_t    layer_mask;
uint32_t    *sticky_bits;

#define STICKY_BITS *sticky_bits


// Functions
//
void        redo_history(void);
void        reset_history(void);
void        forget_keys(uint32_t oldChord);

void        process_qwerty_release(uint32_t keycode);
void        process_qwerty_press(uint32_t keycode);
void        send_all_chords(void);
void        set_best_map(mapping_t);

void        log_chord_history(void);


#endif /* STATE_H */
