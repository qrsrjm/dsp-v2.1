#include "g_variable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


MACHINE machine;
STR_DSP *rDspInfo=0;

STR_DSP dspInfo;



void initDspInfo()
{
    int i,j;

    memset(&dspInfo,0,sizeof(dspInfo));
    
     //3D & sct
    for(i=0;i<2;i++) {
        //dspInfo.m3D[i].en = 0;
        dspInfo.m3D[i].mix[0]=1.0;
        //dspInfo.m3D[i].mix[1]= dspInfo.m3D[i].mix[2]= dspInfo.m3D[i].mix[3]= 0.0;
    
        //dspInfo.sct[i].en = 0;
        dspInfo.sct[i].mix[0] = 1.0;
        //dspInfo.sct[i].mix[1] = dspInfo.sct[i].mix[2] = dspInfo.sct[i].mix[3] = 0.0;
        
        dspInfo.sct[i].Ch = i;
        dspInfo.m3D[i].Ch = i;

        dspInfo.sct[i].AGChp.k2=1.0;
        dspInfo.sct[i].AGCbp.k2=1.0;
        dspInfo.sct[i].AGClp.k2=1.0;
    }
    
    //ach eq
    for(i=0;i<6;i++) {
        switch (i) {
        case 0:for(j=0;j<10;j++) {dspInfo.achEQ[0+j].no = j;  dspInfo.achEQ[0+j].Ch=0; }   break;
        case 1:for(j=0;j<10;j++) {dspInfo.achEQ[10+j].no = j; dspInfo.achEQ[10+j].Ch=1;}   break;
        case 2:for(j=0;j<10;j++) {dspInfo.achEQ[20+j].no = j; dspInfo.achEQ[20+j].Ch=2;}   break;
        case 3:for(j=0;j<10;j++) {dspInfo.achEQ[30+j].no = j; dspInfo.achEQ[30+j].Ch=3;}   break;
        case 4:for(j=0;j<5;j++)  {dspInfo.achEQ[40+j].no = j; dspInfo.achEQ[40+j].Ch=4;}   break;
        case 5:for(j=0;j<3;j++)  {dspInfo.achEQ[45+j].no = j; dspInfo.achEQ[45+j].Ch=5;}   break;
        default:break;
        }
    }
    
    //bch eq
    for(i=0;i<2;i++) {
        for(j=0;j<7;j++) {
            dspInfo.bchEQ[i][j].no = j;
            dspInfo.bchEQ[i][j].Ch = i;
        }
    }
    
    //hpf
    for(i=0;i<6;i++) {
        dspInfo.hpf[i].Ch = i;
    }
    
    //bpf 
    dspInfo.bpf.Ch = 4;

    //limit  && outdly
    for(i=0;i<6;i++) {
        dspInfo.limit[i].Ch = i;
        dspInfo.outDly[i].Ch = i;
    }
    
    //input vol
    for(i=0;i<3;i++)
        dspInfo.vol[i].Ch = i;
    
    //crossbar1
    for(i=0;i<2;i++) {
        for(j=0;j<6;j++) {
            dspInfo.crossbar1[i][j].in = i;
            dspInfo.crossbar1[i][j].out = j;
            dspInfo.crossbar1[i][j].rd = 1;
        }
    }
    
}































#if 0

#ifndef DSPGLOBAL___H___
#define DSPGLOBAL___H___

enum{
  Mix_AnDiIn=0,         //analog,digital  input   [crossbar_2]
  Mix_3D_Start,         //[stereoMixer_1]     
  Mix4Ch_3D_En_0,       //[Mix4Ch_13]
  Mix4Ch_3D_En_1,       //[Mix4Ch_14]
  Mix4Ch_3D_Dly_0,      //[Mix4Ch_11]
  Mix4Ch_3D_Dly_1,      //[Mix4Ch_12]
  Mix4Ch_Sct_0,         //[Mix4Ch_2]
  Mix4Ch_Sct_1,         //[Mix4Ch_10]
  Mix4Ch_SignalSource,  //[Mix4Ch_3]
  Mix_Add_SignalSource, //[crossbar_3]
  Mix_Out               //[crossbar_1]
};



#endif //DSPGLOBAL___H___

#endif
