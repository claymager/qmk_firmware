#include "mode.h"
#include "keycodes.h"


#ifdef ONLYQWERTY
bool steno_mode = false;
#else /* no ONLYQWERTY */
bool steno_mode = true;
#endif



bool kb_macros(uint32_t chord) {
    // If any macros match, performs them
    // Returns whether to send the chord to Plover
    if (!user_macros(chord))
        return false;

#ifndef ONLYQWERTY
    if (chord == FN) {
        steno_mode = !steno_mode;
        return false;
    }
#endif

    return (!as_qwerty_mode(chord));
}


__attribute__ ((weak))
bool user_macros(uint32_t chord) {
    return true;
}


// Returns whether to process keys in Qwerty mode
bool as_qwerty_mode(uint32_t chord) {
#ifdef ONLYQWERTY
    return true;
#else
    return
        ( ((!steno_mode)
               && !(chord & FN) )
        || (steno_mode
               && ((FN | PWR) & chord)
               && (chord != FN) )
        );
#endif
}
