

#include "TAS3xxx.h"
#include "I2C.h"

#include <math.h>

/*
***************************************************************************************************
**
**                                          DapDelay()
**
**
**	功能描述：系统最小单位的延时。
**
**	参  数  ：i
**
**	返回值  ：无
**
**  备  注  ：i = 11   		 1 us
**			  i = 110   	10 us
**			  i = 1106	   100 us
**			  i = 11059		 1 ms
**
**			  其它的延时可以通过对 11059*(10^n) 得到
**
**			  与系统的 Fcclk 时钟有关。系统时钟改变时会不同，时间的宏在 Includes.h 中。
**
***************************************************************************************************
*/
void DapDelay(uint32 i)
{
	while (--i);
}

/*
***************************************************************************************************
**
**                                         DAPFloatTo25P23()
**
**
**	功能描述：浮点转25.23格式
**
**	参  数  ：fval		要转换的浮点数
**			  ceof    	返回uint32类型的数组
**
**	返回值  ：无
**
***************************************************************************************************
*/
void DAPFloatTo25P23(fp64 fval, uint32 *ceof)
{
	int32 	b, ret;
	fp64   	a;


	b = (int32)fval;
	a = fval - b;

	ret = a * 0x00800000;

	ceof[0] = b >> 9;
	ceof[1] = ret | (b << 23);
}
/*
***************************************************************************************************
**
**                                         DAPFloatTo5P23()
**
**
**	功能描述：浮点转5.23格式
**
**	参  数  ：fval		要转换的浮点数
**
**	返回值  ：转换后的5.23格式数（uint32的低28位）
**
***************************************************************************************************
*/
uint32 DAPFloatTo5P23(fp64 fval)
{
	return (int32)(fval * 0x00800000);
}
/*
***************************************************************************************************
**
**                                         DAPBesAndButLPF()
**
**
**	功能描述：多阶Butterworth、Bessel低通滤波器
**
**	参  数  ：order   滤波器的阶数
**			  fc      中心频率
**			  sel     两种滤波器的选择   0: Butterworth,1:Bessel
**
**	返回值  ：coef	  返回多阶数字滤波器转移函数的二十个系数
**
**	备  注  ：order 音频领域最高用到八阶,双线性变换中的c=2，这里直接用了，不想又多定义一个变量。
**
***************************************************************************************************
*/
void DAPBesAndButLPF(uint8 order, fp64 fc, uint32* coef, uint8 sel)
{
	fp64 w0, oc, p[4];
	fp64 a1[4], a2[4], b0[4], b1[4], b2[4];



	w0 = 2 * PI*fc / FS;
	oc = 2 * tan(w0 / 2);

	switch (order) {
	case 1:
		b0[0] = oc / (2 + oc);
		b1[0] = b0[0];
		b2[0] = 0;
		a1[0] = (oc - 2) / (2 + oc);
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 2:
		if (sel == 0) {
			p[0] = 1.41421356237309;
		}
		else {
			p[0] = 1.73205080756888;
		}

		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 3:
		if (sel == 0) {
			p[0] = 1;
			p[1] = 1;
		}
		else {
			p[0] = 1.49128077169616;
			p[1] = 0.94160002653321;
		}

		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = p[1] * oc / (2 + p[1] * oc);
		b1[1] = b0[1];
		b2[1] = 0;
		a1[1] = (p[1] * oc - 2) / (2 + p[1] * oc);
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 4:
		if (sel == 0) {
			p[0] = 0.76536686473018;
			p[1] = 1.84775906502257;
		}
		else {
			p[0] = 1.31442234334377;
			p[1] = 1.80951759357649;
		}

		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = oc*oc / (4 + 2 * p[1] * oc + oc*oc);
		b1[1] = 2 * b0[1];
		b2[1] = b0[1];
		a1[1] = 2 * (oc*oc - 4) / (4 + 2 * p[1] * oc + oc*oc);
		a2[1] = (4 - 2 * p[1] * oc + oc*oc) / (4 + 2 * p[1] * oc + oc*oc);

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 6:
		if (sel == 0) {
			p[0] = 0.51763809020504;
			p[1] = 1.41421356237309;
			p[2] = 1.93185165257814;
		}
		else {
			p[0] = 1.81878136609445;
			p[1] = 1.59930837166566;
			p[2] = 1.07710536333862;
		}

		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = oc*oc / (4 + 2 * p[1] * oc + oc*oc);
		b1[1] = 2 * b0[1];
		b2[1] = b0[1];
		a1[1] = 2 * (oc*oc - 4) / (4 + 2 * p[1] * oc + oc*oc);
		a2[1] = (4 - 2 * p[1] * oc + oc*oc) / (4 + 2 * p[1] * oc + oc*oc);

		b0[2] = oc*oc / (4 + 2 * p[2] * oc + oc*oc);
		b1[2] = 2 * b0[2];
		b2[2] = b0[2];
		a1[2] = 2 * (oc*oc - 4) / (4 + 2 * p[2] * oc + oc*oc);
		a2[2] = (4 - 2 * p[2] * oc + oc*oc) / (4 + 2 * p[2] * oc + oc*oc);

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 8:
		if (sel == 0) {
			p[0] = 0.39018064403226;
			p[1] = 1.11114046603920;
			p[2] = 1.66293922460509;
			p[3] = 1.96157056080646;
		}
		else {
			p[0] = 1.81936630933058;
			p[1] = 1.69465016047187;
			p[2] = 1.42227636169708;
			p[3] = 0.92434808250642;
		}

		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = oc*oc / (4 + 2 * p[1] * oc + oc*oc);
		b1[1] = 2 * b0[1];
		b2[1] = b0[1];
		a1[1] = 2 * (oc*oc - 4) / (4 + 2 * p[1] * oc + oc*oc);
		a2[1] = (4 - 2 * p[1] * oc + oc*oc) / (4 + 2 * p[1] * oc + oc*oc);

		b0[2] = oc*oc / (4 + 2 * p[2] * oc + oc*oc);
		b1[2] = 2 * b0[2];
		b2[2] = b0[2];
		a1[2] = 2 * (oc*oc - 4) / (4 + 2 * p[2] * oc + oc*oc);
		a2[2] = (4 - 2 * p[2] * oc + oc*oc) / (4 + 2 * p[2] * oc + oc*oc);

		b0[3] = oc*oc / (4 + 2 * p[3] * oc + oc*oc);
		b1[3] = 2 * b0[3];
		b2[3] = b0[3];
		a1[3] = 2 * (oc*oc - 4) / (4 + 2 * p[3] * oc + oc*oc);
		a2[3] = (4 - 2 * p[3] * oc + oc*oc) / (4 + 2 * p[3] * oc + oc*oc);
		break;

	default:
		b0[0] = 1;
		b1[0] = 0;
		b2[0] = 0;
		a1[0] = 0;
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	}

	coef[0] = DAPFloatTo5P23(b0[0]);
	coef[1] = DAPFloatTo5P23(b1[0]);
	coef[2] = DAPFloatTo5P23(b2[0]);
	coef[3] = DAPFloatTo5P23(-a1[0]);
	coef[4] = DAPFloatTo5P23(-a2[0]);

	coef[5] = DAPFloatTo5P23(b0[1]);
	coef[6] = DAPFloatTo5P23(b1[1]);
	coef[7] = DAPFloatTo5P23(b2[1]);
	coef[8] = DAPFloatTo5P23(-a1[1]);
	coef[9] = DAPFloatTo5P23(-a2[1]);

	coef[10] = DAPFloatTo5P23(b0[2]);
	coef[11] = DAPFloatTo5P23(b1[2]);
	coef[12] = DAPFloatTo5P23(b2[2]);
	coef[13] = DAPFloatTo5P23(-a1[2]);
	coef[14] = DAPFloatTo5P23(-a2[2]);

	coef[15] = DAPFloatTo5P23(b0[3]);
	coef[16] = DAPFloatTo5P23(b1[3]);
	coef[17] = DAPFloatTo5P23(b2[3]);
	coef[18] = DAPFloatTo5P23(-a1[3]);
	coef[19] = DAPFloatTo5P23(-a2[3]);

}
/*
***************************************************************************************************
**
**                                         DAPBesAndButHPF()
**
**
**	功能描述：多阶Butterworth、Bessel高通滤波器
**
**	参  数  ：order   滤波器的阶数
**			  fc      中心频率
**			  sel     两种滤波器的选择   0: Butterworth,1:Bessel
**
**	返回值  ：coef	  返回多阶数字滤波器转移函数的二十个系数
**
**	备  注  ：order 音频领域最高用到八阶,双线性变换中的c=2，这里直接用了，不想又多定义一个变量。
**
***************************************************************************************************
*/
void DAPBesAndButHPF(uint8 order, fp64 fc, uint32* coef, uint8 sel)
{
	fp64 w0, oc, p[4], c1;
	fp64 a1[4], a2[4], b0[4], b1[4], b2[4];



	w0 = 2 * PI*fc / FS;
	oc = 2 * tan(w0 / 2);
	c1 = oc*tan(w0 / 2);            /* 从低通到高通转换的c的系数 */

	switch (order) {
	case 1:
		p[0] = 1;

		b0[0] = oc / (c1 + p[0] * oc);
		b1[0] = -b0[0];
		b2[0] = 0;
		a1[0] = -(p[0] * oc - c1) / (c1 + p[0] * oc);
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 2:
		if (sel == 0) {
			p[0] = 1.41421356237309;
		}
		else {
			p[0] = 1.73205080756888;
		}

		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 3:
		if (sel == 0) {
			p[0] = 1;
			p[1] = 1;
		}
		else {
			p[0] = 1.49128077169616;
			p[1] = 0.94160002653321;
		}

		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = p[1] * oc / (c1 + p[1] * oc);
		b1[1] = -b0[1];
		b2[1] = 0;
		a1[1] = -(p[1] * oc - c1) / (c1 + p[1] * oc);
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 4:
		if (sel == 0) {
			p[0] = 0.76536686473018;
			p[1] = 1.84775906502257;
		}
		else {
			p[0] = 1.31442234334377;
			p[1] = 1.80951759357649;
		}

		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = oc*oc / (c1*c1 + c1*p[1] * oc + oc*oc);
		b1[1] = -2 * b0[1];
		b2[1] = b0[1];
		a1[1] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[1] * oc + oc*oc);
		a2[1] = (c1*c1 - c1*p[1] * oc + oc*oc) / (c1*c1 + c1*p[1] * oc + oc*oc);

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 6:
		if (sel == 0) {
			p[0] = 0.51763809020504;
			p[1] = 1.41421356237309;
			p[2] = 1.93185165257814;
		}
		else {
			p[0] = 1.81878136609445;
			p[1] = 1.59930837166566;
			p[2] = 1.07710536333862;
		}

		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = oc*oc / (c1*c1 + c1*p[1] * oc + oc*oc);
		b1[1] = -2 * b0[1];
		b2[1] = b0[1];
		a1[1] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[1] * oc + oc*oc);
		a2[1] = (c1*c1 - c1*p[1] * oc + oc*oc) / (c1*c1 + c1*p[1] * oc + oc*oc);

		b0[2] = oc*oc / (c1*c1 + c1*p[2] * oc + oc*oc);
		b1[2] = -2 * b0[2];
		b2[2] = b0[2];
		a1[2] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[2] * oc + oc*oc);
		a2[2] = (c1*c1 - c1*p[2] * oc + oc*oc) / (c1*c1 + c1*p[2] * oc + oc*oc);

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 8:
		if (sel == 0) {
			p[0] = 0.39018064403226;
			p[1] = 1.11114046603920;
			p[2] = 1.66293922460509;
			p[3] = 1.96157056080646;
		}
		else {
			p[0] = 1.81936630933058;
			p[1] = 1.69465016047187;
			p[2] = 1.42227636169708;
			p[3] = 0.92434808250642;
		}

		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = oc*oc / (c1*c1 + c1*p[1] * oc + oc*oc);
		b1[1] = -2 * b0[1];
		b2[1] = b0[1];
		a1[1] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[1] * oc + oc*oc);
		a2[1] = (c1*c1 - c1*p[1] * oc + oc*oc) / (c1*c1 + c1*p[1] * oc + oc*oc);

		b0[2] = oc*oc / (c1*c1 + c1*p[2] * oc + oc*oc);
		b1[2] = -2 * b0[2];
		b2[2] = b0[2];
		a1[2] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[2] * oc + oc*oc);
		a2[2] = (c1*c1 - c1*p[2] * oc + oc*oc) / (c1*c1 + c1*p[2] * oc + oc*oc);

		b0[3] = oc*oc / (c1*c1 + c1*p[3] * oc + oc*oc);
		b1[3] = -2 * b0[3];
		b2[3] = b0[3];
		a1[3] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[3] * oc + oc*oc);
		a2[3] = (c1*c1 - c1*p[3] * oc + oc*oc) / (c1*c1 + c1*p[3] * oc + oc*oc);
		break;

	default:
		b0[0] = 1;
		b1[0] = 0;
		b2[0] = 0;
		a1[0] = 0;
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	}

	coef[0] = DAPFloatTo5P23(b0[0]);
	coef[1] = DAPFloatTo5P23(b1[0]);
	coef[2] = DAPFloatTo5P23(b2[0]);
	coef[3] = DAPFloatTo5P23(-a1[0]);
	coef[4] = DAPFloatTo5P23(-a2[0]);

	coef[5] = DAPFloatTo5P23(b0[1]);
	coef[6] = DAPFloatTo5P23(b1[1]);
	coef[7] = DAPFloatTo5P23(b2[1]);
	coef[8] = DAPFloatTo5P23(-a1[1]);
	coef[9] = DAPFloatTo5P23(-a2[1]);

	coef[10] = DAPFloatTo5P23(b0[2]);
	coef[11] = DAPFloatTo5P23(b1[2]);
	coef[12] = DAPFloatTo5P23(b2[2]);
	coef[13] = DAPFloatTo5P23(-a1[2]);
	coef[14] = DAPFloatTo5P23(-a2[2]);

	coef[15] = DAPFloatTo5P23(b0[3]);
	coef[16] = DAPFloatTo5P23(b1[3]);
	coef[17] = DAPFloatTo5P23(b2[3]);
	coef[18] = DAPFloatTo5P23(-a1[3]);
	coef[19] = DAPFloatTo5P23(-a2[3]);

}
/*
***************************************************************************************************
**
**                                         DAPLinkwitzLPF()
**
**
**	功能描述：多阶Linkwitz低通滤波器
**
**	参  数  ：order   滤波器的阶数
**			  fc      中心频率
**
**	返回值  ：coef	  返回多阶数字滤波器转移函数的二十个系数
**
**	备  注  ：Linkwitz是两个相同的阶数的Butterworth滤波器的叠加。
**
***************************************************************************************************
*/


void DAPLinkwitzLPF(uint8 order, fp64 fc, uint32* coef)
{
	fp64 w0, oc, p[4];
	fp64 a1[4], a2[4], b0[4], b1[4], b2[4];



	w0 = 2 * PI*fc / FS;
	oc = 2 * tan(w0 / 2);

	switch (order) {
	case 2:
		b0[0] = oc / (2 + oc);
		b1[0] = b0[0];
		b2[0] = 0;
		a1[0] = (oc - 2) / (2 + oc);
		a2[0] = 0;

		b0[1] = b0[0];
		b1[1] = b1[0];
		b2[1] = b2[0];
		a1[1] = a1[0];
		a2[1] = a2[0];

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 4:
		p[0] = 1.41421356237309;
		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		b0[1] = b0[0];
		b1[1] = b1[0];
		b2[1] = b2[0];
		a1[1] = a1[0];
		a2[1] = a2[0];

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 6:
		p[0] = 0.76536686473018;
		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		p[1] = 1.84775906502257;
		b0[1] = oc*oc / (4 + 2 * p[1] * oc + oc*oc);
		b1[1] = 2 * b0[1];
		b2[1] = b0[1];
		a1[1] = 2 * (oc*oc - 4) / (4 + 2 * p[1] * oc + oc*oc);
		a2[1] = (4 - 2 * p[1] * oc + oc*oc) / (4 + 2 * p[1] * oc + oc*oc);

		p[2] = 1.41421356237309;
		b0[2] = oc*oc / (4 + 2 * p[2] * oc + oc*oc);
		b1[2] = 2 * b0[2];
		b2[2] = b0[2];
		a1[2] = 2 * (oc*oc - 4) / (4 + 2 * p[2] * oc + oc*oc);
		a2[2] = (4 - 2 * p[2] * oc + oc*oc) / (4 + 2 * p[2] * oc + oc*oc);

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 8:
		p[0] = 0.76536686473018;
		b0[0] = oc*oc / (4 + 2 * p[0] * oc + oc*oc);
		b1[0] = 2 * b0[0];
		b2[0] = b0[0];
		a1[0] = 2 * (oc*oc - 4) / (4 + 2 * p[0] * oc + oc*oc);
		a2[0] = (4 - 2 * p[0] * oc + oc*oc) / (4 + 2 * p[0] * oc + oc*oc);

		p[1] = 1.84775906502257;
		b0[1] = oc*oc / (4 + 2 * p[1] * oc + oc*oc);
		b1[1] = 2 * b0[1];
		b2[1] = b0[1];
		a1[1] = 2 * (oc*oc - 4) / (4 + 2 * p[1] * oc + oc*oc);
		a2[1] = (4 - 2 * p[1] * oc + oc*oc) / (4 + 2 * p[1] * oc + oc*oc);

		b0[2] = b0[0];
		b1[2] = b1[0];
		b2[2] = b2[0];
		a1[2] = a1[0];
		a2[2] = a2[0];

		b0[3] = b0[1];
		b1[3] = b1[1];
		b2[3] = b2[1];
		a1[3] = a1[1];
		a2[3] = a2[1];
		break;

	default:
		b0[0] = 1;
		b1[0] = 0;
		b2[0] = 0;
		a1[0] = 0;
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	}

	coef[0] = DAPFloatTo5P23(b0[0]);
	coef[1] = DAPFloatTo5P23(b1[0]);
	coef[2] = DAPFloatTo5P23(b2[0]);
	coef[3] = DAPFloatTo5P23(-a1[0]);
	coef[4] = DAPFloatTo5P23(-a2[0]);

	coef[5] = DAPFloatTo5P23(b0[1]);
	coef[6] = DAPFloatTo5P23(b1[1]);
	coef[7] = DAPFloatTo5P23(b2[1]);
	coef[8] = DAPFloatTo5P23(-a1[1]);
	coef[9] = DAPFloatTo5P23(-a2[1]);

	coef[10] = DAPFloatTo5P23(b0[2]);
	coef[11] = DAPFloatTo5P23(b1[2]);
	coef[12] = DAPFloatTo5P23(b2[2]);
	coef[13] = DAPFloatTo5P23(-a1[2]);
	coef[14] = DAPFloatTo5P23(-a2[2]);

	coef[15] = DAPFloatTo5P23(b0[3]);
	coef[16] = DAPFloatTo5P23(b1[3]);
	coef[17] = DAPFloatTo5P23(b2[3]);
	coef[18] = DAPFloatTo5P23(-a1[3]);
	coef[19] = DAPFloatTo5P23(-a2[3]);

}
/*
***************************************************************************************************
**
**                                         DAPLinkwitzHPF()
**
**
**	功能描述：多阶Linkwitz高通滤波器
**
**	参  数  ：order   滤波器的阶数
**			  fc      中心频率
**
**	返回值  ：coef	  返回多阶数字滤波器转移函数的二十个系数
**
**	备  注  ：Linkwitz是两个相同的阶数的Butterworth滤波器的叠加。
**
***************************************************************************************************
*/
void DAPLinkwitzHPF(uint8 order, fp64 fc, uint32* coef)
{
	fp64 w0, oc, p[4], c1;
	fp64 a1[4], a2[4], b0[4], b1[4], b2[4];



	w0 = 2 * PI*fc / FS;
	oc = 2 * tan(w0 / 2);
	c1 = oc*tan(w0 / 2);

	switch (order) {
	case 2:
		b0[0] = oc / (c1 + oc);
		b1[0] = -b0[0];
		b2[0] = 0;
		a1[0] = -(oc - c1) / (c1 + oc);
		a2[0] = 0;

		b0[1] = b0[0];
		b1[1] = b1[0];
		b2[1] = b2[0];
		a1[1] = a1[0];
		a2[1] = a2[0];

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 4:
		p[0] = 1.41421356237309;
		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		b0[1] = b0[0];
		b1[1] = b1[0];
		b2[1] = b2[0];
		a1[1] = a1[0];
		a2[1] = a2[0];

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 6:
		p[0] = 0.76536686473018;
		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		p[1] = 1.84775906502257;
		b0[1] = oc*oc / (c1*c1 + c1*p[1] * oc + oc*oc);
		b1[1] = -2 * b0[1];
		b2[1] = b0[1];
		a1[1] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[1] * oc + oc*oc);
		a2[1] = (c1*c1 - c1*p[1] * oc + oc*oc) / (c1*c1 + c1*p[1] * oc + oc*oc);

		p[2] = 1.41421356237309;
		b0[2] = oc*oc / (c1*c1 + c1*p[2] * oc + oc*oc);
		b1[2] = -2 * b0[2];
		b2[2] = b0[2];
		a1[2] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[2] * oc + oc*oc);
		a2[2] = (c1*c1 - c1*p[2] * oc + oc*oc) / (c1*c1 + c1*p[2] * oc + oc*oc);

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	case 8:
		p[0] = 0.76536686473018;
		b0[0] = oc*oc / (c1*c1 + c1*p[0] * oc + oc*oc);
		b1[0] = -2 * b0[0];
		b2[0] = b0[0];
		a1[0] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[0] * oc + oc*oc);
		a2[0] = (c1*c1 - c1*p[0] * oc + oc*oc) / (c1*c1 + c1*p[0] * oc + oc*oc);

		p[1] = 1.84775906502257;
		b0[1] = oc*oc / (c1*c1 + c1*p[1] * oc + oc*oc);
		b1[1] = -2 * b0[1];
		b2[1] = b0[1];
		a1[1] = -2 * (oc*oc - c1*c1) / (c1*c1 + c1*p[1] * oc + oc*oc);
		a2[1] = (c1*c1 - c1*p[1] * oc + oc*oc) / (c1*c1 + c1*p[1] * oc + oc*oc);

		b0[2] = b0[0];
		b1[2] = b1[0];
		b2[2] = b2[0];
		a1[2] = a1[0];
		a2[2] = a2[0];

		b0[3] = b0[1];
		b1[3] = b1[1];
		b2[3] = b2[1];
		a1[3] = a1[1];
		a2[3] = a2[1];
		break;

	default:
		b0[0] = 1;
		b1[0] = 0;
		b2[0] = 0;
		a1[0] = 0;
		a2[0] = 0;

		b0[1] = 1;
		b1[1] = 0;
		b2[1] = 0;
		a1[1] = 0;
		a2[1] = 0;

		b0[2] = 1;
		b1[2] = 0;
		b2[2] = 0;
		a1[2] = 0;
		a2[2] = 0;

		b0[3] = 1;
		b1[3] = 0;
		b2[3] = 0;
		a1[3] = 0;
		a2[3] = 0;
		break;

	}

	coef[0] = DAPFloatTo5P23(b0[0]);
	coef[1] = DAPFloatTo5P23(b1[0]);
	coef[2] = DAPFloatTo5P23(b2[0]);
	coef[3] = DAPFloatTo5P23(-a1[0]);
	coef[4] = DAPFloatTo5P23(-a2[0]);

	coef[5] = DAPFloatTo5P23(b0[1]);
	coef[6] = DAPFloatTo5P23(b1[1]);
	coef[7] = DAPFloatTo5P23(b2[1]);
	coef[8] = DAPFloatTo5P23(-a1[1]);
	coef[9] = DAPFloatTo5P23(-a2[1]);

	coef[10] = DAPFloatTo5P23(b0[2]);
	coef[11] = DAPFloatTo5P23(b1[2]);
	coef[12] = DAPFloatTo5P23(b2[2]);
	coef[13] = DAPFloatTo5P23(-a1[2]);
	coef[14] = DAPFloatTo5P23(-a2[2]);

	coef[15] = DAPFloatTo5P23(b0[3]);
	coef[16] = DAPFloatTo5P23(b1[3]);
	coef[17] = DAPFloatTo5P23(b2[3]);
	coef[18] = DAPFloatTo5P23(-a1[3]);
	coef[19] = DAPFloatTo5P23(-a2[3]);

}

/*
***************************************************************************************************
**
**                                         BandPF2Order(()
**
**
**	功能描述：2阶带通滤波器
**
**	参  数  ：order   滤波器的阶数
**			  fc      中心频率
**            GainDb 增益Db
**			  bandwidth  带宽
**	返回值  ：coef	  返回2阶数字滤波器转移函数的二十个系数
**
**	备  注  ：Linkwitz是两个相同的阶数的Butterworth滤波器的叠加。
**
***************************************************************************************************
*/
void  BandPF2Order(fp64 fc, fp64 GainDb, fp64 bandwidth, uint32* coef)
{
	fp64 w0, gainLinear, alpha;
	fp64 a0, a1, a2, b0, b1, b2;
	w0 = 2 * PI*fc / FS;
	gainLinear = pow(10, GainDb / 20);//10^(GainDb/20);

	alpha = sin(w0)*sinh(log(2.0) / 2 * bandwidth*w0 / sin(w0));
	a0 = 1 + alpha;
	a1 = -2 * cos(w0) / a0;
	a2 = (1 - alpha) / a0;
	b0 = alpha*gainLinear / a0;
	b1 = 0 / a0;
	b2 = -alpha*gainLinear / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(a1);
	coef[4] = DAPFloatTo5P23(a2);
}
/*
***************************************************************************************************
**
**                                        DAPBiquadFilter()
**
**
**	功能描述：二阶椭圆逼近，均衡滤波器系数
**
**	参  数  ：fc	  中心频率
**			  gain    增益系数
**			  q       滤波器的Q值（品质系数），标志滤波的宽窄，与滤波器的带宽有对应关系
**
**	返回值  ：coef	  返回二阶数字滤波器转移函数的五系数
**
***************************************************************************************************
*/
void DAPBiquadFilter(fp64 fc, fp64 gain, fp64 q, uint32* coef)
{
	fp64 w0, alpha, A;
	fp64 a0, a1, a2, b0, b1, b2;



	w0 = 2 * PI*fc / FS;
	A = pow(10, gain / 40);
	alpha = sin(w0) / (2 * q);
	a0 = 1 + alpha / A;

	b0 = (1 + alpha*A) / a0;
	b1 = -2 * cos(w0) / a0;
	b2 = (1 - alpha*A) / a0;
	a1 = -2 * cos(w0) / a0;
	a2 = (1 - alpha / A) / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(-a1);
	coef[4] = DAPFloatTo5P23(-a2);
}
/*
***************************************************************************************************
**
**                                        DAPAllpassFilter()
**
**
**	功能描述：二阶椭圆逼近，全通滤波器系数
**
**	参  数  ：fc	  中心频率
**			  gain    增益系数
**			  q       滤波器的Q值（品质系数），标志滤波的宽窄，与滤波器的带宽有对应关系
**
**	返回值  ：coef	  返回二阶数字滤波器转移函数的五系数
**
***************************************************************************************************
*/
void DAPAllpassFilter(fp64 fc, fp64 gain, fp64 q, uint32* coef)
{
	fp64 w0, alpha;
	fp64 a0, a1, a2, b0, b1, b2;



	w0 = 2 * PI*fc / FS;
	alpha = sin(w0) / (2 * q);
	a0 = 1 + alpha;

	b0 = (1 - alpha) / a0;
	b1 = -2 * cos(w0) / a0;
	b2 = (1 + alpha) / a0;
	a1 = -2 * cos(w0) / a0;
	a2 = (1 - alpha) / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(-a1);
	coef[4] = DAPFloatTo5P23(-a2);
}
/*
***************************************************************************************************
**
**                                          DAPBass()
**
**
**	功能描述：二阶椭圆逼近，Low Shelf Filter系数
**
**	参  数  ：fc	  中心频率
**			  gain    增益系数
**			  q       滤波器的Q值（品质系数），标志滤波的宽窄，与滤波器的带宽有对应关系
**
**	返回值  ：coef	  返回二阶数字滤波器转移函数的五系数
**
***************************************************************************************************
*/
void DAPToneBass(fp64 fc, fp64 gain, fp64 q, uint32* coef)
{
	fp64 w0, alpha, A;
	fp64 a0, a1, a2, b0, b1, b2;



	w0 = 2 * PI*fc / FS;
	A = pow(10, gain / 40);
	alpha = sin(w0) / (2 * q);
	a0 = (A + 1) + (A - 1)*cos(w0) + 2 * sqrt(A)*alpha;

	b0 = A*((A + 1) - (A - 1)*cos(w0) + 2 * sqrt(A)*alpha) / a0;
	b1 = 2 * A*((A - 1) - (A + 1)*cos(w0)) / a0;
	b2 = A*((A + 1) - (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;
	a1 = -2 * ((A - 1) + (A + 1)*cos(w0)) / a0;
	a2 = ((A + 1) + (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(-a1);
	coef[4] = DAPFloatTo5P23(-a2);
}

/*
***************************************************************************************************
**
**                                          DAPTreble()
**
**
**	功能描述：二阶椭圆逼近，High Shelf Filter系数
**
**	参  数  ：fc	  中心频率
**			  gain    增益系数
**			  q       滤波器的Q值（品质系数），标志滤波的宽窄，与滤波器的带宽有对应关系
**
**	返回值  ：coef	  返回二阶数字滤波器转移函数的五系数
**
***************************************************************************************************
*/
void DAPToneTreble(fp64 fc, fp64 gain, fp64 q, uint32* coef)
{
	fp64 w0, alpha, A;
	fp64 a0, a1, a2, b0, b1, b2;



	w0 = 2 * PI*fc / FS;
	A = pow(10, gain / 40);
	alpha = sin(w0) / (2 * q);
	a0 = (A + 1) - (A - 1)*cos(w0) + 2 * sqrt(A)*alpha;

	b0 = A*((A + 1) + (A - 1)*cos(w0) + 2 * sqrt(A)*alpha) / a0;
	b1 = -2 * A*((A - 1) + (A + 1)*cos(w0)) / a0;
	b2 = A*((A + 1) + (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;
	a1 = 2 * ((A - 1) - (A + 1)*cos(w0)) / a0;
	a2 = ((A + 1) - (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(-a1);
	coef[4] = DAPFloatTo5P23(-a2);
}

/*
***************************************************************************************************
**
**                                          DAPBass()
**
**
**	功能描述：二阶椭圆逼近，Low Shelf Filter系数
**
**	参  数  ：fc	  中心频率
**			  gain    增益系数
**			  q       滤波器的Q值（品质系数），标志滤波的宽窄，与滤波器的带宽有对应关系
**
**	返回值  ：coef	  返回二阶数字滤波器转移函数的五系数
**
***************************************************************************************************
*/
void DAPToneMid(fp64 fc1, fp64 fc2, fp64 gain, fp64 q, uint32* coef)
{
	fp64 w0, alpha, A;
	fp64 a0, a1, a2, b0, b1, b2;


	w0 = 2 * PI*fc2 / FS;
	A = pow(10, gain / 40);
	alpha = sin(w0) / (2 * q);
	a0 = (A + 1) + (A - 1)*cos(w0) + 2 * sqrt(A)*alpha;

	b0 = ((A + 1) - (A - 1)*cos(w0) + 2 * sqrt(A)*alpha) / a0;
	b1 = 2 * ((A - 1) - (A + 1)*cos(w0)) / a0;
	b2 = ((A + 1) - (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;
	a1 = -2 * ((A - 1) + (A + 1)*cos(w0)) / a0;
	a2 = ((A + 1) + (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;

	coef[0] = DAPFloatTo5P23(b0);
	coef[1] = DAPFloatTo5P23(b1);
	coef[2] = DAPFloatTo5P23(b2);
	coef[3] = DAPFloatTo5P23(-a1);
	coef[4] = DAPFloatTo5P23(-a2);

	w0 = 2 * PI*fc1 / FS;
	alpha = sin(w0) / (2 * q);
	a0 = (A + 1) - (A - 1)*cos(w0) + 2 * sqrt(A)*alpha;

	b0 = ((A + 1) + (A - 1)*cos(w0) + 2 * sqrt(A)*alpha) / a0;
	b1 = -2 * ((A - 1) + (A + 1)*cos(w0)) / a0;
	b2 = ((A + 1) + (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;
	a1 = 2 * ((A - 1) - (A + 1)*cos(w0)) / a0;
	a2 = ((A + 1) - (A - 1)*cos(w0) - 2 * sqrt(A)*alpha) / a0;

	coef[5] = DAPFloatTo5P23(b0);
	coef[6] = DAPFloatTo5P23(b1);
	coef[7] = DAPFloatTo5P23(b2);
	coef[8] = DAPFloatTo5P23(-a1);
	coef[9] = DAPFloatTo5P23(-a2);
}

/*
***************************************************************************************************
**
**                                        TAS3108Reset()
**
**
**	功能描述：DAP_TAS3108芯片硬件复位
**
**	参  数  ：无
**
**	返回值  ：无
**   注：RST_TAS3XXX_L();RST_TAS3XXX_H();这两个函数需要删除（在车机项目使用时），自己给3204的重启脚
一个低电平信号
***************************************************************************************************
*/
void TAS3xxxReset(void)
{
	//RST_TAS3XXX_L();		// 使用U-595拉低TAS3xxx， 开机时就拉低，到了这里也过了一段时间，刚好也起到延时作用
	//PDN_TAS3XXX_L();
	//DapDelay(DLY_100US);
	//RST_TAS3XXX_H();        //使用U-595拉高TAS3xxx，
	//PDN_TAS3XXX_H();
	//DapDelay(290 * DLY_1MS);
	dsp_reset();
}





































