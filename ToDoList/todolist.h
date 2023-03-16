#ifndef todolist_HEADER
#define todolist_HEADER

#define CLEAR "cls"
#define MAX_TAMANHO_TAREFA 30
#define MAX_TAMANHO_COMANDO 40
#define LISTA "lista.txt"

//minusculo para funções, maiusculo para enum
#define COMANDO_TABLE \
    X(list, LIST)\
    X(add, ADD)\
    X(del, DEL)\
    X(check, CHECK)\
    X(uncheck, UNCHECK)


//Declaração das funções dos respectivos comandos
#define X(comando, COMANDO) void comando(char * param);
COMANDO_TABLE
#undef X

//Copia a primeira palavra(o comando) na entrada para o array 'comando'
//Retorna um ponteiro apontando para a primeira letra da segunda palavra (o(s) parametro(s))
//Caso nao tenha parametro, retorna NULL
char * get_comando(char * comando, const char * entrada);

//Abre arquivo LISTA e emite no terminal as tarefas em cada linha
//Tarefas são enumeradas a fim de auxiliar seleção de tarefa
void ler_lista_all();



#endif