#ifndef KEYCODES_H
#define KEYCODES_H
#include "keymap_steno.h"

extern int32_t read_keycode(uint16_t keycode);

// Shift to internal representation
// i.e) S(teno)R(ight)F
#define STN(n) (1L<<n)
enum ORDER { 
    SFN = 0, SPWR, SST1, SST2, SST3, SST4, SNUML, SNUMR,
    SLSU, SLSD, SLT, SLK, SLP, SLW, SLH, SLR, SLA, SLO, 
    SRE, SRU, SRF, SRR, SRP, SRB, SRL, SRG, SRT, SRS, SRD, SRZ, SRES1, SRES2
};


// Break it all out
#define FN  STN(SFN)
#define PWR STN(SPWR)
#define ST1 STN(SST1)
#define ST2 STN(SST2)
#define ST3 STN(SST3)
#define ST4 STN(SST4)
#define LNO STN(SNUML)  // STN1-6
#define RNO STN(SNUMR)  // STN7-C
#define RES1 STN(SRES1) // Use reserved for sticky state
#define RES2 STN(SRES2)

#define LSU STN(SLSU)
#define LSD STN(SLSD)
#define LFT STN(SLT)    // (L)e(F)t (T), preprocessor conflict
#define LK  STN(SLK)
#define LP  STN(SLP)
#define LW  STN(SLW)
#define LH  STN(SLH)
#define LR  STN(SLR)
#define LA  STN(SLA)
#define LO  STN(SLO)

#define RE  STN(SRE)
#define RU  STN(SRU)
#define RF  STN(SRF)
#define RR  STN(SRR)
#define RP  STN(SRP)
#define RB  STN(SRB)
#define RL  STN(SRL)
#define RG  STN(SRG)
#define RT  STN(SRT)
#define RS  STN(SRS)
#define RD  STN(SRD)
#define RZ  STN(SRZ)

#endif /* KEYCODES_H */
