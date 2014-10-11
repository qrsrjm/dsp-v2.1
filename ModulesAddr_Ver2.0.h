/*=================================================================================Application:  PurePath Studio Graphical Development Environment
FFile Name:    I2C_HEX_Addr.addr
DDate:         2014/9/16 15:38:18   VVersion:      1.88 build 3=================================================================================*/
#ifndef __ModulesAddr_Ver2_0_H_#define __ModulesAddr_Ver2_0_H_
// 定义TAS3XXX的I2C地址
#define I2C_CTRL 1
#if I2C_CTRL
#define TAS_SLA0  			(0x68>>1)
#elif I2C_GPIO
#define TAS_SLA0  			(0x68)
#endif


// TAS3XXX的时钟寄存器的I2C从地址#define I2S_MOD_SUBA	 	0x00
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
#define  TAS3204ADCIn_1		0x23		//0x23 0xC ! (TAS3204ADCIn_1) I2C Interface to pass High pass filter coefficients*/

#define  PEQ_BCh1_Ins1		0x24		//0x24 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 1#define  PEQ_BCh1_Ins2		0x25		//0x25 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 2#define  PEQ_BCh1_Ins3		0x26		//0x26 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 3#define  PEQ_BCh1_Ins4		0x27		//0x27 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 4#define  PEQ_BCh1_Ins5		0x28		//0x28 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 5#define  PEQ_BCh1_Ins6		0x29		//0x29 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 6#define  PEQ_BCh1_Ins7		0x2A		//0x2A 0x14 ! (PEQ_BCh1) BiQuad Coefficients for Instance 7#define  SCT_HP1_Ins1		0x2B		//0x2B 0x14 ! (SCT_HP1) BiQuad Coefficients for Instance 1#define  SCT_HP1_Ins2		0x2C		//0x2C 0x14 ! (SCT_HP1) BiQuad Coefficients for Instance 2#define  SCT_BP1_Ins1		0x2D		//0x2D 0x14 ! (SCT_BP1) BiQuad Coefficients for Instance 1#define  SCT_BP1_Ins2		0x2E		//0x2E 0x14 ! (SCT_BP1) BiQuad Coefficients for Instance 2#define  SCT_BP1_Ins3		0x2F		//0x2F 0x14 ! (SCT_BP1) BiQuad Coefficients for Instance 3#define  SCT_BP1_Ins4		0x30		//0x30 0x14 ! (SCT_BP1) BiQuad Coefficients for Instance 4#define  SCT_BP2_Ins1		0x31		//0x31 0x14 ! (SCT_BP2) BiQuad Coefficients for Instance 1#define  SCT_BP2_Ins2		0x32		//0x32 0x14 ! (SCT_BP2) BiQuad Coefficients for Instance 2#define  SCT_BP2_Ins3		0x33		//0x33 0x14 ! (SCT_BP2) BiQuad Coefficients for Instance 3#define  SCT_BP2_Ins4		0x34		//0x34 0x14 ! (SCT_BP2) BiQuad Coefficients for Instance 4#define  SCT_LP1_Ins1		0x35		//0x35 0x14 ! (SCT_LP1) BiQuad Coefficients for Instance 1#define  SCT_LP1_Ins2		0x36		//0x36 0x14 ! (SCT_LP1) BiQuad Coefficients for Instance 2#define  SCT_HP2_Ins1		0x37		//0x37 0x14 ! (SCT_HP2) BiQuad Coefficients for Instance 1#define  SCT_HP2_Ins2		0x38		//0x38 0x14 ! (SCT_HP2) BiQuad Coefficients for Instance 2#define  SCT_LP2_Ins1		0x39		//0x39 0x14 ! (SCT_LP2) BiQuad Coefficients for Instance 1#define  SCT_LP2_Ins2		0x3A		//0x3A 0x14 ! (SCT_LP2) BiQuad Coefficients for Instance 2#define  PEQ_ACh1_Ins1		0x3B		//0x3B 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 1#define  PEQ_ACh1_Ins2		0x3C		//0x3C 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 2#define  PEQ_ACh1_Ins3		0x3D		//0x3D 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 3#define  PEQ_ACh1_Ins4		0x3E		//0x3E 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 4#define  PEQ_ACh1_Ins5		0x3F		//0x3F 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 5#define  PEQ_ACh1_Ins6		0x40		//0x40 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 6#define  PEQ_ACh1_Ins7		0x41		//0x41 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 7#define  PEQ_ACh1_Ins8		0x42		//0x42 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 8#define  PEQ_ACh1_Ins9		0x43		//0x43 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 9#define  PEQ_ACh1_Ins10		0x44		//0x44 0x14 ! (PEQ_ACh1) BiQuad Coefficients for Instance 10#define  PEQ_BCh2_Ins1		0x45		//0x45 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 1#define  PEQ_BCh2_Ins2		0x46		//0x46 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 2#define  PEQ_BCh2_Ins3		0x47		//0x47 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 3#define  PEQ_BCh2_Ins4		0x48		//0x48 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 4#define  PEQ_BCh2_Ins5		0x49		//0x49 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 5#define  PEQ_BCh2_Ins6		0x4A		//0x4A 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 6#define  PEQ_BCh2_Ins7		0x4B		//0x4B 0x14 ! (PEQ_BCh2) BiQuad Coefficients for Instance 7#define  PEQ_ACh2_Ins1		0x4C		//0x4C 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 1#define  PEQ_ACh2_Ins2		0x4D		//0x4D 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 2#define  PEQ_ACh2_Ins3		0x4E		//0x4E 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 3#define  PEQ_ACh2_Ins4		0x4F		//0x4F 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 4#define  PEQ_ACh2_Ins5		0x50		//0x50 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 5#define  PEQ_ACh2_Ins6		0x51		//0x51 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 6#define  PEQ_ACh2_Ins7		0x52		//0x52 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 7#define  PEQ_ACh2_Ins8		0x53		//0x53 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 8#define  PEQ_ACh2_Ins9		0x54		//0x54 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 9#define  PEQ_ACh2_Ins10		0x55		//0x55 0x14 ! (PEQ_ACh2) BiQuad Coefficients for Instance 10#define  PEQ_ACh3_Ins1		0x56		//0x56 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 1#define  PEQ_ACh3_Ins2		0x57		//0x57 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 2#define  PEQ_ACh3_Ins3		0x58		//0x58 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 3#define  PEQ_ACh3_Ins4		0x59		//0x59 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 4#define  PEQ_ACh3_Ins5		0x5A		//0x5A 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 5#define  PEQ_ACh3_Ins6		0x5B		//0x5B 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 6#define  PEQ_ACh3_Ins7		0x5C		//0x5C 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 7#define  PEQ_ACh3_Ins8		0x5D		//0x5D 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 8#define  PEQ_ACh3_Ins9		0x5E		//0x5E 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 9#define  PEQ_ACh3_Ins10		0x5F		//0x5F 0x14 ! (PEQ_ACh3) BiQuad Coefficients for Instance 10#define  PEQ_ACh4_Ins1		0x60		//0x60 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 1#define  PEQ_ACh4_Ins2		0x61		//0x61 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 2#define  PEQ_ACh4_Ins3		0x62		//0x62 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 3#define  PEQ_ACh4_Ins4		0x63		//0x63 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 4#define  PEQ_ACh4_Ins5		0x64		//0x64 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 5#define  PEQ_ACh4_Ins6		0x65		//0x65 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 6#define  PEQ_ACh4_Ins7		0x66		//0x66 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 7#define  PEQ_ACh4_Ins8		0x67		//0x67 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 8#define  PEQ_ACh4_Ins9		0x68		//0x68 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 9#define  PEQ_ACh4_Ins10		0x69		//0x69 0x14 ! (PEQ_ACh4) BiQuad Coefficients for Instance 10#define  PEQ_ACh5_Ins1		0x6A		//0x6A 0x14 ! (PEQ_ACh5) BiQuad Coefficients for Instance 1#define  PEQ_ACh5_Ins2		0x6B		//0x6B 0x14 ! (PEQ_ACh5) BiQuad Coefficients for Instance 2#define  PEQ_ACh5_Ins3		0x6C		//0x6C 0x14 ! (PEQ_ACh5) BiQuad Coefficients for Instance 3#define  PEQ_ACh5_Ins4		0x6D		//0x6D 0x14 ! (PEQ_ACh5) BiQuad Coefficients for Instance 4#define  PEQ_ACh5_Ins5		0x6E		//0x6E 0x14 ! (PEQ_ACh5) BiQuad Coefficients for Instance 5#define  PEQ_ACh6_Ins1		0x6F		//0x6F 0x14 ! (PEQ_ACh6) BiQuad Coefficients for Instance 1#define  PEQ_ACh6_Ins2		0x70		//0x70 0x14 ! (PEQ_ACh6) BiQuad Coefficients for Instance 2#define  PEQ_ACh6_Ins3		0x71		//0x71 0x14 ! (PEQ_ACh6) BiQuad Coefficients for Instance 3#define  Limiter1_ae		0x72		//0x72 0x8 ! (Limiter1) ae and 1_ae/*
#define  Limiter1		0x73		//0x73 0x10 ! (Limiter1) T1_input and T2_input
#define  Limiter1		0x74		//0x74 0xC ! (Limiter1) k0, k1, and k2
#define  Limiter1		0x75		//0x75 0x10 ! (Limiter1) O1_input and O2_input
#define  Limiter1		0x76		//0x76 0x10 ! (Limiter1) aa, 1_aa, ad, and 1_ad
#define  Limiter1		0x77		//0x77 0x8 ! (Limiter1) DRC enable*/#define  Limiter2_ae		0x78		//0x78 0x8 ! (Limiter2) ae and 1_ae/*
#define  Limiter2		0x79		//0x79 0x10 ! (Limiter2) T1_input and T2_input
#define  Limiter2		0x7A		//0x7A 0xC ! (Limiter2) k0, k1, and k2
#define  Limiter2		0x7B		//0x7B 0x10 ! (Limiter2) O1_input and O2_input
#define  Limiter2		0x7C		//0x7C 0x10 ! (Limiter2) aa, 1_aa, ad, and 1_ad
#define  Limiter2		0x7D		//0x7D 0x8 ! (Limiter2) DRC enable*/#define  Limiter3_ae		0x7E		//0x7E 0x8 ! (Limiter3) ae and 1_ae/*
#define  Limiter3		0x7F		//0x7F 0x10 ! (Limiter3) T1_input and T2_input
#define  Limiter3		0x80		//0x80 0xC ! (Limiter3) k0, k1, and k2
#define  Limiter3		0x81		//0x81 0x10 ! (Limiter3) O1_input and O2_input
#define  Limiter3		0x82		//0x82 0x10 ! (Limiter3) aa, 1_aa, ad, and 1_ad
#define  Limiter3		0x83		//0x83 0x8 ! (Limiter3) DRC enable*/#define  Limiter4_ae		0x84		//0x84 0x8 ! (Limiter4) ae and 1_ae/*
#define  Limiter4		0x85		//0x85 0x10 ! (Limiter4) T1_input and T2_input
#define  Limiter4		0x86		//0x86 0xC ! (Limiter4) k0, k1, and k2
#define  Limiter4		0x87		//0x87 0x10 ! (Limiter4) O1_input and O2_input
#define  Limiter4		0x88		//0x88 0x10 ! (Limiter4) aa, 1_aa, ad, and 1_ad
#define  Limiter4		0x89		//0x89 0x8 ! (Limiter4) DRC enable*/#define  Limiter5_ae		0x8A		//0x8A 0x8 ! (Limiter5) ae and 1_ae/*
#define  Limiter5		0x8B		//0x8B 0x10 ! (Limiter5) T1_input and T2_input
#define  Limiter5		0x8C		//0x8C 0xC ! (Limiter5) k0, k1, and k2
#define  Limiter5		0x8D		//0x8D 0x10 ! (Limiter5) O1_input and O2_input
#define  Limiter5		0x8E		//0x8E 0x10 ! (Limiter5) aa, 1_aa, ad, and 1_ad
#define  Limiter5		0x8F		//0x8F 0x8 ! (Limiter5) DRC enable*/
#define  Limiter6_ae		0xF0		//0xF0 0x8 ! (Limiter6) ae and 1_ae/*
#define  Limiter6		0xF1		//0xF1 0x10 ! (Limiter6) T1_input and T2_input
#define  Limiter6		0xF2		//0xF2 0xC ! (Limiter6) k0, k1, and k2
#define  Limiter6		0xF3		//0xF3 0x10 ! (Limiter6) O1_input and O2_input
#define  Limiter6		0xF4		//0xF4 0x10 ! (Limiter6) aa, 1_aa, ad, and 1_ad
#define  Limiter6		0xF5		//0xF5 0x8 ! (Limiter6) DRC enable*/
#define  MIXER01_I2C_ADDR		0x90		//0x90 0x10 ! (Crossbar_1) Mixer values for X11, X21, X31, X41#define  MIXER02_I2C_ADDR		0x91		//0x91 0x10 ! (Crossbar_1) Mixer values for X12, X22, X32, X42#define  MIXER03_I2C_ADDR		0x92		//0x92 0x10 ! (Crossbar_1) Mixer values for X13, X23, X33, X43#define  MIXER04_I2C_ADDR		0x93		//0x93 0x10 ! (Crossbar_1) Mixer values for X14, X24, X34, X44#define  MIXER05_I2C_ADDR		0x94		//0x94 0x10 ! (Crossbar_1) Mixer values for X51, X52, X53, X54#define  MIXER06_I2C_ADDR		0x95		//0x95 0x10 ! (Crossbar_1) Mixer values for X55, X15, X25, X35#define  MIXER07_I2C_ADDR		0x96		//0x96 0x10 ! (Crossbar_1) Mixer values for X45, X61, X62, X63#define  MIXER08_I2C_ADDR		0x97		//0x97 0x10 ! (Crossbar_1) Mixer values for X64, X65, X66, X16#define  MIXER09_I2C_ADDR		0x98		//0x98 0x10 ! (Crossbar_1) Mixer values for X26, X36, X46, X56#define  MIXER10_I2C_ADDR		0x99		//0x99 0x10 ! (Crossbar_1) Mixer values for X71, X72, X73, X74#define  MIXER11_I2C_ADDR		0x9A		//0x9A 0x10 ! (Crossbar_1) Mixer values for X75, X76, X17, X27#define  MIXER12_I2C_ADDR		0x9B		//0x9B 0x10 ! (Crossbar_1) Mixer values for X37, X47, X57, X67#define  MIXER13_I2C_ADDR		0x9C		//0x9C 0x10 ! (Crossbar_1) Mixer values for X77, X81, X82, X83#define  MIXER14_I2C_ADDR		0x9D		//0x9D 0x10 ! (Crossbar_1) Mixer values for X84, X85, X86, X87#define  MIXER15_I2C_ADDR		0x9E		//0x9E 0x10 ! (Crossbar_1) Mixer values for X18, X28, X38, X48#define  MIXER16_I2C_ADDR		0x9F		//0x9F 0x10 ! (Crossbar_1) Mixer values for X58, X68, X78, X88#define  BP1_Ins1		0xA0		//0xA0 0x14 ! (BP1) BiQuad Coefficients for Instance 1#define  BP1_Ins2		0xA1		//0xA1 0x14 ! (BP1) BiQuad Coefficients for Instance 2#define  BP1_Ins3		0xA2		//0xA2 0x14 ! (BP1) BiQuad Coefficients for Instance 3#define  BP1_Ins4		0xA3		//0xA3 0x14 ! (BP1) BiQuad Coefficients for Instance 4#define  BP2_Ins1		0xA4		//0xA4 0x14 ! (BP2) BiQuad Coefficients for Instance 1#define  BP2_Ins2		0xA5		//0xA5 0x14 ! (BP2) BiQuad Coefficients for Instance 2#define  BP2_Ins3		0xA6		//0xA6 0x14 ! (BP2) BiQuad Coefficients for Instance 3#define  BP2_Ins4		0xA7		//0xA7 0x14 ! (BP2) BiQuad Coefficients for Instance 4#define  BP3_Ins1		0xA8		//0xA8 0x14 ! (BP3) BiQuad Coefficients for Instance 1#define  BP3_Ins2		0xA9		//0xA9 0x14 ! (BP3) BiQuad Coefficients for Instance 2#define  BP3_Ins3		0xAA		//0xAA 0x14 ! (BP3) BiQuad Coefficients for Instance 3#define  BP3_Ins4		0xAB		//0xAB 0x14 ! (BP3) BiQuad Coefficients for Instance 4#define  BP4_Ins1		0xAC		//0xAC 0x14 ! (BP4) BiQuad Coefficients for Instance 1#define  BP4_Ins2		0xAD		//0xAD 0x14 ! (BP4) BiQuad Coefficients for Instance 2#define  BP4_Ins3		0xAE		//0xAE 0x14 ! (BP4) BiQuad Coefficients for Instance 3#define  BP4_Ins4		0xAF		//0xAF 0x14 ! (BP4) BiQuad Coefficients for Instance 4#define  BP5_Ins1		0xB0		//0xB0 0x14 ! (BP5) BiQuad Coefficients for Instance 1#define  BP5_Ins2		0xB1		//0xB1 0x14 ! (BP5) BiQuad Coefficients for Instance 2#define  BP5_Ins3		0xB2		//0xB2 0x14 ! (BP5) BiQuad Coefficients for Instance 3#define  BP5_Ins4		0xB3		//0xB3 0x14 ! (BP5) BiQuad Coefficients for Instance 4#define  BP6_Ins1		0xB4		//0xB4 0x14 ! (BP6) BiQuad Coefficients for Instance 1#define  BP6_Ins2		0xB5		//0xB5 0x14 ! (BP6) BiQuad Coefficients for Instance 2#define  BP6_Ins3		0xB6		//0xB6 0x14 ! (BP6) BiQuad Coefficients for Instance 3#define  BP6_Ins4		0xB7		//0xB7 0x14 ! (BP6) BiQuad Coefficients for Instance 4#define  Mix4Ch_1		0xB8		//0xB8 0x10 ! (Mix4Ch_1) Gain function for Channel 1-4#define  Mix4Ch_2		0xB9		//0xB9 0x10 ! (Mix4Ch_2) Gain function for Channel 1-4#define  SCT_HP1_Vol		0xBA		//0xBA 0x4 ! (SCT_HP1_Vol) Volume Level for All Channels for this Volume Instance#define  SCT_BP1_Vol		0xBB		//0xBB 0x4 ! (SCT_BP1_Vol) Volume Level for All Channels for this Volume Instance#define  SCT_LP1_Vol		0xBE		//0xBE 0x4 ! (SCT_LP1_Vol) Volume Level for All Channels for this Volume Instance#define  SCT_HP2_Vol		0xBF		//0xBF 0x4 ! (SCT_HP2_Vol) Volume Level for All Channels for this Volume Instance#define  SCT_BP2_Vol		0xC0		//0xC0 0x4 ! (SCT_BP2_Vol) Volume Level for All Channels for this Volume Instance#define  SCT_LP2_Vol		0xC1		//0xC1 0x4 ! (SCT_LP2_Vol) Volume Level for All Channels for this Volume Instance
#define  Mux_1		0xBC		//0xBC 0x4 ! (Mux_1) Mux Control#define  Mux_2		0xBD		//0xBD 0x4 ! (Mux_2) Mux Control
#define  Volume_13		0xC2		//0xC2 0x4 ! (Volume_13) Volume Level for All Channels for this Volume Instance#define  AGC_H1_ae		0xC3		//0xC3 0x8 ! (AGC_H1) ae and 1_ae/*
#define  AGC_H1		0xC4		//0xC4 0x10 ! (AGC_H1) T1_input and T2_input
#define  AGC_H1		0xC5		//0xC5 0xC ! (AGC_H1) k0, k1, and k2
#define  AGC_H1		0xC6		//0xC6 0x10 ! (AGC_H1) O1_input and O2_input
#define  AGC_H1		0xC7		//0xC7 0x10 ! (AGC_H1) aa, 1_aa, ad, and 1_ad*/
#define  AGC_H1_enable		0xD5		//0xD5 0x8 ! (AGC_H1) DRC enable
#define  Delay1		0xC8		//0xC8 0x4 ! (TAS3204AudioApp_1) Delay Pointer 0 and 1 Length#define  Delay2		0xC8		//0xC8 0x4 ! (TAS3204AudioApp_1) Delay Pointer 0 and 1 Length#define  Delay3		0xC9		//0xC9 0x4 ! (TAS3204AudioApp_1) Delay Pointer 2 and 3 Length#define  Delay4		0xC9		//0xC9 0x4 ! (TAS3204AudioApp_1) Delay Pointer 2 and 3 Length#define  Delay5		0xCA		//0xCA 0x4 ! (TAS3204AudioApp_1) Delay Pointer 4 and 5 Length#define  Delay6		0xCA		//0xCA 0x4 ! (TAS3204AudioApp_1) Delay Pointer 4 and 5 Length#define  Delay7		0xCB		//0xCB 0x4 ! (TAS3204AudioApp_1) Delay Pointer 6 and 7 Length#define  Delay8		0xCB		//0xCB 0x4 ! (TAS3204AudioApp_1) Delay Pointer 6 and 7 Length#define  Delay9		0xCC		//0xCC 0x4 ! (TAS3204AudioApp_1) Delay Pointer 8 and 9 Length#define  Delay10		0xCC		//0xCC 0x4 ! (TAS3204AudioApp_1) Delay Pointer 8 and 9 Length
/*
#define  TAS3204AudioApp_1		0xCD		//0xCD 0x4 ! (TAS3204AudioApp_1) Delay Pointer 10 and 11 Length
#define  TAS3204AudioApp_1		0xCE		//0xCE 0x4 ! (TAS3204AudioApp_1) Delay Pointer 12 and 13 Length
#define  TAS3204AudioApp_1		0xCF		//0xCF 0x4 ! (TAS3204AudioApp_1) Delay Pointer 14 and 15 Length
#define  TAS3204AudioApp_1		0xD0		//0xD0 0x4 ! (TAS3204AudioApp_1) Delay Pointer 16 and 17 Length
#define  TAS3204AudioApp_1		0xD1		//0xD1 0x4 ! (TAS3204AudioApp_1) Delay Pointer 18 and 19 Length
#define  TAS3204AudioApp_1		0xD2		//0xD2 0x4 ! (TAS3204AudioApp_1) Delay Pointer 20 and 21 Length
#define  TAS3204AudioApp_1		0xD3		//0xD3 0x4 ! (TAS3204AudioApp_1) Delay Pointer 22 and 23 Length*/#define  Delay_Update		0xD4		//0xD4 0x4 ! (TAS3204AudioApp_1) Delay Update Flag
#define  AGC_B1_ae		0xD6		//0xD6 0x8 ! (AGC_B1) ae and 1_ae/*
#define  AGC_B1		0xD7		//0xD7 0x10 ! (AGC_B1) T1_input and T2_input
#define  AGC_B1		0xD8		//0xD8 0xC ! (AGC_B1) k0, k1, and k2
#define  AGC_B1		0xD9		//0xD9 0x10 ! (AGC_B1) O1_input and O2_input
#define  AGC_B1		0xDA		//0xDA 0x10 ! (AGC_B1) aa, 1_aa, ad, and 1_ad
#define  AGC_B1		0xDB		//0xDB 0x8 ! (AGC_B1) DRC enable*/#define  AGC_L1_ae		0xDC		//0xDC 0x8 ! (AGC_L1) ae and 1_ae/*
#define  AGC_L1		0xDD		//0xDD 0x10 ! (AGC_L1) T1_input and T2_input
#define  AGC_L1		0xDE		//0xDE 0xC ! (AGC_L1) k0, k1, and k2
#define  AGC_L1		0xDF		//0xDF 0x10 ! (AGC_L1) O1_input and O2_input
#define  AGC_L1		0xE0		//0xE0 0x10 ! (AGC_L1) aa, 1_aa, ad, and 1_ad
#define  AGC_L1		0xE1		//0xE1 0x8 ! (AGC_L1) DRC enable*/#define  AGC_H2_ae		0xE2		//0xE2 0x8 ! (AGC_H2) ae and 1_ae/*
#define  AGC_H2		0xE3		//0xE3 0x10 ! (AGC_H2) T1_input and T2_input
#define  AGC_H2		0xE4		//0xE4 0xC ! (AGC_H2) k0, k1, and k2
#define  AGC_H2		0xE5		//0xE5 0x10 ! (AGC_H2) O1_input and O2_input
#define  AGC_H2		0xE6		//0xE6 0x10 ! (AGC_H2) aa, 1_aa, ad, and 1_ad
#define  AGC_H2		0xE7		//0xE7 0x8 ! (AGC_H2) DRC enable*/#define  AGC_B2_ae		0xE8		//0xE8 0x8 ! (AGC_B2) ae and 1_ae/*
#define  AGC_B2		0xE9		//0xE9 0x10 ! (AGC_B2) T1_input and T2_input
#define  AGC_B2		0xEA		//0xEA 0xC ! (AGC_B2) k0, k1, and k2
#define  AGC_B2		0xEB		//0xEB 0x10 ! (AGC_B2) O1_input and O2_input
#define  AGC_B2		0xEC		//0xEC 0x10 ! (AGC_B2) aa, 1_aa, ad, and 1_ad
#define  AGC_B2		0xED		//0xED 0x8 ! (AGC_B2) DRC enable*/#define  Mix4Ch_7		0xEE		//0xEE 0x10 ! (Mix4Ch_7) Gain function for Channel 1-4#define  Mix4Ch_9		0xEF		//0xEF 0x10 ! (Mix4Ch_9) Gain function for Channel 1-4
#define  AGC_L2_ae		0xF6		//0xF6 0x8 ! (AGC_L2) ae and 1_ae/*
#define  AGC_L2		0xF7		//0xF7 0x10 ! (AGC_L2) T1_input and T2_input
#define  AGC_L2		0xF8		//0xF8 0xC ! (AGC_L2) k0, k1, and k2
#define  AGC_L2		0xF9		//0xF9 0x10 ! (AGC_L2) O1_input and O2_input
#define  AGC_L2		0xFA		//0xFA 0x10 ! (AGC_L2) aa, 1_aa, ad, and 1_ad
#define  AGC_L2		0xFB		//0xFB 0x8 ! (AGC_L2) DRC enable*/#define  VUMeter_1		0xFC		//0xFC 0x8 ! (VUMeter_1) RMS coefficient aSA and 1-aSA#define  VUMeter_1_OutEn		0xFD		// 0xFD 0x8 ! (VUMeter_1) OutputEnable#define  Mux_5		0xFE		//0xFE 0x4 ! (Mux_5) Mux Control#define  Mux_6		0xFF		//0xFF 0x4 ! (Mux_6) Mux Control#endif  //__ModulesAddr_Ver2_0_H_