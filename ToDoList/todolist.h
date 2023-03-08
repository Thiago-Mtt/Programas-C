#ifndef todolist_HEADER
#define todolist_HEADER

#define COMANDOS \
    comList,\
    comAdd,\
    comDel,\
    comCheck,\
    comUncheck

char * getComando(char * comando, const char * entrada);

void comList(char * param);
void lerListaAll();

void comAdd(char * param);

void comDel(char * param);

void comCheck(char * param);

void comUncheck(char * param);

#endif