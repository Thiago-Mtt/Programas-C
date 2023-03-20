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


// lista_atual mantem registrada qual foi a ultima lista apresentada na tela
// A atualização dessa variável deve ser implementada dentro de funções que apresentem uma lista no terminal
list_state lista_atual;




// Vetor de ponteiros para funções de comandos
#define X(comando, COMANDO) comando ,
// 'COMANDOS_TABLE' termina com um ','
void (*comVect[])(char * param) = {COMANDO_TABLE};
#undef X


int main() {
    
    //system(CLEAR);

    // Cria a lista caso nao exista, não verifica erro em caso de falha
    FILE *fp_lista;
    if(!(fp_lista = fopen( LISTA, "r"))){
        fp_lista = fopen( LISTA, "w");
        printf("Novo arquivo de lista criado\n");
    }
    fclose(fp_lista);

    // Ler lista completa
    ler_lista_all();

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
        (*comVect[comando_index])(param);
        

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
    
    switch (lista_atual)
    {
        case l_all : 
            return get_tarefa_l_all(linha);
            break;
        case l_check :
            return get_tarefa_l_check(linha);
            break;
        case l_uncheck :
            return get_tarefa_l_uncheck(linha);
            break;
    }

}

fpos_t get_tarefa_l_all(int linha)
{

    printf("get_tarefa_l_all alcançado\n");

    FILE * fp_lista = fopen(LISTA, "r");
    int count_linha = 1;
    char read_char;
    fpos_t pos_linha;

    while(count_linha != linha || feof(fp_lista))
    {
        read_char = fgetc(fp_lista);
        printf("Caracter lido = %c\n", read_char);
        if (read_char == '\n' && !feof(fp_lista)) count_linha++; 
    }

    if (feof(fp_lista)) return -1;

    fgetpos(fp_lista, &pos_linha);
    return pos_linha;
}

fpos_t get_tarefa_l_check(int linha)
{
    FILE * fp_lista = fopen(LISTA, "r");
    int count_linha = 0;
    char read_char;

    while(count_linha != linha || feof(fp_lista))
    {
        read_char = fgetc(fp_lista);
        if (read_char == '\n' && !feof(fp_lista))
        {
            fseek(fp_lista, 1, SEEK_CUR);
            if(fgetc(fp_lista) == CHECKMARK) count_linha++;
        }
    }

    if (feof(fp_lista)) return -1;

    return count_linha;
}

fpos_t get_tarefa_l_uncheck(int linha)
{
    FILE * fp_lista = fopen(LISTA, "r");
    int count_linha = 0;
    char read_char;

    while(count_linha != linha || feof(fp_lista))
    {
        read_char = fgetc(fp_lista);
        if (read_char == '\n' && !feof(fp_lista))
        {
            fseek(fp_lista, 1, SEEK_CUR);
            if(fgetc(fp_lista) == CHECKMARK) count_linha++;
        }
    }

    if (feof(fp_lista)) return -1;

    return count_linha;

}