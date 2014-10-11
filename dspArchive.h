#ifndef DSPARCHIVE____H___
#define DSPARCHIVE____H___

#include "lrx.h"
#include "g_variable.h"



int addName(char Aname[NAME_CNT][NAME_LEN], char *name);

int delName(char Aname[NAME_CNT][NAME_LEN], char *name);

int findName(char Aname[NAME_CNT][NAME_LEN], char *name);

void showNameToStr(char Aname[NAME_CNT][NAME_LEN], char *str);

void showName(char Aname[NAME_CNT][NAME_LEN]);

int readMacInfo(MACINFO *mac);

int readNameList(char Aname[NAME_CNT][NAME_LEN]);

int changeStartName(MACINFO *mac, char *name);


int readArchiveHead();

int readArchive(char *name);
int saveArchive(char *name);
void readAllArchiveName(char *str);
void readMachine(MACINFO *mac);
int initLoadArchive(char *name);



#endif //DSPARCHIVE____H___
