#include "state.h"
#include "stenoqwerty_io.h"
#include "steno_map.h"
#include "logging.h"


// Data
//
uint16_t    buffer_time     = 0;    // timestamp when best_map chosen
uint32_t    chord_state[32] = {0};  // History of chord
uint32_t *sticky_bits = &chord_state[0];
uint8_t     first_empty_idx = 1;    // First empty slot in chord_state
uint8_t     history_idx     = 1;    // pointer in chord_state when redoing history
uint32_t    layer_mask     = 0;    // keys to treat as layers rather than staged keys

// Private
bool        valid_state     = true; // whether qwerty_mode thinks it can ever process the state




// Helper functions
//
uint8_t send_longest_chord(uint8_t maxIndex) {
    // Step back through history, sending the latest matching chord found
    // Returns number of states removed from history
    uint32_t      tempState = 0;
    map_results_t matching;


    for (int i=maxIndex; i > 0; i--) {
        tempState = chord_state[i];

        if (layer_mask == (tempState | layer_mask))
            break;

        matching = matching_chords(tempState);
        if (matching.map.chord != 0) {
            // it's valid! send the longest chord
            uint8_t tmp_idx = first_empty_idx;
            register_map(matching.map);
            return tmp_idx - first_empty_idx;
        }
    }

    valid_state = false;
    return 0;
}


void process_qwerty(uint8_t idx) {
    // Find all possible chords we may be building
    map_results_t match = matching_chords(chord_state[idx]);

    verbose_log("match count: %d", match.count);

    // Chord is broken, let's try to fix it
    while (match.count == 0 && idx > 1 && valid_state) {
        idx -= send_longest_chord(idx);
        if (idx > 1)
            match = matching_chords(chord_state[idx]);
    }

    // Found it
    if (match.count == 1 && (match.map.chord == chord_state[idx])) {
        register_map(match.map);
        return;
    }

    // Found something
    if(match.map.chord != 0) 
            set_best_map(match.map);

}


void log_chord_history(void) {
    for (int j=0; j < 31 && chord_state[j] != UINT32_MAX; j++) {
        verbose_log("%x:%12lo", j, chord_state[j]);
    }
    verbose_log("%x:", first_empty_idx);
}



// Public functions
//
void redo_history(void) {
    history_idx = 1;
    while (history_idx < first_empty_idx && layer_mask != chord_state[first_empty_idx-1]) {
        process_qwerty(history_idx); // may update either _idx
        history_idx++;
    }
}


void reset_history(void) {
    set_best_map(empty_map);
    valid_state = true;
    first_empty_idx = 1;
    for (int i = 1; i < 32; i++)
        chord_state[i] = UINT32_MAX;
}


void send_all_chords(void) {
    for (uint8_t i=1; i < first_empty_idx && valid_state; i++) {
        send_longest_chord(first_empty_idx-1);
    }
}


void forget_keys(uint32_t oldChord) {
    verbose_log("forget %lo", oldChord);

    // Remove keys from history
    for (int i = 1; i < first_empty_idx; i++) {
        chord_state[i] &= ~oldChord;
    }

    // collapse history to remove duplicate entries
    uint32_t prior;
    uint32_t stop = UINT32_MAX;
    chord_state[31] = stop; // Should be true anyway

    for (int i = 1; i < first_empty_idx; i++) {
        prior = chord_state[i-1];
        while ((chord_state[i] == prior) && (chord_state[i] != stop)) {
            for (int j = i; chord_state[j] != stop; j++)
                chord_state[j] = chord_state[j+1];
        }
        if (chord_state[i] == stop) first_empty_idx = i;
    }

    // history's changed! If we were stepping through, start over
    history_idx = 1;
}


void process_qwerty_release(uint32_t keycode) {

    bool wasLayerKey = layer_mask & keycode;

    if (wasLayerKey)
        layer_mask &= ~keycode;
    else if (best_map.map.chord & keycode)
        register_map(best_map.map);

    // unregister logic
    for (uint8_t i=0; i < n_sent; i++)
        if (sent[i].chord & keycode)
            unregister_by_index(i);

    if (keycode & chord_state[first_empty_idx-1]) {
        forget_keys(keycode);
        log_chord_history();
    }

    if (!wasLayerKey) redo_history();
}


void process_qwerty_press(uint32_t keycode) {

    chord_state[first_empty_idx] = chord_state[first_empty_idx-1] | keycode;
    first_empty_idx++;
    log_chord_history();

    if (first_empty_idx > 31) {
        error("chord_state overflow");
        reset_history();
    }

    process_qwerty(first_empty_idx-1);
}


void set_best_map(mapping_t new_map) {
    struct best_guess tmp = { new_map, timer_read() };
    best_map = tmp;
}
