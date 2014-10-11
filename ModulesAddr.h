/*=================================================================================Application:  PurePath Studio Graphical Development Environment
FFile Name:    I2C_HEX_Addr.addr
DDate:         2014/9/6 10:28:43
VVersion:      1.88 build 3
=================================================================================*/

#ifndef __ModulesAddr_H_
#define __ModulesAddr_H_

// 定义TAS3XXX的I2C地址

#define I2C_CTRL 1

#if I2C_CTRL

#define TAS_SLA0  			(0x68>>1)

#elif I2C_GPIO

#define TAS_SLA0  			(0x68)

#endif


// TAS3XXX的时钟寄存器的I2C从地址
#define I2S_MOD_SUBA	 	0x00

/*#define  TAS3204AudioApp_1		0x0		//0x0 0x4 ! (TAS3204AudioApp_1) Clock and SAP control
#define  TAS3204AudioApp_1		0x1		//0x1 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x2		//0x2 0x4 ! (TAS3204AudioApp_1) Status Register
#define  TAS3204AudioApp_1		0x3		//0x3 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x4		//0x4 0x8 ! (TAS3204AudioApp_1) I2C Memory Load Control
#define  TAS3204AudioApp_1		0x5		//0x5 0x8 ! (TAS3204AudioApp_1) I2C Memory Load Data
#define  TAS3204AudioApp_1		0x6		//0x6 0x4 ! (TAS3204AudioApp_1) Peek/Poke Address
#define  TAS3204AudioApp_1		0x7		//0x7 0x8 ! (TAS3204AudioApp_1) Peek/Poke Data
#define  TAS3204AudioApp_1		0x8		//0x8 0x4 ! (TAS3204AudioApp_1) Application Version
#define  TAS3204AudioApp_1		0x9		//0x9 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0xA		//0xA 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0xB		//0xB 0x4 ! (TAS3204AudioApp_1) DSP PC Start Address
#define  TAS3204AudioApp_1		0xC		//0xC 0x4 ! (TAS3204AudioApp_1) GPIO Control via I2C
#define  TAS3204AudioApp_1		0xD		//0xD 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0xE		//0xE 0x4 ! (TAS3204AudioApp_1) Treble/Bass Slew Rate
#define  TAS3204AudioApp_1		0xF		//0xF 0x4 ! (TAS3204AudioApp_1) Master Download
#define  TAS3204AudioApp_1		0x10		//0x10 0x4 ! (TAS3204AudioApp_1) Analog Central Power Down
#define  TAS3204AudioApp_1		0x11		//0x11 0x4 ! (TAS3204AudioApp_1) Analog Individual Power Down
#define  TAS3204AudioApp_1		0x12		//0x12 0x4 ! (TAS3204AudioApp_1) ADC Mux Control
#define  TAS3204AudioApp_1		0x13		//0x13 0x4 ! (TAS3204AudioApp_1) ADC DEM Control
#define  TAS3204AudioApp_1		0x14		//0x14 0x4 ! (TAS3204AudioApp_1) ADC2 Current Control 1
#define  TAS3204AudioApp_1		0x15		//0x15 0x4 ! (TAS3204AudioApp_1) ADC2 Current Control  2
#define  TAS3204AudioApp_1		0x16		//0x16 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x17		//0x17 0x4 ! (TAS3204AudioApp_1) ADC1 Current Control 1
#define  TAS3204AudioApp_1		0x18		//0x18 0x4 ! (TAS3204AudioApp_1) ADC1 Current Control 2
#define  TAS3204AudioApp_1		0x19		//0x19 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x1A		//0x1A 0x4 ! (TAS3204AudioApp_1) DAC Current Control
#define  TAS3204AudioApp_1		0x1B		//0x1B 0x4 ! (TAS3204AudioApp_1) DAC Chopper Control
#define  TAS3204AudioApp_1		0x1C		//0x1C 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x1D		//0x1D 0x4 ! (TAS3204AudioApp_1) Reserved by Texas Instruments
#define  TAS3204AudioApp_1		0x1E		//0x1E 0x4 ! (TAS3204AudioApp_1) ADC/DAC Reset
#define  TAS3204AudioApp_1		0x1F		//0x1F 0x4 ! (TAS3204AudioApp_1) DEM bit toggle for ADC DWA
#define  TAS3204AudioApp_1		0x20		//0x20 0x4 ! (TAS3204AudioApp_1) ADC Input Gain
#define  TAS3204AudioApp_1		0x21		//0x21 0x4 ! (TAS3204AudioApp_1) MCLK OUT 2 Divider
#define  TAS3204AudioApp_1		0x22		//0x22 0x4 ! (TAS3204AudioApp_1) MCLK OUT 3 Divider
#define  TAS3204ADCIn_1		0x23		//0x23 0xC ! (TAS3204ADCIn_1) I2C Interface to pass High pass filter coefficients
*/

#define  MIXER01_I2C_ADDR		0x24		//0x24 0x10 ! (Crossbar_1) Mixer values for X11, X21, X31, X41

#define  MIXER02_I2C_ADDR		0x25		//0x25 0x10 ! (Crossbar_1) Mixer values for X12, X22, X32, X42

#define  MIXER03_I2C_ADDR		0x26		//0x26 0x10 ! (Crossbar_1) Mixer values for X13, X23, X33, X43

#define  MIXER04_I2C_ADDR		0x27		//0x27 0x10 ! (Crossbar_1) Mixer values for X14, X24, X34, X44

#define  MIXER05_I2C_ADDR		0x28		//0x28 0x10 ! (Crossbar_1) Mixer values for X51, X52, X53, X54

#define  MIXER06_I2C_ADDR		0x29		//0x29 0x10 ! (Crossbar_1) Mixer values for X55, X15, X25, X35

#define  MIXER07_I2C_ADDR		0x2A		//0x2A 0x10 ! (Crossbar_1) Mixer values for X45, X61, X62, X63

#define  MIXER08_I2C_ADDR		0x2B		//0x2B 0x10 ! (Crossbar_1) Mixer values for X64, X65, X66, X16

#define  MIXER09_I2C_ADDR		0x2C		//0x2C 0x10 ! (Crossbar_1) Mixer values for X26, X36, X46, X56

#define  MIXER10_I2C_ADDR		0x2D		//0x2D 0x10 ! (Crossbar_1) Mixer values for X71, X72, X73, X74

#define  MIXER11_I2C_ADDR		0x2E		//0x2E 0x10 ! (Crossbar_1) Mixer values for X75, X76, X17, X27

#define  MIXER12_I2C_ADDR		0x2F		//0x2F 0x10 ! (Crossbar_1) Mixer values for X37, X47, X57, X67

#define  MIXER13_I2C_ADDR		0x30		//0x30 0x10 ! (Crossbar_1) Mixer values for X77, X81, X82, X83

#define  MIXER14_I2C_ADDR		0x31		//0x31 0x10 ! (Crossbar_1) Mixer values for X84, X85, X86, X87

#define  MIXER15_I2C_ADDR		0x32		//0x32 0x10 ! (Crossbar_1) Mixer values for X18, X28, X38, X48

#define  MIXER16_I2C_ADDR		0x33		//0x33 0x10 ! (Crossbar_1) Mixer values for X58, X68, X78, X88
/*
#define  Crossbar_1		0x24		//0x24 0x10 ! (Crossbar_1) Mixer values for X11, X21, X31, X41
#define  Crossbar_1		0x25		//0x25 0x10 ! (Crossbar_1) Mixer values for X12, X22, X32, X42
#define  Crossbar_1		0x26		//0x26 0x10 ! (Crossbar_1) Mixer values for X13, X23, X33, X43
#define  Crossbar_1		0x27		//0x27 0x10 ! (Crossbar_1) Mixer values for X14, X24, X34, X44
#define  Crossbar_1		0x28		//0x28 0x10 ! (Crossbar_1) Mixer values for X51, X52, X53, X54
#define  Crossbar_1		0x29		//0x29 0x10 ! (Crossbar_1) Mixer values for X55, X15, X25, X35
#define  Crossbar_1		0x2A		//0x2A 0x10 ! (Crossbar_1) Mixer values for X45, X61, X62, X63
#define  Crossbar_1		0x2B		//0x2B 0x10 ! (Crossbar_1) Mixer values for X64, X65, X66, X16
#define  Crossbar_1		0x2C		//0x2C 0x10 ! (Crossbar_1) Mixer values for X26, X36, X46, X56
#define  Crossbar_1		0x2D		//0x2D 0x10 ! (Crossbar_1) Mixer values for X71, X72, X73, X74
#define  Crossbar_1		0x2E		//0x2E 0x10 ! (Crossbar_1) Mixer values for X75, X76, X17, X27
#define  Crossbar_1		0x2F		//0x2F 0x10 ! (Crossbar_1) Mixer values for X37, X47, X57, X67
#define  Crossbar_1		0x30		//0x30 0x10 ! (Crossbar_1) Mixer values for X77, X81, X82, X83
#define  Crossbar_1		0x31		//0x31 0x10 ! (Crossbar_1) Mixer values for X84, X85, X86, X87
#define  Crossbar_1		0x32		//0x32 0x10 ! (Crossbar_1) Mixer values for X18, X28, X38, X48
#define  Crossbar_1		0x33		//0x33 0x10 ! (Crossbar_1) Mixer values for X58, X68, X78, X88*/

#define  Volume_10		0x34		//0x34 0x4 ! (Volume_10) Volume Level for All Channels for this Volume Instance

#define  SCT_HP_Ins1		0x38		//0x38 0x14 ! (SCT_HP) BiQuad Coefficients for Instance 1
#define  SCT_HP_Ins2		0x39		//0x39 0x14 ! (SCT_HP) BiQuad Coefficients for Instance 2
#define  SCT_HP_Ins3		0x3A		//0x3A 0x14 ! (SCT_HP) BiQuad Coefficients for Instance 3
#define  SCT_HP_Ins4		0x3B		//0x3B 0x14 ! (SCT_HP) BiQuad Coefficients for Instance 4
#define  SCT_BP_Ins1		0x3C		//0x3C 0x14 ! (SCT_BP) BiQuad Coefficients for Instance 1
#define  SCT_BP_Ins2		0x3D		//0x3D 0x14 ! (SCT_BP) BiQuad Coefficients for Instance 2
#define  SCT_BP_Ins3		0x3E		//0x3E 0x14 ! (SCT_BP) BiQuad Coefficients for Instance 3
#define  SCT_BP_Ins4		0x3F		//0x3F 0x14 ! (SCT_BP) BiQuad Coefficients for Instance 4
#define  SCT_LP_Ins1		0x66		//0x66 0x14 ! (SCT_LP) BiQuad Coefficients for Instance 1
#define  SCT_LP_Ins2		0x67		//0x67 0x14 ! (SCT_LP) BiQuad Coefficients for Instance 2
#define  SCT_LP_Ins3		0x68		//0x68 0x14 ! (SCT_LP) BiQuad Coefficients for Instance 3
#define  SCT_LP_Ins4		0x80		//0x80 0x14 ! (SCT_LP) BiQuad Coefficients for Instance 4

#define  SCT_HP_1_Ins1		0x69		//0x69 0x14 ! (SCT_HP_1) BiQuad Coefficients for Instance 1
#define  SCT_HP_1_Ins2		0x6A		//0x6A 0x14 ! (SCT_HP_1) BiQuad Coefficients for Instance 2
#define  SCT_HP_1_Ins3		0x6B		//0x6B 0x14 ! (SCT_HP_1) BiQuad Coefficients for Instance 3
#define  SCT_HP_1_Ins4		0x90		//0x90 0x14 ! (SCT_HP_1) BiQuad Coefficients for Instance 4

#define  SCT_BP_1_Ins1		0x76		//0x76 0x14 ! (SCT_BP_1) BiQuad Coefficients for Instance 1
#define  SCT_BP_1_Ins2		0x77		//0x77 0x14 ! (SCT_BP_1) BiQuad Coefficients for Instance 2
#define  SCT_BP_1_Ins3		0x78		//0x78 0x14 ! (SCT_BP_1) BiQuad Coefficients for Instance 3
#define  SCT_BP_1_Ins4		0x79		//0x79 0x14 ! (SCT_BP_1) BiQuad Coefficients for Instance 4

#define  SCT_LP_1_Ins1		0x6C		//0x6C 0x14 ! (SCT_LP_1) BiQuad Coefficients for Instance 1
#define  SCT_LP_1_Ins2		0x6D		//0x6D 0x14 ! (SCT_LP_1) BiQuad Coefficients for Instance 2
#define  SCT_LP_1_Ins3		0x7E		//0x7E 0x14 ! (SCT_LP_1) BiQuad Coefficients for Instance 3

#define  SCT_LP_1_Ins4		0x91		//0x91 0x14 ! (SCT_LP_1) BiQuad Coefficients for Instance 4

#define  Mix4Ch_2		0x40		//0x40 0x10 ! (Mix4Ch_2) Gain function for Channel 1-4
#define  AGC_H_ae		0x41		//0x41 0x8 ! (AGC_H) ae and 1_ae/*
#define  AGC_H		0x42		//0x42 0x10 ! (AGC_H) T1_input and T2_input
#define  AGC_H		0x43		//0x43 0xC ! (AGC_H) k0, k1, and k2
#define  AGC_H		0x44		//0x44 0x10 ! (AGC_H) O1_input and O2_input
#define  AGC_H		0x45		//0x45 0x10 ! (AGC_H) aa, 1_aa, ad, and 1_ad
#define  AGC_H		0x46		//0x46 0x8 ! (AGC_H) DRC enable*/

#define  pEQ_Ins1		0x48		//0x48 0x14 ! (pEQ) BiQuad Coefficients for Instance 1
#define  pEQ_Ins2		0x49		//0x49 0x14 ! (pEQ) BiQuad Coefficients for Instance 2
#define  pEQ_Ins3		0x4A		//0x4A 0x14 ! (pEQ) BiQuad Coefficients for Instance 3
#define  pEQ_Ins4		0x4B		//0x4B 0x14 ! (pEQ) BiQuad Coefficients for Instance 4
#define  pEQ_Ins5		0x4C		//0x4C 0x14 ! (pEQ) BiQuad Coefficients for Instance 5#define  pEQ_Ins6		0x5F		//0x5F 0x14 ! (pEQ) BiQuad Coefficients for Instance 6
#define  pEQ_Ins7		0x60		//0x60 0x14 ! (pEQ) BiQuad Coefficients for Instance 7
#define  pEQ_Ins8		0x61		//0x61 0x14 ! (pEQ) BiQuad Coefficients for Instance 8
#define  pEQ_Ins9		0x62		//0x62 0x14 ! (pEQ) BiQuad Coefficients for Instance 9
#define  pEQ_Ins10		0x63		//0x63 0x14 ! (pEQ) BiQuad Coefficients for Instance 10#define  pEQ_1_Ins1		0x92		//0x92 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 1

#define  pEQ_1_Ins2		0x99		//0x99 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 2

#define  pEQ_1_Ins3		0x9B		//0x9B 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 3
#define  pEQ_1_Ins4		0x9C		//0x9C 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 4
#define  pEQ_1_Ins5		0xB5		//0xB5 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 5

#define  pEQ_1_Ins6		0x97		//0x97 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 6
#define  pEQ_1_Ins7		0x98		//0x98 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 7
#define  pEQ_1_Ins8		0x9A		//0x9A 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 8

#define  pEQ_1_Ins9		0x9D		//0x9D 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 9
#define  pEQ_1_Ins10		0x9E		//0x9E 0x14 ! (pEQ_1) BiQuad Coefficients for Instance 10


#define  pEQ_6_Ins1		0xBA		//0xBA 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 1
#define  pEQ_6_Ins2		0xBB		//0xBB 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 2
#define  pEQ_6_Ins3		0xBC		//0xBC 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 3
#define  pEQ_6_Ins4		0xBD		//0xBD 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 4
#define  pEQ_6_Ins5		0xBE		//0xBE 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 5
#define  pEQ_6_Ins6		0xBF		//0xBF 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 6
#define  pEQ_6_Ins7		0xC0		//0xC0 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 7
#define  pEQ_6_Ins8		0xC1		//0xC1 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 8
#define  pEQ_6_Ins9		0xC2		//0xC2 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 9
#define  pEQ_6_Ins10		0xC3		//0xC3 0x14 ! (pEQ_6) BiQuad Coefficients for Instance 10
#define  pEQ_7_Ins1		0x5C		//0x5C 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 1
#define  pEQ_7_Ins2		0x5D		//0x5D 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 2

#define  pEQ_7_Ins3		0x93		//0x93 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 3
#define  pEQ_7_Ins4		0x94		//0x94 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 4
#define  pEQ_7_Ins5		0x95		//0x95 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 5

#define  pEQ_7_Ins6		0x9F		//0x9F 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 6
#define  pEQ_7_Ins7		0xA0		//0xA0 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 7

#define  pEQ_7_Ins8		0xB8		//0xB8 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 8
#define  pEQ_7_Ins9		0xB9		//0xB9 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 9
#define  pEQ_7_Ins10		0xC4		//0xC4 0x14 ! (pEQ_7) BiQuad Coefficients for Instance 10




#define  AGC_L_ae		0x4D		//0x4D 0x8 ! (AGC_L) ae and 1_ae/*
#define  AGC_L		0x4E		//0x4E 0x10 ! (AGC_L) T1_input and T2_input
#define  AGC_L		0x4F		//0x4F 0xC ! (AGC_L) k0, k1, and k2
#define  AGC_L		0x50		//0x50 0x10 ! (AGC_L) O1_input and O2_input
#define  AGC_L		0x51		//0x51 0x10 ! (AGC_L) aa, 1_aa, ad, and 1_ad
#define  AGC_L		0x52		//0x52 0x8 ! (AGC_L) DRC enable*/
#define  AGC_B_ae		0x53		//0x53 0x8 ! (AGC_B) ae and 1_ae/*
#define  AGC_B		0x54		//0x54 0x10 ! (AGC_B) T1_input and T2_input
#define  AGC_B		0x55		//0x55 0xC ! (AGC_B) k0, k1, and k2
#define  AGC_B		0x56		//0x56 0x10 ! (AGC_B) O1_input and O2_input
#define  AGC_B		0x57		//0x57 0x10 ! (AGC_B) aa, 1_aa, ad, and 1_ad
#define  AGC_B		0x58		//0x58 0x8 ! (AGC_B) DRC enable*/
#define  Volume_1		0x59		//0x59 0x4 ! (Volume_1) Volume Level for All Channels for this Volume Instance
#define  NoiseFilter_Ins1		0x5A		//0x5A 0x14 ! (NoiseFilter) BiQuad Coefficients for Instance 1
#define  NoiseFilter_Ins2		0x5B		//0x5B 0x14 ! (NoiseFilter) BiQuad Coefficients for Instance 2

#define  Mix4Ch_3		0x5E		//0x5E 0x10 ! (Mix4Ch_3) Gain function for Channel 1-4
#define  HP_Ins1		0x35		//0x35 0x14 ! (HP) BiQuad Coefficients for Instance 1
#define  HP_Ins2		0x36		//0x36 0x14 ! (HP) BiQuad Coefficients for Instance 2
#define  HP_Ins3		0x37		//0x37 0x14 ! (HP) BiQuad Coefficients for Instance 3#define  HP_Ins4		0x47		//0x47 0x14 ! (HP) BiQuad Coefficients for Instance 4

#define  HP_1_Ins1		0x64		//0x64 0x14 ! (HP_1) BiQuad Coefficients for Instance 1
#define  HP_1_Ins2		0x65		//0x65 0x14 ! (HP_1) BiQuad Coefficients for Instance 2#define  HP_1_Ins3		0x74		//0x74 0x14 ! (HP_1) BiQuad Coefficients for Instance 3
#define  HP_1_Ins4		0x75		//0x75 0x14 ! (HP_1) BiQuad Coefficients for Instance 4



#define  Limiter_ae		0x6E		//0x6E 0x8 ! (Limiter) ae and 1_ae/*
#define  Limiter		0x6F		//0x6F 0x10 ! (Limiter) T1_input and T2_input
#define  Limiter		0x70		//0x70 0xC ! (Limiter) k0, k1, and k2
#define  Limiter		0x71		//0x71 0x10 ! (Limiter) O1_input and O2_input
#define  Limiter		0x72		//0x72 0x10 ! (Limiter) aa, 1_aa, ad, and 1_ad
#define  Limiter		0x73		//0x73 0x8 ! (Limiter) DRC enable*/


#define  VUMeter_1		0x7A		//0x7A 0x8 ! (VUMeter_1) RMS coefficient aSA and 1-aSA
#define  VUMeter_1_OutEn		0x7B		//0x7B 0x4 ! (VUMeter_1) OutputEnable
#define  VUMeter_3		0x7C		//0x7C 0x8 ! (VUMeter_3) RMS coefficient aSA and 1-aSA
#define  VUMeter_3_OutEn		0x7D		//0x7D 0x4 ! (VUMeter_3) OutputEnable
/*
#define  Crossbar_2		0x7F		//0x7F 0x10 ! (Crossbar_2) Mixer values for X11, X21, X31, X41
#define  Crossbar_2		0x81		//0x81 0x10 ! (Crossbar_2) Mixer values for X12, X22, X32, X42
#define  Crossbar_2		0x82		//0x82 0x10 ! (Crossbar_2) Mixer values for X13, X23, X33, X43
#define  Crossbar_2		0x83		//0x83 0x10 ! (Crossbar_2) Mixer values for X14, X24, X34, X44
#define  Crossbar_2		0x84		//0x84 0x10 ! (Crossbar_2) Mixer values for X51, X52, X53, X54
#define  Crossbar_2		0x85		//0x85 0x10 ! (Crossbar_2) Mixer values for X55, X15, X25, X35
#define  Crossbar_2		0x86		//0x86 0x10 ! (Crossbar_2) Mixer values for X45, X61, X62, X63
#define  Crossbar_2		0x87		//0x87 0x10 ! (Crossbar_2) Mixer values for X64, X65, X66, X16
#define  Crossbar_2		0x88		//0x88 0x10 ! (Crossbar_2) Mixer values for X26, X36, X46, X56
#define  Crossbar_2		0x89		//0x89 0x10 ! (Crossbar_2) Mixer values for X71, X72, X73, X74
#define  Crossbar_2		0x8A		//0x8A 0x10 ! (Crossbar_2) Mixer values for X75, X76, X17, X27
#define  Crossbar_2		0x8B		//0x8B 0x10 ! (Crossbar_2) Mixer values for X37, X47, X57, X67
#define  Crossbar_2		0x8C		//0x8C 0x10 ! (Crossbar_2) Mixer values for X77, X81, X82, X83
#define  Crossbar_2		0x8D		//0x8D 0x10 ! (Crossbar_2) Mixer values for X84, X85, X86, X87
#define  Crossbar_2		0x8E		//0x8E 0x10 ! (Crossbar_2) Mixer values for X18, X28, X38, X48
#define  Crossbar_2		0x8F		//0x8F 0x10 ! (Crossbar_2) Mixer values for X58, X68, X78, X88
*/

#define  MIXER01_I2C_ADDR_2		0x7F		//0x7F 0x10 ! (Crossbar_2) Mixer values for X11, X21, X31, X41

#define  MIXER02_I2C_ADDR_2		0x81		//0x81 0x10 ! (Crossbar_2) Mixer values for X12, X22, X32, X42

#define  MIXER03_I2C_ADDR_2		0x82		//0x82 0x10 ! (Crossbar_2) Mixer values for X13, X23, X33, X43

#define  MIXER04_I2C_ADDR_2		0x83		//0x83 0x10 ! (Crossbar_2) Mixer values for X14, X24, X34, X44

#define  MIXER05_I2C_ADDR_2		0x84		//0x84 0x10 ! (Crossbar_2) Mixer values for X51, X52, X53, X54

#define  MIXER06_I2C_ADDR_2		0x85		//0x85 0x10 ! (Crossbar_2) Mixer values for X55, X15, X25, X35

#define  MIXER07_I2C_ADDR_2		0x86		//0x86 0x10 ! (Crossbar_2) Mixer values for X45, X61, X62, X63

#define  MIXER08_I2C_ADDR_2		0x87		//0x87 0x10 ! (Crossbar_2) Mixer values for X64, X65, X66, X16

#define  MIXER09_I2C_ADDR_2		0x88		//0x88 0x10 ! (Crossbar_2) Mixer values for X26, X36, X46, X56

#define  MIXER10_I2C_ADDR_2		0x89		//0x89 0x10 ! (Crossbar_2) Mixer values for X71, X72, X73, X74

#define  MIXER11_I2C_ADDR_2		0x8A		//0x8A 0x10 ! (Crossbar_2) Mixer values for X75, X76, X17, X27

#define  MIXER12_I2C_ADDR_2		0x8B		//0x8B 0x10 ! (Crossbar_2) Mixer values for X37, X47, X57, X67

#define  MIXER13_I2C_ADDR_2		0x8C		//0x8C 0x10 ! (Crossbar_2) Mixer values for X77, X81, X82, X83

#define  MIXER14_I2C_ADDR_2		0x8D		//0x8D 0x10 ! (Crossbar_2) Mixer values for X84, X85, X86, X87

#define  MIXER15_I2C_ADDR_2		0x8E		//0x8E 0x10 ! (Crossbar_2) Mixer values for X18, X28, X38, X48

#define  MIXER16_I2C_ADDR_2		0x8F		//0x8F 0x10 ! (Crossbar_2) Mixer values for X58, X68, X78, X88

#define  SCT_HP_1_Ins4		0x90		//0x90 0x14 ! (SCT_HP_1) BiQuad Coefficients for Instance 4


#define  Volume_11		0x96		//0x96 0x4 ! (Volume_11) Volume Level for All Channels for this Volume Instance


#define  Mix4Ch_10		0xA1		//0xA1 0x10 ! (Mix4Ch_10) Gain function for Channel 1-4
#define  AGC_H_1_ae		0xA2		//0xA2 0x8 ! (AGC_H_1) ae and 1_ae/*
#define  AGC_H_1		0xA3		//0xA3 0x10 ! (AGC_H_1) T1_input and T2_input
#define  AGC_H_1		0xA4		//0xA4 0xC ! (AGC_H_1) k0, k1, and k2
#define  AGC_H_1		0xA5		//0xA5 0x10 ! (AGC_H_1) O1_input and O2_input
#define  AGC_H_1		0xA6		//0xA6 0x10 ! (AGC_H_1) aa, 1_aa, ad, and 1_ad
#define  AGC_H_1		0xA7		//0xA7 0x8 ! (AGC_H_1) DRC enable*/
#define  AGC_L_1_ae		0xA8		//0xA8 0x8 ! (AGC_L_1) ae and 1_ae/*
#define  AGC_L_1		0xA9		//0xA9 0x10 ! (AGC_L_1) T1_input and T2_input
#define  AGC_L_1		0xAA		//0xAA 0xC ! (AGC_L_1) k0, k1, and k2
#define  AGC_L_1		0xAB		//0xAB 0x10 ! (AGC_L_1) O1_input and O2_input
#define  AGC_L_1		0xAC		//0xAC 0x10 ! (AGC_L_1) aa, 1_aa, ad, and 1_ad
#define  AGC_L_1		0xAD		//0xAD 0x8 ! (AGC_L_1) DRC enable*/
#define  AGC_B_1_ae		0xAE		//0xAE 0x8 ! (AGC_B_1) ae and 1_ae/*
#define  AGC_B_1		0xAF		//0xAF 0x10 ! (AGC_B_1) T1_input and T2_input
#define  AGC_B_1		0xB0		//0xB0 0xC ! (AGC_B_1) k0, k1, and k2
#define  AGC_B_1		0xB1		//0xB1 0x10 ! (AGC_B_1) O1_input and O2_input
#define  AGC_B_1		0xB2		//0xB2 0x10 ! (AGC_B_1) aa, 1_aa, ad, and 1_ad
#define  AGC_B_1		0xB3		//0xB3 0x8 ! (AGC_B_1) DRC enable*/
#define  Volume_4		0xB4		//0xB4 0x4 ! (Volume_4) Volume Level for All Channels for this Volume Instance

#define  Mix4Ch_12		0xB6		//0xB6 0x10 ! (Mix4Ch_12) Gain function for Channel 1-4
#define  Mix4Ch_13		0xB7		//0xB7 0x10 ! (Mix4Ch_13) Gain function for Channel 1-4

/*
0xC5 0x4 
0xC6 0x4 
0xC7 0x4 */
#define  Delay1		0xC8		//0xC8 0x4 ! (TAS3204AudioApp_1) Delay Pointer 0 and 1 Length
#define  Delay3		0xC8		//0xC9 0x4 ! (TAS3204AudioApp_1) Delay Pointer 2 and 3 Length
#define  Delay4		0xC9		//0xCA 0x4 ! (TAS3204AudioApp_1) Delay Pointer 4 and 5 Length#define  Delay5		    0xC9		//0xCA 0x4 ! (TAS3204AudioApp_1) Delay Pointer 4 and 5 Length/*
#define  TAS3204AudioApp_1		0xCB		//0xCB 0x4 ! (TAS3204AudioApp_1) Delay Pointer 6 and 7 Length
#define  TAS3204AudioApp_1		0xCC		//0xCC 0x4 ! (TAS3204AudioApp_1) Delay Pointer 8 and 9 Length
#define  TAS3204AudioApp_1		0xCD		//0xCD 0x4 ! (TAS3204AudioApp_1) Delay Pointer 10 and 11 Length
#define  TAS3204AudioApp_1		0xCE		//0xCE 0x4 ! (TAS3204AudioApp_1) Delay Pointer 12 and 13 Length
#define  TAS3204AudioApp_1		0xCF		//0xCF 0x4 ! (TAS3204AudioApp_1) Delay Pointer 14 and 15 Length
#define  TAS3204AudioApp_1		0xD0		//0xD0 0x4 ! (TAS3204AudioApp_1) Delay Pointer 16 and 17 Length
#define  TAS3204AudioApp_1		0xD1		//0xD1 0x4 ! (TAS3204AudioApp_1) Delay Pointer 18 and 19 Length
#define  TAS3204AudioApp_1		0xD2		//0xD2 0x4 ! (TAS3204AudioApp_1) Delay Pointer 20 and 21 Length
#define  TAS3204AudioApp_1		0xD3		//0xD3 0x4 ! (TAS3204AudioApp_1) Delay Pointer 22 and 23 Length*/
#define  Delay_Update		0xD4		//0xD4 0x4 ! (TAS3204AudioApp_1) Delay Update Flag/*
0xD5 0x4 
0xD6 0x4 
0xD7 0x4 
0xD8 0x4 */
#define  Limiter_1_ae		0xD9		//0xD9 0x8 ! (Limiter_1) ae and 1_ae/*
#define  Limiter_1		0xDA		//0xDA 0x10 ! (Limiter_1) T1_input and T2_input
#define  Limiter_1		0xDB		//0xDB 0xC ! (Limiter_1) k0, k1, and k2
#define  Limiter_1		0xDC		//0xDC 0x10 ! (Limiter_1) O1_input and O2_input
#define  Limiter_1		0xDD		//0xDD 0x10 ! (Limiter_1) aa, 1_aa, ad, and 1_ad
#define  Limiter_1		0xDE		//0xDE 0x8 ! (Limiter_1) DRC enable*/
#define  Mix4Ch_14		0xDF		//0xDF 0x10 ! (Mix4Ch_14) Gain function for Channel 1-4
#define  Volume_5		0xE0		//0xE0 0x4 ! (Volume_5) Volume Level for All Channels for this Volume Instance
#define  StereoMixer_1		0xE1		//0xE1 0x10 ! (StereoMixer_1) Ch1Gain - Ch4Gain
#define  Volume_7		0xE2		//0xE2 0x4 ! (Volume_7) Volume Level for All Channels for this Volume Instance
//0xE3 0x4 
#define  Volume_9		0xE4		//0xE4 0x4 ! (Volume_9) Volume Level for All Channels for this Volume Instance/*
0xE5 0x4 
0xE6 0x4 
0xE7 0x4 */

#define  Mix4Ch_11		0xED		//0xED 0x10 ! (Mix4Ch_11) Gain function for Channel 1-4
/*
#define  Crossbar_3		0xE8		//0xE8 0x10 ! (Crossbar_3) Mixer values for X11, X21, X31, X41
#define  Crossbar_3		0xE9		//0xE9 0x10 ! (Crossbar_3) Mixer values for X12, X22, X32, X42
#define  Crossbar_3		0xEA		//0xEA 0x10 ! (Crossbar_3) Mixer values for X13, X23, X33, X43
#define  Crossbar_3		0xEB		//0xEB 0x10 ! (Crossbar_3) Mixer values for X14, X24, X34, X44
#define  Crossbar_3		0xEC		//0xEC 0x10 ! (Crossbar_3) Mixer values for X51, X52, X53, X54

#define  Crossbar_3		0xEE		//0xEE 0x10 ! (Crossbar_3) Mixer values for X55, X15, X25, X35
#define  Crossbar_3		0xEF		//0xEF 0x10 ! (Crossbar_3) Mixer values for X45, X61, X62, X63
#define  Crossbar_3		0xF0		//0xF0 0x10 ! (Crossbar_3) Mixer values for X64, X65, X66, X16
#define  Crossbar_3		0xF1		//0xF1 0x10 ! (Crossbar_3) Mixer values for X26, X36, X46, X56
#define  Crossbar_3		0xF2		//0xF2 0x10 ! (Crossbar_3) Mixer values for X71, X72, X73, X74
#define  Crossbar_3		0xF3		//0xF3 0x10 ! (Crossbar_3) Mixer values for X75, X76, X17, X27
#define  Crossbar_3		0xF4		//0xF4 0x10 ! (Crossbar_3) Mixer values for X37, X47, X57, X67
#define  Crossbar_3		0xF5		//0xF5 0x10 ! (Crossbar_3) Mixer values for X77, X81, X82, X83
#define  Crossbar_3		0xF6		//0xF6 0x10 ! (Crossbar_3) Mixer values for X84, X85, X86, X87
#define  Crossbar_3		0xF7		//0xF7 0x10 ! (Crossbar_3) Mixer values for X18, X28, X38, X48
#define  Crossbar_3		0xF8		//0xF8 0x10 ! (Crossbar_3) Mixer values for X58, X68, X78, X88*/

#define  MIXER01_I2C_ADDR_3		0xE8		//0xE8 0x10 ! (Crossbar_3) Mixer values for X11, X21, X31, X41

#define  MIXER02_I2C_ADDR_3		0xE9		//0xE9 0x10 ! (Crossbar_3) Mixer values for X12, X22, X32, X42

#define  MIXER03_I2C_ADDR_3		0xEA		//0xEA 0x10 ! (Crossbar_3) Mixer values for X13, X23, X33, X43

#define  MIXER04_I2C_ADDR_3		0xEB		//0xEB 0x10 ! (Crossbar_3) Mixer values for X14, X24, X34, X44

#define  MIXER05_I2C_ADDR_3		0xEC		//0xEC 0x10 ! (Crossbar_3) Mixer values for X51, X52, X53, X54

#define  MIXER06_I2C_ADDR_3		0xEE		//0xEE 0x10 ! (Crossbar_3) Mixer values for X55, X15, X25, X35

#define  MIXER07_I2C_ADDR_3		0xEF		//0xEF 0x10 ! (Crossbar_3) Mixer values for X45, X61, X62, X63

#define  MIXER08_I2C_ADDR_3		0xF0		//0xF0 0x10 ! (Crossbar_3) Mixer values for X64, X65, X66, X16

#define  MIXER09_I2C_ADDR_3		0xF1		//0xF1 0x10 ! (Crossbar_3) Mixer values for X26, X36, X46, X56

#define  MIXER10_I2C_ADDR_3		0xF2		//0xF2 0x10 ! (Crossbar_3) Mixer values for X71, X72, X73, X74

#define  MIXER11_I2C_ADDR_3		0xF3		//0xF3 0x10 ! (Crossbar_3) Mixer values for X75, X76, X17, X27

#define  MIXER12_I2C_ADDR_3		0xF4		//0xF4 0x10 ! (Crossbar_3) Mixer values for X37, X47, X57, X67

#define  MIXER13_I2C_ADDR_3		0xF5		//0xF5 0x10 ! (Crossbar_3) Mixer values for X77, X81, X82, X83

#define  MIXER14_I2C_ADDR_3		0xF6		//0xF6 0x10 ! (Crossbar_3) Mixer values for X84, X85, X86, X87

#define  MIXER15_I2C_ADDR_3		0xF7		//0xF7 0x10 ! (Crossbar_3) Mixer values for X18, X28, X38, X48
 #define  MIXER16_I2C_ADDR_3		0xF8		//0xF8 0x10 ! (Crossbar_3) Mixer values for X58, X68, X78, X88
#define  SCT_BP_Vol		0xF9		//0xF9 0x4 ! (SCT_BP_Vol) Volume Level for All Channels for this Volume Instance
#define  SCT_HP_Vol		0xFA		//0xFA 0x4 ! (SCT_HP_Vol) Volume Level for All Channels for this Volume Instance
#define  SCT_LP_Vol		0xFB		//0xFB 0x4 ! (SCT_LP_Vol) Volume Level for All Channels for this Volume Instance
#define  SCT_BP_Vol_1		0xFC		//0xFC 0x4 ! (SCT_BP_Vol_1) Volume Level for All Channels for this Volume Instance
#define  SCT_HP_Vol_1		0xFD		//0xFD 0x4 ! (SCT_HP_Vol_1) Volume Level for All Channels for this Volume Instance
#define  SCT_LP_Vol_1		0xFE		//0xFE 0x4 ! (SCT_LP_Vol_1) Volume Level for All Channels for this Volume Instance
//0xFF 0x4 #endif        //__ModulesAddr_H_