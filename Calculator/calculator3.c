/*
O programa implementa uma calculadora capaz de resolver equações com operações de soma, subtração,
multiplicação de divisão, com suporte ao uso de parênteses
*/

/*
Algoritmo do programa
    Apresentação do programa
    Loop
        Recebimento e sanitização de entrada
            Erro em caso de 
              Caractere inválido
              Parênteses não fechado
              Operação inválida (Ex: +*-2)
            Eliminação de Espaços
        Enquanto houver parenteses: 
            Obter equação entre parênteses mais profundo (que não possui parênteses entre parênteses)
            Resolver multiplicação e divisão
            Resolver soma e subtração
            Substituir resultado na entrada com operações de sinal apropriadas
        Resolver equação final
            Resolver multiplicação e divisão
            Resolver soma e subtração
        Devolver resposta
    */

#include <stdio.h>
#include <string.h>

#define MAX_DIG_ENTR 32

char entrada[MAX_DIG_ENTR+1];

const char white_list[] = "0123456789+-/* ()";


int main()
{
    //Acentos e 'ç' não reconhecidos
    printf("Calculadora Basica {+, -, *, /, ()}");

    while (1){
        printf("\nInserir equacao: ");

        fgets(entrada, MAX_DIG_ENTR, stdin);
        int len = strlen(entrada);

        //Remoção de caracter newline '\n'
        if(entrada[len-1] == '\n'){
        entrada[len-1] = '\0';
        len -= 1;
        }

        //Verificação de entrada inválida
        //1.Caractere inválido:
        if (strspn(entrada, white_list) != len){
            printf("Caractere inválido na entrada.\n"
            "Entrada deve consistir somente dos seguintes caracteres:\n0123456789+-/* ()\n");
            continue;
        }

        //2.Parênteses não fechado
        int paren = 0; int err = 0;
        for (int i = 0; i < len; i++){
            if (entrada[i] == '(') paren++;
            if(entrada[i] == ')') paren--;

            if (paren < 0){ // ')' sem um '(' anterior
                err = 1;
                break;
            }
        }
        if (paren != 0 || err == 1){
            printf("Parênteses não fechado na entrada");
            continue;
        }

        

       
        
    }


    return (0);
}