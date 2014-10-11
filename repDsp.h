#ifndef REPDSP___H___
#define REPDSP___H___

#include "lrx.h"
#include "g_variable.h"

void repCrossBar(Crossbar_STR *p);

void repOutDly(Outdly *p);


void repLimit(LimiterOP_STR *p);

void repOutputVol(uint8_t out, fp32 vol);


void repInputVol(VOL_OP *p);



void repAD(AnaOrDigSrc_STR *p);

void repSctDepth(unsigned char Ch, unsigned char hbl, float depth);

void repSctBpf(unsigned char Ch, BPF_STR *p);


void repSctHLpf(unsigned char Ch, unsigned char hl,HLPF_STR *p);



void repSctAgc(unsigned char Ch, unsigned char hbl, DRC_STR *p);

void repSctMix(unsigned char Ch, float mixer[4]);

void repSctEn(unsigned char Ch, uint8_t en);


void rep3DDly(unsigned char Ch, DLY_STR *p);



void rep3DEn(unsigned char Ch, unsigned char en);

void rep3DMix(unsigned char Ch, float mixer[4]);

void repBCHEQ(EQOP_STR *p);


void repACHEQ(EQOP_STR *p);

void repBPF(BPF_STR *p, uint8 Ch);

void repLPF(CHanHLPF_STR *p);


void repHPF(CHanHLPF_STR *p);



#endif //REPDSP_______H________
