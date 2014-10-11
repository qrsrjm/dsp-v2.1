#ifndef VOLLIST____H___
#define VOLLIST____H___

typedef int elemType;
typedef struct Clinklist{	
    elemType in;
    elemType out;
    elemType gain;
    struct Clinklist* next;
}Clinklist;

#endif //VOLLIST____H___