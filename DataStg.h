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
**	文件名	：DataStg.h
**	
**	程序员	：陈家承
**
**	日　期  ：2009年1月19日
**
**	文件描述：各数据类型转拆成多个字节存储，从多个保存的字节读出，转换成相应的类型的数。
**
**
***************************************************************************************************
*/
#ifndef _DataStg_H
#define _DataStg_H

#include <stdint.h>
#include "MyType.h"
#include "UserMath.h"

extern void DstFlt2Chr(uint8 *px, fp32 fVal);

extern fp32 DstChr2Flt(uint8 *px);

extern void DstInt2Chr(uint8 *px, int32 iVal);

extern int32 DstChr2Int(uint8 *px);

extern void DstSht2Chr(uint8 *px, int16 sVal);

extern int16 DstChr2Sht(uint8 *px);

extern void DSTStr2Byte(uint8 *pDat, void *pStr, int32 len);

extern void DSTByte2Str(uint8 *pDat, void *pStr, int32 len);
 
#endif


