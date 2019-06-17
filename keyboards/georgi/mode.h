#ifndef MODE_H
#define MODE_H

#include <stdbool.h>


// Data
//
bool    steno_mode;


// Functions
//
bool    kb_macros(uint32_t chord);
bool    user_macros(uint32_t chord);
bool    as_qwerty_mode(uint32_t chord);

#define USER_MACRO(_chord, act)\
    if ((!steno_mode) && chord == (_chord)) { \
        act; \
        clear_keyboard(); \
        return false; \
    }

#endif /* MODE_H */
