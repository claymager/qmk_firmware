#include "keycodes.h"
#include "logging.h"


int32_t read_keycode(uint16_t keycode) {
    switch (keycode) {
#ifndef NO_DEBUG
        case STN_ST1:            sprintf(debug_key, "ST1"); return ST1;
        case STN_ST2:           sprintf(debug_key, "ST2"); return ST2;
        case STN_ST3:           sprintf(debug_key, "ST3"); return ST3;
        case STN_ST4:           sprintf(debug_key, "ST4"); return ST4;
        case STN_FN:            sprintf(debug_key, "FN"); return FN;
        case STN_PWR:           sprintf(debug_key, "PWR"); return PWR;
        case STN_N1...STN_N6:   sprintf(debug_key, "LNO"); return LNO;
        case STN_N7...STN_NC:   sprintf(debug_key, "RNO"); return RNO;
        case STN_S1:            sprintf(debug_key, "LSU"); return LSU;
        case STN_S2:            sprintf(debug_key, "LSD"); return LSD;
        case STN_TL:            sprintf(debug_key, "LFT"); return LFT;
        case STN_KL:            sprintf(debug_key, "LK"); return LK;
        case STN_PL:            sprintf(debug_key, "LP"); return LP;
        case STN_WL:            sprintf(debug_key, "LW"); return LW;
        case STN_HL:            sprintf(debug_key, "LH"); return LH;
        case STN_RL:            sprintf(debug_key, "LR"); return LR;
        case STN_A:             sprintf(debug_key, "LA"); return LA;
        case STN_O:             sprintf(debug_key, "LO"); return LO;
        case STN_E:             sprintf(debug_key, "RE"); return RE;
        case STN_U:             sprintf(debug_key, "RU"); return RU;
        case STN_FR:            sprintf(debug_key, "RF"); return RF;
        case STN_RR:            sprintf(debug_key, "RR"); return RR;
        case STN_PR:            sprintf(debug_key, "RP"); return RP;
        case STN_BR:            sprintf(debug_key, "RB"); return RB;
        case STN_LR:            sprintf(debug_key, "RL"); return RL;
        case STN_GR:            sprintf(debug_key, "RG"); return RG;
        case STN_TR:            sprintf(debug_key, "RT"); return RT;
        case STN_SR:            sprintf(debug_key, "RS"); return RS;
        case STN_DR:            sprintf(debug_key, "RD"); return RD;
        case STN_ZR:            sprintf(debug_key, "RZ"); return RZ;

#else
        case STN_ST1:           return ST1;
        case STN_ST2:           return ST2;
        case STN_ST3:           return ST3;
        case STN_ST4:           return ST4;
        case STN_FN:            return FN;
        case STN_PWR:           return PWR;
        case STN_N1...STN_N6:   return LNO;
        case STN_N7...STN_NC:   return RNO;
        case STN_S1:            return LSU;
        case STN_S2:            return LSD;
        case STN_TL:            return LFT;
        case STN_KL:            return LK;
        case STN_PL:            return LP;
        case STN_WL:            return LW;
        case STN_HL:            return LH;
        case STN_RL:            return LR;
        case STN_A:             return LA;
        case STN_O:             return LO;
        case STN_E:             return RE;
        case STN_U:             return RU;
        case STN_FR:            return RF;
        case STN_RR:            return RR;
        case STN_PR:            return RP;
        case STN_BR:            return RB;
        case STN_LR:            return RL;
        case STN_GR:            return RG;
        case STN_TR:            return RT;
        case STN_SR:            return RS;
        case STN_DR:            return RD;
        case STN_ZR:            return RZ;

#endif
    }
    return 0;
}


