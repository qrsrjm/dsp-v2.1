/*
*****************************************Copyright (c)*********************************************
**									 广州立锐升电子有限公司
**                             Guangzhou Lrsun Electronic Co.,Ltd.
**                                    http://www.lrsun.net
**	文件名	：TAS3xxxDownload.c
**	程序员	：陈家承
**	日　期  ：2009年2月2日
**	文件描述：TAS3xxx固件下载操作
***************************************************************************************************
*/
#include 	<string.h>
#include	<stdio.h>
//#include	 <stdint.h>

#include 	"TAS3xxxDownload.h"
#include 	"TAS3xxx.h"	
#include 	"I2C.h"
//#include    "ModulesAddr.h"
//#include    "ModulesAddr_Ver2.0.h"
#include    "ModulesAddr_Ver2_1.h"
#include    "TAS3204_MotAudio_Slave_Addr.h"


#include "unistd.h"



#define QMD_DSP    1

extern unsigned char TAS3208_AUDIO_Algorithm[];
//extern const uint8 SourceImage1[];


#if QMD_DSP
void DapHwInit(void)
{   
    printf("-->%s,%d> ...\n",__FUNCTION__,__LINE__);
    //testI2C();
    //return 0;
    
    uint8 downloadSta[2] = { 1, 0 };							// Download status
	uint8 TasInit[4] = { 0x01, 0x00, 0x12, 0x00 };  //;{ 0x00, 0x40, 0x1b, 0x22 }; 
    uint8 rstEn = 1;
	uint8 rcv[8] = { 0 };

    open_fd_i2c();

#if 1
    
    uint8 TasStateREG[4] = {0x00,0x00,0x00,0xD0};    //0x12寄存器 

    while (downloadSta[0] != 0)	
	{
		
		if (rstEn)
		{
			//TAS3xxxReset();
			dsp_reset();
		}
        usleep(10*1000);
		//DapDelay(DLY_1MS*10);		
		//I2CSendStr(TAS_SLA0, 0x00, TasInit, 4);

        //test i2s  2014-9-25
		_i2c_write(TAS_SLA0, 0x00, TasInit, 4);
        
        //I2CSendStr(TAS_SLA0, 0x12, TasStateREG, 4);		
		//I2CRcvStr(TAS_SLA0, 0x00, rcv, 4);	
		_i2c_read(TAS_SLA0, 0x00, rcv, 4);	
		
		do
		{
			downloadSta[0] = DapStatusCheck(TAS_SLA0);
			
		} while (downloadSta[0] != TAS3XXX_NO_EEPROM);
		
		downloadSta[0] = DapPrgDownload(TAS_SLA0);
		
		rstEn = 1;
	}
    usleep(100*1000);
    //DapDelay(DLY_1MS*100);		
	//I2CSendStr(TAS_SLA0, 0x00, TasInit, 4);
    //I2CSendStr(TAS_SLA0, 0x12, TasStateREG, 4);	
	//I2CRcvStr(TAS_SLA0, 0x00, rcv, 4);
	
	//_i2c_write(TAS_SLA0, 0x00, TasInit, 4);
    
	_i2c_write(TAS_SLA0, 0x12, TasStateREG, 4);	
	_i2c_read(TAS_SLA0, 0x00, rcv, 4);

#endif
    
    //sleep(2);
#if 0

    memset(rcv,0,4);
    if(0 != _i2c_read(TAS_SLA0, 0x08, rcv, 4)){
       printf("-->%s> read 0x08 fail.\n",__FUNCTION__);
       exit(-1);
    }
    printf("*****0x08: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

    memset(rcv,0,4);
    if(0 != _i2c_read(TAS_SLA0, 0x08, rcv, 4)){
       printf("-->%s> read 0x08 fail.\n",__FUNCTION__);
       exit(-1);
    }
    printf("*****0x08: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

    
    usleep(20*1000);

   
    memset(rcv,0,4);
    if(0 != _i2c_read(TAS_SLA0, 0x00, rcv, 4)){
       printf("-->%s> read 0x08 fail.\n",__FUNCTION__);
       exit(-1);
    }
    printf("*****0x00: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
    
#endif

   
}

#else
/*
***************************************************************************************************
**                                         DapHrdInit()
**	功能描述：TAS3xxx系列芯片的固件初始化。
**	参  数  ：无
**	返回值  ：无
***************************************************************************************************
*/
void DapHwInit(void)
{
    printf("-->%s,%d> ...\n",__FUNCTION__,__LINE__);
    
	uint8 downloadSta[2] = { 1, 0 };							// Download status
	uint8 TasInit[4] = { 0x01, 0x00, 0x12, 0x00 };				// Tas3xxx Init {0x01,0x00,0x12,0x00} 20bit 左对齐
	uint8 rstEn = 1;
	uint8 rcv[4] = { 0 };


	// TAS3108代码块下载
	while (downloadSta[0] != 0)
	//while(1)
	{
		if (rstEn)    //重启TAS3XXX,TAS3xxxReset()函数根据主控芯片来重写
		{
			//TAS3xxxReset();
			dsp_reset();
		}

        //read_init_value();
        
		//DapDelay(DLY_1MS * 10);
		usleep(1000*10);
/*
        memset(rcv,0,4);
        if(0 != _i2c_read(TAS_SLA0, 0x00, rcv, 4)){
            printf("-->%s> read 0x00 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("init clock&sap: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
*/
        //usleep(1000*10);
        
    //while(1){
        memset(rcv,0,4);
        if(0 != _i2c_write(TAS_SLA0, 0x00, TasInit, 4)){
            printf("-->%s> write 0x00 fail.\n",__FUNCTION__);
            exit(-1);
        }
        if(0 != _i2c_read(TAS_SLA0, 0x00, rcv, 4)){
            printf("-->%s> read 0x00 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("clock&sap: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

        //usleep(1000*10);
#if 0
        if(0 != _i2c_read(TAS_SLA0, 0x02, rcv, 4)){
            printf("\n-->%s> read 0x02 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("\n02: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
        usleep(1000*10);

        if(0 != _i2c_read(TAS_SLA0, 0x08, rcv, 4)){
            printf("-->%s> read 0x08 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("08: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
        usleep(1000*10);

        if(0 != _i2c_read(TAS_SLA0, 0x04, rcv, 4)){
            printf("-->%s> read 0x04 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("04: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
        usleep(1000*10);

        if(0 != _i2c_read(TAS_SLA0, 0x05, rcv, 4)){
            printf("-->%s> read 0x05 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("05: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);
        usleep(1000*10);
        #endif
    //}    
    //    return 0;
        //memset(rcv,0,4); 
        //if(0 != _i2c_read(TAS_SLA0, 0x01, rcv, 4)){
        //    printf("-->%s> read 0x01 fail.\n",__FUNCTION__);
        //    exit(-1);
        //}
        //printf("reserved : %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

        
		do
		{
		    printf("-->%s,%d> ..DapStatusCheck .\n",__FUNCTION__,__LINE__);
			downloadSta[0] = DapStatusCheck(TAS_SLA0);

		} while (downloadSta[0] != TAS3XXX_NO_EEPROM);
                
		downloadSta[0] = DapPrgDownload(TAS_SLA0);
        printf("-->%s,%d> .downloadSta=%x..\n",__FUNCTION__,__LINE__,downloadSta[0]);

        memset(rcv,0,4);
        if(0 != _i2c_read(TAS_SLA0, 0x12, rcv, 4)){
            printf("-->%s> read 0x12 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf(": %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

        memset(rcv,0,4);
        if(0 != _i2c_read(TAS_SLA0, 0x1b, rcv, 4)){
            printf("-->%s> read 0x02 fail.\n",__FUNCTION__);
            exit(-1);
        }
        printf("****statu: %x,%x,%x,%x\n",rcv[0],rcv[1],rcv[2],rcv[3]);

        //read_init_value();
    
		rstEn = 1;
	}
}

#endif

/*
***************************************************************************************************
**
**                                        DapPrgDownload()
**
**
**	功能描述：TAS3xxx固件的下载
**
**	参  数  ：sla		芯片地址
**			  sel		芯片选择
**
**	返回值  ：返回状态标志
**
***************************************************************************************************
*/
uint8 DapPrgDownload(uint8 sla)
{
	int32  NumOfBlock;
	uint8  tas3xxxRun[8] = { 0 };
	uint8  RetStatus;
	uint8  Rtype;
	uint16 DatByteLen;
	uint8  *pImageFile;
    int count8=0,count7=0,count6=0;

	//pImageFile = (uint8 *)&SourceImage1[0];
	pImageFile = (uint8 *)TAS3208_AUDIO_Algorithm;


	while (1)
	{																// Write 1 time to I2C memory load register
		Rtype = CheckMemloadCtrl(sla, pImageFile);
		if (Rtype == TAS3108_TERMINATION_BLOCK)
			break;
        
        //usleep(2*1000);
        
		DatByteLen = (((uint16)pImageFile[6]) << 8 & 0xFF00) | (((uint16)pImageFile[7]) & 0x00FF);
		DatByteLen -= 10;											// 8 bytes Header and last 2 bytes of checksum

		// Write multiple times data to I2C memory load data register
		switch (pImageFile[2])
		{
		case 0:
		case 1:
		case 3:
		case 6:													// 8-bit/28-bits memory download
			NumOfBlock = DatByteLen / 8 + 1;            
			pImageFile = DataOfBlockDownload(sla, pImageFile + 8, NumOfBlock);
            count8++;
			break;

		case 2:													// 54-bit memory download	
			NumOfBlock = DatByteLen / 7 + 1;
			pImageFile = DataOfBlockDownload(sla, pImageFile + 8, NumOfBlock);
            count7++;
			break;

		case 4:
		case 5:													// 48-bit /24-bit memory download
			NumOfBlock = DatByteLen / 6 + 1;
			pImageFile = DataOfBlockDownload(sla, pImageFile + 8, NumOfBlock);
            count6++;
			break;

		default:
			break;
		}
	}

    //printf("download finish ...count8=%d,count7=%d,count6=%d\n",count8,count7,count6);
    
	// Check downloading status
	RetStatus = DapStatusCheck(sla);

    //printf("download finish .RetStatus = %x\n",RetStatus);
    //usleep(20*1000);
    
	if (RetStatus == TAS3XXX_LOAD_SUCCEED)
	{
		_i2c_write(sla, TAS3XXX_MEMLOAD_CTRL, tas3xxxRun, 8);
	}

	return RetStatus;
}
/*
***************************************************************************************************
**
**                                     DapStatusCheck()
**
**
**	功能描述：下载完的状态，检查是否下载成功，或错误标志
**
**	参  数  ：sla	芯片地址
**
**	返回值  ：返回成功标志或错误标志
**
***************************************************************************************************
*/
uint8 DapStatusCheck(uint8 sla)
{
	uint8 Stabuf[4];
	uint8 RetStatus = 0;

    int ret=-1;
	if(ret = _i2c_read(sla, TAS3XXX_STATUS, Stabuf, 4)){ 
            printf("-->%s> read TAS3XXX_STATUS fail.%d\n",__FUNCTION__,ret);
            exit(-1);
    }
#if DEBUG_DOWNLOAD	
    printf("--->%s, stabuf[]=%x,%x,%x,%x\n",__FUNCTION__,Stabuf[0],Stabuf[1],Stabuf[2],Stabuf[3]);
#endif
	// Convert and check the Status Register value List the meaning of the register value

	if (Stabuf[3] == 0x00) 		RetStatus = TAS3XXX_LOAD_SUCCEED;
	else if (Stabuf[3] == 0xFF) RetStatus = TAS3XXX_NO_EEPROM;
	else if (Stabuf[3] == 0xF0) RetStatus = TAS3XXX_END_HEADER_ERR;
	else if (Stabuf[3] & 0x20) 	RetStatus = TAS3XXX_INVALID_MEMSEL;
	else if (Stabuf[3] & 0x10) 	RetStatus = TAS3XXX_DAP_DATAMEM_ERR;
	else if (Stabuf[3] & 0x08)  RetStatus = TAS3XXX_DAP_COEFFMEM_ERR;
	else if (Stabuf[3] & 0x04)  RetStatus = TAS3XXX_DAP_PROGMEM_ERR;
	else if (Stabuf[3] & 0x02)  RetStatus = TAS3XXX_MICRO_EXMEM_ERR;
	else if (Stabuf[3] & 0x01)  RetStatus = TAS3XXX_MICRO_PROGMEM_ERR;

	//DapDelay(100 * DLY_1MS);
	usleep(100*1000);
	return RetStatus;
}

/*
***************************************************************************************************
**
**                                     CheckMemloadCtrl()
**
**
**	功能描述：检查目前的Block是否为结束块，并把当前的Header的值送到TAS3108_I2C_MEMLOAD_CTRL去
**
**	参  数  ：sla	    芯片地址
**            *src_header_ptr	Block的头地址
**
**	返回值  ：返回0和1，0代表普通Block，1代表结束Block
**
***************************************************************************************************
*/
uint8 CheckMemloadCtrl(uint8 sla, uint8 *SrcHeaderPtr)
{
	uint8 TerIndicator, DstHeader[8];
    uint8 TasInit[4]={0x0,0x0,0x0,0x31};
    
	memcpy(DstHeader, SrcHeaderPtr, 8);
	// Check if this is termination block
	TerIndicator = DstHeader[0] | DstHeader[1] | DstHeader[2] | 
		DstHeader[3] | DstHeader[5] | DstHeader[6] | DstHeader[7];

	if (0 == TerIndicator) {
        printf("CheckMemloadCtrl over....\n");       
		return TAS3108_TERMINATION_BLOCK;
    }

	_i2c_write(sla, TAS3XXX_MEMLOAD_CTRL, DstHeader, 8);

	return TAS3108_NORMAL_HEADER;
}
/*
***************************************************************************************************
**
**                                     DataOfBlockDownload()
**
**
**	功能描述：数据块下载
**
**	参  数  ：sla	芯片地址
**			  *data_ptr   	Block的头地址
**            num_of_block	Block的字节总数，应该是8的倍数
**
**	返回值  ：返回下一个要下载的数据的地址
**
***************************************************************************************************
*/
uint8 *DataOfBlockDownload(uint8 sla, uint8 *DataPtr, int32 NumOfBlock)
{
	uint8 DataBytes[8];

	while (NumOfBlock--)
	{
		memcpy(DataBytes, DataPtr, 8);

		_i2c_write(sla, TAS3XXX_MEMLOAD_DATA, DataBytes, 8);

		DataPtr += 8;
		//DapDelay(DLY_10US);
		usleep(10);
	}
	//DapDelay(DLY_1MS)
	usleep(1000);

    
	return DataPtr;
}


