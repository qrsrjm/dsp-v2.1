#include "dspArchive.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "g_variable.h"
#include "flash_api.h"


int addName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
    if (*name=='\0') return -1;
    if (name == NULL) return -4;
    if (strlen(name)> 19) return -2;
	for(i=0;i<NAME_CNT;i++) {
		if (Aname[i][0] == '\0') {
			printf("is null. i=%d\n",i);
			strcpy(Aname[i],name);
			return i;
		} 
	}	
	return -1;
}

int delName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
    if (*name == '\0') return -1;
    if (name==NULL) return -4;
	for(i=0;i<NAME_CNT;i++) {
		if (0 == strcmp(Aname[i],name)) {
			memset(Aname[i],0,NAME_LEN);
		}
	}
    return 0;
}


int findName(char Aname[NAME_CNT][NAME_LEN], char *name)
{
	int i;
	if (Aname[0][0] == '\0') return -2;
	if (*name == '\0') return -3;
    if (name==NULL) return -4;
	for(i=0;i<NAME_CNT;i++) {
		if (0 == strcmp(Aname[i],name)) {
			return i;
		}
	}
	return -1;
}


void showNameToStr(char Aname[NAME_CNT][NAME_LEN], char *str)
{	
	char tmp[NAME_LEN]={0};
	int i,len=0;
	for(i=0;i<NAME_CNT;i++) {
		if (Aname[i][0] == '\0') continue;
		sprintf(tmp,"%s,",Aname[i]);
		strcpy(str+len,tmp);
		len += strlen(tmp);
	}
	char *p = strrchr(str,',');
	*p = '\0';
}

int nameToStr(char Aname[NAME_CNT][NAME_LEN], char *str)
{	
	if (str == NULL) return -1;
    memset(str,0,NAME_CNT*NAME_LEN);
    memcpy(str,Aname,NAME_CNT*NAME_LEN-1);
    str[NAME_CNT*NAME_LEN-1] = '\0';
    printf("-->%s\n",str);
    return 0;
}


void showName(char Aname[NAME_CNT][NAME_LEN])
{
	int i;
	for(i=0;i<NAME_CNT;i++) {
		printf("<%d> %s\n",i,Aname[i]);
	}
}


int readMacInfo(MACINFO *mac)
{
	char tmp[36]={0};
	flash_read_archive(tmp, MACINF_ADDR, sizeof(tmp));
	if (tmp[0]=='\0') {
		flash_write_archive((char*)mac, MACINF_ADDR, sizeof(MACINFO));
		//for(i=0;i<NAME_CNT;i++)
		//	flash_write_archive(Aname[i], sizeof(MACINFO)+i*NAME_LEN, sizeof(char)*NAME_LEN);	
		//flash_write_archive((char*)&dsp, DATA_ADDR, sizeof(DSP));	
		printf("not have start name.\n");
		return -1;
	} else {
		memcpy(mac,tmp,sizeof(MACINFO));
	}
	return 0;
}


int readNameList(char Aname[NAME_CNT][NAME_LEN])
{
	char tmp[NAME_CNT*NAME_LEN]={0};
	flash_read_archive(tmp, NAME_ADDRX(0), sizeof(tmp));
	if (tmp[0]=='\0') {
		printf("not have name list.\n");
		return -1;
	} else {
		memcpy(Aname,tmp,NAME_LEN*NAME_CNT);
	}
	return 0;
}


int changeStartName(MACINFO *mac, char *name)
{
	if (*name == '\0' || strlen(name)>19 ||name==NULL) return -1;
	strncpy(mac->name,name,19);
    mac->name[19]='\0';
	flash_write_archive((char*)mac, MACINF_ADDR, sizeof(MACINFO));
    return 0;
}


int readArchiveHead()
{   
    int res=0;
#if 1
    rDspInfo = (STR_DSP*)malloc(sizeof(STR_DSP));
#else
    rDspInfo = &dspInfo;
#endif

    memset(&machine,0,sizeof(machine));
    machine.macInfo.hv = machine.macInfo.sv = machine.macInfo.SerialNumber = 11;
    int rM = readMacInfo(&(machine.macInfo));
    int rN = readNameList(machine.archiveName);

    showName(machine.archiveName);

    printf("rm=%d,rn=%d\n",rM,rN);
    
    //DspAllByPass();


    int ret;
    if (rM == -1 && rN == 0) {
        ret = readArchive(machine.archiveName[0]);
        if (ret >= 0) {	    
            res = ret;   //initArchive();
        } else {
            res = -1;   //DspAllByPass();
        }
    } else if (rM == 0 && rN == 0) {
        ret = readArchive(machine.macInfo.name);
        if (ret >= 0) {		    
            res = ret;   //initArchive();
        } else {
            res = -1;   //DspAllByPass();
        }
    } else if (rM == -1 && rN == -1) {
        res = -1;   //DspAllByPass();
    } 
#if 0    
    int ret;
    if (rM == -1 && rN == 0) {
        ret = findName(machine.archiveName, machine.archiveName[0]); 
        if (ret >= 0) {
		    flash_read_archive((char*)rDspInfo, DATA_ADDRX(ret), sizeof(STR_DSP));
            res = ret;   //initArchive();
        } else {
            res = -1;   //DspAllByPass();
        }
    } else if (rM == 0 && rN == 0) {
        ret = findName(machine.archiveName, machine.macInfo.name); 
        if (ret >= 0) {
		    flash_read_archive((char*)rDspInfo, DATA_ADDRX(ret), sizeof(STR_DSP));
            res = ret;   //initArchive();
        } else {
            res = -1;   //DspAllByPass();
        }
    } else if (rM == -1 && rN == -1) {
        res = -1;   //DspAllByPass();
    } 
#endif
    machine.readDspInfo = rDspInfo;
    
    printf("read Archive head finish. ret=%d\n",ret);

    return res; 
}


int readArchive(char *name)
{
    showName(machine.archiveName);
    int ret = findName(machine.archiveName, name);
    if (ret >= 0) {
        memset((char*)rDspInfo, 0, sizeof(STR_DSP));
        memset((char*)&dspInfo, 0, sizeof(STR_DSP));
        flash_read_archive((char*)rDspInfo, DATA_ADDRX(ret), sizeof(STR_DSP)); 
        memcpy(&dspInfo,rDspInfo,sizeof(STR_DSP));
    } 
    printf("\n-->%s> name=%s,ret=%d\n",__FUNCTION__,name,ret);
    return ret;
}

int saveArchive(char *name)
{
    int rt = findName(machine.archiveName, name);
    if (rt >= 0) {
        char cls[sizeof(dspInfo)]={0};
        flash_write_archive(cls, DATA_ADDRX(rt), sizeof(dspInfo));
        flash_write_archive((char*)&dspInfo, DATA_ADDRX(rt), sizeof(dspInfo));
    } else {
        rt = addName(machine.archiveName, name);
        if (rt >= 0) {
            flash_write_archive((char*)&dspInfo, DATA_ADDRX(rt), sizeof(dspInfo));
        } else if (rt == -1) {
            printf("name is NULL,pls input file name.\n");
        } else if (rt == -2) {
            printf("name is too long, pls input file name.\n");
        }
    }
    showName(machine.archiveName); 
    char *str = (char*)malloc(NAME_CNT*sizeof(char)*NAME_LEN);
    nameToStr(machine.archiveName, str);
	flash_write_archive(str, NAME_ADDRX(0), sizeof(char)*NAME_LEN*NAME_CNT);
    free(str);
    
    return rt;
}


void readAllArchiveName(char *str)
{
    showNameToStr(machine.archiveName, str);
}


void readMachine(MACINFO *mac)
{

	char tmp[36]={0};
	flash_read_archive((char*)mac, MACINF_ADDR, sizeof(MACINFO));
}

int initLoadArchive(char *name)
{
    changeStartName(&(machine.macInfo), name);
    return 0;
}


