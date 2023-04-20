/*
Programa tem o intuito de criar uma interface no prompt de comando para gerenciar uma lista de tarefas
Requisitos
    - Ver tarefas
    - Adicionar tarefa
    - Remover tarefa
    - Remover todas as tarefas
    - Remover tarefas cumpridas
    - Marcar tarefa como cumprida
    - Desmarcar tarefa como cumprida
    - Ver somente tarefas cumpridas
    - Ver somente tarefas não cumpridas
*/

/*
Comandos:
list
add [tarefa]
del [nº tarefa]
del check
check [nº tarefa]
uncheck [nº tarefa]
list check
list uncheck
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"


// Vetor de ponteiros para funções de comandos
#define X(comando, COMANDO) comando ,
// 'COMANDOS_TABLE' termina com um ','
void (*comVect[])(char * param) = {COMANDO_TABLE};
#undef X


int main() {
    
    system(CLEAR);

    // Cria a lista caso nao exista, não verifica erro em caso de falha
    FILE *fp_lista;
    if(!(fp_lista = fopen( LISTA, "r"))){
        fp_lista = fopen( LISTA, "w");
        printf("Novo arquivo de lista criado\n");
    }
    fclose(fp_lista);

    //Ler opção de lista atual (inicialmente lista completa)
    list(PARAM_LIST_ALL);

    // Loop de comando
    char entrada[MAX_TAMANHO_COMANDO];
    char comando[MAX_TAMANHO_COMANDO];
    char * param;
    while(1){

        // Limpar arrays de entrada e comando de lixo e entradas antigas
        memset(entrada, '\0', MAX_TAMANHO_COMANDO);
        memset(comando, '\0', MAX_TAMANHO_COMANDO);

        printf("\n>");
        fgets(entrada, MAX_TAMANHO_COMANDO, stdin);
        // Remover caracter de nova linhha no final da entrada
        if(entrada[strlen(entrada)-1] == '\n') entrada[strlen(entrada)-1] = '\0';

        // param recebe um ponteiro apontando para o primeiro caractere da segunda palavra da entrada (inicio
        // do parâmetro)
        param = get_comando(comando, entrada);

        en_comando comando_index = str_to_en_comando(comando);
        if (comando_index == EN_ERR){
            printf("Comando não reconhecido\n");
            continue;
        }
        
        system(CLEAR);
        (*comVect[comando_index])(param);
        
        if (comando_index != LIST)
        {        
            list(PARAM_LIST_CUR);
        }

    }



    return 0;
}


// Copia a primeira palavra(o comando) na entrada para o array 'comando'
// Retorna um ponteiro apontando para a primeira letra da segunda palavra (o(s) parametro(s))
// Caso nao tenha uma segunda palavra na entrada (o parametro), retorna NULL
char * get_comando(char * comando, const char * entrada){
    
    // Pula espaço em branco no inicio da entrada
    while(*entrada == ' '){
        entrada++;
    }

    int len_comando = strcspn(entrada, " ");
    memcpy(comando, entrada, len_comando);

    // Aponta para o primeiro espaço após a primeira palavra ou para o caracter de fim de string
    entrada += len_comando;

    // Pula espaço em branco após primeira palavra, agora aponta para início da segunda palavra, se houver
    while(*entrada == ' '){
        entrada++;
    }

    if(entrada) return (char*)entrada;
    else return NULL;

}

