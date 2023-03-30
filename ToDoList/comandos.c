#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"

list_state lista_atual = l_all;         // Estado inicial da lista como completa

//----------------------------------------------------------------------------------------------------------------

void list(char * param)
{
    // Verifica o parametro passado junto do comando de listar as tarefas
    // Um parâmetro nulo (== '\0'), quando só o comando 'list' é passado, resulta na listagem completa
    printf("Comando list alcançado\n");

    if          (*param == '\0' || strcmp(param, PARAM_LIST_ALL) == 0 )     ler_lista_all();
    else if     (strcmp(param, PARAM_LIST_CHECK) == 0 )                     ler_lista_check();
    else if     (strcmp(param, PARAM_LIST_UNCHECK) == 0)                    ler_lista_uncheck();
    
    else
    {
        printf("Erro: Opção de lista não definida\n");
    }
}


void ler_lista_all()
{

    lista_atual = l_all;   
    
    FILE *fp_lista = fopen(LISTA, "r");
    if(feof(fp_lista)){
        printf("\nNenhuma tarefa na lista\n");
        fclose(fp_lista);
        return;
    }

    char tarefa[MAX_TAMANHO_TAREFA];

    printf("Lista:\n");
    for(int i = 1; ; i++)
    {
        if(!fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista)) break;
        printf("%d. %s", i,tarefa);
    }
    printf("\n");
    fclose(fp_lista);

}

void ler_lista_check()
{
    lista_atual = l_check;

    if (get_tarefa(1, l_check) == -1)
    {
        printf("\nNenhuma tarefa marcada na lista\n");
        return;
    }

    FILE *fp_lista = fopen(LISTA, "r");
    char tarefa[MAX_TAMANHO_TAREFA];
    fpos_t linha_tarefa_marcada;

    printf("Lista:\n");
    for(int i = 1; ; i++)
    {
        linha_tarefa_marcada = get_tarefa(i, l_check);
        if (linha_tarefa_marcada == -1)
        {
            break;
        }

        fsetpos(fp_lista, &linha_tarefa_marcada);

        if(!fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista))
        {
            break;
        }

        printf("%d. %s", i,tarefa);
    }

    printf("\n");
    fclose(fp_lista);
}

void ler_lista_uncheck()
{

}

//----------------------------------------------------------------------------------------------------------------

#define X(comando, COMANDO) if(strcmp(str, #comando) == 0) return COMANDO ;
en_comando str_to_en_comando(const char * str){
    COMANDO_TABLE
    return EN_ERR;
}
#undef X

//----------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------

void del(char * param)
{
    printf("Comando del alcançado\n");
    return;
}

//----------------------------------------------------------------------------------------------------------------

void check(char * param)
{
    // Marca tarefa como cumprida, adicionando um 'X' entre as chaves '[ ]' à esquerda da tarefa selecionada
    // A tarefa é selecionada a partir da numeração da última lista apresentada (completa, só marcadas, só não marcadas, etc)
    // 'param' pode ser o número da linha a ser marcada ou 'all' para marcar todas as linhas da última lista apresentada
    
    printf("Comando check alcançado\n");

    FILE * fp_lista = fopen(LISTA, "r+");
    fpos_t linha_pos = get_tarefa(atoi(param), lista_atual);

    if (linha_pos == -1)
    {
        printf("Erro: Tarefa não encontrada\n");
        return;
    }

    fsetpos(fp_lista, &linha_pos);
    fseek(fp_lista, 1, SEEK_CUR);
    putc(CHECKMARK, fp_lista);
    fclose(fp_lista);



    return;
}

//----------------------------------------------------------------------------------------------------------------

void uncheck(char * param)
{
    printf("Comando uncheck alcançado\n");
    return;
}

//----------------------------------------------------------------------------------------------------------------

fpos_t get_tarefa(int linha, list_state lista_atual)
{

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
                    nova_linha = 0;
                    fseek(fp_lista, 1, SEEK_CUR);
                    if (fgetc(fp_lista) == CHECKMARK)
                    {
                        count_linha++;
                    } 
                    if (count_linha == linha)
                    {
                        fseek(fp_lista, -2, SEEK_CUR);
                        break;
                    }   
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
                    if (count_linha == linha)
                    {
                        fseek(fp_lista, -2, SEEK_CUR);
                        break;
                    }   
                    nova_linha = 0;
                }
                read_char = fgetc(fp_lista);
                if (read_char == '\n') nova_linha = 1; 
            }
            break;
    }

    if (feof(fp_lista) || ferror(fp_lista))
    {
        fclose(fp_lista);
        return -1;
    }

    fgetpos(fp_lista, &pos_linha);
    return pos_linha;
}