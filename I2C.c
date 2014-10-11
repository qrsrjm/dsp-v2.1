/**
* @file 		I2C.c
* @brief		This is a brief description.
* @details	This is the detail description.
* @author		qmd
* @date		2014-8-18
* @version	001
* @par Copyright (c): 
* 		广州立锐升电子有限公司
* @par History:         
*	version: author, date, desc\n
*/


#include 	"I2C.h"
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h> 

#include <unistd.h> //sleep close
#include <stdlib.h> //exit




/* 以下为I2C操作时所需要的变量 */
//volatile  uint8  I2C_sla;  		/* 从机地址 (即器件地址)											*/
//volatile  uint8  I2C_suba;      /* 子地址															*/
//volatile  uint8  *I2C_buf;      /* 数据缓冲区指针 (读操作时会被更改)								*/
//volatile  uint8  I2C_num;       /* 操作数据个数 (会被更改)											*/
//volatile  uint8  I2C_end;       /* 操作结束标志，为1时表示操作结束，为0xFF时表示操作失败 (会被设置) */
//volatile  uint8  I2C_suba_en;   /* 子地址使能控制，读操作时请设置为1，写操作时请设置为2 (会被更改)  */

struct i2c_write_data2 wdata2;

unsigned char DEVICE_ADDRESS=0x7a;  /// Write Addr : 0x7a, Read Addr, 0x7a | 0x01

//加密状态标识，1表示ok
int check_aplus_ok_g = 0;


/** i2c 设备描述符*/
int fd_i2c = -1;

int open_fd_i2c(void)
{
	char nm[16];
	int fd = -1;

    if (fd_i2c >= 0) return fd_i2c;
    
	snprintf(nm, 16, "/dev/%s", I2C_DEV_NAME);
	if ((fd = open(nm, O_RDONLY)) < 0) {
		perror(nm);
		return -1;
	}
	
	fd_i2c = fd;
	
	return fd;
}

int close_fd_i2c(void)
{
    close(fd_i2c);
    return 0;
}


/**
 * 软件延时，提供给I2C总线等待超时使用
 * @param[in]	dly		延时参数，值越大，延时越久
 * @retval	无
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
uint8 I2CDlyEnd(uint32 dly)
{
	uint32  i;

	for (; dly>0; dly--)
	for (i = 0; i<5000; i++) {
        ;
	}
	return 0;
}


/**
 * 向有子地址器件发送多字节数据。 使用前要初始化好I2C引脚功能和I2C中断，并已使能I2C主模式
 * @param[in]	sla		器件从机地址
 * @param[in]   suba	器件子地址
 * @param[in]   s		数据发送缓冲区指针
 * @param[in]   no		发送数据个数
 * @retval	1	成功
 * @retval	0	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
uint8 I2CSendStr(uint8 sla, uint8 suba, uint8 *s, uint8 no)
{
	/* 参数设置 */
	//I2C_sla = sla;			/* 写操作的器件地址		 */
	//I2C_suba = suba;			/* 子地址				 */
	//I2C_buf = s;
	//I2C_num = no;
	//I2C_suba_en = 2;			/* 有子地址写 			 */
	//I2C_end = 0;

	printf("%s\n",__FUNCTION__);

	unsigned char ert = _i2c_write(sla, suba, s, no);
	int ret=-1;
	
	if(ert == 1)	/**失败*/
		ret = 0;
	else			/**成功*/
		ret = 1;

	return ret;
}

/**
 * 向有子地址器件读取多字节数据。 使用前要初始化好I2C引脚功能和I2C中断，并已使能I2C主模式
 * @param[in]	sla		器件从机地址
 * @param[in]   suba	器件子地址
 * @param[out]   s		数据接收缓冲区指针
 * @param[in]   no		读取数据个数
 * @retval	1	成功
 * @retval	0	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
uint8 I2CRcvStr(uint8 sla, uint8 suba, uint8 *s, uint8 no)
{
	if (0 == no)
		return 0;

	/* 参数设置 */
	//I2C_sla = sla + 1;		/* 读操作的器件地址		  */
	//I2C_suba = suba;
	//I2C_buf = s;
	//I2C_num = no;
	//I2C_suba_en = 1;			/* 有子地址读			  */
	//I2C_end = 0;

	printf("%s\n", __FUNCTION__);
    
	unsigned char ert = _i2c_write(sla, suba, s, no);
	int ret=-1;
	
	if(ert == 1)	/**失败*/
		ret = 0;
	else			/**成功*/
		ret = 1;
		
	return ret;
}

/**
 * 向有子地址器件发送多32位的数据。。
 * @param[in]	sla		器件从机地址
 * @param[in]   suba	器件子地址
 * @param[in]   s		数据发送缓冲区指针
 * @param[in]   no		发送数据个数
 * @retval	1	成功
 * @retval	0	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
uint8 I2CWriteMultiWord(uint8 sla, uint8 suba, uint32* s, uint8 no)
{
	uint8 	charbuf[20];
	uint32 	i;
    
    printf("%s\n", __FUNCTION__);

	for (i = 0; i<no; i++) {
		charbuf[4 * i] = (uint8)(s[i] >> 24);
		charbuf[4 * i + 1] = (uint8)(s[i] >> 16);
		charbuf[4 * i + 2] = (uint8)(s[i] >> 8);
		charbuf[4 * i + 3] = (uint8)s[i];
	}

	if (_i2c_write(sla, suba, charbuf, 4 * no) == 0)
		return 1;
	else
		return 0;
}

/**
 * 向有子地址器件读取多个32位的数据。
 * @param[in]	sla		器件从机地址
 * @param[in]   suba	器件子地址
 * @param[in]   s		数据接收缓冲区指针
 * @param[in]   no		读取数据个数
 * @retval	1	成功
 * @retval	0	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
uint8 I2CReadMultiWord(uint8 sla, uint8 suba, uint32* s, uint8 no)
{
	uint8 	charbuf[20];
	uint32 	i;

    printf("%s\n", __FUNCTION__);

	if (_i2c_read(sla, suba, charbuf, 4 * no) == 0) {
		for (i = 0; i<no; i++) {
			s[i] = ((uint32)charbuf[4 * i]) << 24;
			s[i] |= ((uint32)charbuf[4 * i + 1]) << 16;
			s[i] |= ((uint32)charbuf[4 * i + 2]) << 8;
			s[i] |= ((uint32)charbuf[4 * i + 3]);
		}
		return 1;
	}
	else
		return 0;
}



/**
 * This is a brief description.
 * This is a detail description.
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description. 
 * @retval	0	成功
 * @retval	1	错误 
 * @par 标识符
 * 		保留
 * @par 其它
 * 		无
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
static unsigned char _i2c_write2(int fd_i2c,unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	if((fd_i2c < 0) || !buff) {
        printf("fd<0 or !buff\n");
        return 1;
    }
	
	//设置iic芯片地址
	if(ioctl(fd_i2c, RT2880_I2C_SET_ADDR, device_addr) != 0){
        printf("set device_addr error.\n");
        return 1;
    }
	
	//usleep(50000);
	//usleep(500);

	wdata2	.address = sub_addr;
	//wdata2.pData_i2c = buff;
	memcpy(wdata2.data_i2c,buff,ByteNo);
	wdata2.size = ByteNo;

	if(ioctl(fd_i2c, RT2880_I2C_WRITE, &wdata2) != 0){
        printf("sub and buff fail.\n");
        return 1;
    }

	//usleep(50000);
	//usleep(500);

    //printf("%s\n", __FUNCTION__);
    
	return 0;
}


/**
 * This is a brief description.
 * This is a detail description.
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description. 
 * @retval	0	成功
 * @retval	1	错误 
 * @par 标识符
 * 		保留
 * @par 其它
 * 		无
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
static unsigned char _i2c_read2(int fd_i2c,unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	if((fd_i2c < 0) || !buff){
        printf("%s> fd < 0\n",__FUNCTION__);
		return 1;
    }
	
	//设置iic芯片地址
	if(ioctl(fd_i2c, RT2880_I2C_SET_ADDR, device_addr) != 0){
        printf("%s> set device_addr fail.\n",__FUNCTION__);
		return 1;
    }

	//usleep(50000);
    //usleep(500);

	wdata2.address = sub_addr;
	//wdata2.pData_i2c = buff;
	//memcpy(wdata2.data_i2c,buff,ByteNo);
	wdata2.size = ByteNo;
	
	if (ioctl(fd_i2c, RT2880_I2C_READ, &wdata2) != 0){
        printf("%s> RT2880_I2C_READ fail.\n",__FUNCTION__);
		return 1;
    }

	if(wdata2.size != ByteNo){
        printf("%s> ByteNo fail. %d,%d\n",__FUNCTION__,wdata2.size,ByteNo);
		return 1;
    }

	memcpy(buff,wdata2.data_i2c,ByteNo);
	
	//usleep(50000);
	//usleep(500);

    //printf("%s\n", __FUNCTION__);
    
	return 0;
}

/**
 * 延时函数 样例，延时的单位为MS
 * @param[in]	inArgName input argument description.
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
void _alpu_delay_ms(unsigned int i)
{
	//Delay_ms(i);
	usleep(i*1000);
}

/**
 * 随机数的样例
 * @retval	 
 * @retval	 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
unsigned char _alpu_rand(void)   //Modify this fuction using RTC. But you should not change the function name.
{
  static unsigned long seed; // 2byte, must be a static variable

  seed = seed + rand(); // rand(); <------------------ add time value
  seed =  seed * 1103515245 + 12345;

  return (seed/65536) % 32768;
}


/**
 * This is a brief description.
 * This is a detail description.
 * @param[in] device_addr :设备地址，和您通信测试设备地址 是一致的（库中默认的值是7A 如果您驱动中设置不同，可以不使用这个数据）	
 * @param[in] sub_addr：子地址
 * @param[out] buff：存储数据的buff
 * @param[in] ByteNo:数据的长度
 * @retval	0	    成功
 * @retval	非零	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
unsigned char _i2c_read(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	//iic_read_fun()                          //your IIC read funtion 
	return  _i2c_read2(fd_i2c, device_addr, sub_addr, buff, ByteNo);
}


/**
 * This is a brief description.
 * This is a detail description.
 * @param[in] device_addr :设备地址，和您通信测试设备地址 是一致的（库中默认的值是7A 如果您驱动中设置不同，可以不使用这个数据）	
 * @param[in] sub_addr：子地址
 * @param[in] buff：存储数据的buff
 * @param[in] ByteNo:数据的长度
 * @retval	0	    成功
 * @retval	非零	错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
unsigned char _i2c_write(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
	//iic_write_fun()                          //your IIC write funtion
	return _i2c_write2(fd_i2c, device_addr,  sub_addr, buff, ByteNo);
}



/**
 *For Encryption mode, you are supposed to call the _alpum_process() function in ALPU Check fuction or main source.
 *The return value would be "0"(zero) if the library file is work well. otherwise, the return value would be error_code value.
 * @retval		    成功
 * @retval		错误 
 * @par 修改日志
 * 		XXX于201X-XX-XX创建
 */
#if test_i2c
void _alpuc_process_bypass(void)
{
	int i;
	int j=0;
    unsigned char error_code;
	unsigned char dx_data[8];		 // 计算的数据， 加密 正确的话应该和tx_data相等
	unsigned char tx_data[8];		//	随机数 或 您的系统的数据

	static int seed2=0;

    //for(j=0; j<1000; j++)   {
    for(j=0; j<1; j++)   {
		
#if 0		
	for(i=0; i<8; i++)
	{	
		tx_data[i] = _alpu_rand();
		dx_data[i] = 0;
	}
#else
	for(i=0; i<8; i++)
	{
		srand((int) time(0) + i + seed2++); //必须用srand函数产生随机种子，再用rand函数产生随机数
		tx_data[i] = rand()&0xff;
		dx_data[i] = 0;
	}
#endif	
	
		error_code = alpuc_process(tx_data,dx_data);  //加密API接口

		if(error_code){
			printf("\r\nAlpu-M Encryption Test Fail!!!\r\n");
			check_aplus_ok_g = 0;
			break;
		}

		else{
			printf("\r\nAlpu-M Encryption Test Success!!!\r\n");
			check_aplus_ok_g = 1;
    		}

    }

	//other functions..
}
#else 

unsigned char dec_tx_data[8];
unsigned char dec_rx_data[8];
unsigned char dec_dx_data[8];


static void _alpuc_bypass(void)
{
    int i;
    for ( i=0; i<8; i++ ) 
		dec_dx_data[i] = dec_tx_data[i] ^ 0x01 ;
}


//先用此函数测试通过，然后才能找厂家定制加密算法
//返回0表示成功
unsigned char _alpuc_process_bypass(void)
{
    unsigned char error_code;
    int i;

	char nm[16];
	
#if 0
	int fd_i2c;
	//打开iic设备
	snprintf(nm, 16, "/dev/%s", I2C_DEV_NAME);
	if ((fd_i2c = open(nm, O_RDONLY)) < 0) {
		printf("_alpuc_process_bypass(open i2c error)\n");
		return 1;
	}
#else
	if(fd_i2c <= 0)
		return 0x88;
#endif

	for(i=0; i<8;i++)
	{
		dec_tx_data[i] =0x00;
		dec_rx_data[i] =0x00;
		dec_dx_data[i] =0x00;
	}
	
	//Seed Generate
    //for(i=0; i<8; i++) dec_tx_data[i] = _alpu_rand();
    for(i=0; i<8; i++)
	{
		srand((int) time(0)+i); //必须用srand函数产生随机种子，再用rand函数产生随机数
		dec_tx_data[i] = rand()&0xff;
	}

    //Write Seed Data to ALPU-C
    unsigned char sub_address = 0x80;
    error_code = _i2c_write(DEVICE_ADDRESS, sub_address, dec_tx_data, 8);
    if ( error_code ) 
    {
    	//close(fd_i2c);
		return error_code ;
    }

    //Read Result Data from ALPU-C
    error_code = _i2c_read(DEVICE_ADDRESS, sub_address, dec_rx_data, 8);
    if ( error_code ) 
    {
    	//close(fd_i2c);
		return error_code ;
    }
	
    //Bypass Operation
    _alpuc_bypass();

    //Compare the encoded data and received data
    for (i=0; i<8; i++) 
    {
		if(dec_dx_data[i] != dec_rx_data[i]) 
		{
			//close(fd_i2c);
			printf("fail........\n");
			return 60;
		}
    }

	printf(" ok  ........\n");
	
	//关闭iic设备
	//close(fd_i2c);
	
    return 0;
}

void dsp_reset()
{
	printf("-->%s\n",__FUNCTION__);

    if (ioctl(fd_i2c, 99, NULL) < 0)
       return; 
	usleep(100);
    if (ioctl(fd_i2c, 88, NULL) < 0)
       return;
	usleep(290*1000);	
}

#endif



unsigned char alpuc_process(unsigned char *a, unsigned char *b)
{

}





































