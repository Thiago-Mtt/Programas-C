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


//lista_atual mantem registrada qual foi a ultima lista apresentada na tela, a fim de selecionar um item especifico
//dessa lista
enum list_state{all, check, uncheck} lista_atual;


//Vetor de ponteiros para funções de comandos
#define X(comando) func_##comando ,
//'COMANDOS' termina com um ','
void (*comVect[])(char * param) = {COMANDOS};
#undef X

int main() {
    
    //system(CLEAR);

    //Cria a lista caso nao exista, não verifica erro em caso de falha
    FILE *fp_lista;
    if(!(fp_lista = fopen( LISTA, "r"))){
        fp_lista = fopen( LISTA, "w");
        printf("Novo arquivo de lista criado\n");
    }
    fclose(fp_lista);

    //Ler lista completa
    ler_lista_all();

    //Loop de comando
    char entrada[MAX_TAMANHO_COMANDO];
    char comando[MAX_TAMANHO_COMANDO];
    char * param;
    while(1){
        //Limpar arrays de entrada e comando de lixo e entradas antigas
        memset(entrada, '\0', MAX_TAMANHO_COMANDO);
        memset(comando, '\0', MAX_TAMANHO_COMANDO);

        printf("\n>");
        fgets(entrada, MAX_TAMANHO_COMANDO, stdin);
        //Remover caracter de nova linhha no final da entrada
        if(entrada[strlen(entrada)-1] == '\n') entrada[strlen(entrada)-1] = '\0';

        //param recebe um ponteiro apontando para o primeiro caractere da segunda palavra da entrada (inicio
        //do parâmetro)
        param = get_comando(comando, entrada);
        printf("Comando = %s\n", comando);
        printf("param = %s\n", param);

    }



    return 0;
}


//Copia a primeira palavra(o comando) na entrada para o array 'comando'
//Retorna um ponteiro apontando para a primeira letra da segunda palavra (o(s) parametro(s))
//Caso nao tenha parametro, retorna NULL
char * get_comando(char * comando, const char * entrada){
    
    //Pula espaço em branco no inicio da entrada
    while(*entrada == ' '){
        entrada++;
    }

    int len_comando = strcspn(entrada, " ");
    memcpy(comando, entrada, len_comando);

    //Aponta para o primeiro espaço após a primeira palavra ou para o caracter de fim de string
    entrada += len_comando;

    //Pula espaço em branco após primeira palavra
    while(*entrada == ' '){
        entrada++;
    }

    if(entrada) return (char*)entrada;
    else return NULL;

}

void func_list(char * param){
    if (param == NULL) ler_lista_all();
}


//Print da lista de tarefas;
//Tarefas são enumeradas a fim de auxiliar seleção de tarefa
void ler_lista_all(){
    FILE *fp_lista = fopen(LISTA, "r");
    if(feof(fp_lista)){
        printf("\nNenhuma tarefa na lista\n");
        return;
    }

    printf("Lista:\n");
    char tarefa[MAX_TAMANHO_TAREFA];
    for(int i = 1;!feof(fp_lista); i++){
        fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista);
        printf("%d. %s", i,tarefa);
    }
    
    lista_atual = all;

}

void func_add(char * param){
    return;
}

void func_del(char * param){
    return;
}

void func_check(char * param){
    return;
}

void func_uncheck(char * param){
    return;
}