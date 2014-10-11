/**
 * @file         DSP.c
 * @brief        This is a brief description.
 * @details  This is the detail description.
 * @author       author
 * @date     2014.9.20
 * @version  A001
 * @par Copyright (c): 
 *       XXX��˾
 * @par History:         
 *   version: author, date, desc\n
 */ 


#include "I2C.h"
#include "TAS3xxx.h"

#include "lrx.h"


#include <unistd.h> //sleep close




/*********************************************************************************************************
** Function name:       DspMixerSet
** Descriptions:        ·�ɿ���,Crossbar_1ģ��
** input parameters:    in ����ͨ�� out ���ͨ�� mixer ����ֵ�����Ա�����in��outһһ��Ӧ�����ܻ���
in={0,1,2,3},out={0,1,2,3}
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspMixerSet(uint8_t rd,uint32_t in, uint32_t out, float mixer);





/*********************************************************************************************************
** Function name:       DspMixerSet4Ch
** Descriptions:        ·�ɿ���
** input parameters:    in ����ͨ�� select Mix4Chģ�������  mixer ����ֵ

select 0-.Mix4Ch_11,1-.Mix4Ch_12,3D������2-.Mix4Ch_13,3-.Mix4Ch_14,3D���أ�
4-.Mix4Ch_2,5-.Mix4Ch_10��SCT���أ�6-.Mix4Ch_3��������Դѡ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspMixerSet4Ch(uint8_t rd, uint32_t select, float mixer[]);





/*********************************************************************************************************
** Function name:       DspGain
** Descriptions:        ��������
** input parameters:    gain �����ṹ��ָ��
**                    index =0.����Volume_4��crossbar_3������˵�һͨ����������Ch =1.����Volume_5��crossbar_3������˵ڶ�ͨ����������
**                    index =3.����Volume_11��crossbar_3������˵�һͨ����������Ch =3.����Volume_10��crossbar_3������˵ڶ�ͨ��������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
//int DspGain(VOL_STR *gain);  //v2.0
int DspGain(VOL_OP *gain);



/*********************************************************************************************************
** Function name:       DspOutDelay
** Descriptions:        ���ͨ����ʱ����
** input parameters:    Ch ���ͨ�� delay ��ʱ�ṹ��ָ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspOutDelay(Outdly *OutPutDly);



void DspClsCrossbar1(uint8 rd,uint32_t rep[64]);

void DspWiteCrossbar1(uint32_t rep[64]);


/*
***************************************************************************************************
**                                          DspLimiter()
**	����������DRC��̬��Χ���ơ�
**	��  ��  ��Chn             ��Ƶͨ��ѡ��
**		drc.T1,T2       ��ص�ƽ
**            drc.k0,k1,k2    б��
**            drc.O1,O2       ��ƽƫ����
**            drc.Attack      ���ʱ��
**            drc.Release       �ͷ�ʱ��
**            drc.en          ����ʹ�ܱ�־
**	����ֵ  ����
***************************************************************************************************
*/

int DspLimiter(LimiterOP_STR *LimOP);




/*
***************************************************************************************************
**                                          Dsp3DMusicEn()
**	��������������3DЧ����
**	��  ��  ��en
**	����ֵ  ����
***************************************************************************************************
*/
int Dsp3DMusicEn(uint8 en, uint8_t Ch);


int Dsp3DMusicMix(float mixer[], uint8_t Ch );



/*********************************************************************************************************
** Function name:       Dsp3DMusicDelay
** Descriptions:        ���ͨ����ʱ����
** input parameters:    Ch ���ͨ�� delay ��ʱ�ṹ��ָ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int Dsp3DMusicDelay(DLY_STR delay, uint32_t Ch);


/*
***************************************************************************************************
**
**                                          DspMixer3DMusMultIn()
**
**
**	����������3Dmusic�е�·��ѡ������롣
**
**	��  ��  ��Ch  ͨ�������� Ch={0,1}
**			LinType ����3DMusicͨ�������ͣ�LinType=0ʱ,3D�رգ�ֱͨ����
**			LinType=1ʱ����ʱ����һ·���ڶ�·�����������LinType=2ʱ��
**			��ʱ�͵�һ·����ʱ�͵ڶ�·����һ·�͵ڶ�·��ϣ�����һ�������LinType=3ʱ����ʱ����һ·���ڶ�·һ�����
**			In  �����ͨ�����ͣ���LinType=1ʱ��In=1��Ϊ��ʱ�����In=2��Ϊ��һ·�����In=3��Ϊ�ڶ�·�����
**			��LinType=2ʱ��In=1��Ϊ��ʱ�͵�һ·���������In=2��Ϊ��ʱ�͵ڶ�·���������In=3��Ϊ��һ·�͵ڶ�·���������
**			��LinType=3ʱ��In=1��Ϊ��ʱ����һ·���ڶ�·һ��������
**			mixer Ϊ·��ϵ�����ݶ���·��ϵ������ͬ���Ժ���Ҫ�ٸ� 
**
**	����ֵ  ����
**
**
***************************************************************************************************
*/
int DspMixer3DMusMultIn(uint8 Ch, uint8 LinType, uint8 In, float *mix);



/*
***************************************************************************************************
**                                          Dsp3DMusicOP()
**	��������������3DЧ����
**	��  ��  ��en        Music3DOp_STR* Music3DOp1
**	����ֵ  ����
***************************************************************************************************
*/
int Dsp3DMusicOP(Music3DOp_STR *Music3DOp1);



/*********************************************************************************************************
** Function name:       DspMixerSet4Ch_3DMusic
** Descriptions:        ·�ɿ��ƣ�Mix4Ch_11��Mix4Ch_12ģ��
** input parameters:    in Mix4Chģ��������ͨ�� select ��ͨ����ţ�select={0,1}��  mixer ����ֵ
**						in =0��mixer������0ʱֱͨ����������3D����
select 0-.Mix4Ch_7,1-.Mix4Ch_9,��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspMixerSet4Ch_3DMusic(uint32_t select, Mix4Ch_STR *Mix4ChNo);




/*
***************************************************************************************************
**                                         DspSctHp()
**	������������Բ�ƽ���ͨ�˲�������
**	��  ��  ��hpf.Fc   	����Ƶ��
**			  hpf.Type 	��ͨ�˲�������
**			  hpf.en	�˲���ʹ��
**			  Ch      	ͨ��ѡ��
**			  grp      	����
**	����ֵ  ����
**	��  ע  ���Ӷ�Ӧ���˲����㷨�ȵ�ϵ������I2C����ص�ϵ���͵�TAS3108������˲��������á�
***************************************************************************************************
*/
int DspSctHp(uint8 Ch, HLPF_STR hpf);



/*********************************************************************************************************
** Function name:       DspSctBp
** Descriptions:        ���������е���Ƶ��
** input parameters:    Bpf ��ͨ����ָ�룬Ch ͨ��������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspSctBp(uint8 Ch, BPF_STR bpf);



/*********************************************************************************************************
** Function name:       DspSctLp
** Descriptions:        ���������еĵ�Ƶ��
** input parameters:    hpf ��ͨ����ָ�룬Ch ͨ��������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspSctLp(uint8 Ch, HLPF_STR lpf);



/*
***************************************************************************************************
**                                          DspSCTVolDepth
**	�������������������е���ȡ�
**	��  ��  ��Ch ͨ������Ch={0,1};SCTType  SCT�����ͣ�HP��LP,BP����VolDepth ���
**	����ֵ  ����
***************************************************************************************************
*/
int DspSCTVolDepth(uint8 Ch,uint8 SCTType,float VolDepth);



void DspSetSctDepth(uint8_t type, float VolDepth, uint8_t Ch);


/*
***************************************************************************************************
**                                          DspAGC()
**	����������AGC��̬��Χ���ơ�
**
**	��  ��  ��SCT_ChCh             ��Ƶͨ��ѡ��
**			  agc.T1,T2       ��ص�ƽ
**            agc.k0,k1,k2    б��
**            agc.O1,O2       ��ƽƫ����
**            agc.Attack      ���ʱ��
**            agc.Release       �ͷ�ʱ��
**            agc.en          ����ʹ�ܱ�־
**	����ֵ  ����
***************************************************************************************************
*/
int DspAGC(uint8 SCT_Ch, DRC_STR AGC);
void DspSetSctAgc(uint8_t type, DRC_STR agc, uint8_t Ch);


//void DspSetSctAgc(uint8_t type, uint8_t en, fp32 T2, fp32 k2, fp32 attack, fp32 release, uint8_t Ch);

void DspSctEn(uint8_t en, uint8_t Ch);

//void DspSctEn(float mixer[], uint8_t Ch);
void DspSctMix(float mixer[], uint8_t Ch);


/*
***************************************************************************************************
**
**                                          DspSCTMixMulIn()
**
**
**	�������������������е�·��ѡ������롣
**
**	��  ��  ��Ch  ͨ�������� Ch={0,1}
**			LinType ����SCTͨ�������ͣ�LinType=1ʱ���ߡ��С����������������LinType=2ʱ��
**			���С��ߵ͡��е���ϣ�����һ����������LinType=3ʱ�����е�һ��������
**			In  �����ͨ�����ͣ���LinType=1ʱ��In=0��Ϊ���������In=1��Ϊ�������In=2��Ϊ�������
**			��LinType=2ʱ��In=0��Ϊ���������In=1��Ϊ�ߵ��������In=2��Ϊ�е��������
**			��LinType=3ʱ��In=0��Ϊ���е���һ��·�����
**			mix Ϊ·��ϵ���� 
**
**	����ֵ  ����
**
**
***************************************************************************************************
*/
int DspSCTMixMulIn(uint8 Ch, uint8 LinType, uint8 In, float *mix);




/*
***************************************************************************************************
**                                          DspSCTOP()
**	��������������������SCT��
**	��  ��  ��       SCTOP_STR* SCTOP1
**	����ֵ  ����
***************************************************************************************************
*/
int DspSCTOP( SCTOP_STR *SCTOP1);






/*
***************************************************************************************************
**                                         DspACHBp_HP()
**	������������Բ�ƽ���ͨ�˲�������
**	��  ��  ��hpf.Fc   	����Ƶ��
**			  hpf.Type 	��ͨ�˲�������
**			  hpf.en	�˲���ʹ��
**			  Ch      	ͨ��ѡ��
**			  grp      	����
**			  Ch=0,ǰ��Ch=1,ǰ�ң�Ch=2,����Ch=3,���ң�Ch=4,���ͣ�Ch=5,���ã�
**	����ֵ  ����
**	��  ע  ���Ӷ�Ӧ���˲����㷨�ȵ�ϵ������I2C����ص�ϵ���͵�TAS3108������˲��������á�
***************************************************************************************************
*/
int DspACHBp_HP(CHanHLPF_STR *ChHP);


/*
***************************************************************************************************
**                                         DspACHBp_LP()
**	������������Բ�ƽ���ͨ�˲�������
**
**	��  ��  ��hpf.Fc   	����Ƶ��
**			  hpf.Type 	��ͨ�˲�������
**			  hpf.en	�˲���ʹ��
**			  Ch      	ͨ��ѡ��
**			  grp      	����
**           Ch=0,ǰ��Ch=1,ǰ�ң�Ch=2,����Ch=3,���ң�Ch=4,���ͣ�Ch=5,���ã�
**	����ֵ  ����
**	��  ע  ���Ӷ�Ӧ���˲����㷨�ȵ�ϵ������I2C����ص�ϵ���͵�TAS3108������˲��������á�
***************************************************************************************************
*/
int DspACHBp_LP(CHanHLPF_STR *ChLP);

void DspACHBp_BP(BPF_STR *bpf, uint8 Ch);


/*********************************************************************************************************
** Function name:      
** Descriptions:        ���PEQ����
** input parameters:    peq PEQ�ṹ��ָ�룬���ͨ������Ch��ÿ��ͨ��Eq������no
**						 Ch=0,ǰ��Ch=1,ǰ�ң�Ch=2,����Ch=3,���ң�Ch=4,���ͣ�Ch=5,���ã�
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

int DspACHPEQ(EQOP_STR *PEQOP);



/*********************************************************************************************************
** Function name:       DspBCHPEQ
** Descriptions:        ����PEQ����
** input parameters:    peq PEQ�ṹ��ָ�룬���ͨ������Ch��ÿ��ͨ��Eq������no
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

int DspBCHPEQ(EQOP_STR *PEQOP);




/*********************************************************************************************************
** Function name:       DspAorDChanMixer()
** Descriptions:        ģ�⡢����ͨ��·�ɿ��ƣ�Crossbar_2ģ��
** input parameters:    Aen ģ��ͨ��ʹ�ܣ���Aen=1ʱ��ģ��ͨ��·�ɵ���ģ�������˿ڣ���������ͨ·������˿�
**						mixer ����ֵ
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspAorDChanMixer(AnaOrDigSrc_STR *AnaOrDig);



/**
* ��ȡ�����ƽ
* This is a detail description.
* @outVal       ��������ĵ�ƽֵ 
* @par ��ʶ��
*      ����
* @par ����
*      ��
* @par �޸���־
*      XXX��2014-9-20����
*/
void VuDetect(uint8 *outVal);



/**
* 6·�����������
* This is a detail description.
* @in       ������Դ����ʱ��ʹ�á�
* @out     �����Դ
* @gain,  ������� 
* @par �޸���־
*      XXX��2014-9-28����
*/
void volOutput(uint8_t in, uint8_t out, fp32 gain);

/**
* �����ź�Դ���enable
* This is a detail description.
* @par �޸���־
*      XXX��2014-9-28����
*/
void DspSignalSourceEnable();


/**
* �����ź�Դ���cancel
* This is a detail description.
* @par �޸���־
*      XXX��2014-9-28����
*/
void DspSignalSourceCancel();




/**
* �����ź�Դ���ѡ��
* This is a detail description.
* @in       ������Դ
* @out     �����Դ
* @total,  �����Դ���� 
* @type   ��������
* @retval  0 �ɹ�
* @retval  -1   ���� 
* @par �޸���־
*      XXX��2014-9-20����
*/
int DspSigSourSelectOut(uint8_t in, uint8_t out, uint8_t total, uint8_t type);



/**
* ����·��ֱͨ
* This is a detail description. 
* @par ��ʶ��
*      ����                (������....)
* @par ����
*      ��
* @par �޸���־
*      XXX��2014-9-20����
*/
void AllMixThrough();







/*********************************************************************************************************
** Function name:       DspDigChansMux()
** Descriptions:        ģ�⡢����ͨ��·�ɿ��ƣ�Mux_5,Mux_6ģ��
** input parameters:    uint8 DigChan    DigChan=1ʱ��Ϊ��һ·I2Sͨ��������Ϊ�ڶ�·I2Sͨ��
**						
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspDigChansMux(uint8 DigChan);







/*********************************************************************************************************
** Function name:       DspFunModInit
** Descriptions:        ʵ��DSP��������ģ��ĳ�ʼ����3D��ͨ������PEQ��ͨ��HP��ͨ��SCT��ͨ������ģ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int DspFunModInit(void);
int DspAllByPass(void);


void readArchiveInitDsp();
void archiveInitDsp();




void testMUX();






































