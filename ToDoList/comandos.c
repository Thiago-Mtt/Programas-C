#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"

#ifdef WINDOWS
#include <io.h>
#endif

list_state lista_atual = l_all;         // Estado inicial da lista como completa

//----------------------------------------------------------------------------------------------------------------

void list(char * param)
{
    // Verifica o parametro passado junto do comando de listar as tarefas
    // Um parâmetro nulo (== '\0'), quando só o comando 'list' é passado, resulta na listagem completa

    if          (*param == '\0' || strcmp(param, PARAM_LIST_ALL) == 0 )     ler_lista_all();
    else if     (strcmp(param, PARAM_LIST_CHECK) == 0 )                     ler_lista_check();
    else if     (strcmp(param, PARAM_LIST_UNCHECK) == 0)                    ler_lista_uncheck();
    
    else if     (strcmp(param, PARAM_LIST_CUR) == 0)
    {   
        switch (lista_atual)
        {
            case l_all:
                ler_lista_all();
                break;
            case l_check:
                ler_lista_check();
                break;
            case l_uncheck:
                ler_lista_uncheck();
                break;
            default:
                printf("Erro em list(char * param): param == PARAM_LIST_CUR\n");
                break;
        }
    }
    
    else
    {
        printf("Erro: Opção de lista não definida\n");
    }
}


void ler_lista_all()
{   
    
    FILE *fp_lista = fopen(LISTA, "r");
    if(feof(fp_lista)){
        printf("\nNenhuma tarefa na lista\n");
        fclose(fp_lista);
        return;
    }

    lista_atual = l_all;

    char tarefa[MAX_TAMANHO_TAREFA];

    printf("Lista:\n");
    for(int i = 1; ; i++)
    {
        if(!fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista))
        {
            break;
        }
        printf("%d. %s", i,tarefa);
    }
    printf("\n");
    fclose(fp_lista);

}

void ler_lista_check()
{

    if (get_tarefa(1, l_check) == -1)
    {
        printf("\nNenhuma tarefa marcada na lista\n");
        return;
    }

    lista_atual = l_check;

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

    if (get_tarefa(1, l_uncheck) == -1)
    {
        printf("\nNenhuma tarefa nao marcada na lista\n");
        return;
    }

    lista_atual = l_uncheck;

    FILE *fp_lista = fopen(LISTA, "r");
    char tarefa[MAX_TAMANHO_TAREFA];
    fpos_t linha_tarefa_nao_marcada;

    printf("Lista:\n");
    for(int i = 1; ; i++)
    {
        linha_tarefa_nao_marcada = get_tarefa(i, l_uncheck);
        if (linha_tarefa_nao_marcada == -1)
        {
            break;
        }

        fsetpos(fp_lista, &linha_tarefa_nao_marcada);

        if(!fgets(tarefa, MAX_TAMANHO_TAREFA, fp_lista))
        {
            break;
        }

        printf("%d. %s", i,tarefa);
        }

    printf("\n");
    fclose(fp_lista);

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

    if (!*param)
    {
        printf("Erro: tarefa não inserida para adicição à lista\n");
        return;
    }

    FILE *fp_lista = fopen(LISTA, "a");
    fputs("[ ] ",fp_lista);
    fputs(param, fp_lista);
    fputs("\n",fp_lista);
    fclose(fp_lista);

    return;
}

//----------------------------------------------------------------------------------------------------------------

void del(char * param)
{
    // Sobreescreve a linha a ser apagada com as linhas seguintes
    // Espaço restante após sobreinscrição é truncado
    // Somente compatível com Windows no momento

    if (strcmp(param, PARAM_ALL) == 0)
    {
        FILE *fp_lista = fopen(LISTA, "w");
        fclose(fp_lista);
        return;
    }

    if (atoi(param) == 0)
    {
        printf("Erro: Parâmetro inexistente ou inválido\n");
        return;
    }
    
    FILE *fp_lista = fopen(LISTA, "r+");

    fpos_t read_pos, write_pos;
    write_pos = get_tarefa(atoi(param), lista_atual);
    if(write_pos == -1)
    {
        printf("Linha selecionada não existe\n");
        fclose(fp_lista);
        return;
    }

    fsetpos(fp_lista, &write_pos);

    char ch;
    do
    {   
        ch = fgetc(fp_lista);
        
    } while (ch != '\n' && ch != EOF);

    if ( ferror(fp_lista) != 0)
    {
        printf("Erro ao ler linha selecionada\n");
        fclose(fp_lista);
        return;
    }

    fgetpos(fp_lista, &read_pos);
    while((ch = fgetc(fp_lista)) != EOF)
    {
       
        fgetpos(fp_lista, &read_pos);

        fsetpos(fp_lista, &write_pos);
        fputc(ch, fp_lista);
        fgetpos(fp_lista, &write_pos);

        fsetpos(fp_lista, &read_pos);

    }

    #ifdef WINDOWS
    if (_chsize(_fileno(fp_lista), (long) (write_pos))) printf("Erro") ;
    #endif

    fclose(fp_lista);

    return;
}

//----------------------------------------------------------------------------------------------------------------

void check(char * param)
{
    // Marca tarefa como cumprida, adicionando um 'X' entre as chaves '[ ]' à esquerda da tarefa selecionada
    // A tarefa é selecionada a partir da numeração da última lista apresentada (completa, só marcadas, só não marcadas, etc)
    // 'param' pode ser o número da linha a ser marcada ou 'all' para marcar todas as linhas da última lista apresentada
    

    if (strcmp(param, PARAM_ALL) == 0)
    {
        int nro_tarefa = 1;
        while (marcar_tarefa(nro_tarefa,CHECKMARK) != 1)
        {
            nro_tarefa++;
        }

        return;
    }

    if (atoi(param) != 0)
    {
        if (marcar_tarefa(atoi(param), CHECKMARK) == -1)
        {
            printf("Erro: Tarefa não encontrada\n");
        }
        return;
    }


    printf ("Erro: Falha na interpretação do parâmetro passado ao comando\n");
    return;
}



void uncheck(char * param)
{

    if (strcmp(param, PARAM_ALL) == 0)
    {
        int nro_tarefa = 1;
        while (marcar_tarefa(nro_tarefa,UNCHECKMARK) != 1)
        {
            nro_tarefa++;
        }

        return;
    }

    if (atoi(param) != 0)
    {
        if (marcar_tarefa(atoi(param), UNCHECKMARK) == -1)
        {
            printf("Erro: Tarefa não encontrada\n");
        }
        return;
    }


    printf ("Erro: Falha na interpretação do parâmetro passado ao comando\n");
    return;

}

int marcar_tarefa(int linha, char simbolo)
{
    FILE * fp_lista = fopen(LISTA, "r+");
    fpos_t linha_pos;

    linha_pos = get_tarefa(linha, lista_atual);

    if (linha_pos == -1)
    {
        return 1;
    }

    fsetpos(fp_lista, &linha_pos);
    fseek(fp_lista, 1, SEEK_CUR);
    putc(simbolo, fp_lista);

    fclose(fp_lista);

    return 0;

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
                    if ((read_char = fgetc(fp_lista)) == EOF) break;    // Verificar se é \n da última linha do arquivo
                    else fseek(fp_lista, -1, SEEK_CUR);
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