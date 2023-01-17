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


int main()
{
    fgets(entrada, MAX_DIG_ENTR, stdin);
    printf("%s", entrada);

    if(entrada[strlen(entrada)-1] == '\n');


    return (0);
}