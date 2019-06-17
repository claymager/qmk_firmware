#ifndef STENOQWERTY_IO_H
#define STENOQWERTY_IO_H

#include "steno_map.h"


// Data
//
mapping_t sent[32];
uint8_t   n_sent;


// Functions
//
void            register_by_chord(uint32_t chord);
void            register_map(mapping_t map);
void            unregister_by_index(uint8_t idx);



#endif /* STENOQWERTY_IO_H */
