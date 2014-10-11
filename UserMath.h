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
**	文件名	：UserMath.h
**	
**	程序员	：陈家承
**
**	日　期  ：2009年4月20日
**
**	文件描述：用户自定义的数学函数库。
**			  有时候根据特定的应用来定义自己的函数要比系统自带的执行效率要高。
**			  
**
***************************************************************************************************
*/
#ifndef _UMATH_H
#define _UMATH_H

//#include <stdlib.h>

#include "MyType.h"


extern fp32 MathRound(fp32 indata, int8 precision);

extern void MathRound1(fp32* indata, int8 precision);

#endif


