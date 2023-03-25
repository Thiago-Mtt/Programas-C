#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"

// Estado inicial da lista como completa
list_state lista_atual;

void list(char * param){
    printf("Comando list alcançado\n");
    if (*param == '\0') ler_lista_all();
}


// Print da lista de tarefas;
// Tarefas são enumeradas a fim de auxiliar seleção de tarefa
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
    printf("\n");
    fclose(fp_lista);
    
    lista_atual = l_all;

}

#define X(comando, COMANDO) if(strcmp(str, #comando) == 0) return COMANDO ;
en_comando str_to_en_comando(const char * str){
    COMANDO_TABLE
    return EN_ERR;
}
#undef X

void add(char * param){
    // Adiciona tarefa (char * param) ao fim da lista, em uma nova linha.
    // Tarefa inicialmente não é marcada
    printf("Comando add alcançado\n");

    FILE *fp_lista = fopen(LISTA, "a");
    fputs("[ ] ",fp_lista);
    fputs(param, fp_lista);
    fputs("\n",fp_lista);
    fclose(fp_lista);

    ler_lista_all();

    return;
}

void del(char * param){
    printf("Comando del alcançado\n");
    return;
}

void check(char * param)
{
    // Marca tarefa como cumprida, adicionando um 'X' entre as chaves '[ ]' à esquerda da tarefa selecionada
    // A tarefa é selecionada a partir da numeração da última lista apresentada (completa, só marcadas, só não marcadas, etc)
    // 'param' pode ser o número da linha a ser marcada ou 'all' para marcar todas as linhas da última lista apresentada
    
    printf("Comando check alcançado\n");

    FILE * fp_lista = fopen(LISTA, "r");
    char str[MAX_TAMANHO_TAREFA];
    fpos_t linha_pos = get_tarefa(atoi(param), lista_atual);

    if (linha_pos == -1)
    {
        printf("Erro: Tarefa não encontrada\n");
        return;
    }

    fsetpos(fp_lista, &linha_pos);
    fgets(str, MAX_TAMANHO_TAREFA, fp_lista);
    printf("Linha selecionada = %s\n", str);




    return;
}

void uncheck(char * param){
    printf("Comando uncheck alcançado\n");
    return;
}

fpos_t get_tarefa(int linha, list_state lista_atual){

    FILE * fp_lista = fopen(LISTA, "r");
    int count_linha = 0;
    int nova_linha = 1;
    char read_char = '\0';
    fpos_t pos_linha;

    switch (lista_atual)
    {
        case l_all :
            while(!feof(fp_lista))
            {
                if (nova_linha)
                {
                    count_linha++;
                    if (count_linha == linha) break;
                    nova_linha = 0;
                }
                read_char = fgetc(fp_lista);
                if (read_char == '\n') nova_linha = 1; 
            }
            break;
        case l_check :
            while(!feof(fp_lista))
            {
                if (nova_linha)
                {
                    fseek(fp_lista, 1, SEEK_CUR);
                    if (fgetc(fp_lista) == CHECKMARK) count_linha++;
                    fseek(fp_lista, -2, SEEK_CUR);
                    if (count_linha == linha) break;
                    nova_linha = 0;
                }
                read_char = fgetc(fp_lista);
                if (read_char == '\n') nova_linha = 1; 
            }
            break;
        case l_uncheck :
            while(!feof(fp_lista))
            {
                if (nova_linha)
                {
                    fseek(fp_lista, 1, SEEK_CUR);
                    if (fgetc(fp_lista) == UNCHECKMARK) count_linha++;
                    fseek(fp_lista, -2, SEEK_CUR);
                    if (count_linha == linha) break;
                    nova_linha = 0;
                }
                read_char = fgetc(fp_lista);
                if (read_char == '\n') nova_linha = 1; 
            }
            break;
    }

    if (feof(fp_lista)) return -1;

    fgetpos(fp_lista, &pos_linha);
    return pos_linha;
}