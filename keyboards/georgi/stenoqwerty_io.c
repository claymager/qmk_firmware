#include "stenoqwerty_io.h"
#include "steno_map.h"
#include "mousekey.h"
#include "logging.h"
#include "state.h"


mapping_t sent[32] = {{0, 0, 0}}; // keys the computer thinks are pressed
uint8_t   n_sent           = 0;   // Number of mapping_t currently registered



void register_map(mapping_t map) {
    // This chord acted as a layer
    if (layer_mask == map.chord) {
        warn("tried to send layer chord!");
        return;
    }

    // fail gracefully
    if (n_sent >= 32) {
        error("n_sent overflow");
        return;
    }

    verbose_log("REGISTER: %lo", map.chord);

    // Log the mapping for later release
    memcpy(&sent[n_sent], &map, sizeof(mapping_t));
    n_sent++;

#ifdef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY(map.key)) {
        mousekey_on(map.key);
        mousekey_send();
    } else
#endif
    register_code16(map.key);

    // Reset buffers
    set_best_map(empty_map);

    // Remember if we are on a layer
    for (uint8_t i=0; i < n_steno_layers; i++)
        if ((steno_layers[i] & map.chord) == steno_layers[i] &&
            !(layer_mask && (layer_mask ^ steno_layers[i]) == map.chord))
            layer_mask |= steno_layers[i];

    // Handle dual-function layer chords
    if (layer_mask == map.chord)
        layer_mask = 0;
    forget_keys(map.chord & ~layer_mask);

}


void unregister_by_index(uint8_t idx) {
#ifdef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY(sent[idx].key)) {
        mousekey_off(sent[idx].key);
        mousekey_send();
    } else
#endif
    unregister_code16(sent[idx].key);

    verbose_log("UNREGISTER: %lo", sent[idx].chord);

    for ( uint8_t i=idx; i < n_sent && sent[i].chord != 0; i++) {
        sent[i] = sent[i+1];
    }
    n_sent--;
}
