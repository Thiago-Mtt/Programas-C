#ifndef todolist_HEADER
#define todolist_HEADER

#define CLEAR "cls"             //Comando do sistema operacional para limpar o prompt de comando
#define MAX_TAMANHO_TAREFA 30   //Numero máximo de caracteres em uma linha na lista de tarefas 
#define MAX_TAMANHO_COMANDO 40  //Máximo de caracteres recebidos como entrada
#define LISTA "lista.txt"       //Nome do arquivo onde se implementa a lista

//X Macro. Guarda os comandos reconhecidos pelo programa, utilizada para automatizar declaração das funções, codificação
//  dos comandos e facilitar adição de um novo comando
//A definição de X(comando,COMANDO) indica aplicação desta macro.
//[comando] escrito em minusculo para funções, maiusculo para enum
//Adicionar um comando nessa lista requer também a definição de sua função, a qual é declarada automaticamente
#define COMANDO_TABLE \
    X(list, LIST)\          //Listar tarefas com ou sem filtros (Ex: mostrar só tarefas não marcadas)
    X(add, ADD)\            //Adicionar tarefa
    X(del, DEL)\            //Deletar tarefa(s) (Ex: deletar a tarefa selecionada ou deletar todas as marcadas)
    X(check, CHECK)\        //Marcar tarefa(s) como cumpridas
    X(uncheck, UNCHECK)     //Desmarcar tarefa(s) como cumpridas


//Declaração das funções dos respectivos comandos
#define X(comando, COMANDO) void comando(char * param);
COMANDO_TABLE
#undef X

//Definição do tipo en_comando, codificação dos comandos
#define X(comando, COMANDO) COMANDO ,
typedef enum {
    COMANDO_TABLE
    NRO_COMANDOS, EN_ERR=-1
} en_comando;
#undef X

//Retorna o valor codificado do comando passado como string
en_comando str_to_en_comando(const char * str);

//Copia a primeira palavra(o comando) da entrada para o array 'comando'
//Retorna um ponteiro apontando para a primeira letra da segunda palavra (o(s) parametro(s))
//Caso nao tenha parametro, retorna NULL
char * get_comando(char * comando, const char * entrada);

//Abre arquivo LISTA e emite no terminal as tarefas em cada linha
//Tarefas são enumeradas a fim de auxiliar seleção de tarefa para operaçãos como 'check' e 'del'
void ler_lista_all();



#endif //todolist_HEADER