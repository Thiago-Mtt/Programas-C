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

int lerLista();

#define CLEAR "cls"
#define MAX_TAMANHO_TAREFA 30
#define MAX_TAMANHO_COMANDO 40
#define LISTA "lista.txt"

enum lista{all, check, uncheck} lista_atual;

int main(){
    
    system(CLEAR);

    //Cria a lista caso nao exista
    FILE *fp_lista;
    if(!(fp_lista = fopen( LISTA, "r"))){
        fp_lista = fopen( LISTA, "w");
        printf("Novo arquivo de lista criado\n");
    }
    fclose(fp_lista);

    //Ler lista
    if(!lerLista()){
        printf("Erro ao tenta ler lista\n");
    }

    char comando[MAX_TAMANHO_COMANDO];
    while(1){
        printf("\n>");
        fgets(comando, MAX_TAMANHO_COMANDO, stdin);

    }



    return 0;
}

//Print da lista de tarefas
//Tarefas são enumeradas a fim de auxiliar seleção de tarefa
int lerLista(){
    FILE *fp_lista = fopen(LISTA, "r");
    if(feof(fp_lista)){
        printf("\nNenhuma tarefa na lista\n");
        return 1;
    }

    printf("Lista:\n");
    char tarefa[MAX_TAMANHO_TAREFA];
    for(int i = 1;!feof(fp_lista); i++){
        fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista);
        printf("%d. %s", i,tarefa);
    }
    lista_atual = all;

    return 1;
}