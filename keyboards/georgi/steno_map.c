#include "steno_map.h"

const mapping_t empty_map = { 0, UINT16_MAX, 0 };


mapping_t read_map_P(uint32_t index) {
    mapping_t map = empty_map;
    if (index < keymap_length)
        memcpy_P(&map, &keymap[index], sizeof(mapping_t));
    return map;
}


bool has_perfect_match(uint32_t chord) {
    mapping_t tmp_map;

    for (uint16_t i=0; i < keymap_length; i++) {
        tmp_map = read_map_P(i);
        if (tmp_map.chord == chord) return true;
    }
    return false;
}


map_results_t matching_chords(uint32_t chord) {
    map_results_t out = {empty_map, 0};
    mapping_t tmp_map = empty_map;

    for (uint16_t i=0; i < keymap_length; i++) {
        tmp_map = read_map_P(i);

        if ((tmp_map.chord & chord) == chord) {
            out.count++;
            if (tmp_map.chord == chord)
                out.map = tmp_map;
        }
    }
    return out;
}

