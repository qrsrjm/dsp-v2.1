#include "repDsp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void repCrossBar(Crossbar_STR *p)
{
	if (p->in >= 2 || p->out >= 6) return;
    dspInfo.crossbar1[p->in][p->out].in = p->in;
    dspInfo.crossbar1[p->in][p->out].out = p->out;
    dspInfo.crossbar1[p->in][p->out].rd = p->rd;
    dspInfo.crossbar1[p->in][p->out].mix = p->mix;
}


void repOutDly(Outdly *p)
{
    dspInfo.outDly[p->Ch].delay.Dly = p->delay.Dly;
    dspInfo.outDly[p->Ch].delay.en  = p->delay.en;
    dspInfo.outDly[p->Ch].Ch = p->Ch;
}


void repLimit(LimiterOP_STR *p)
{
    dspInfo.limit[p->Ch].limiter.T2 = p->limiter.T2;
    dspInfo.limit[p->Ch].limiter.k2 = p->limiter.k2;
    dspInfo.limit[p->Ch].limiter.Attack = p->limiter.Attack;
    dspInfo.limit[p->Ch].limiter.Release = p->limiter.Release;
    dspInfo.limit[p->Ch].limiter.en= p->limiter.en;
    dspInfo.limit[p->Ch].Ch = p->Ch;
}

void repOutputVol(uint8_t out, fp32 vol)
{
    if (out >= 6) return;
    dspInfo.outVol[out] = vol;
} 


void repInputVol(VOL_OP *p)
{
    if (p->Ch >= 3) return;
    dspInfo.vol[p->Ch].vol.Gain = p->vol.Gain;
    dspInfo.vol[p->Ch].vol.Pol = p->vol.Pol;
    dspInfo.vol[p->Ch].vol.Mute = p->vol.Mute;   
    dspInfo.vol[p->Ch].Ch = p->Ch;
}



void repAD(AnaOrDigSrc_STR *p)
{
	if (p->en >= 3) return;
    dspInfo.ad.en = p->en;
    dspInfo.ad.mixer = p->mixer;
}

void repSctDepth(unsigned char Ch, unsigned char hbl, float depth)
{
    if (Ch >=2) return;
    
    if (hbl == 0) {
        dspInfo.sct[Ch].hVolDepth = depth;
    } else if (hbl == 1) {
        dspInfo.sct[Ch].bVolDepth = depth;
    } else if (hbl == 2) {
        dspInfo.sct[Ch].lVolDepth = depth;
    }
}

void repSctBpf(unsigned char Ch, BPF_STR *p)
{
    if (Ch >=2) return;
    
    dspInfo.sct[Ch].bpf.Fp = p->Fp;
    dspInfo.sct[Ch].bpf.Fs = p->Fs;
    dspInfo.sct[Ch].hpf.Type = p->Type;
    dspInfo.sct[Ch].hpf.en = p->en;
}


void repSctHLpf(unsigned char Ch, unsigned char hl,HLPF_STR *p)
{
    if (Ch >=2) return;
    
    if (hl == 0) {
        dspInfo.sct[Ch].hpf.Fc = p->Fc;
        dspInfo.sct[Ch].hpf.Type = p->Type;
        dspInfo.sct[Ch].hpf.en = p->en;
    } else if (hl == 2) {
        dspInfo.sct[Ch].lpf.Fc = p->Fc;
        dspInfo.sct[Ch].lpf.Type = p->Type;
        dspInfo.sct[Ch].lpf.en = p->en;
    }
}



void repSctAgc(unsigned char Ch, unsigned char hbl, DRC_STR *p)
{
    if (Ch >=2) return;
    
    if (hbl == 0) {    
        dspInfo.sct[Ch].AGChp.T2 = p->T2;
        dspInfo.sct[Ch].AGChp.k2 = p->k2;
        dspInfo.sct[Ch].AGChp.Attack = p->Attack;
        dspInfo.sct[Ch].AGChp.Release = p->Release;
        dspInfo.sct[Ch].AGChp.en = p->en;
    } else if (hbl == 1) {
        dspInfo.sct[Ch].AGCbp.T2 = p->T2;
        dspInfo.sct[Ch].AGCbp.k2 = p->k2;
        dspInfo.sct[Ch].AGCbp.Attack = p->Attack;
        dspInfo.sct[Ch].AGCbp.Release = p->Release;
        dspInfo.sct[Ch].AGCbp.en = p->en;
    } else if (hbl ==2) {
        dspInfo.sct[Ch].AGClp.T2 = p->T2;
        dspInfo.sct[Ch].AGClp.k2 = p->k2;
        dspInfo.sct[Ch].AGClp.Attack = p->Attack;
        dspInfo.sct[Ch].AGClp.Release = p->Release;
        dspInfo.sct[Ch].AGClp.en = p->en;
    }
}


void repSctMix(unsigned char Ch, float mixer[4])
{
	if (Ch >= 2) return;
	memcpy(dspInfo.sct[Ch].mix,mixer,sizeof(mixer)*4);	
    
    printf("=>%s ch=%d,%f,%f,%f,%f\n",__FUNCTION__,Ch,
        mixer[0],mixer[1],mixer[2],mixer[3]);
}


void repSctEn(unsigned char Ch, uint8_t en)
{
	if (Ch >= 2) return;
	dspInfo.sct[Ch].en = en;
	dspInfo.sct[Ch].Ch = Ch;

    printf("=>%s ch=%d,en=%d\n",__FUNCTION__,Ch,en);
}


void rep3DDly(unsigned char Ch, DLY_STR *p)
{
    if (Ch >= 2) return;
    dspInfo.m3D[Ch].Ch = Ch;
    dspInfo.m3D[Ch].delay.Dly = p->Dly;
    dspInfo.m3D[Ch].delay.en = p->en;
}



void rep3DEn(unsigned char Ch, unsigned char en)
{
    if (Ch >=2) return;
    dspInfo.m3D[Ch].en = en;
    dspInfo.m3D[Ch].Ch = Ch;
}


void rep3DMix(unsigned char Ch, float mixer[4])
{
    if (Ch >=2) return;
    dspInfo.m3D[Ch].Ch = Ch;
    memcpy(dspInfo.m3D[Ch].mix, mixer, sizeof(float)*4);
}


void repBCHEQ(EQOP_STR *p)
{
	if (p->Ch >= 2 || p->no >= 8) return;
    dspInfo.bchEQ[p->Ch][p->no].peq.Q = p->peq.Q;
    dspInfo.bchEQ[p->Ch][p->no].peq.Gain = p->peq.Gain;
    dspInfo.bchEQ[p->Ch][p->no].peq.Fc = p->peq.Fc;
    dspInfo.bchEQ[p->Ch][p->no].peq.Type = p->peq.Type;
    dspInfo.bchEQ[p->Ch][p->no].peq.en = p->peq.en;
    dspInfo.bchEQ[p->Ch][p->no].Ch = p->Ch;
    dspInfo.bchEQ[p->Ch][p->no].no = p->no;
}


void repACHEQ(EQOP_STR *p)
{
    unsigned char Ch=0, no = p->no;
 
    switch (p->Ch) {
    case 0:Ch = 0; break;
    case 1:Ch = 10; break;
    case 2:Ch = 20; break;
    case 3:Ch = 30; break;
    case 4:Ch = 40; break;
    case 5:Ch = 45; break;
    default:break;
    }
  
    dspInfo.achEQ[Ch+no].peq.Q = p->peq.Q;
    dspInfo.achEQ[Ch+no].peq.Gain = p->peq.Gain;
    dspInfo.achEQ[Ch+no].peq.Fc = p->peq.Fc;
    dspInfo.achEQ[Ch+no].peq.Type = p->peq.Type;
    dspInfo.achEQ[Ch+no].peq.en = p->peq.en;
    dspInfo.achEQ[Ch+no].Ch = p->Ch;
    dspInfo.achEQ[Ch+no].no = p->no;
}


void repBPF(BPF_STR *p, uint8 Ch)
{
    if (Ch != 4) return;
    dspInfo.bpf.Ch = Ch;
    dspInfo.bpf.Fp = p->Fp;
    dspInfo.bpf.Fs = p->Fs;
    dspInfo.bpf.Type = p->Type;
    dspInfo.bpf.en = p->en;

}


void repLPF(CHanHLPF_STR *p)
{
    if (p->Ch == 4) {
        dspInfo.lpf.Ch = p->Ch;
        dspInfo.lpf.xpf.Fc = p->xpf.Fc;
        dspInfo.lpf.xpf.Type = p->xpf.Type;
        dspInfo.lpf.xpf.en = p->xpf.en;
    }
}


void repHPF(CHanHLPF_STR *p)
{
    if (p->Ch >= 6 || p->Ch == 4) return;
    dspInfo.hpf[p->Ch].Ch = p->Ch;
    dspInfo.hpf[p->Ch].xpf.Fc = p->xpf.Fc;
    dspInfo.hpf[p->Ch].xpf.Type = p->xpf.Type;
    dspInfo.hpf[p->Ch].xpf.en = p->xpf.en;
}















