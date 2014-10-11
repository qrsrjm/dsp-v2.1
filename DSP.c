/**
 * @file         DSP.c
 * @brief        This is a brief description.
 * @details  This is the detail description.
 * @author       author
 * @date     2014.9.20
 * @version  A001
 * @par Copyright (c): 
 *       XXX公司
 * @par History:         
 *   version: author, date, desc\n
 */ 


#include "DSP.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //sleep close


#include "I2C.h"
#include "TAS3xxx.h"

#include "DataStg.h"
#include "UserMath.h"

#include "TAS3xxxDownload.h"
#include "ModulesAddr_Ver2_1.h"

#include "g_variable.h"
#include "repDsp.h"
#include "dspArchive.h"




#define DEBUG 1

volatile uint32_t outVolFlag[2][6]={0};    //输出路由标志，1: 输出 0: 没输出
uint32_t outVolFlagBak[2][6]={0}; //输出路由标志，1: 输出 0: 没输出 【副本】 
uint32_t repCrossBar1[64]={0};
volatile uint32_t SSFlag=0;



/*********************************************************************************************************
** Function name:       DspMixerSet
** Descriptions:        路由控制,Crossbar_1模块
** input parameters:    in 输入通道 out 输出通道 mixer 比例值，线性比例；in和out一一对应，不能混音
in={0,1,2,3},out={0,1,2,3}
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet(uint8_t rd,uint32_t in, uint32_t out, float mixer)
{
	uint32 mix_val[4] = {0,0,0,0};
	uint8  mix_i2c_addr=0;
	char ret = 0;
    
#if DEBUG
    printf("-->%s> rd=%d,in=%d,out=%d,mixer=%f\n",__FUNCTION__,rd,in,out,mixer);
#endif  

    Crossbar_STR *p = (Crossbar_STR*)malloc(sizeof(Crossbar_STR));
    p->in=in; p->rd=rd; p->out=out; p->mix=mixer;
    repCrossBar(p);
    free(p);

    if (0 == DAPFloatTo5P23(mixer)) {
        outVolFlag[in][out]= 0;
    } else {
        outVolFlag[in][out]= 1;
    }
    
    printf("outVolFlag[%d][%d]=%d\n",in,out,outVolFlag[in][out]);
    
    memset(mix_val,0,4);

	switch (in)
	{
	case 0:    //x1x
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;          
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;  
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER08_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER11_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 1:   //x2x
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER11_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 2:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 3:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 4:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 5:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 6:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER11_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER11_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 7:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			ret = mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	default:
		break;

	}

    //uint32_t cls[4]={0,0,0,0},addr=0x90;
    //I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, cls, 4);
    //for(int i=0;i<4;i++){
    //    printf("%x,",mix_val[i]);
    //}
    //printf("\n ---> ");


	ret = I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
    
    memset(mix_val,0,4);
    I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);

    for(int i=0;i<4;i++){
        printf("%x,",mix_val[i]);
    }
    printf("\n");

    
	return ret;
}


/*********************************************************************************************************
** Function name:       DspMixerSet     v2.1
** Descriptions:        路由控制,Crossbar_1模块
** input parameters:    in 输入通道 out 输出通道 mixer 比例值，线性比例；in和out一一对应，不能混音
in={0,1,2,3},out={0,1,2,3}
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSetSignalSource(uint8_t rd,uint32_t in, uint32_t out, float mixer)
{
	uint32 mix_val[4] = {0,0,0,0};
	uint8  mix_i2c_addr=0;
	char ret = 0;
    
#if DEBUG
    printf("-->%s> rd=%d,in=%d,out=%d,mixer=%f\n",__FUNCTION__,rd,in,out,mixer);
#endif  

    memset(mix_val,0,4);

	switch (in)
	{
	case 0:    //x1x
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;          
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;  
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER08_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER11_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 1:   //x2x
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER11_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 2:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
            if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 3:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER01_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER02_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER03_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER04_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER15_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 4:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER05_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER06_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER09_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 5:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER07_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER08_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER12_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 6:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER10_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER11_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER11_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	case 7:
		switch (out)
		{
		case 0:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 1:
			mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 2:
			ret = mix_i2c_addr = MIXER13_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 3:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;

		case 4:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;

		case 5:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
			break;

		case 6:
			mix_i2c_addr = MIXER14_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;

		case 7:
			mix_i2c_addr = MIXER16_I2C_ADDR;
			if (rd) I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		}
		break;

	default:
		break;

	}

    //uint32_t cls[4]={0,0,0,0},addr=0x90;
    //for(int i=0;i<16;i++)
    //    I2CWriteMultiWord(TAS_SLA0, addr+i, cls, 4);
    uint32 rep[1];
    DspClsCrossbar1(0,rep);


	ret = I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
    
    memset(mix_val,0,4);
    I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);

    for(int i=0;i<4;i++){
        printf("%x,",mix_val[i]);
    }
    printf("\n");

    
	return ret;
}


/**
* clean crossbar_1 reg    v2.1
* This is a detail description.
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspClsCrossbar1(uint8 rd,uint32_t rep[64])
{
#if DEBUG
        printf("-->%s> rd=%d,rep[]\n",__FUNCTION__,rd);
#endif

    uint32_t cls[4]={0,0,0,0},addr=0x90;
    int j=0;
    if (rd) {
        for(int i=0;i<16;i++,j+=4)
        I2CReadMultiWord(TAS_SLA0, addr+i, rep+j, 4);  
    }
    for(int i=0;i<16;i++)
        I2CWriteMultiWord(TAS_SLA0, addr+i, cls, 4);   
}

/**
* crossbar1 write all reg     v2.1
* This is a detail description.
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspWiteCrossbar1(uint32_t rep[64])
{
#if DEBUG
    printf("-->%s> rep[]\n",__FUNCTION__);
#endif
    uint32_t addr=0x90;
    int j=0;

    for(int i=0;i<16;i++,j+=4)
    I2CWriteMultiWord(TAS_SLA0, addr+i, rep+j, 4);  

}



/*********************************************************************************************************
** Function name:       DspMixerSet4Ch
** Descriptions:        路由控制
** input parameters:    in 输入通道 select Mix4Ch模块的索引  mixer 比例值

select 0-.Mix4Ch_11,1-.Mix4Ch_12,3D混音；2-.Mix4Ch_13,3-.Mix4Ch_14,3D开关；
4-.Mix4Ch_2,5-.Mix4Ch_10，SCT开关；6-.Mix4Ch_3，测试音源选择；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet4Ch(uint8_t rd, uint32_t select, float mixer[])
{
	uint32 mix_val[4] = {0,0,0,0};
	uint8  mix_i2c_addr = 0;
	char   ret = 0;

#if DEBUG	
    printf("--%s> rd=%d,select=%d,mixer=%f,%f,%f,%f\n",__FUNCTION__,
        rd,select,mixer[0],mixer[1],mixer[2],mixer[3]);
#endif

	switch (select) {
    case 0: mix_i2c_addr = Mix4Ch_1;   break;
    case 1: mix_i2c_addr = Mix4Ch_2;   break;
    case 2: mix_i2c_addr = Mix4Ch_7;   break;
    case 3: mix_i2c_addr = Mix4Ch_9;   break;
	case 4: mix_i2c_addr = Mix4Ch_10;    break;
	case 5: mix_i2c_addr = Mix4Ch_11;   break;
/*	case 6: mix_i2c_addr = Mix4Ch_3;    break;
*/
	default: break;
	}

    const float EPSINON = 0.000001;
    if (rd) { 
        I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
        for (int i=0;i<4;i++){
            if (mixer[i] > EPSINON) 
			{
                mix_val[i] = DAPFloatTo5P23(mixer[i]);
				printf("i=%d\n",i);
            }
        }
    } else {
        for (int i=0;i<4;i++){
            mix_val[i] = DAPFloatTo5P23(mixer[i]);
        }
    }
    
    uint32 mix_cls[4] = {0,0,0,0};
    I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_cls, 4);   //clear mix4Ch_x

	ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
	return ret;
}




/*********************************************************************************************************
** Function name:       DspGain     v2.0
** Descriptions:        音量控制
** input parameters:    gain 音量结构体指针
**                    index =0.控制Volume_4，crossbar_3的输入端第一通道的音量，Ch =1.控制Volume_5，crossbar_3的输入端第二通道的音量，
**                    index =3.控制Volume_11，crossbar_3的输出端第一通道的音量，Ch =3.控制Volume_10，crossbar_3的输出端第二通道的音量
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspGain_0(VOL_STR *gain)
{
	uint32_t volume;
	char ret = 0;
    
#if DEBUG
    printf("-->%s> gain=%f,pol=%d,mute=%d\n",__FUNCTION__,
        gain->Gain,gain->Pol,gain->Mute);
#endif

	if (1 == gain->Mute  || gain->Gain < -60)
	{
		volume = 0;
	}
	else
	{
		if (gain->Pol == 1)
		{
			volume = DAPFloatTo5P23(-pow(10.0, gain->Gain*0.05));
		}
		else
		{
			volume = DAPFloatTo5P23(pow(10.0, gain->Gain*0.05));
		}
	}
    
    //2014.9.26   v2.0  没有Volume_13
    //I2CWriteMultiWord(TAS_SLA0, Volume_13, &volume, 1);
    
	return ret;
}


/**
*
* 2014.9.26   v2.1
**/
int DspGain(VOL_OP *gain)
{
    uint32_t volume;
    char ret = 0;
    
#if DEBUG
    printf("-->%s> gain=%f,pol=%d,mute=%d,Ch=%d\n",__FUNCTION__,
        gain->vol.Gain,gain->vol.Pol,gain->vol.Mute,gain->Ch);
#endif

    repInputVol(gain);

    if (1 == gain->vol.Mute  || gain->vol.Gain < -60)
    {
        volume = 0;
    }
    else
    {
        if (gain->vol.Pol == 1)
        {
            volume = DAPFloatTo5P23(-pow(10.0, gain->vol.Gain*0.05));
        }
        else
        {
            volume = DAPFloatTo5P23(pow(10.0, gain->vol.Gain*0.05));
        }
    }
    uint8 mix_i2c_addr0 = Mix4Ch_10;
	uint8 mix_i2c_addr1 = Mix4Ch_11;
    uint32_t mixer[8]={0};

    memset(mixer,0,8);
    I2CReadMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);
    I2CReadMultiWord(TAS_SLA0, mix_i2c_addr1, mixer+4, 4);
    printf("0:mix=%x,%x,%x,%x, 1:%x,%x,%x,%x\n",mixer[0],mixer[1],mixer[2],mixer[3],mixer[4],mixer[5],mixer[6],mixer[7]);

    //if(mixer[gain->Ch] == 0 || mixer[4+gain->Ch]==0) return 0;
    
    if (gain->Ch == 0) {
        //memset(mixer,0,4);
        mixer[0]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);  
    } else if (gain->Ch == 1) {
        //memset(mixer,0,4);
        mixer[1]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);  
    } else if (gain->Ch == 2) {
        //memset(mixer,0,4);
        mixer[2]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4); 
    }
    
    return ret;
}


/*********************************************************************************************************
** Function name:       DspOutDelay
** Descriptions:        输出通道延时控制
** input parameters:    Ch 输出通道 delay 延时结构体指针
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspOutDelay(Outdly *OutPutDly)
{
    uint32 delayVal[1];
    uint32 delayTmp;
    uint32 en[1] = { 1 };
    char ret = 0;
#if DEBUG
        printf("-->%s> Dly=%f,en=%d,ch=%d\n",__FUNCTION__,
            OutPutDly->delay.Dly,OutPutDly->delay.en,OutPutDly->Ch);
#endif 

    repOutDly(OutPutDly);


    if (1 == OutPutDly->delay.en)
    {
        if (OutPutDly->delay.Dly >= (fp32)122.50)
        {
            delayTmp = 5880;
        }
        else if (OutPutDly->delay.Dly >= 0)
        {
            delayTmp = MathRound(48 * OutPutDly->delay.Dly, 0);
        }
        else
        {
            delayTmp = 0;
        }
    }
    else
    {
        delayTmp = 0;
    }

    switch (OutPutDly->Ch)
    {
    case 0:
        I2CReadMultiWord(TAS_SLA0, Delay1, delayVal, 1);            // Delay Ch 1
        //delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16);        

        I2CWriteMultiWord(TAS_SLA0, Delay1, delayVal, 1);

        I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    case 1:
        I2CReadMultiWord(TAS_SLA0, Delay2, delayVal, 1);            // Delay Ch 2
        delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        
       // delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16); 
        
        I2CWriteMultiWord(TAS_SLA0, Delay2, delayVal, 1);
        ret = I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    case 2:
        I2CReadMultiWord(TAS_SLA0, Delay3, delayVal, 1);            // Delay Ch 3
        //delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16);        

        I2CWriteMultiWord(TAS_SLA0, Delay3, delayVal, 1);

        I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    case 3:
        I2CReadMultiWord(TAS_SLA0, Delay4, delayVal, 1);            // Delay Ch 4
        delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        
       // delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16); 
        
        I2CWriteMultiWord(TAS_SLA0, Delay4, delayVal, 1);
        ret = I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    case 4:
        I2CReadMultiWord(TAS_SLA0, Delay5, delayVal, 1);            // Delay Ch 5
        //delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16);        

        I2CWriteMultiWord(TAS_SLA0, Delay5, delayVal, 1);

        I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    case 5:
        I2CReadMultiWord(TAS_SLA0, Delay6, delayVal, 1);            // Delay Ch 6
        delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        
       // delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16); 
        
        I2CWriteMultiWord(TAS_SLA0, Delay6, delayVal, 1);
        ret = I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);
        break;
    default:
        break;
    }
    return ret;
}





/*
***************************************************************************************************
**                                          DspLimiter()
**	功能描述：DRC动态范围控制。
**	参  数  ：Chn             音频通道选择
**		drc.T1,T2       起控电平
**            drc.k0,k1,k2    斜率
**            drc.O1,O2       电平偏移量
**            drc.Attack      起控时间
**            drc.Release       释放时间
**            drc.en          功能使能标志
**	返回值  ：无
***************************************************************************************************
*/
#define	DRC_GAIN_SUB	51.9224
#define DRC_THR_OFFSET  (-22.0)

int DspLimiter(LimiterOP_STR *LimOP)
{
	fp64 	ad;
	fp64	aa;
	fp32    k2;
	uint32 	drcEn[2];
	uint32	drcTimeConst[4];
	uint32	drcThreshold[4];
	uint32	drcOffset[4];
	uint32	drcSlope[3];
	char ret = 0;

    uint8_t en[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

    uint8_t mix_val[16]={0};       

#if DEBUG
        printf("-->%s> T2=%f,k2=%f,Attack=%f,Release=%f,en=%d,ch=%d\n",__FUNCTION__,
            LimOP->limiter.T2,LimOP->limiter.k2,LimOP->limiter.Attack,LimOP->limiter.Release,
            LimOP->limiter.en,LimOP->Ch);
#endif 

    repLimit(LimOP);

    if (1 == LimOP->limiter.en)
    {
        drcEn[0] = 0x00800000;
        drcEn[1] = 0x00000000;

    	aa = pow(2.7182818, -1 / (48 * (fp64)LimOP->limiter.Attack));
    	ad = pow(2.7182818, -1 / (48 * (fp64)LimOP->limiter.Release));

    	drcTimeConst[0] = DAPFloatTo5P23(1 - aa);
    	drcTimeConst[1] = DAPFloatTo5P23(aa);
    	drcTimeConst[2] = DAPFloatTo5P23(1 - ad);
    	drcTimeConst[3] = DAPFloatTo5P23(ad);


    	drcThreshold[0] = 0x00000000;
    	drcThreshold[1] = 0x0FF055DB;
    	//  DAPFloatTo25P23((-140-DRC_GAIN_SUB)/-6.0206, &drcThreshold[0]);
    	DAPFloatTo25P23((LimOP->limiter.T2 + DRC_THR_OFFSET - DRC_GAIN_SUB) / -6.0206, &drcThreshold[2]);
    	drcOffset[0] = 0x00000000;
    	drcOffset[1] = 0x02000000;
    	drcOffset[2] = 0x00000000;
    	drcOffset[3] = 0x02000000;
    	//	    DAPFloatTo25P23((0+24.0824)/6.0206, &drcOffset[0]);
    	//	    DAPFloatTo25P23((0+24.0824)/6.0206, &drcOffset[2]);

    	drcSlope[0] = 0x00000000;//DAPFloatTo5P23(0);
    	drcSlope[1] = 0x00000000;//DAPFloatTo5P23(0);

    	k2 = 1 / LimOP->limiter.k2 - 1;
    	if (k2 < -0.966667)
    	{
    		k2 = -1;
    	}
    	drcSlope[2] = DAPFloatTo5P23(k2);
        
    	switch (LimOP->Ch)
    	{
        case 0:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 5, drcEn, 2);
            break;
        case 1:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 5, drcEn, 2);
            break;
        case 2:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 5, drcEn, 2);
            break;
        case 3:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 5, drcEn, 2);
            break;
        case 4:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 5, drcEn, 2);
            break;
        case 5:
            ret = I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 1, drcThreshold, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 2, drcSlope, 3);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 3, drcOffset, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 4, drcTimeConst, 4);
            ret |= I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 5, drcEn, 2);
            break;
    	}           
    }    
    else
    {
		drcEn[0] = 0x00000000;
		drcEn[1] = 0x00800000;

        switch(LimOP->Ch){
        case 0: I2CWriteMultiWord(TAS_SLA0, Limiter1_ae + 5, drcEn, 2);   break;
        case 1: I2CWriteMultiWord(TAS_SLA0, Limiter2_ae + 5, drcEn, 2); break;
        case 2: I2CWriteMultiWord(TAS_SLA0, Limiter3_ae + 5, drcEn, 2);   break;
        case 3: I2CWriteMultiWord(TAS_SLA0, Limiter4_ae + 5, drcEn, 2); break;
        case 4: I2CWriteMultiWord(TAS_SLA0, Limiter5_ae + 5, drcEn, 2);   break;
        case 5: I2CWriteMultiWord(TAS_SLA0, Limiter6_ae + 5, drcEn, 2); break;
        }
    }
    
	return ret;
}



/*
***************************************************************************************************
**                                          Dsp3DMusicEn()
**	功能描述：音乐3D效果。
**	参  数  ：en
**	返回值  ：无
***************************************************************************************************
*/
int Dsp3DMusicEn(uint8 en, uint8_t Ch)
{
	char ret=0;
    float mixer[4] = {0};
#if DEBUG
    printf("-->%s> en=%d,Ch=%d\n",__FUNCTION__,en,Ch);
#endif    

    rep3DEn(Ch, en);

	if (1 == en ) {   
	    memset(mixer,0,4);
        mixer[1] = mixer[2] = mixer[3] = 1.0;
	} else {   
	    memset(mixer,0,4);
        mixer[0] = 1.0;
	}
    
    if (Ch) {
        DspMixerSet4Ch(0, 3, mixer); 
    } else {
        DspMixerSet4Ch(0, 2, mixer); 
    }
	return ret;
}

int Dsp3DMusicMix(float mixer[], uint8_t Ch )
{
#if DEBUG
        printf("-->%s> Ch=%d,mix[]=%f,%f,%f,%f\n",__FUNCTION__,
        Ch,mixer[0],mixer[1],mixer[2],mixer[3]);
#endif 

    rep3DMix(Ch, mixer);


    if (Ch) {
        DspMixerSet4Ch(0, 3, mixer); 
    } else {
        DspMixerSet4Ch(0, 2, mixer); 
    }
}


/*********************************************************************************************************
** Function name:       Dsp3DMusicDelay
** Descriptions:        输出通道延时控制
** input parameters:    Ch 输出通道 delay 延时结构体指针
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int Dsp3DMusicDelay(DLY_STR delay, uint32_t Ch)
{
	uint32 delayVal[1];
	uint32 delayTmp;
	uint32 en[1] = { 1 };
	char ret = 0;
#if DEBUG
        printf("-->%s> Ch=%d,Dly=%f,en=%d\n",__FUNCTION__,
        Ch,delay.Dly,delay.en);
#endif

    rep3DDly(Ch, &delay);


	if (1 == delay.en)
	{
		if (delay.Dly >= (fp32)122.50)
		{
			delayTmp = 5880;
		}
		else if (delay.Dly >= 0)
		{
			delayTmp = MathRound(48 * delay.Dly, 0);
		}
		else
		{
			delayTmp = 0;
		}
	}
	else
	{
		delayTmp = 0;
	}

	switch (Ch)
	{
	case 0:
        I2CReadMultiWord(TAS_SLA0, Delay7, delayVal, 1);
        //printf("%x\n",delayVal[0]);
        
        delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16);
        //delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        
        I2CWriteMultiWord(TAS_SLA0, Delay7, delayVal, 1);			// Delay Node 1

		ret |= I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);


		break;
	case 1:
        I2CReadMultiWord(TAS_SLA0, Delay8, delayVal, 1);	
        //printf("%x\n",delayVal[0]);
        
        delayVal[0] = (delayVal[0] & 0xffff0000) | (delayTmp);
        //delayVal[0] = (delayVal[0] & 0x0000ffff)|(delayTmp<<16);
        
		ret = I2CWriteMultiWord(TAS_SLA0, Delay8, delayVal, 1);			// Delay Node 1	
		ret |= I2CWriteMultiWord(TAS_SLA0, Delay_Update, en, 1);

		break;
	default:
		break;
	}
	return ret;
}

/*
***************************************************************************************************
**
**                                          DspMixer3DMusMultIn()
**
**
**	功能描述：3Dmusic中的路由选择多输入。
**
**	参  数  ：Ch  通道的索引 Ch={0,1}
**			LinType 连接3DMusic通道的类型，LinType=0时,3D关闭，直通开启
**			LinType=1时，延时、第一路、第二路，单个输出，LinType=2时，
**			延时和第一路、延时和第二路、第一路和第二路组合，两个一起输出，LinType=3时，延时、第一路、第二路一起输出
**			In  输出的通道类型，当LinType=1时，In=1，为延时输出，In=2，为第一路输出，In=3，为第二路输出；
**			当LinType=2时，In=1，为延时和第一路混音输出，In=2，为延时和第二路混音输出，In=3，为第一路和第二路混音输出，
**			当LinType=3时，In=1，为延时、第一路、第二路一起混音输出
**			mixer 为路由系数，暂定各路由系数都相同，以后需要再改 
**
**	返回值  ：无
**
**
***************************************************************************************************
*/
int DspMixer3DMusMultIn(uint8 Ch, uint8 LinType, uint8 In, float *mix)
{char ret = 0;
	uint32 mix_val[4] = { 0,0,0,0 };
	uint8  mix_i2c_addr;
	float mixer0,mixer,mixer1,mixer2;
	mixer0 = mix[0];
	mixer = mix[1];
	mixer1 = mix[2];
	mixer2 = mix[3];
	


	switch(Ch)
	{
	case 0:
		{
			mix_i2c_addr = Mix4Ch_7;
			switch(LinType)
			{
				case 0:
					ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
					mix_val[1]=mix_val[2]=mix_val[3]=DAPFloatTo5P23(0.0);
					mix_val[0] = DAPFloatTo5P23(mixer0);
					ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
					break;


				
			case 1:
				{
					switch(In)
					{
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 3:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				}
				break;
			case 2:
				switch(In)
					{
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 3:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;
			case 3:
				switch(In)
					{
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;

			}
		}
		break;
	case 1:
		mix_i2c_addr = Mix4Ch_9;
		{
			switch(LinType)
			{
			case 0:
				ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
				mix_val[1]=mix_val[2]=mix_val[3]=DAPFloatTo5P23(0.0);
				mix_val[0] = DAPFloatTo5P23(mixer0);
				ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
				break;
			case 1:
				{
					switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				}
				break;
			case 2:
				switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[3] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;
			case 3:
				switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					default:
						break;

					}
				break;

			}
		}
		break;
	}

//	ret = I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
	return ret;
}


/*
***************************************************************************************************
**                                          Dsp3DMusicOP()
**	功能描述：音乐3D效果。
**	参  数  ：en        Music3DOp_STR* Music3DOp1
**	返回值  ：无
***************************************************************************************************
*/
int Dsp3DMusicOP(Music3DOp_STR *Music3DOp1)
{
	//uint32 selbuf[1] = { 0 };
	float mixer[4]={0};
	char ret=0;

    mixer[0] = Music3DOp1->mix[0];
    mixer[1] = Music3DOp1->mix[1];
    mixer[2] = Music3DOp1->mix[2];

#if DEBUG
    Music3DOp_STR *p = Music3DOp1;
    printf("-->%s> Dly:%f,en:%d,mix[0]:%f,mix[1]:%f,mix[2]:%f,en:%d,Ch=%d\n",
        __FUNCTION__,p->delay.Dly,p->delay.en,p->mix[0],p->mix[1],p->mix[2],
        p->en,p->Ch);
#endif

	if (1 == Music3DOp1->en )
	{
		if (0 == Music3DOp1->Ch)
		{
		    Dsp3DMusicEn(Music3DOp1->en, Music3DOp1->Ch);
			Dsp3DMusicDelay(Music3DOp1->delay, Music3DOp1->Ch);
            Dsp3DMusicMix(mixer,Music3DOp1->Ch);
		}
		else if (1 == Music3DOp1->Ch )
		{
		    Dsp3DMusicEn(Music3DOp1->en, Music3DOp1->Ch);
			Dsp3DMusicDelay(Music3DOp1->delay, Music3DOp1->Ch);
            Dsp3DMusicMix(mixer,Music3DOp1->Ch);
		}
	}
	else
	{
		Dsp3DMusicEn(Music3DOp1->en, Music3DOp1->Ch);
	}
	return ret;
}


/*********************************************************************************************************
** Function name:       DspMixerSet4Ch_3DMusic
** Descriptions:        路由控制，Mix4Ch_11，Mix4Ch_12模块
** input parameters:    in Mix4Ch模块的输入端通道 select 主通道标号，select={0,1}；  mixer 比例值
**						in =0，mixer不等于0时直通开启，否则3D开启
select 0-.Mix4Ch_7,1-.Mix4Ch_9,；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspMixerSet4Ch_3DMusic(uint32_t select, Mix4Ch_STR *Mix4ChNo)
{char ret = 0;
	uint32 mix_val[4] = { 0,0,0,0 };
	uint8  mix_i2c_addr=0;
	float mixer;
	mixer = Mix4ChNo->mix;
	//mix_i2c_addr = Mix4Ch_11;


	switch (select)
	{
	case 0:
		mix_i2c_addr = Mix4Ch_7;
		switch (Mix4ChNo->in)
		{
		case 0:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		case 1:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		case 2:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
		case 3:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		default:
			break;
		}
		break;

	case 1:
		mix_i2c_addr = Mix4Ch_9;
		switch (Mix4ChNo->in)
		{
		case 0:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[0] = DAPFloatTo5P23(mixer);
			break;
		case 1:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[1] = DAPFloatTo5P23(mixer);
			break;
		case 2:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[2] = DAPFloatTo5P23(mixer);
		case 3:
			
			ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
			mix_val[3] = DAPFloatTo5P23(mixer);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
	return ret;
}



/*
***************************************************************************************************
**                                         DspSctHp()
**	功能描述：椭圆逼近高通滤波器设置
**	参  数  ：hpf.Fc   	中心频率
**			  hpf.Type 	高通滤波器类型
**			  hpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspSctHp(uint8 Ch, HLPF_STR hpf)
{
#if DEBUG
    printf("-->%s> ch=%d,fc=%d,type=%d,en=%d\n",__FUNCTION__,Ch,
        hpf.Fc,hpf.Type,hpf.en);
#endif

    repSctHLpf(Ch, 0,&hpf);

	uint32 hpfCoef[20];
	
	char ret =0;

	if (1 == hpf.en)
	{
		switch (hpf.Type)
		{
		case BW_06: DAPBesAndButHPF(1, hpf.Fc, hpfCoef, 0); break;
		case BW_12: DAPBesAndButHPF(2, hpf.Fc, hpfCoef, 0); break;
		case BL_06:	DAPBesAndButHPF(1, hpf.Fc, hpfCoef, 1); break;
		case BW_24: DAPBesAndButHPF(4, hpf.Fc, hpfCoef, 0); break;
		case BL_12:	DAPBesAndButHPF(2, hpf.Fc, hpfCoef, 1); break;
		case BL_24:	DAPBesAndButHPF(4, hpf.Fc, hpfCoef, 1); break;
		case LK_12:	DAPLinkwitzHPF(2, hpf.Fc, hpfCoef);    break;
		case LK_24:	DAPLinkwitzHPF(4, hpf.Fc, hpfCoef);    break;
		default:
			hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
			hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
			hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
			hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
			hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;
			break;
		}
	}
	else
	{
		hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
		hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
		hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
		hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
		hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;
	}
	
	switch (Ch)
	{
	case 0:   
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_HP1_Ins1, &hpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_HP1_Ins2, &hpfCoef[5], 5);
        break;
    case 1:
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_HP2_Ins1, &hpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_HP2_Ins2, &hpfCoef[5], 5);
        break;
	default:
		break;
	}

	//	DAPDelay(DLY_1MS*25);		
	return ret;
}


/*********************************************************************************************************
** Function name:       DspSctBp
** Descriptions:        声音补偿中的中频段
** input parameters:    Bpf 低通结体指针，Ch 通道的索引
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
#define lpfc 1
int DspSctBp(uint8 Ch, BPF_STR bpf)
{
	uint32 lpfCoef[20];
	uint32 hpfCoef[20];
	char ret = 0;
    
#if DEBUG
        printf("-->%s> ch=%d,fp=%d,fs=%d,type=%d,en=%d\n",__FUNCTION__,Ch,
            bpf.Fp,bpf.Fs,bpf.Type,bpf.en);
#endif

    repSctBpf(Ch, &bpf);


	if (1 == bpf.en)
	{
		switch (bpf.Type)
		{
		case BW_06: DAPBesAndButHPF(1, bpf.Fp, hpfCoef, 0);
                    #if lpfc
			        DAPBesAndButLPF(1, bpf.Fs, lpfCoef, 0); 
                    #endif
                    break;
		case BW_12: DAPBesAndButHPF(2, bpf.Fp, hpfCoef, 0);
                    #if lpfc
			        DAPBesAndButLPF(2, bpf.Fs, lpfCoef, 0); 
                    #endif
                    break;
		case BL_06:	DAPBesAndButHPF(1, bpf.Fp, hpfCoef, 1);
                    #if lpfc
			        DAPBesAndButLPF(1, bpf.Fs, lpfCoef, 1);
                    #endif
                    break;
		case BW_24: DAPBesAndButHPF(4, bpf.Fp, hpfCoef, 0);
                    #if lpfc
			        DAPBesAndButLPF(4, bpf.Fs, lpfCoef, 0); 
                    #endif
                    break;
		case BL_12:	DAPBesAndButHPF(2, bpf.Fp, hpfCoef, 1);
                    #if lpfc
			        DAPBesAndButLPF(2, bpf.Fs, lpfCoef, 1); 
                    #endif
                    break;
		case BL_24:	DAPBesAndButHPF(4, bpf.Fp, hpfCoef, 1);
                    #if lpfc
			        DAPBesAndButLPF(4, bpf.Fs, lpfCoef, 1); 
                    #endif
                    break;
		case LK_12:	DAPLinkwitzHPF(2, bpf.Fp, hpfCoef);
                    #if lpfc
			        DAPLinkwitzLPF(2, bpf.Fs, lpfCoef);
                    #endif
                    break;
		case LK_24:	DAPLinkwitzHPF(4, bpf.Fp, hpfCoef);
                    #if lpfc
			        DAPLinkwitzLPF(4, bpf.Fs, lpfCoef); 
                    #endif
                    break;
		default:
			hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
			hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
			hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
			hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
			hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;

			lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
			lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
			lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
			lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
			lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
			break;
		}
	}
	else
	{
		hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
		hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
		hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
		hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
		hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;

		lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
		lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
		lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
		lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
		lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
	}
    
	switch (Ch)
	{
	case 0:
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_BP1_Ins1, &hpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Ins2, &hpfCoef[5], 5);
    
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP1_Ins3, &lpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP1_Ins4, &lpfCoef[5], 5);
        break;
    case 1:
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Ins1, &hpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Ins2, &hpfCoef[5], 5);
    
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Ins3, &lpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Ins4, &lpfCoef[5], 5);
		break;
	default:
		break;
	}
	return ret;
}


/*********************************************************************************************************
** Function name:       DspSctLp
** Descriptions:        声音补偿中的低频段
** input parameters:    hpf 低通结体指针，Ch 通道的索引
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspSctLp(uint8 Ch, HLPF_STR lpf)
{
	uint32 lpfCoef[20];
	char ret = 0;
#if DEBUG
    printf("-->%s> ch=%d,fc=%d,type=%d,en=%d\n",__FUNCTION__,Ch,
        lpf.Fc,lpf.Type,lpf.en);
#endif

    repSctHLpf(Ch, 2,&lpf);


	if (1 == lpf.en)
	{
		switch (lpf.Type)
		{
		case BW_06: DAPBesAndButLPF(1, lpf.Fc, lpfCoef, 0); break;
		case BW_12: DAPBesAndButLPF(2, lpf.Fc, lpfCoef, 0); break;
			//	case BW_18: DAPBesAndButLPF(3, lpf.Fc, lpfCoef, 0);break;
		case BW_24: DAPBesAndButLPF(4, lpf.Fc, lpfCoef, 0); break;
			//	case BW_36: DAPBesAndButLPF(6, lpf.Fc, lpfCoef, 0);break;
			//	case BW_48: DAPBesAndButLPF(8, lpf.Fc, lpfCoef, 0);break;
		case BL_06:	DAPBesAndButLPF(1, lpf.Fc, lpfCoef, 1); break;
		case BL_12:	DAPBesAndButLPF(2, lpf.Fc, lpfCoef, 1); break;
			//	case BL_18:	DAPBesAndButLPF(3, lpf.Fc, lpfCoef, 1);break;
		case BL_24:	DAPBesAndButLPF(4, lpf.Fc, lpfCoef, 1); break;
			//	case BL_36:	DAPBesAndButLPF(6, lpf.Fc, lpfCoef, 1);break;
			//	case BL_48:	DAPBesAndButLPF(8, lpf.Fc, lpfCoef, 1);break;
		case LK_12:	DAPLinkwitzLPF(2, lpf.Fc, lpfCoef);    break;
		case LK_24:	DAPLinkwitzLPF(4, lpf.Fc, lpfCoef);    break;
			//	case LK_36:	DAPLinkwitzLPF(6, lpf.Fc, lpfCoef);    break;
			//	case LK_48:	DAPLinkwitzLPF(8, lpf.Fc, lpfCoef);    break;	
		default:
			lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
			lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
			lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
			lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
			lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
			break;
		}
	}
	else
	{
		lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
		lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
		lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
		lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
		lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
	}

	switch (Ch)
	{
	case 0:
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_LP1_Ins1, &lpfCoef[0], 5);
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_LP1_Ins2, &lpfCoef[5], 5);
        //  I2CWriteMultiWord(TAS_SLA0, SCT_LP_Ins1+2, &lpfCoef[10], 5);
        //  I2CWriteMultiWord(TAS_SLA0, SCT_LP_Ins1+3, &lpfCoef[15], 5);
        break;
    case 1:
        ret |= I2CWriteMultiWord(TAS_SLA0, SCT_LP2_Ins1, &lpfCoef[0], 5);
        ret = I2CWriteMultiWord(TAS_SLA0, SCT_LP2_Ins2, &lpfCoef[5], 5);
        //  I2CWriteMultiWord(TAS_SLA0, SCT_LP_1_Ins1+2, &lpfCoef[10], 5);
        //  I2CWriteMultiWord(TAS_SLA0, SCT_LP_1_Ins1+3, &lpfCoef[15], 5);
        break;
	default: break;

	}

	//I2CWriteMultiWord(TAS_SLA0, OUT4_SUB_LPF_EN_I2C_ADDR, &bpState, 1);
	return ret;
}


/*
***************************************************************************************************
**                                          DspSCTVolDepth     v2.0
**	功能描述：声音补偿中的深度。
**	参  数  ：Ch 通道数，Ch={0,1};SCTType  SCT的类型（HP，LP,BP）；VolDepth 深度
**	返回值  ：无
***************************************************************************************************
*/
#if 0 //V2_0
int DspSCTVolDepth_0(uint8 Ch,uint8 SCTType,float VolDepth)
{
	char ret = 0;
	uint32_t volume;
	volume = DAPFloatTo5P23(pow(10.0, VolDepth*0.05));
	switch(Ch) {
    case 0:
    {
        switch(SCTType) {
        case 0:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_HP1_Vol, &volume, 1);
            break;
        case 1:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_BP1_Vol, &volume, 1);
            break;
        case 2:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_LP1_Vol, &volume, 1);
            break;
        default: break;
        }
    }
    break;
    case 1:
    {
        switch(SCTType) {
        case 0:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_HP2_Vol, &volume, 1);
            break;
        case 1:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_BP2_Vol, &volume, 1);
            break;
        case 2:
            ret = I2CWriteMultiWord(TAS_SLA0, SCT_LP2_Vol, &volume, 1);
            break;
        default:
            break;
        }
    }
    break;
   }
	return ret;
}
#endif

//v2.1
int DspSCTVolDepth(uint8 Ch,uint8 SCTType,float VolDepth)
{
	char ret = 0;
	uint32_t volume;
	volume = DAPFloatTo5P23(pow(10.0, VolDepth*0.05));

    uint8 mix_i2c_addr0 = Mix4Ch_1;
	uint8 mix_i2c_addr1 = Mix4Ch_2;
    uint32_t mixer[4]={0};
            
	switch(Ch) {
    case 0:
    {
        memset(mixer,0,4);
        I2CReadMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        //printf("0:mixer=%x,%x,%x,%x\n",mixer[0],mixer[1],mixer[2],mixer[3]);
        if (mixer[SCTType+1] == 0) break;
        switch(SCTType) {
        case 0: mixer[1]= volume; break;
        case 1: mixer[2]= volume; break;
        case 2: mixer[3]= volume; break;
        default: break;
        }
    }
    I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4); 
    break;
    case 1:
    {   
        memset(mixer,0,4);     
        I2CReadMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);
        //printf("1:mixer=%x,%x,%x,%x\n",mixer[0],mixer[1],mixer[2],mixer[3]);
        if (mixer[SCTType+1] == 0) break;
        switch(SCTType) {
        case 0: mixer[1]= volume; break;
        case 1: mixer[2]= volume; break;
        case 2: mixer[3]= volume; break;
        default: break;
        }
    }  
    I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4); 
    break;
   }
	return ret;
}


void DspSetSctDepth(uint8_t type, float VolDepth, uint8_t Ch)
{
#if DEBUG
    printf("-->%s> type=%d,vol=%f,ch=%d\n",__FUNCTION__,
    	type,VolDepth,Ch);
#endif

    repSctDepth(Ch,type,VolDepth);


    if (0 == Ch )
    {      
        if(0 == type) {          //hp
            DspSCTVolDepth(Ch, 0, VolDepth);
        } else if (1 == type) {  //bp
            DspSCTVolDepth(Ch, 1, VolDepth);
        } else if (2 == type) {  //lp
            DspSCTVolDepth(Ch, 2, VolDepth);
        }
	}
	else if (1 == Ch )
	{
        if(0 == type) {          //hp
            DspSCTVolDepth(Ch, 0, VolDepth);
        } else if (1 == type) {  //bp
            DspSCTVolDepth(Ch, 1, VolDepth);
        } else if (2 == type) {  //lp
            DspSCTVolDepth(Ch, 2, VolDepth);
        }
	}

}

/*
***************************************************************************************************
**                                          DspAGC()
**	功能描述：AGC动态范围控制。
**
**	参  数  ：SCT_ChCh             音频通道选择
**			  agc.T1,T2       起控电平
**            agc.k0,k1,k2    斜率
**            agc.O1,O2       电平偏移量
**            agc.Attack      起控时间
**            agc.Release       释放时间
**            agc.en          功能使能标志
**	返回值  ：无
***************************************************************************************************
*/
#define	AGC_GAIN_SUB	51.9224

int DspAGC(uint8 SCT_Ch, DRC_STR AGC)
{
	fp64 	ad;
	fp64	aa;
	fp32    k2;
	uint32 	agcEn[2];
	uint32	agcTimeConst[4];
	uint32	agcThreshold[4];
	uint32	agcOffset[4];
	uint32	agcSlope[3];
	char ret = 0;

#if DEBUG
    printf("-->%s> T2=%f,k2=%f,Attack=%f,Release=%f,en=%d,SCT_Ch=%d\n",__FUNCTION__,
        AGC.T2,AGC.k2,AGC.Attack,AGC.Release,AGC.en,SCT_Ch);
#endif

	if (AGC.en)
	{   
	    agcEn[0] = 0x00800000;
		agcEn[1] = 0x00000000;
	}
	else
	{
		agcEn[0] = 0x00000000;
		agcEn[1] = 0x00800000;
	}

	aa = pow(2.7182818, -1 / (48 * (fp64)AGC.Attack));
	ad = pow(2.7182818, -1 / (48 * (fp64)AGC.Release));

	agcTimeConst[0] = DAPFloatTo5P23(1 - aa);
	agcTimeConst[1] = DAPFloatTo5P23(aa);
	agcTimeConst[2] = DAPFloatTo5P23(1 - ad);
	agcTimeConst[3] = DAPFloatTo5P23(ad);


	agcThreshold[0] = 0x00000000;
	agcThreshold[1] = 0x0FF055DB;
	//	    DAPFloatTo25P23((-140-AGC_GAIN_SUB)/-6.0206, &agcThreshold[0]);
	DAPFloatTo25P23((AGC.T2 + DRC_THR_OFFSET - AGC_GAIN_SUB) / -6.0206, &agcThreshold[2]);
	agcOffset[0] = 0x00000000;
	agcOffset[1] = 0x02000000;
	agcOffset[2] = 0x00000000;
	agcOffset[3] = 0x02000000;
	//	    DAPFloatTo25P23((0+24.0824)/6.0206, &agcOffset[0]);
	//	    DAPFloatTo25P23((0+24.0824)/6.0206, &agcOffset[2]);

	agcSlope[0] = 0x00000000;//DAPFloatTo5P23(0);
	agcSlope[1] = 0x00000000;//DAPFloatTo5P23(0);

	k2 = 1 / AGC.k2 - 1;
	if (k2 < -0.966667)
	{
		k2 = -1;
	}
	agcSlope[2] = DAPFloatTo5P23(k2);

	switch (SCT_Ch)
	{
    case 0:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, AGC_H1_ae + 5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, AGC_H1_ae + 1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, AGC_H1_ae + 2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, AGC_H1_ae+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, AGC_H1_ae + 4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0,AGC_H1_enable, agcEn, 2);
        }
        break;
    case 1:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L1_ae)+5, agcEn, 2);
        }
        break;
    case 2:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B1_ae)+5, agcEn, 2);
        }
        break;
    case 3:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_H2_ae)+5, agcEn, 2);
        }
        break;
    
    case 4:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_L2_ae)+5, agcEn, 2);
        }
        break;
    case 5:
        if (AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+5, agcEn, 2);
        }
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+1, agcThreshold, 4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+2, agcSlope, 3);
               I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+3, agcOffset,    4);
        ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+4, agcTimeConst, 4);
    
        if (!AGC.en)
        {
            ret |= I2CWriteMultiWord(TAS_SLA0, (AGC_B2_ae)+5, agcEn, 2);
        }
        break;
    
    default:
        break;

	}

	return ret;
}


//void DspSetSctAgc(uint8_t type, uint8_t en, fp32 T2, fp32 k2, fp32 attack, fp32 release, uint8_t Ch)
void DspSetSctAgc(uint8_t type, DRC_STR agc, uint8_t Ch)
{
  /*  DRC_STR agc;
    agc.T2 = T2;
    agc.k2 = k2;
    agc.Attack = attack;
    agc.Release = release;
    agc.en = en;*/
    
#if DEBUG
    printf("-->%s> type=%d,T2=%f,k2=%f,Attack=%f,Release=%f,en=%d,ch=%d\n",__FUNCTION__,type,
        agc.T2,agc.k2,agc.Attack,agc.Release,agc.en,Ch);
#endif

    repSctAgc(Ch, type, &agc);


    if (Ch) {  
        if (0 == type) {  //hp
            DspAGC(3, agc);
        } else if (1 == type) { //bp
            DspAGC(5, agc);
        } else if (2 == type) { //lp
            DspAGC(4, agc);
        }
    } else {
        if (0 == type) {
            DspAGC(0, agc);
        } else if (1 == type) {
            DspAGC(2, agc);
        } else if (2 == type) {
            DspAGC(1, agc);
        }  
    } 
}

/**
mixer[0,1,2,3]: 0=直通,1=hp, 2=bp, 3=lp

**/
//void DspSctEn(float mixer[], uint8_t Ch)
void DspSctEn(uint8_t en, uint8_t Ch)
{
#if DEBUG
    printf("-->%s> ch=%d,en=%d\n",__FUNCTION__, Ch,en);
#endif

    repSctEn(Ch, en);

	float mixer[4] = {0};
	if (en) {
		mixer[0] = 0.0; mixer[1]=mixer[2]=mixer[3] = 1.0;
	} else {
		mixer[0] = 1.0; mixer[1]=mixer[2]=mixer[3] = 0.0;
	}

	if (Ch) {
		DspMixerSet4Ch(0, 1, mixer); 
	} else {
		DspMixerSet4Ch(0, 0, mixer); 
	}

}

/**
*             DspSctMix()
* This is a detail description.
* @mixer       路由系数
* @Ch     通道
* @par 标识符
* @par 修改日志
*      XXX于2014-10-4创建
*/
void DspSctMix(float mixer[], uint8_t Ch)
{
#if DEBUG
	printf("-->%s> ch=%d,mix=%f,%f,%f,%f\n",__FUNCTION__,
		Ch,mixer[0],mixer[1],mixer[2],mixer[3]);
#endif

    repSctMix(Ch, mixer);

	if (Ch) {
		DspMixerSet4Ch(0, 1, mixer); 
	} else {
		DspMixerSet4Ch(0, 0, mixer); 
	}
}

/*
***************************************************************************************************
**
**                                          DspSCTMixMulIn()
**
**
**	功能描述：声音补偿中的路由选择多输入。
**
**	参  数  ：Ch  通道的索引 Ch={0,1}
**			LinType 连接SCT通道的类型，LinType=1时，高、中、低音，单个输出，LinType=2时，
**			高中、高低、中低组合，两个一起混音输出，LinType=3时，高中低一起混音输出
**			In  输出的通道类型，当LinType=1时，In=0，为高音输出，In=1，为中输出，In=2，为低输出；
**			当LinType=2时，In=0，为高中输出，In=1，为高低音输出，In=2，为中低音输出，
**			当LinType=3时，In=0，为高中低音一起路由输出
**			mix 为路由系数， 
**
**	返回值  ：无
**
**
***************************************************************************************************
*/
int DspSCTMixMulIn(uint8 Ch, uint8 LinType, uint8 In, float *mix)
{
	char ret = 0;
	uint32 mix_val[4] = { 0 };
	uint8  mix_i2c_addr;
	//uint8  mix_i2c_addr1;
	//uint8  mix_i2c_addr2;
	float mixer,mixer1,mixer2;

	mixer=mix[0],mixer1=mix[1],mixer2=mix[2];

	switch(Ch)
	{
	case 0: //通道0
		{
			mix_i2c_addr = Mix4Ch_1;
			switch(LinType)
			{
			case 1: //单个输出
				{
					switch(In)
					{
					case 0:   //高音输出
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:  //中输出
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:  //低输出
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				}
				break;
			case 2:     //两个组合一起混音输出
				switch(In)
					{
					case 0:   //高中
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:    //高低
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:   //中低组合
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;
			case 3:      //高中低一起混音输出
				switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;

			}
		}
		break;
	case 1: //通道1
		mix_i2c_addr = Mix4Ch_2;
		{
			switch(LinType)
			{
			case 1:
				{
					switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				}
				break;
			case 2:
				switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 1:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[3] = DAPFloatTo5P23(mixer1);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;
					case 2:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;
			case 3:
				switch(In)
					{
					case 0:
						ret = I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						mix_val[1] = DAPFloatTo5P23(mixer);
						mix_val[2] = DAPFloatTo5P23(mixer1);
						mix_val[3] = DAPFloatTo5P23(mixer2);
						ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, mix_val, 4);
						break;

					}
				break;

			}
		}
		break;
	}
	//mix_i2c_addr = Mix4Ch_11;
	return ret;
}



/*
***************************************************************************************************
**                                          DspSCTOP()
**	功能描述：声音补偿，SCT。
**	参  数  ：       SCTOP_STR* SCTOP1
**	返回值  ：无
***************************************************************************************************
*/
int DspSCTOP( SCTOP_STR *SCTOP1)
{
	float mixer[4]={0};
	char ret=0;

#if DEBUG
        printf("-->%s> \n",__FUNCTION__);
#endif


	if (1 == SCTOP1->en)
	{
		if (0 == SCTOP1->Ch )
		{
			if (0 == SCTOP1->Type)   //hp
			{
				memset(mixer,0,4);
                mixer[1]=1.0;
				ret = DspMixerSet4Ch(0,0, mixer);
				DspSctHp(SCTOP1->Ch, SCTOP1->hpf);
				DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				DspAGC(0, SCTOP1->AGChp);
			}

			if (1 == SCTOP1->Type)  //bp
			{
				memset(mixer,0,4);
                mixer[2]=1.0;
				ret = DspMixerSet4Ch(0,0, mixer);
				DspSctBp(SCTOP1->Ch, SCTOP1->bpf);
				DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				DspAGC(2, SCTOP1->AGCbp);
			}

			if (2 == SCTOP1->Type)  //lp
			{
			    memset(mixer,0,4);
                mixer[3]=1.0;
				ret = DspMixerSet4Ch(0,0, mixer);
				ret |= DspSctLp(SCTOP1->Ch, SCTOP1->lpf);
				ret |= DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				ret |= DspAGC(1, SCTOP1->AGClp);
			}

			//DspMixerSet4Ch(1, 4, 1.0);
			//DspMixerSet4Ch(1, 4, 1.0);
			DspSCTMixMulIn(SCTOP1->Ch, (SCTOP1->LinType&0xf0)>>4, SCTOP1->LinType&0x0f, SCTOP1->mix);
		}
		else if (1 == SCTOP1->Ch )
		{
			//DspMixerSet4Ch(1, 5, 1.0);
			if (0 == SCTOP1->Type)
			{
			    memset(mixer,0,4);
                mixer[1]=1.0;
				DspMixerSet4Ch(0,1, mixer);
				DspSctHp(SCTOP1->Ch, SCTOP1->hpf);
				DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				DspAGC(3, SCTOP1->AGChp);
			}

			if (1 == SCTOP1->Type )
			{
				memset(mixer,0,4);
                mixer[2]=1.0;
				DspMixerSet4Ch(0,1, mixer);
				DspSctBp(SCTOP1->Ch, SCTOP1->bpf);
				DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				DspAGC(5, SCTOP1->AGCbp);
			}

			if (2 == SCTOP1->Type)
			{
				memset(mixer,0,4);
                mixer[3]=1.0;
				DspMixerSet4Ch(0,1, mixer);
				DspSctLp(SCTOP1->Ch, SCTOP1->lpf);
				DspSCTVolDepth(SCTOP1->Ch, SCTOP1->Type, SCTOP1->VolDepth);
				DspAGC(4, SCTOP1->AGClp);
			}

			DspSCTMixMulIn(SCTOP1->Ch, (SCTOP1->LinType&0xf0)>>4, SCTOP1->LinType&0x0f, SCTOP1->mix);
		}
	}
	else
	{
        memset(mixer,0,4);
        mixer[0]=1.0;
        if (0 == SCTOP1->Ch )
		    DspMixerSet4Ch(0,0, mixer);
        else
            DspMixerSet4Ch(0,1, mixer);
	}
	return ret;
}





/*
***************************************************************************************************
**                                         DspACHBp_HP()
**	功能描述：椭圆逼近高通滤波器设置
**	参  数  ：hpf.Fc   	中心频率
**			  hpf.Type 	高通滤波器类型
**			  hpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**			  Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspACHBp_HP(CHanHLPF_STR *ChHP)
{
	char ret=0;
	uint32 hpfCoef[20];
#if DEBUG
    printf("--%s> Fc:%d,Type:%d,en:%d,Ch=%d\n",__FUNCTION__,
          ChHP->xpf.Fc,ChHP->xpf.Type,ChHP->xpf.en,ChHP->Ch);
#endif

    repHPF(ChHP);

	if (1 == ChHP->xpf.en )
	{

		switch (ChHP->xpf.Type)
		{
		case BW_06: DAPBesAndButHPF(1, ChHP->xpf.Fc, hpfCoef, 0); break;
		case BW_12: DAPBesAndButHPF(2, ChHP->xpf.Fc, hpfCoef, 0); break;
		case BL_06:	DAPBesAndButHPF(1, ChHP->xpf.Fc, hpfCoef, 1); break;
		case BW_24: DAPBesAndButHPF(4, ChHP->xpf.Fc, hpfCoef, 0); break;
		case BL_12:	DAPBesAndButHPF(2, ChHP->xpf.Fc, hpfCoef, 1); break;
		case BL_24:	DAPBesAndButHPF(4, ChHP->xpf.Fc, hpfCoef, 1); break;
		case LK_12:	DAPLinkwitzHPF(2, ChHP->xpf.Fc, hpfCoef);    break;
		case LK_24:	DAPLinkwitzHPF(4, ChHP->xpf.Fc, hpfCoef);    break;
		default:
			hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
			hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
			hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
			hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
			hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;
			break;
		}

	}
	else
	{
		hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
		hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
		hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
		hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
		hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;
	}

	switch (ChHP->Ch)
	{
	case 0:
		ret = I2CWriteMultiWord(TAS_SLA0, BP1_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP1_Ins2, &hpfCoef[5], 5);
		break;

	case 1:
		ret = I2CWriteMultiWord(TAS_SLA0, BP2_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP2_Ins2, &hpfCoef[5], 5);
		break;

	case 2:
		ret = I2CWriteMultiWord(TAS_SLA0, BP3_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP3_Ins2, &hpfCoef[5], 5);
		break;

	case 3:
		ret = I2CWriteMultiWord(TAS_SLA0, BP4_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP4_Ins2, &hpfCoef[5], 5);
		break;
	case 4:
		ret = I2CWriteMultiWord(TAS_SLA0, BP5_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP5_Ins2, &hpfCoef[5], 5);
		break;

	case 5:
		ret = I2CWriteMultiWord(TAS_SLA0, BP6_Ins1, &hpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP6_Ins2, &hpfCoef[5], 5);
		break;

	default:
		break;
	}
		
	return ret;
}

/*
***************************************************************************************************
**                                         DspACHBp_LP()
**	功能描述：椭圆逼近低通滤波器设置
**
**	参  数  ：hpf.Fc   	中心频率
**			  xpf.Type 	高通滤波器类型
**			  xpf.en	滤波器使能
**			  Ch      	通道选择
**			  grp      	编组
**           Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
**	返回值  ：无
**	备  注  ：从对应的滤波器算法等到系数，用I2C把相关的系数送到TAS3108即完成滤波器的设置。
***************************************************************************************************
*/
int DspACHBp_LP(CHanHLPF_STR *ChLP)
{
	char ret=0;
	uint32 lpfCoef[20];

#if DEBUG
    printf("-->%s> Fc:%d,Type:%d,en:%d,Ch=%d\n",__FUNCTION__,
         ChLP->xpf.Fc,ChLP->xpf.Type,ChLP->xpf.en,ChLP->Ch);
#endif

    repLPF(ChLP);


	if (1 == ChLP->xpf.en )
	{
		switch (ChLP->xpf.Type)
		{
		case BW_06: DAPBesAndButLPF(1, ChLP->xpf.Fc, lpfCoef, 0); break;
		case BW_12: DAPBesAndButLPF(2, ChLP->xpf.Fc, lpfCoef, 0); break;
		case BW_24: DAPBesAndButLPF(4, ChLP->xpf.Fc, lpfCoef, 0); break;
		case BL_06:	DAPBesAndButLPF(1, ChLP->xpf.Fc, lpfCoef, 1); break;
		case BL_12:	DAPBesAndButLPF(2, ChLP->xpf.Fc, lpfCoef, 1); break;
		case BL_24:	DAPBesAndButLPF(4, ChLP->xpf.Fc, lpfCoef, 1); break;
		case LK_12:	DAPLinkwitzLPF(2, ChLP->xpf.Fc, lpfCoef);    break;
		case LK_24:	DAPLinkwitzLPF(4, ChLP->xpf.Fc, lpfCoef);    break;

		default:
			lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
			lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
			lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
			lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
			lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
			break;
		}

	}

	else
	{
		lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
		lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
		lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
		lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
		lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
	}

	switch (ChLP->Ch)
	{/*
	case 0:
		ret = I2CWriteMultiWord(TAS_SLA0, BP1_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP1_Ins4, &lpfCoef[5], 5);
		break;

	case 1:
		ret = I2CWriteMultiWord(TAS_SLA0, BP2_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0,BP2_Ins4, &lpfCoef[5], 5);
		break;

	case 2:
		ret = I2CWriteMultiWord(TAS_SLA0, BP3_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0,  BP3_Ins4, &lpfCoef[5], 5);
		break;

	case 3:
		ret = I2CWriteMultiWord(TAS_SLA0, BP4_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP4_Ins4, &lpfCoef[5], 5);
		break;*/

	case 4:
		ret = I2CWriteMultiWord(TAS_SLA0, BP5_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP5_Ins4, &lpfCoef[5], 5);
		break;/*
	case 5:
		ret = I2CWriteMultiWord(TAS_SLA0, BP6_Ins3, &lpfCoef[0], 5);
		ret |= I2CWriteMultiWord(TAS_SLA0, BP6_Ins4, &lpfCoef[5], 5);
		break;*/
	default:
		break;
	}

	//	DAPDelay(DLY_1MS*25);		
	return ret;
}


/**
*    第四通道带通
* This is a detail description.
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
* @par 修改日志
*      XXX于2014-10-6创建
*/
void DspACHBp_BP(BPF_STR *bpf, uint8 Ch)
{
#if DEBUG
    printf("-->%s> Fp:%d,Fs:%d,Type:%d,en:%d,Ch=%d\n",__FUNCTION__,
         bpf->Fp,bpf->Fs,bpf->Type,bpf->en,Ch);
#endif

    repBPF(bpf, Ch);

    uint32 hpfCoef[20];
    uint32 lpfCoef[20];

    if (bpf->en) {
        switch (bpf->Type) {
        case BW_06: DAPBesAndButHPF(1, bpf->Fp, hpfCoef, 0);
			        DAPBesAndButLPF(1, bpf->Fs, lpfCoef, 0); 
                    break;
		case BW_12: DAPBesAndButHPF(2, bpf->Fp, hpfCoef, 0);
			        DAPBesAndButLPF(2, bpf->Fs, lpfCoef, 0); 
                    break;
		case BL_06:	DAPBesAndButHPF(1, bpf->Fp, hpfCoef, 1);
			        DAPBesAndButLPF(1, bpf->Fs, lpfCoef, 1);
                    break;
		case BW_24: DAPBesAndButHPF(4, bpf->Fp, hpfCoef, 0);
			        DAPBesAndButLPF(4, bpf->Fs, lpfCoef, 0); 
                    break;
		case BL_12:	DAPBesAndButHPF(2, bpf->Fp, hpfCoef, 1);
			        DAPBesAndButLPF(2, bpf->Fs, lpfCoef, 1); 
                    break;
		case BL_24:	DAPBesAndButHPF(4, bpf->Fp, hpfCoef, 1);
			        DAPBesAndButLPF(4, bpf->Fs, lpfCoef, 1); 
                    break;
		case LK_12:	DAPLinkwitzHPF(2, bpf->Fp, hpfCoef);
			        DAPLinkwitzLPF(2, bpf->Fs, lpfCoef);
                    break;
		case LK_24:	DAPLinkwitzHPF(4, bpf->Fp, hpfCoef);
			        DAPLinkwitzLPF(4, bpf->Fs, lpfCoef); 
                    break;
		default:
			hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
			hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
			hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
			hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
			hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;

			lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
			lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
			lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
			lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
			lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
			break;
        }
    } else {
		hpfCoef[0] = hpfCoef[5] = hpfCoef[10] = hpfCoef[15] = 0x00800000;
		hpfCoef[1] = hpfCoef[6] = hpfCoef[11] = hpfCoef[16] = 0x00000000;
		hpfCoef[2] = hpfCoef[7] = hpfCoef[12] = hpfCoef[17] = 0x00000000;
		hpfCoef[3] = hpfCoef[8] = hpfCoef[13] = hpfCoef[18] = 0x00000000;
		hpfCoef[4] = hpfCoef[9] = hpfCoef[14] = hpfCoef[19] = 0x00000000;

		lpfCoef[0] = lpfCoef[5] = lpfCoef[10] = lpfCoef[15] = 0x00800000;
		lpfCoef[1] = lpfCoef[6] = lpfCoef[11] = lpfCoef[16] = 0x00000000;
		lpfCoef[2] = lpfCoef[7] = lpfCoef[12] = lpfCoef[17] = 0x00000000;
		lpfCoef[3] = lpfCoef[8] = lpfCoef[13] = lpfCoef[18] = 0x00000000;
		lpfCoef[4] = lpfCoef[9] = lpfCoef[14] = lpfCoef[19] = 0x00000000;
    }
    
    switch (Ch){
    case 4: 
		I2CWriteMultiWord(TAS_SLA0, BP5_Ins1, &hpfCoef[0], 5);
		I2CWriteMultiWord(TAS_SLA0, BP5_Ins2, &hpfCoef[5], 5);
        
        I2CWriteMultiWord(TAS_SLA0, BP5_Ins3, &lpfCoef[0], 5);
		I2CWriteMultiWord(TAS_SLA0, BP5_Ins4, &lpfCoef[5], 5);
        break;   
    default:break;
    }
        
}


/*********************************************************************************************************
** Function name:      
** Descriptions:        输出PEQ控制
** input parameters:    peq PEQ结构体指针，输出通道索引Ch，每个通道Eq的索引no
**						 Ch=0,前左；Ch=1,前右；Ch=2,后左；Ch=3,后右；Ch=4,超低；Ch=5,中置；
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8_t OUT_PEQ_I2C_TABLE1[6][10] ={
	{ 
		PEQ_ACh1_Ins1,PEQ_ACh1_Ins2,PEQ_ACh1_Ins3,PEQ_ACh1_Ins4,PEQ_ACh1_Ins5,
		PEQ_ACh1_Ins6,PEQ_ACh1_Ins7,PEQ_ACh1_Ins8,PEQ_ACh1_Ins9,PEQ_ACh1_Ins10
	},
	{ 

		PEQ_ACh2_Ins1,PEQ_ACh2_Ins2,PEQ_ACh2_Ins3,PEQ_ACh2_Ins4,PEQ_ACh2_Ins5,
		PEQ_ACh2_Ins6,PEQ_ACh2_Ins7,PEQ_ACh2_Ins8,PEQ_ACh2_Ins9,PEQ_ACh2_Ins10
	},
	{ 
		PEQ_ACh3_Ins1,PEQ_ACh3_Ins2,PEQ_ACh3_Ins3,PEQ_ACh3_Ins4,PEQ_ACh3_Ins5,
		PEQ_ACh3_Ins6,PEQ_ACh3_Ins7,PEQ_ACh3_Ins8,PEQ_ACh3_Ins9,PEQ_ACh3_Ins10
	},
	{ 

		PEQ_ACh4_Ins1,PEQ_ACh4_Ins2,PEQ_ACh4_Ins3,PEQ_ACh4_Ins4,PEQ_ACh4_Ins5,
		PEQ_ACh4_Ins6,PEQ_ACh4_Ins7,PEQ_ACh4_Ins8,PEQ_ACh4_Ins9,PEQ_ACh4_Ins10
	},
	{ 
		PEQ_ACh5_Ins1,PEQ_ACh5_Ins2,PEQ_ACh5_Ins3,PEQ_ACh5_Ins4,PEQ_ACh5_Ins5
	},
	{ 

		PEQ_ACh6_Ins1,PEQ_ACh6_Ins2,PEQ_ACh6_Ins3
	}
};

int DspACHPEQ(EQOP_STR *PEQOP)
{
	uint32 peqCoef[5];
	char ret = 0;

    
	printf("-->%s> Q:%f,Gain:%f,Fc:%d,Type:%d,en:%d,Ch:%d,no:%d\n",__FUNCTION__,
			PEQOP->peq.Q,PEQOP->peq.Gain,PEQOP->peq.Fc,PEQOP->peq.Type,PEQOP->peq.en,PEQOP->Ch,PEQOP->no);

    repACHEQ(PEQOP);


	if (1 == PEQOP->peq.en)
	{
		switch (PEQOP->peq.Type) 
		{

			///case 0: 一般的参量均衡，//case 1:低架滤波，//case 2:高架滤波，//case 3:全通滤波
		case 0:	DAPBiquadFilter(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);	break;
		case 1:	DAPToneBass(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);		break;
		case 2:	DAPToneTreble(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);		break;
		case 3:
			if (1 == PEQOP->peq.en) 
			{
				DAPAllpassFilter(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);
			}
			else 
			{
				peqCoef[0] = 0x00800000;
				peqCoef[1] = 0x00000000;
				peqCoef[2] = 0x00000000;
				peqCoef[3] = 0x00000000;
				peqCoef[4] = 0x00000000;
			}
			break;
		}

        switch(PEQOP->Ch) {
        case 0: case 1: case 2: case 3: 
                if(PEQOP->no < 10)
                I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[PEQOP->Ch][PEQOP->no], peqCoef, 5); break;
        case 4: if(PEQOP->no < 5)
			    I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[4][PEQOP->no], peqCoef, 5); break;
        case 5: if(PEQOP->no < 3)
			    I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[5][PEQOP->no], peqCoef, 5); break;
        }

        printf("__no=%d\n",PEQOP->no);
	} 
	else 
	{
		peqCoef[0] = 0x00800000;
		peqCoef[1] = 0x00000000;
		peqCoef[2] = 0x00000000;
		peqCoef[3] = 0x00000000;
		peqCoef[4] = 0x00000000;

        switch(PEQOP->Ch) {
        case 0: case 1: case 2: case 3: 
                I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[PEQOP->Ch][PEQOP->no], peqCoef, 5); break;
        case 4: if(PEQOP->no < 5)
			    I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[4][PEQOP->no], peqCoef, 5); break;
        case 5: if(PEQOP->no < 3)
			    I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[5][PEQOP->no], peqCoef, 5); break;
        }

        printf("-->no=%d\n",PEQOP->no);
	}
	return ret;
}


/*********************************************************************************************************
** Function name:       DspBCHPEQ
** Descriptions:        输入PEQ控制
** input parameters:    peq PEQ结构体指针，输出通道索引Ch，每个通道Eq的索引no
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

uint8_t OUT_PEQ_I2C_TABLE2[2][7] ={
	{ 
		PEQ_BCh1_Ins1,PEQ_BCh1_Ins2,PEQ_BCh1_Ins3,PEQ_BCh1_Ins4,
		PEQ_BCh1_Ins5,PEQ_BCh1_Ins6,PEQ_BCh1_Ins7
	},
	{ 

		PEQ_BCh2_Ins1,PEQ_BCh2_Ins2,PEQ_BCh2_Ins3,PEQ_BCh2_Ins4,
		PEQ_BCh2_Ins5,PEQ_BCh2_Ins6,PEQ_BCh2_Ins7
	}
};


int DspBCHPEQ(EQOP_STR *PEQOP)
{
	uint32 peqCoef[5];
	char ret = 0;

#if DEBUG    
	printf("-->%s> Q:%f,Gain:%f,Fc:%d,Type:%d,en:%d,Ch:%d,no:%d\n",__FUNCTION__,
			PEQOP->peq.Q,PEQOP->peq.Gain,PEQOP->peq.Fc,PEQOP->peq.Type,PEQOP->peq.en,PEQOP->Ch,PEQOP->no);
#endif

    repBCHEQ(PEQOP);


	if (1 == PEQOP->peq.en)
	{
		switch (PEQOP->peq.Type) 
		{

			///case 0: 一般的参量均衡，//case 1:低架滤波，//case 2:高架滤波，//case 3:全通滤波
		case 0:	DAPBiquadFilter(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);	break;
		case 1:	DAPToneBass(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);		break;
		case 2:	DAPToneTreble(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);		break;
		case 3:
			if (1 == PEQOP->peq.en) 
			{
				DAPAllpassFilter(PEQOP->peq.Fc, PEQOP->peq.Gain, PEQOP->peq.Q, peqCoef);
			}
			else 
			{
				peqCoef[0] = 0x00800000;
				peqCoef[1] = 0x00000000;
				peqCoef[2] = 0x00000000;
				peqCoef[3] = 0x00000000;
				peqCoef[4] = 0x00000000;
			}
			break;
		}

		I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE2[PEQOP->Ch][PEQOP->no], peqCoef, 5);
		//I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE[PEQOP->no], peqCoef, 5);

        printf("__no=%d\n",PEQOP->no);
	} 
	else 
	{
		peqCoef[0] = 0x00800000;
		peqCoef[1] = 0x00000000;
		peqCoef[2] = 0x00000000;
		peqCoef[3] = 0x00000000;
		peqCoef[4] = 0x00000000;

		I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE2[PEQOP->Ch][PEQOP->no], peqCoef, 5);
		//I2CWriteMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE[PEQOP->no], peqCoef, 5);
        printf("-->no=%d\n",PEQOP->no);
	}
	return ret;
}



/*********************************************************************************************************
** Function name:       DspAorDChanMixer()   v2.0
** Descriptions:        模拟、数字通道路由控制，Crossbar_2模块
** input parameters:    Aen 模拟通道使能，当Aen=1时，模拟通道路由到此模块的输出端口，否则数字通路由输出端口
**						mixer 比例值
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
#if 0 //V_0
int DspAorDChanMixer_0(AnaOrDigSrc_STR *AnaOrDig)
{
	uint32 MuxIn1,MuxIn2;
	uint8  mix_i2c_addr,mix_i2c_addr1;
	char ret = 0;
	MuxIn1=1,MuxIn2=2;
	mix_i2c_addr = Mux_10;
	mix_i2c_addr1 = Mux_2;
    
#if DEBUG
        printf("-->%s> en=%d,mix=%f\n",__FUNCTION__,AnaOrDig->en,AnaOrDig->mixer);
#endif

    //MuxIn1 = DAPFloatTo5P23(MuxIn1);
    //MuxIn2 = DAPFloatTo5P23(MuxIn2);

	if(1 == AnaOrDig->en)
	{
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn1, 1);
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn1, 1);
     
	}
	else
	{
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn2, 1);
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn2, 1);
	}
	return ret;
}
#endif
//v2.1
int DspAorDChanMixer(AnaOrDigSrc_STR *AnaOrDig)
{    
#if DEBUG
        printf("-->%s> en=%d,mix=%f\n",__FUNCTION__,AnaOrDig->en,AnaOrDig->mixer);
#endif

    repAD(AnaOrDig);

    uint8 mix_i2c_addr0 = Mix4Ch_10;
	uint8 mix_i2c_addr1 = Mix4Ch_11;
    uint32_t mixer[4]={0};
    uint32_t volume = DAPFloatTo5P23(1.00000);
    
    if (AnaOrDig->en == 0) {
        memset(mixer,0,4);
        mixer[0]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);  
    } else if (AnaOrDig->en == 1) {
        memset(mixer,0,4);
        mixer[1]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);  
    } else if (AnaOrDig->en == 2) {
        memset(mixer,0,4);
        mixer[2]= volume;      
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);  
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4); 
    }

	return 0;
}


/**
* 读取输入电平
* This is a detail description.
* @outVal       输出读到的电平值 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
void VuDetect(uint8 *outVal)
{		
	uint8   VUen[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	uint8   VUbuf[8] = {0};
	uint32  i;
	memset(outVal,0,8);

    printf("-->%s>\n",__FUNCTION__);
	_i2c_write(0x68>>1, VUMeter_1_OutEn, VUen, 8);
	_i2c_read( 0x68>>1, VUMeter_1_OutEn, outVal, 8);


#if DEBUG	
	for (i=0; i<8; i++)
	{
		printf("%x ",outVal[i]);
		printf("\n");
	}
#endif    
}

/**
* 6路输出音量设置
* This is a detail description.
* @in       输入音源【暂时不使用】
* @out     输出音源
* @gain,  输出音量 
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-28创建
*/
void volOutput(uint8_t in, uint8_t out, fp32 gain)
{
#if DEBUG
                printf("-->%s> out=%d,gain=%f\n",__FUNCTION__,out,gain);
#endif

    repOutputVol(out, gain);

    uint8_t p0=0,p1=0;           //position
    uint32_t volume;

    uint8 mix_i2c_addr0 = 0;
	uint8 mix_i2c_addr1 = 0;
    uint32_t mixer[4]={0};

    if (gain < -60) gain = 0;
    volume = DAPFloatTo5P23(pow(10.0, gain*0.05));
    
    if (out >= 6 ) return;
    
    switch (out) {
    case 0:
        mix_i2c_addr0 = MIXER01_I2C_ADDR;
	    mix_i2c_addr1 = MIXER01_I2C_ADDR;
        p0=0; p1=1;
        break;
    case 1:        
        mix_i2c_addr0 = MIXER02_I2C_ADDR;
	    mix_i2c_addr1 = MIXER02_I2C_ADDR;
        p0=0; p1=1;
        break;
    case 2:        
        mix_i2c_addr0 = MIXER03_I2C_ADDR;
	    mix_i2c_addr1 = MIXER03_I2C_ADDR;
        p0=0; p1=1;
        break;
    case 3:
        mix_i2c_addr0 = MIXER04_I2C_ADDR;
	    mix_i2c_addr1 = MIXER04_I2C_ADDR;
        p0=0; p1=1;
        break;
    case 4:
        mix_i2c_addr0 = MIXER06_I2C_ADDR;
	    mix_i2c_addr1 = MIXER06_I2C_ADDR;
        p0=1; p1=2;
        break;
    case 5:
        mix_i2c_addr0 = MIXER08_I2C_ADDR;
	    mix_i2c_addr1 = MIXER09_I2C_ADDR;
        p0=3; p1=0;
        break;
    default:break;
    }
    
    if (outVolFlag[0][out]) {
        memset(mixer,0,4);
        I2CReadMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);
        printf("read out[0][%d]=1 X1%d connect. %x,%x,%x,%x\n",out,out+1,mixer[0],mixer[1],mixer[2],mixer[3]);
        mixer[p0] = volume;
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr0, mixer, 4);
        printf("write out[0][%d]=1 X1%d connect. %x,%x,%x,%x\n",out,out+1,mixer[0],mixer[1],mixer[2],mixer[3]);
    }
    
    if (outVolFlag[1][out]) {
        memset(mixer,0,4);
        I2CReadMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);
        printf("read out[1][%d]=1 X2%d connect. %x,%x,%x,%x\n",out,out+1,mixer[0],mixer[1],mixer[2],mixer[3]);
        mixer[p1] = volume;
        I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, mixer, 4);
        printf("write out[1][%d]=1 X2%d connect. %x,%x,%x,%x\n",out,out+1,mixer[0],mixer[1],mixer[2],mixer[3]);
    }
}

/**
* 测试信号源输出enable
* This is a detail description.
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspSignalSourceEnable()
{
#if DEBUG
    printf("-->%s> SSFlag=%d\n",__FUNCTION__,SSFlag);
#endif
    if (SSFlag == 1) {
        printf("__>%s> SSFlag=%d\n",__FUNCTION__,SSFlag);
        return;
    }
    SSFlag = 1;
    memcpy(outVolFlagBak,outVolFlag,sizeof(outVolFlagBak));
    for(int i=0;i<2;i++)
    for(int j=0;j<6;j++)
        printf("%d,",outVolFlag[i][j]);
    memset(outVolFlag,0,sizeof(outVolFlag));
    DspClsCrossbar1(1,repCrossBar1);
    printf("\n==>%s> end\n",__FUNCTION__);
}

/**
* 测试信号源输出cancel
* This is a detail description.
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-28创建
*/
void DspSignalSourceCancel()
{
#if DEBUG
        printf("-->%s> SSFlag=%d\n",__FUNCTION__,SSFlag);
#endif
    if (SSFlag == 0) {
        printf("__>%s> SSFlag=%d\n",__FUNCTION__,SSFlag);
        return;
    }
    SSFlag = 0;
    memcpy(outVolFlag,outVolFlagBak,sizeof(outVolFlag));
    DspWiteCrossbar1(repCrossBar1);   
    for(int i=0;i<2;i++)
    for(int j=0;j<6;j++)
        printf("%d,",outVolFlag[i][j]);
    printf("\n==>%s> SSFlag=%d\n",__FUNCTION__,SSFlag);
}


/**
* 测试信号源输出选择
* This is a detail description.
* @in       输入音源
* @out     输出音源
* @total,  输出音源总数 
* @type   测试类型
* @retval  0 成功
* @retval  -1   错误 
* @par 标识符
*      保留
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
int DspSigSourSelectOut(uint8_t in, uint8_t out, uint8_t total, uint8_t type)
{
#if DEBUG
    printf("-->%s> in=%d,out=%d,total=%d,type=%d,SSFlag=%d\n",__FUNCTION__,
        in,out,total,type,SSFlag);
#endif
    uint8_t rd = 0;
    float mixer = 1.0;

    if (SSFlag == 0) return 0;
    
    //if (out >= total) return -1;

    uint32_t rep[1];
    DspClsCrossbar1(0,rep);
    memset(outVolFlag,0,sizeof(outVolFlag));
    
    if (type == 0) {
        DspMixerSet(rd, in, out, mixer);
        outVolFlag[in][out] = 1;
    } else if (type == 1) {
        for(int i=0;i<total;i++) {
            DspMixerSet(rd, in, i, mixer);
            sleep(4);
            DspMixerSet(rd, in, i, 0.0);
        }
        DspMixerSet(rd, in, 0, mixer);
        outVolFlag[in][0] = 1;
    } else if (type == 2) {
        rd = 1;
        for(int i=0;i<total;i++) {
            DspMixerSet(rd, in, i, mixer);
            outVolFlag[in][i] = 1;
        }
    }
}


/**
* 所有路由直通
* This is a detail description. 
* @par 标识符
*      保留                (测试中....)
* @par 其它
*      无
* @par 修改日志
*      XXX于2014-9-20创建
*/
void AllMixThrough()
{
#if DEBUG
        printf("-->%s>\n",__FUNCTION__);
#endif

      uint32_t in = 0;
      float mixer = 1.0;
      uint8_t rd = 0;
 #if 1  
      in = 0;
      DspMixerSet(rd, in, 0, 1.0);  //x11
      outVolFlag[0][0]= 1;
      //DspMixerSet(rd, in, 2, 1.0);  //x13
      in = 1;
      DspMixerSet(rd, in, 1, 1.0);  //x22
      outVolFlag[1][1]= 1;
      //DspMixerSet(rd, in, 3, 0.0);  //x24
 #else
        DspMixerSet(1, in, 0, 1.0);  //x11
        DspMixerSet(1, 1, 0, 1.0);  //x21
 #endif
    
      //DspMixerSet_2(0,0,0.0);   //x11
      //DspMixerSet_2(1,1,0.0);   //x22
     
      //DspMixerSet_2(0,0,1.0);   //x11
      //DspMixerSet_2(1,1,1.0);   //x22 
#if 0
      DspMixerSet_3(0,0,0);  //11
      DspMixerSet_3(1,1,0);    //22
#endif 

}






/*********************************************************************************************************
** Function name:       DspDigChansMux()  v2.0
** Descriptions:        模拟、数字通道路由控制，Mux_5,Mux_6模块
** input parameters:    uint8 DigChan    DigChan=1时，为第一路I2S通道，否则为第二路I2S通道
**						
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
#if 0//V2_0
int DspDigChansMux(uint8 DigChan)
{
	uint32 MuxIn1,MuxIn2;
	uint8  mix_i2c_addr,mix_i2c_addr1;
	char ret = 0;
#if DEBUG
    printf("-->%s> DigChan=%d\n",__FUNCTION__,DigChan);
#endif 
	MuxIn1=1,MuxIn2=2;
	mix_i2c_addr = Mux_5;
	mix_i2c_addr1 = Mux_6;

	if(1 == DigChan)
	{
		
		I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn1, 1);
		MuxIn1 = DAPFloatTo5P23(MuxIn1);
		I2CReadMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn1, 1);
		MuxIn1 = DAPFloatTo5P23(MuxIn1);

		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn1, 1);
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn1, 1);

	}
	else
	{

		I2CReadMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn2, 4);
		MuxIn2 = DAPFloatTo5P23(MuxIn2);
		I2CReadMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn2, 4);
		MuxIn2 = DAPFloatTo5P23(MuxIn2);

		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr, &MuxIn2, 1);
		ret |= I2CWriteMultiWord(TAS_SLA0, mix_i2c_addr1, &MuxIn2, 1);
	}
	return ret;
}
#endif


/*********************************************************************************************************
** Function name:       DspFunModInit
** Descriptions:        实现DSP各个功能模块的初始化，3D旁通，各个PEQ旁通，HP旁通，SCT旁通，音量模块
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspFunModInit(void)
{
#if DEBUG
        printf("-->%s> \n",__FUNCTION__);
#endif
}

/*********************************************************************************************************
** Function name:       DspAllByPass
** Descriptions:        实现DSP各个功能模块的初始化，3D旁通，各个PEQ旁通，HP旁通，SCT旁通，音量模块
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int DspAllByPass(void)
{

	char ret=0;   
    uint8_t i, j;
#if DEBUG
    printf("-->%s> \n",__FUNCTION__);
#endif


#if 1    
	//HP bypass
	CHanHLPF_STR *ChHP = (CHanHLPF_STR*)malloc(sizeof(CHanHLPF_STR));
    memset(ChHP,0,sizeof(CHanHLPF_STR));
	ChHP->xpf.en = 0;
	for (i = 0; i<6; i++)
	{
		ChHP->Ch = i;
		DspACHBp_HP(ChHP);
        if (i==4)
            DspACHBp_LP(ChHP);
	}
    free(ChHP);
    
	//All EQ bypass 
	EQOP_STR *PEQOP  =  (EQOP_STR*)malloc(sizeof(EQOP_STR));
    memset(PEQOP,0,sizeof(EQOP_STR));
	PEQOP->peq.en = 0;
	for (i = 0; i<6; i++)
	{
		PEQOP->Ch = i;
		for (j = 0; j<10; j++)
		{
			PEQOP->no = j;
            DspACHPEQ(PEQOP);
		}
	}
    
    PEQOP->peq.en = 0;
    for (i = 0; i<2; i++) {
        PEQOP->Ch = i;
        for (j = 0; j<7; j++){
            PEQOP->no = j;
            DspBCHPEQ(PEQOP);
        }
    }
    free(PEQOP);

	//关闭3dmusic/////
	float mix[4]={1.0,0,0,0};
    DLY_STR delay; delay.en = delay.Dly = 0;
	for (i = 0; i<2; i++) {
        Dsp3DMusicMix(mix,i);   //Dsp3DMusicEn(0, i);
        Dsp3DMusicDelay(delay, i);
    }

	//关闭 SCT声音补偿
    float mixer[4]={1.0,0,0,0};
    for (i = 0; i<2; i++)
        DspSctEn(0, i);
    DRC_STR agc;
    memset(&agc,0,sizeof(agc));
    agc.en = 0; agc.k2 = 1.0;
    for (i = 0; i<3; i++) {
        DspSetSctAgc(i,agc,0);
        DspSetSctAgc(i,agc,1);
    }
    
    HLPF_STR hpf; hpf.en = 0;
    BPF_STR bpf;  bpf.en = 0;
    for (i = 0; i<2; i++) {
        DspSctHp(i, hpf);
        DspSctLp(i, hpf);
        DspSctBp(i, bpf);
    }

	//关闭测试音源
	//DspSigSourChoise(TestSignal);
    

	//路由设置  输入端只对模拟音频数据进行处理，，输出到模拟端，
	AnaOrDigSrc_STR *AnaOrDig = (AnaOrDigSrc_STR*)malloc(sizeof(AnaOrDigSrc_STR));
    memset(AnaOrDig,0,sizeof(AnaOrDigSrc_STR));
    AnaOrDig->en = 0;
    DspAorDChanMixer(AnaOrDig);

	//音量增益设置
	VOL_OP* gain1= (VOL_OP*)malloc(sizeof(VOL_OP));
    memset(gain1,0,sizeof(VOL_OP));
    gain1->vol.Gain = gain1->vol.Pol = gain1->vol.Mute = 0;
    for (i = 0; i<3; i++){
        gain1->Ch = i;
    	DspGain(gain1);
    }

    LimiterOP_STR *limt= (LimiterOP_STR*)malloc(sizeof(LimiterOP_STR));
    memset(limt,0,sizeof(LimiterOP_STR));
	limt->limiter.en = 0;
    
    for (i = 0; i<6; i++){
	    limt->Ch = i;
	    DspLimiter(limt);
    }
    free(limt);

    Outdly *p = (Outdly *)malloc(sizeof(Outdly));
    memset(p,0,sizeof(Outdly));
	p->delay.en = 0;
    for (i = 0; i<6; i++){
    	p->Ch = i;
    	DspOutDelay(p);
    }
	free(p);
    
   uint32_t rep[1]; 
   DspClsCrossbar1(0,rep);
   memset(outVolFlag,0,sizeof(outVolFlag));
   AllMixThrough();

    #if 0
     uint32_t in = 0;
     uint8_t rd = 1;   
     in = 0;
     DspMixerSet(0, in, 0, 1.0);  //x11
     DspMixerSet(rd, in, 2, 1.0);  //x13
     in = 1;
     DspMixerSet(rd, in, 1, 1.0);  //x22
     DspMixerSet(rd, in, 3, 1.0);  //x24
     #endif
#endif
	return ret;
}




void archiveInitDsp()
{
    int i,j;
    //AD
    DspAorDChanMixer(&(rDspInfo->ad));
    
    printf("input vol\n");  
    //input vol
    for(i=0;i<3;i++)
        DspGain(&(rDspInfo->vol[i]));

    printf("3D\n");   
    //3D
    for(i=0;i<2;i++)
        Dsp3DMusicDelay(rDspInfo->m3D[i].delay, rDspInfo->m3D[i].Ch);
    Dsp3DMusicEn(rDspInfo->m3D[i].en, rDspInfo->m3D[i].Ch);

    printf("sct\n");    
    //SCT
    for(i=0;i<2;i++) {
        DspSctHp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].hpf);
        DspSctLp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].lpf);
        DspSctBp(rDspInfo->sct[i].Ch, rDspInfo->sct[i].bpf);
        
        DspSetSctAgc(0,rDspInfo->sct[i].AGChp,rDspInfo->sct[i].Ch);     
        DspSetSctAgc(1,rDspInfo->sct[i].AGCbp,rDspInfo->sct[i].Ch);
        DspSetSctAgc(2,rDspInfo->sct[i].AGClp,rDspInfo->sct[i].Ch); 
        
        DspSetSctDepth(0, rDspInfo->sct[i].hVolDepth, rDspInfo->sct[i].Ch);
        DspSetSctDepth(1, rDspInfo->sct[i].bVolDepth, rDspInfo->sct[i].Ch);
        DspSetSctDepth(2, rDspInfo->sct[i].lVolDepth, rDspInfo->sct[i].Ch);

        DspSctEn(rDspInfo->sct[i].en,rDspInfo->sct[i].Ch);
        if (rDspInfo->sct[i].en) {
            DspSctMix(rDspInfo->sct[i].mix,rDspInfo->sct[i].Ch);
        }
    }

    printf("crossbar\n");   
    for(i=0;i<2;i++) {
        for(j=0;j<6;j++) {
            //DspMixerSet(0, rDspInfo->crossbar1[i][j].in, rDspInfo->crossbar1[i][j].out,
            //    rDspInfo->crossbar1[i][j].mix);
            DspMixerSet(1, i, j,
                rDspInfo->crossbar1[i][j].mix);
        }
    }

    printf("output vol\n"); 
    //output vol
    for(i=0;i<6;i++) {
        volOutput(0, i, rDspInfo->outVol[i]);
    }

    printf("bch eq\n"); 
    //BCHEQ
    for(i=0;i<2;i++) {
        for(j=0;j<7;j++) {
            DspBCHPEQ(&(rDspInfo->bchEQ[i][j]));
        }
    }

    printf("ach eq\n"); 
    //ACHEQ
    for(i=0;i<48;i++) {
        DspACHPEQ(&(rDspInfo->achEQ[i]));
    }

    printf("hpf\n");    
    //hpf
    for(i=0;i<6;i++) {
        if (i == 4) continue;
        DspACHBp_HP(&(rDspInfo->hpf[i]));
    }

    printf("bpf\n");    
    //bpf
    DspACHBp_BP((BPF_STR*)&(rDspInfo->bpf), rDspInfo->bpf.Ch);

    printf("limit\n");  
    //limit
    for(i=0;i<6;i++) {
        DspLimiter(&(rDspInfo->limit[i]));
    }

    printf("output dly\n"); 
    //output dly
    for(i=0;i<6;i++)
        DspOutDelay(&(rDspInfo->outDly[i]));

    printf("init finish\n");

}


void readArchiveInitDsp()
{
    int res;
    res = readArchiveHead();
    if (res) {
        archiveInitDsp();
    } else {
        DspAllByPass();
    }
}





void readACHEQ(uint8 Ch, uint8 no, uint32 peqCoef[5])
{
    memset(peqCoef,0,sizeof(uint32)*5);
    switch(Ch) {
    case 0: case 1: case 2: case 3: 
            if(no < 10)
            I2CReadMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[Ch][no], peqCoef, 5); break;
    case 4: if(no < 5)
            I2CReadMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[4][no], peqCoef, 5); break;
    case 5: if(no < 3)
            I2CReadMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE1[5][no], peqCoef, 5); break;
    }
}

void readBCHEQ(uint8 Ch, uint8 no, uint32 peqCoef[5])
{
    memset(peqCoef,0,sizeof(uint32)*5);
    I2CReadMultiWord(TAS_SLA0, OUT_PEQ_I2C_TABLE2[Ch][no], peqCoef, 5);
}

void readACHBP_HP(uint8 Ch,uint32 hpfCoef[20])
{
    memset(hpfCoef,0,sizeof(uint32)*20);

	switch (Ch)
	{
	case 0:
		I2CReadMultiWord(TAS_SLA0, BP1_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP1_Ins2, &hpfCoef[5], 5);
		break;

	case 1:
		I2CReadMultiWord(TAS_SLA0, BP2_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP2_Ins2, &hpfCoef[5], 5);
		break;

	case 2:
		I2CReadMultiWord(TAS_SLA0, BP3_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP3_Ins2, &hpfCoef[5], 5);
		break;

	case 3:
		I2CReadMultiWord(TAS_SLA0, BP4_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP4_Ins2, &hpfCoef[5], 5);
		break;
	case 4:
		I2CReadMultiWord(TAS_SLA0, BP5_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP5_Ins2, &hpfCoef[5], 5);
		break;

	case 5:
		I2CReadMultiWord(TAS_SLA0, BP6_Ins1, &hpfCoef[0], 5);
		I2CReadMultiWord(TAS_SLA0, BP6_Ins2, &hpfCoef[5], 5);
		break;
	default: break;
	}
    
}

#if 1 //v2_0
void readACHBP_LP(uint8 Ch,uint32 lpfCoef[20])
{
    memset(lpfCoef,0,sizeof(uint32)*20);

	switch (Ch)
	{/*
	case 0:
		 I2CReadMultiWord(TAS_SLA0, BP1_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0, BP1_Ins4, &lpfCoef[5], 5);
		break;

	case 1:
		 I2CReadMultiWord(TAS_SLA0, BP2_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0,BP2_Ins4, &lpfCoef[5], 5);
		break;

	case 2:
		 I2CReadMultiWord(TAS_SLA0, BP3_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0,  BP3_Ins4, &lpfCoef[5], 5);
		break;

	case 3:
		 I2CReadMultiWord(TAS_SLA0, BP4_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0, BP4_Ins4, &lpfCoef[5], 5);
		break;*/

	case 4:
		 I2CReadMultiWord(TAS_SLA0, BP5_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0, BP5_Ins4, &lpfCoef[5], 5);
		break;/*
	case 5:
		 I2CReadMultiWord(TAS_SLA0, BP6_Ins3, &lpfCoef[0], 5);
		 I2CReadMultiWord(TAS_SLA0, BP6_Ins4, &lpfCoef[5], 5);
		break;*/
	default:
		break;
	}

}
#endif

void readAllHLpfEQ()
{

    uint32 peqCoef[5]={0};
    //read eq
    printf("ACHEQ: \n");
    for (int i=0;i<6;i++) {
        for (int j=0;j<10;j++) {
            readACHEQ(i, j, peqCoef);  
            printf("Ch=%d,no=%d,%x,%x,%x,%x,%x\n", i,j,peqCoef[0],peqCoef[1],peqCoef[2],peqCoef[3],peqCoef[4]);
        }
    }
    printf("BCHEQ: \n");
    for (int i=0;i<2;i++) {
        for (int j=0;j<7;j++) {
            readACHEQ(i, j, peqCoef);
            printf("Ch=%d,no=%d,%x,%x,%x,%x,%x\n", i,j,peqCoef[0],peqCoef[1],peqCoef[2],peqCoef[3],peqCoef[4]);
        }
    }

    //readACHBP_HP
    printf("readACHBP_HP: \n");
    uint32 xpfCoef[20]={0};
    for (int i=0;i<2;i++) {
        readACHBP_HP(i,xpfCoef);
        printf("Ch=%d ",i);
        for (int j=0;j<20;j++) {
            printf("%x,", xpfCoef[j]);
        }
        printf("\n");
    }
#if 0
    printf("readACHBP_LP: \n");
    for (int i=0;i<2;i++) {
        readACHBP_LP(i,xpfCoef);
        printf("Ch=%d ",i);
        for (int j=0;j<20;j++) {
            printf("%x,", xpfCoef[j]);
        }
        printf("\n");
    }
#endif
}







/**
*#include "mux_test_0918.h"
*/
void testMUX()
{
    uint32_t m1,m2,m3,m4;

    I2CReadMultiWord(0x68>>1, 0xae, &m1, 1);  
    I2CReadMultiWord(0x68>>1, 0xaf, &m2, 1);
    printf("m1=%d,m2=%d\n",m1,m2);

    m3 = 2;   //DAPFloatTo5P23(2);
    m4 = 1;    //DAPFloatTo5P23(1);
    
    I2CWriteMultiWord(0x68>>1, 0xae, &m3, 1);
    I2CWriteMultiWord(0x68>>1, 0xaf, &m4, 1);
    
    I2CReadMultiWord(0x68>>1, 0xae, &m1, 1); 
    I2CReadMultiWord(0x68>>1, 0xaf, &m2, 1);

    printf("m1=%d,m2=%d\n",m1,m2);
}








































