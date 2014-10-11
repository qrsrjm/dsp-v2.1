#ifndef DATA_TO_STRING____H____
#define DATA_TO_STRING____H____

#include "lrx.h"

//void initDsp(STR_DSP *dspInfo);
void volToStr(char *dest);

void achEQToStr0(char *dest);
void achEQToStr1(char *dest);
void achEQToStr2(char *dest);
void achEQToStr3(char *dest);
void achEQToStr4(char *dest);
void achEQToStr5(char *dest);

void bchEQToStr(char *dest);
void outDlyToStr(char *dest);
void limitToStr(char *dest);
void m3DToStr(char *dest);
void sctToStr(char *dest);
void hpfToStr(char *dest);
void lpfToStr(char *dest);
void BpfToStr(char * dest);
void ADToStr(char *dest);
void crossbar1ToStr(char *dest);
void outVolToStr(char *dest);


#endif// DATA_TO_STRING____H____

