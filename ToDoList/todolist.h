#ifndef _todolist_HEADER
#define _todolist_HEADER

#define WINDOWS

#define CLEAR                   "cls"          // Comando do sistema operacional para limpar o prompt de comando
#define MAX_TAMANHO_TAREFA      30             // Numero máximo de caracteres em uma linha na lista de tarefas 
#define MAX_TAMANHO_COMANDO     40             // Máximo de caracteres recebidos como entrada
#define LISTA                   "lista.txt"    // Nome do arquivo onde se implementa a lista

#define CHECKMARK               'X'            // Caracter utilizado para marcar tarefa como cumprida
#define UNCHECKMARK             ' '            // Caracter utilizado para marcar tarefa como não cumprida
#define PARAM_ALL               "all"          // Parametro passado com comandos para indicar seleção de todos os itens da lista
#define PARAM_LIST_ALL          "all"          // Parametro passado com comando 'list' para mostrar lista completa
#define PARAM_LIST_CHECK        "check"        // Parametro passado com comando 'list' para mostrar somente tarefas marcadas
#define PARAM_LIST_UNCHECK      "uncheck"      // Parametro passado com comando 'list' para mostrar somente tarefas não marcadas
#define PARAM_LIST_CUR          "cur"          //  Parametro passado com comando 'list' para mostrar lista atual

// Enumeração utilizada para codificar qual lista foi apresentada ao usuário por último
// lista_atual mantem registrada qual foi a ultima lista apresentada na tela
// A atualização dessa variável deve ser implementada dentro de funções que apresentem uma lista no terminal
typedef enum {l_all, l_check, l_uncheck} list_state;
extern list_state lista_atual;

//----------------------------------------------------------------------------------------------------------------

// X Macro. Guarda os comandos reconhecidos pelo programa, utilizada para automatizar declaração das funções, codificação
//  dos comandos e facilitar adição de um novo comando
// A definição de X(comando,COMANDO) indica aplicação desta macro.
// [comando] escrito em minusculo para funções, maiusculo para enum
// Adicionar um comando nessa lista requer também a definição de sua função, a qual é declarada automaticamente
#define COMANDO_TABLE\
    X(list, LIST)\
    X(add, ADD)\
    X(del, DEL)\
    X(check, CHECK)\
    X(uncheck, UNCHECK)

// Declaração das funções dos respectivos comandos
#define X(comando, COMANDO) void comando(char * param);
COMANDO_TABLE
#undef X

// Definição do tipo en_comando, codificação dos comandos
#define X(comando, COMANDO) COMANDO ,
typedef enum {
    COMANDO_TABLE
    NRO_COMANDOS, EN_ERR=-1
} en_comando;
# undef X

//----------------------------------------------------------------------------------------------------------------

// Retorna o valor codificado do comando passado como string
en_comando str_to_en_comando(const char * str);

// Copia a primeira palavra(o comando) da entrada para o array 'comando'
// Retorna um ponteiro apontando para a primeira letra da segunda palavra (o(s) parametro(s))
// Caso nao tenha parametro, retorna NULL
char * get_comando(char * comando, const char * entrada);

//----------------------------------------------------------------------------------------------------------------

// Funções utilizadas pela função correspondente ao comando 'list' 
// Opções de lista completa, só marcadas ou só não marcadas
// Tarefas são enumeradas a fim de auxiliar seleção de tarefa para operaçãos como 'check' e 'del'
void ler_lista_all();
void ler_lista_check();
void ler_lista_uncheck();

//----------------------------------------------------------------------------------------------------------------

// Retorna a posição do início da linha requerida pelo usuário mediante o parâmetro 'linha'
// A linha requerida depende da lista sendo apresentada
// Caso ocorra uma falha (Ex: o número passado é 8 mas a lista só tem 6 linhas), retorna -1
fpos_t get_tarefa (int linha, list_state lista_atual);


//----------------------------------------------------------------------------------------------------------------

// Função utilizada por comandos como check e uncheck para alterar o estado de uma tarefa na lista
// Simbolo é inserido entre as chaves '[]' à esquerda da tarefa
int marcar_tarefa (int linha, char simbolo);

#endif //todolist_HEADER