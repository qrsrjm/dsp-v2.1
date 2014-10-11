/*
*****************************************Copyright (c)*********************************************
**
**
**									 广州立锐升电子有限公司
**                             Guangzhou Lrsun Electronic Co.,Ltd.
**
**                                    http://www.lrsun.net
**
**
**
**	文件名	：TAS3xxx.h
**	
**	程序员	：陈家承
**
**	日　期  ：2009年1月20日
**
**	文件描述：DAP全功能实现文件。
**			  
**
***************************************************************************************************
*/
#ifndef _TAS3XXX_H
#define _TAS3XXX_H


#include "MyType.h"
//#include "lrx.h"
//#include "DataStg.h"



#define PI 	3.1415926535897932384626433832795
#define FS 	48000




extern void     DapDelay(uint32 i);
extern uint32 	DAPFloatTo5P23(fp64 fVal);

extern void 	DAPFloatTo25P23(fp64 fVal,uint32 *Ceof);

extern void 	DAPBesAndButLPF(uint8 order, fp64 fc, uint32* coef, uint8 sel);

extern void 	DAPBesAndButHPF(uint8 order, fp64 fc, uint32* coef, uint8 sel);

extern void 	DAPLinkwitzLPF(uint8 order, fp64 fc, uint32* coef); 

extern void 	DAPLinkwitzHPF(uint8 order, fp64 fc, uint32* coef);

extern void		BandPF2Order(fp64 fc,fp64 GainDb,fp64 bandwidth,uint32* coef);

extern void 	DAPBiquadFilter(fp64 fc, fp64 gain, fp64 q, uint32* coef);

extern void     DAPAllpassFilter (fp64 fc, fp64 gain, fp64 q, uint32* coef);

extern void		DAPToneBass (fp64 fc, fp64 gain, fp64 q, uint32* coef);

extern void		DAPToneTreble (fp64 fc, fp64 gain, fp64 q, uint32* coef);

extern void		DAPToneMid (fp64 fc1, fp64 fc2, fp64 gain, fp64 q, uint32* coef);

extern void		TAS3xxxReset(void);

/*
extern void 	DAPFbx(uint8 menu, uint8 cursor);

extern void 	DAPMixers(MIX_STR mix);
extern void 	DAPSetMixers(uint8 start, uint8 end);

extern void 	DAPHPFSet(uint8 chn, uint8 grp, HLPF_STR* hpf);
extern void		DAPHPFSet_a(uint8 chn, uint8 grp, HLPF_STR* lpf);

extern void 	DAPLPFSet(uint8 chn, uint8 grp, HLPF_STR* lpf);
extern void		DAPLPFSet_a(uint8 chn, uint8 grp, HLPF_STR* lpf);

extern void 	DAPPEQSet(uint8 chn, uint8 grp, uint8 num, EQ_STR peq);
extern void 	DAPChnPEQSet(uint8 chn, uint8 grp, uint8 cursor);

extern void 	DAPFSSet(uint8 num, EQ_STR peq, uint8 aAn);
extern void 	DAPToneSet(uint8 num, TONE_STR tone, uint8 aAn);

extern void 	DAPMuteSyn(void);

extern void 	DAPVolAdjustment(uint8 chn, uint8 grp, float *gain, int8 *pol, uint8 mute);
extern void 	DAPVolAdjustmentPreset(uint8 chn, uint8 grp, VOL_STR *gain, uint8 mute);
extern void 	DAPVolAdjustment_b(uint8 chn, uint8 grp, VOL_STR *gain, uint8 mute);

extern void     DAPMicVolMute(uint32 en);
extern void     DAPEffVolMute(uint32 en);

extern void 	DAPDelaySet(uint8 chn, uint8 grp, DLY_STR* delay);

extern void 	DAPDRC(uint8 chn, uint8 grp, DRC_STR* drc);
extern void     DAPDRCSet(uint8 chn, uint8 grp);
extern void 	DAPDRC_a(uint8 chn, uint8 grp, DRC_STR* drc);

extern void 	DAPAGC(uint8 chn, uint8 grp, DRC_STR* agc);
extern void 	DAPAGC_a(uint8 chn, uint8 grp, DRC_STR* agc);

extern void 	DAPMusicPara(const uint8 cursor);

extern void     DAPNGC_a(uint8 chn, uint8 grp, NGC_STR* ngc);
extern void     DAPNoiseGateSet(uint8 chn, uint8 grp, NGC_STR* ngc);

extern void 	VuDetect(uint8 *inVal, uint8 *outVal);
extern void 	DAPsubDecay(uint8 enable);
extern void 	DAPMicAutoMute(uint8 enable);

extern void 	DAPMusicInput(uint8 sel);
extern void		DAPMicInput(uint8 sel);

extern void 	DAPMusic3DEnable(uint8 en);

extern void 	TAS3xxxReset(void);

extern void     DAPSetsubDecay(fp32 thd);

extern void 	DAPMode(uint8 chn, uint8 grp, uint8 mode);

extern void     DAPRecall(const int8 loadSel);

extern void 	TAS3xxxInit(void);

extern void     DAPSysTimes(uint16 times, uint8 en);

extern void     DAPFsFreqSet(int8 freq);

extern void     DAPFsGainSet(fp32 gain);
*/
/************************/
/* 激励器 start			*/
/************************/
/*
extern void 	DAPVolSet(uint8 chn, uint8 grp, uint8 num, float fTemp);

extern void 	DAPMixSet(uint8 chn, uint8 grp, uint8 num, uint8 index, float fTemp);

extern void 	DAPEqFreqSet(uint8 chn, uint8 grp, uint8 num, float fTemp);

extern void 	DAPEffSelect(uint8 chn, uint8 grp, uint32 ulTemp);

extern void 	DAPEffInit(void);

extern void 	DAPHLpf(uint8 chn, uint8 grp, uint8 num, float freq);

*/
/************************/
/* 激励器 end			*/
/************************/

#endif  //_TAS3XXX_H


