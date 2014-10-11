#include "dataToString.h"

#include <string.h>
#include <stdio.h>

#include "lrx.h"
#include "g_variable.h"

void versionToString(char *p, char *dest)
{
    strcpy(dest,p);
    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void outVolToString(fp32 *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"outVol%f,",*p);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void crossbar1ToString(Crossbar_STR ptr[][6], char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    Crossbar_STR *p = ptr;
    for(i=0;i<12;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"crossbar%d,%d,%f,",p->in,p->out,p->mix);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void ADToString(AnaOrDigSrc_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"ad%d,%f,",p->en,p->mixer);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void hlpfToString(HLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"pf%d,%d,%d,",p->Fc,p->Type,p->en);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void agcToString(DRC_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;

    memset(tmp,0,64);
    sprintf(tmp,"agc%f,%f,%f,%f,%d,",p->T2,p->k2,p->Attack,p->Release,p->en);
    strcpy(dest+len,tmp);

    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void lpfToString(CHanHLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<1;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"hpf%d,",p->Ch);
        hlpfToString(&(p->xpf), tmp+strlen(tmp));
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void hpfToString(CHanHLPF_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<6;i++,p+=1) {
        if (i == 4) continue;
        memset(tmp,0,64);
        sprintf(tmp,"hpf%d,",p->Ch);
        hlpfToString(&(p->xpf), tmp+strlen(tmp));
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void BpfToString(BPF_OP *p, char *dest)
{   
    int i;
    char tmp[64]={0};
    int len=0;
    
    memset(tmp,0,64);
	sprintf(tmp,"bpf %d,%d,%d,%d,%d,\n",p->Ch,p->Fp,p->Fs,p->Type,p->en);
    strcpy(dest+len,tmp);
    len += strlen(tmp);
    
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void bpfToString(BPF_STR *p, char *dest)
{   
    int i;
    char tmp[64]={0};
    int len=0;
    
    memset(tmp,0,64);
	sprintf(tmp,"bpf %d,%d,%d,%d,\n",p->Fp,p->Fs,p->Type,p->en);
    strcpy(dest+len,tmp);
    len += strlen(tmp);
    
    printf("\n%s,len=%d\n",dest,strlen(dest));
}


void sctToString(SCTDATA_STR *p, char *dest)
{
    char tmp[512]={0};
    int len=0;
    int i;
    for(i=0;i<2;i++,p+=1) {
        memset(tmp,0,512);

        sprintf(tmp,"SCT%d,%d,",p->Ch,p->en);

        hlpfToString(&(p->hpf), tmp+strlen(tmp));
        agcToString(&(p->AGChp), tmp+strlen(tmp));

        bpfToString(&(p->bpf), tmp+strlen(tmp));
        agcToString(&(p->AGCbp), tmp+strlen(tmp));

        hlpfToString(&(p->lpf), tmp+strlen(tmp));
        agcToString(&(p->AGClp), tmp+strlen(tmp));

        sprintf(tmp+strlen(tmp),"vol%f,%f,%f,%f,%f,%f,%f,",p->hVolDepth,p->bVolDepth,p->lVolDepth,p->mix[0],p->mix[1],p->mix[2],p->mix[3]);

        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}



void m3DToString(Music3DOp_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    for(i=0;i<2;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"3d%d,%f,%d,%f,%f,%f,%f,%d,",p->Ch,p->delay.Dly,p->delay.en,p->mix[0],p->mix[1],p->mix[2],p->mix[3],p->en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("\n%s,len=%d\n",dest,strlen(dest));
}

void limitToString(LimiterOP_STR *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"limit%d,%f,%f,%f,%f,%d,",p->Ch,p->limiter.T2,p->limiter.k2,p->limiter.Attack,p->limiter.Release,p->limiter.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

void outDlyToString(Outdly *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<6;i++,p+=1) {
        memset(tmp,0,64);
        sprintf(tmp,"outDly%d,%f,%d,",p->Ch,p->delay.Dly,p->delay.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

void eqToString(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<1;i++)        // 1个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    printf("%s,len=%d\n",dest,strlen(dest));
}

void achEQToString(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<48;i++,p+=1)   //48个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString0(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<10;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString1(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<10;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString2(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<10;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString3(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<10;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString4(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<5;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

/*
* 2014.10.7
*/
void achEQToString5(EQOP_STR  *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<3;i++,p+=1)   //10个
    {
        //printf("%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        memset(tmp,0,64);
        sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }
    printf("%s,len=%d\n",dest,strlen(dest));
}



void bchEQToString(EQOP_STR  p[2][7], char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    int j;
    
    for(i=0;i<2;i++)
    {
        for(j=0;j<7;j++) {
            //printf("EQ%d,%d,%f,%f,%d,%d,%d,",p[i][j].Ch,p[i][j].no,p[i][j].peq.Q,p[i][j].peq.Gain, p[i][j].peq.Fc,p[i][j].peq.Type,p[i][j].peq.en);            memset(tmp,0,64);
            sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p[i][j].Ch,p[i][j].no,p[i][j].peq.Q,p[i][j].peq.Gain, p[i][j].peq.Fc,p[i][j].peq.Type,p[i][j].peq.en);
            strcpy(dest+len,tmp);
            len += strlen(tmp);
        }

    }
    printf("%s,len=%d\n",dest,strlen(dest));
}

void volToString(VOL_OP *p, char *dest)
{
    char tmp[64]={0};
    int len=0;
    int i;
    
    for(i=0;i<3;i++,p+=1)
    {
        //printf("vol%d,%f,%d,%d,",p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
        memset(tmp,0,64);
        sprintf(tmp,"vol%d,%f,%d,%d,",p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
        strcpy(dest+len,tmp);
        len += strlen(tmp);
    }

    //printf("%s,len=%d\n",dest,strlen(dest));
}

//input vol
void volToStr(char *dest)
{
    volToString(rDspInfo->vol, dest);
}

void achEQToStr0(char *dest)
{
    achEQToString0(rDspInfo->achEQ, dest);
}

void achEQToStr1(char *dest)
{
    achEQToString1(&(rDspInfo->achEQ[10]), dest);
}

void achEQToStr2(char *dest)
{
    achEQToString2(&(rDspInfo->achEQ[20]), dest);
}

void achEQToStr3(char *dest)
{
    achEQToString3(&(rDspInfo->achEQ[30]), dest);
}

void achEQToStr4(char *dest)
{
    achEQToString4(&(rDspInfo->achEQ[40]), dest);
}

void achEQToStr5(char *dest)
{
    achEQToString5(&(rDspInfo->achEQ[45]), dest);
}


void bchEQToStr(char *dest)
{
    bchEQToString(rDspInfo->bchEQ, dest);
}

void outDlyToStr(char *dest)
{
    outDlyToString(rDspInfo->outDly, dest);
}

void limitToStr(char *dest)
{
    limitToString(rDspInfo->limit, dest);
}

void m3DToStr(char *dest)
{
    m3DToString(rDspInfo->m3D, dest);
}
void sctToStr(char *dest)
{
    sctToString(rDspInfo->sct, dest);
}

void hpfToStr(char *dest)
{
    hpfToString(rDspInfo->hpf, dest);
}

void lpfToStr(char *dest)
{
    lpfToString(&(rDspInfo->lpf), dest);
}

void BpfToStr(char * dest)
{
    BpfToString(&(rDspInfo->bpf), dest);
}

void ADToStr(char *dest)
{
    ADToString(&(rDspInfo->ad), dest);
}

void crossbar1ToStr(char *dest)
{
    crossbar1ToString(rDspInfo->crossbar1, dest);
}

void outVolToStr(char *dest)
{
    outVolToString(rDspInfo->outVol, dest);
}


void initDsp(STR_DSP *dspInfo)
{
    int i;
    for(i=0;i<3;i++) {
        dspInfo->vol[i].vol.Gain = 2+i;
        dspInfo->vol[i].vol.Pol =0;
        dspInfo->vol[i].vol.Mute=0;
        dspInfo->vol[i].Ch=i;
    }

    for(i=0;i<48;i++) {
        dspInfo->achEQ[i].peq.Q = 1.0+i;
        dspInfo->achEQ[i].peq.Gain = 1.1+i;
        dspInfo->achEQ[i].peq.Fc = 100+i*10;
        dspInfo->achEQ[i].peq.Type = 8;
        dspInfo->achEQ[i].peq.en = 1;
        dspInfo->achEQ[i].Ch = i%5;
        dspInfo->achEQ[i].no = i%10;
    }
    
    int j;
    for(i=0;i<2;i++) {
        for(j=0;j<7;j++) {
            dspInfo->bchEQ[i][j].peq.Q = 1;
            dspInfo->bchEQ[i][j].peq.Gain = 2;
            dspInfo->bchEQ[i][j].peq.Fc = 100+i*10;
            dspInfo->bchEQ[i][j].peq.Type = 7;
            dspInfo->bchEQ[i][j].peq.en = 1;
            dspInfo->bchEQ[i][j].Ch = i;
            dspInfo->bchEQ[i][j].no = j;
            //printf("EQ%d,%d,%f,%f,%d,%d,%d,",dspInfo->bchEQ[i][j].Ch,dspInfo->bchEQ[i][j].no,dspInfo->bchEQ[i][j].peq.Q,dspInfo->bchEQ[i][j].peq.Gain, dspInfo->bchEQ[i][j].peq.Fc,dspInfo->bchEQ[i][j].peq.Type,dspInfo->bchEQ[i][j].peq.en);
        }
    }

    for(i=0;i<6;i++) {
        dspInfo->outDly[i].delay.Dly = i;
        dspInfo->outDly[i].delay.en = 1;
        dspInfo->outDly[i].Ch = i;
    }

    for(i=0;i<6;i++) {
        dspInfo->limit[i].limiter.T2 = i;
        dspInfo->limit[i].limiter.k2 = i;
        dspInfo->limit[i].limiter.Attack = 1;
        dspInfo->limit[i].limiter.Release = 1;
        dspInfo->limit[i].limiter.en = 1;
        dspInfo->limit[i].Ch = i;
    }

    for(i=0;i<2;i++) {
        dspInfo->m3D[i].delay.Dly=12;
        dspInfo->m3D[i].delay.en =1;
        dspInfo->m3D[i].mix[0] =1;
        dspInfo->m3D[i].mix[1] =2;
        dspInfo->m3D[i].mix[2] =3;
        dspInfo->m3D[i].mix[3] =4;
        dspInfo->m3D[i].en = 1;
        dspInfo->m3D[i].Ch = i;
    }

    for(i=0;i<2;i++) {
        dspInfo->sct[i].hpf.Fc = i*1000;
        dspInfo->sct[i].hpf.Type = i;
        dspInfo->sct[i].hpf.en = 1;
        dspInfo->sct[i].AGChp.T2 = i+1;
        dspInfo->sct[i].AGChp.k2 = i+1;
        dspInfo->sct[i].AGChp.Attack = 1;
        dspInfo->sct[i].AGChp.Release = 1;
        dspInfo->sct[i].AGChp.en = 1;

        dspInfo->sct[i].bpf.Fp = 1000;
        dspInfo->sct[i].bpf.Fs = 2000;
        dspInfo->sct[i].bpf.Type = 1;
        dspInfo->sct[i].bpf.en = 1;
        dspInfo->sct[i].AGCbp.T2 = i+2;
        dspInfo->sct[i].AGCbp.k2 = i+2;
        dspInfo->sct[i].AGCbp.Attack = 2;
        dspInfo->sct[i].AGCbp.Release = 2;
        dspInfo->sct[i].AGCbp.en = 1;

        dspInfo->sct[i].lpf.Fc = i*2000;
        dspInfo->sct[i].lpf.Type = i+1;
        dspInfo->sct[i].lpf.en = 1;
        dspInfo->sct[i].AGClp.T2 = i+3;
        dspInfo->sct[i].AGClp.k2 = i+3;
        dspInfo->sct[i].AGClp.Attack = 3;
        dspInfo->sct[i].AGClp.Release = 3;
        dspInfo->sct[i].AGClp.en = 1;

        dspInfo->sct[i].hVolDepth = 23;
        dspInfo->sct[i].bVolDepth = 13;
        dspInfo->sct[i].lVolDepth = 10;
        dspInfo->sct[i].mix[0] = 1;
        dspInfo->sct[i].mix[1] = 1;
        dspInfo->sct[i].mix[2] = 1;
        dspInfo->sct[i].mix[3] = 1;
        dspInfo->sct[i].en = 1;
        dspInfo->sct[i].Ch = i;
    }

    for(i=0;i<6;i++) {
        dspInfo->hpf[i].xpf.Fc = i*100+500;
        dspInfo->hpf[i].xpf.Type = i;
        dspInfo->hpf[i].xpf.en = 1;
        dspInfo->hpf[i].Ch = i;
    }

    for(i=0;i<1;i++) {
        dspInfo->lpf.xpf.Fc = i*100+500;
        dspInfo->lpf.xpf.Type = i+1;
        dspInfo->lpf.xpf.en = 1;
        dspInfo->lpf.Ch = 5;
    }

    dspInfo->ad.en = 1;
    dspInfo->ad.mixer = 1.1;

    for(i=0;i<2;i++)
    for(j=0;j<6;j++) {
        dspInfo->crossbar1[i][j].in = i;
        dspInfo->crossbar1[i][j].out = j;
        dspInfo->crossbar1[i][j].rd = 1;
        dspInfo->crossbar1[i][j].mix = 1.5;
    }


    for(i=0;i<6;i++){
        dspInfo->outVol[i] = i*2+1;
    }
}



#if 0 //TEST_STRING
int main()
{
    char *dest = (char*)malloc(1024*4);
    memset(&dspInfo,0,sizeof(dspInfo));

    initDsp(&dspInfo);
    volToStr(dspInfo.vol,dest);
    //achEQToStr(dspInfo.achEQ, dest+strlen(dest));
    //bchEQToStr(dspInfo.bchEQ, dest+strlen(dest));
    //outDlyToStr(dspInfo.outDly, dest+strlen(dest));
    //limitToStr(dspInfo.limit, dest+strlen(dest));
    //m3DToStr(dspInfo.m3D, dest+strlen(dest));
    //sctToStr(dspInfo.sct,  dest+strlen(dest));
    //hpfToStr(dspInfo.hpf, dest+strlen(dest));
    //lpfToStr(&(dspInfo.lpf), dest+strlen(dest));
    //ADToStr(&(dspInfo.ad), dest+strlen(dest));
    //crossbar1ToStr(&(dspInfo.crossbar1), dest+strlen(dest));
    outVolToStr(dspInfo.outVol, dest+strlen(dest));

    printf("\n%s,len=%d\n",dest,strlen(dest));

    return 0;
}

#endif

#if 1 //test info show

void showInputVol(VOL_OP *p)
{
	int i;
    for(i=0;i<3;i++,p+=1)
        printf("vol_%d %d,%f,%d,%d,\n",i,p->Ch,p->vol.Gain, p->vol.Pol,p->vol.Mute);
}

void showOutputVol(fp32 *p)
{
	int i;
    for(i=0;i<6;i++,p+=1)
		printf("outVol_%d %f,\n",i,*p);
}

void showOutDly(Outdly *p)
{
	int i;
    for(i=0;i<6;i++,p+=1)
        printf("outDly_%d %d,%f,%d,\n",i,p->Ch,p->delay.Dly,p->delay.en);
}

void showEQ(EQOP_STR *p)
{
    int i;
    for(i=0;i<1;i++)        // 1个
    {
        printf("%d,%d,%f,%f,%d,%d,%d,\n",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
        //sprintf(tmp,"EQ%d,%d,%f,%f,%d,%d,%d,",p->Ch,p->no,p->peq.Q,p->peq.Gain, p->peq.Fc,p->peq.Type,p->peq.en);
    }
}

void showAchEQ(EQOP_STR *p)
{
	 int i;	 
	 for(i=0;i<48;i++,p+=1)	{//48个
		printf("i=%d ",i);
		showEQ(p);
	 }
}

void showBchEQ(EQOP_STR p[][7])
{
	 int i,j;	 
	 for(i=0;i<2;i++)
     for(j=0;j<7;j++) {
	 	printf("ch=%d no=%d ",i,j);
	 	showEQ(&(p[i][j]));
     }
}


void showLimit(LimiterOP_STR *p)
{
	int i;
    for(i=0;i<6;i++,p+=1)
        printf("limit_%d %d,%f,%f,%f,%f,%d,\n",i,p->Ch,p->limiter.T2,p->limiter.k2,p->limiter.Attack,p->limiter.Release,p->limiter.en);
}

void show3D(Music3DOp_STR *p)
{
	int i;
    for(i=0;i<2;i++,p+=1)     
        printf("3d_%d %d,%f,%d,%f,%f,%f,%f,%d,\n",i,p->Ch,p->delay.Dly,p->delay.en,p->mix[0],p->mix[1],p->mix[2],p->mix[3],p->en);
}

void showSctHLpf(HLPF_STR *p)
{
	printf("hlpf %d,%d,%d,\n",p->Fc,p->Type,p->en);
}
void showSctBpf(BPF_STR *p)
{
	printf("bpf %d,%d,%d,%d,\n",p->Fp,p->Fs,p->Type,p->en);
}

void showAgc(DRC_STR *p)
{
    printf("agc %f,%f,%f,%f,%d,\n",p->T2,p->k2,p->Attack,p->Release,p->en);
}

void showSct(SCTDATA_STR *p)
{
	int i;
    for(i=0;i<2;i++,p+=1) {
        printf("SCT_%d %d,%d,vol %f,%f,%f,mix=%f,%f,%f,%f,",i,
			p->Ch,p->en,p->hVolDepth,p->bVolDepth,p->lVolDepth,
			p->mix[0],p->mix[1],p->mix[2],p->mix[3]);
		showSctHLpf(&(p->hpf));
		showSctBpf(&(p->bpf));
		showSctHLpf(&(p->lpf));
		showAgc(&(p->AGChp));
		showAgc(&(p->AGCbp));
		showAgc(&(p->AGClp));
	}
}

void showHLpf(CHanHLPF_STR *p, uint8_t hl)
{
	int i;
	if (hl) {
	    for(i=0;i<6;i++,p+=1) {			
			showSctHLpf(&(p->xpf));
			printf(" Ch=%d\n",p->Ch);
		}
	}else{
		showSctHLpf(&(p->xpf));
		printf(" Ch=%d\n",p->Ch);
	}
}

void showBpf(BPF_OP *p)
{   
    int i;
    //for(i=0;i<2;i++,p+=1) {
	    printf("bpf %d,%d,%d,%d,%d,\n",p->Ch,p->Fp,p->Fs,p->Type,p->en);
    //}
}

void showAD(AnaOrDigSrc_STR *p)
{
	printf("ad %d,%f,\n",p->en,p->mixer);
}


void showCrossbar1(Crossbar_STR *p)
{
	int i;
	for(i=0;i<12;i++,p+=1)
		printf("crossbar_%d %d,%d,%f,\n",i,p->in,p->out,p->mix);
}





#endif //test info show


























































