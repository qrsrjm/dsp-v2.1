



#ifndef  I2C_H
#define  I2C_H

#include  "MyType.h"

#define I2C_DELAYTYPE	0

#define ENABLE    (1)
#define DISABLE	  (0)


/** 四舍五入 */
#define Round(x)	(((x)>=0.0)?((int)((x)+0.5)):(-(int)(-(x)+0.5)))

/** 调试代码的宏 */
//#define DEBUG
#ifdef  DEBUG
#define DBG(CODE) CODE
#else
#define DBG(CODE)
#endif

/** i2c 命令*/
#define	RT2880_I2C_READ_STR			"read"	/* I2C read operation */
#define	RT2880_I2C_WRITE_STR		"write"	/* I2C read operation */

#define RT2880_I2C_DUMP			1
#define RT2880_I2C_READ			3
#define RT2880_I2C_WRITE		5
#define RT2880_I2C_SET_ADDR		7

#define I2C_DEV_NAME			"i2cM0"


extern unsigned char DEVICE_ADDRESS;  /// Write Addr : 0x7a, Read Addr, 0x7a | 0x01


typedef struct i2c_write_data2 {
	unsigned long address;
	//unsigned long size;
	unsigned char data_i2c[128];
    unsigned long size;
} I2C_WRITE2;

///加密状态标识，1表示ok
extern int check_aplus_ok_g;


int open_fd_i2c(void);
int close_fd_i2c(void);

void dsp_reset();


/** 加密接口*/
extern unsigned char alpuc_process(unsigned char *, unsigned char *);

///These fuction below are necessary for ecryption mode.
///Please declare these fuction as below in your ALPU Check function or main source.
///下面函数需要调用时实现
unsigned char _alpu_rand(void);
void _alpu_delay_ms(unsigned int i);
///Please follow the format of IIC read and write
unsigned char _i2c_read(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo);
unsigned char _i2c_write(unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo);

unsigned char _alpuc_process_bypass(void);

extern void	I2CInit(uint32 fi2c);

extern uint8 	I2CDlyEnd (uint32 dly);

extern uint8 	I2CSendByte(uint8 sla, uint8 dat);

extern uint8 	I2CRcvByte(uint8 sla, uint8 *dat);

extern uint8 	I2CSendStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);

extern uint8 	I2CRcvStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);

extern uint8 	I2CWriteMultiWord(uint8 SlaAddr, uint8 SubAddr, uint32* WBuf, uint8 Num);

extern uint8 	I2CReadMultiWord(uint8 SlaAddr, uint8 SubAddr, uint32* Buf, uint8 Num);

#endif


