/*
Programa tem o intuito de criar uma interface no prompt de comando para gerenciar uma lista de tarefas
Requisitos
    - Ver tarefas
    - Adicionar tarefa
    - Remover tarefa
    - Remover todas as tarefas
    - Marcar tarefa como cumprida
    - Desmarcar tarefa como cumprida
    - Ver somente tarefas cumpridas
    - Ver somente tarefas não cumpridas
*/

#include <stdio.h>
#include <stdlib.h>

int lerLista(FILE *fp_lista);

#define CLEAR "cls"

int main(){
    
    while(1){
        system(CLEAR);

        FILE *fp_lista;
        if(!(fp_lista = fopen("lista.txt", "r"))){
            fp_lista = fopen("lista.txt", "w");
            printf("Novo arquivo de lista criado\n");
            fclose(fp_lista);
            fp_lista = fopen("lista.txt", "r");
        }

        if(!lerLista(fp_lista)){
            printf("\n Erro ao tenta ler lista");
        }




        //printf("Todo List :");
        break;

    }

    return 0;
}


int lerLista(FILE *fp_lista){
    if(!feof(fp_lista)){
        printf("\nNenhuma tarefa na lista\n");
        return 1;
    }

    return 0;
}