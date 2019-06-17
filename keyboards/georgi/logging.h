#ifndef LOGGING_H
#define LOGGING_H

#include QMK_KEYBOARD_H

bool use_verbose_debugging;


#ifndef NO_DEBUG

char debug_str[64];
char debug_key[5];

#define print_2(base, ...) \
    sprintf(debug_str, __VA_ARGS__); \
    uprintf("\n%s%s", base, debug_str);

#define error(...) \
    print_2("ERROR:", __VA_ARGS__);

#define warn(...) \
    print_2("WARN:", __VA_ARGS__);

#define verbose_log(...) \
    if (use_verbose_debugging) { \
        print_2("", __VA_ARGS__); \
    }


#else /* NO_DEBUG */
#define debug_key
#define verbose_log( ... )
#define error( ... )
#define warn( ... )
#endif /* NO_DEBUG */

#endif /* LOGGING_H */
