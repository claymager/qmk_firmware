#include "keycodes.h"
#include "logging.h"
#include "steno_map.h"
#include "mode.h"
#include "stenoqwerty_io.h"
#include "state.h"


uint32_t  macro_chord       = 0;   // current chord


// Called only once, while booting up
//
void keyboard_pre_init_kb(void) {
    *sticky_bits = 0;
    reset_history();
}


// On every event_t with a steno keycode
//
bool process_steno_user(uint16_t keycode, keyrecord_t *record) {
    uint32_t new_key = read_keycode(keycode);

    // Process key release
    if (!record->event.pressed) {
        verbose_log("\nr: %s  code: %lo", debug_key, new_key);

        // Leave momentary Qwerty mode
        if (new_key == FN && steno_mode)
            send_all_chords();

        if (as_qwerty_mode(macro_chord)) process_qwerty_release(new_key);
        return true;
    }


    verbose_log("\np: %s  code: %lo", debug_key, new_key);

    // Process key press
    macro_chord |= new_key;
    if (new_key == FN) {
        if ((!steno_mode))
            send_all_chords();
        reset_history();
    }
    else if (as_qwerty_mode(macro_chord)) {
        process_qwerty_press(new_key);
    }

    // Returning True -> continue with default.
    //  -> Log key with steno engine
    //  -> call send_steno_chord[_user] on chordUp
    return true;
}


// This is called when last key is released (aka chordUp)
//
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {

    bool send_to_plover = kb_macros(macro_chord);

    if (n_sent != 0) {
        error("n_sent improperly cleared");
        n_sent = 0;
    }
    verbose_log("\n----   CHORDUP   ----");

    // Reset things
    clear_keyboard();
    macro_chord = *sticky_bits;
    layer_mask = 0;
    reset_history();

    return send_to_plover;
}


// Called many, many times a second
//
void matrix_scan_user(void) {
    if (!as_qwerty_mode(macro_chord)) return;
    if (timer_elapsed(best_map.time) > best_map.map.delay) {
        if ((layer_mask == best_map.map.chord) || (best_map.map.chord == empty_map.chord)) {
            set_best_map(empty_map);
            return;
        }
        register_map(best_map.map);
    }
}
