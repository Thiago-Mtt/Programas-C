/*
Calculadora capaz de realizar operações de +,-,*,/
Supõe-se que o input já esteja sanitizado (não há espaços, letras ou simbolos)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    char calculo[20];
    printf("Insira calculo: \n");
    fgets( calculo, 100, stdin);

    //Remove caracter de newLine do fim da entrada, substituindo pelo caracter de termino de string
    calculo[strlen(calculo)-1] = '\0';

    //Copia da entrada para referencia(imutavel)
    char entrada[20];
    strcpy(entrada, calculo);
    printf("Entrada: %s \n", entrada);


    //Distribuir segmentos de soma e subtração nos vetores operador e operando
    //Vetor operando pode guardar tanto numeros singulares quanto produtos e divisões 
    char *iterator = calculo;
    char operador[20];
    char operando[20][20];

    //Limpar espaço usado por operandos
    //for (int i = 0; i < 20; i++){
    //    memset(operando[i], '\0', 20);
    //}
    memset(operando, '\0', 400);

    char sum_sub[3] = "+-";
    int len = strlen(iterator);
    int pos_operador;

    int n_operador = 0;
    int n_operando = 0;

    while(len){
        pos_operador = strcspn(iterator, sum_sub);
        if (pos_operador == 0){
            operador[n_operador] = iterator[0];
            iterator++;
            n_operador++;
        }
        else{
            strncpy(operando[n_operando], iterator, pos_operador);
            iterator += pos_operador;
            n_operando++;
        }
        len = strlen(iterator);
    }

    //Realiza a soma/subtração dos operandos com base nos operadores antecedentes a sua posição na entrada
    double res = 0;
    if (n_operador+1 == n_operando){
        res += atof(operando[0]);
        for (int i=0; i < n_operador; i++){
            if (operador[i] == '+') res += atof(operando[i+1]);
            else if(operador[i== '-']) res -= atof(operando[i+1]);
        }
    }
    else if (n_operador == n_operando){
        for (int i=0; i < n_operador; i++){
            if (operador[i] == '+') res += atof(operando[i]);
            else if(operador[i== '-']) res -= atof(operando[i]);
        }
    }

    printf("resultado = %f\n", res);

}


//Pega uma parcela da soma/subtração, que pode conter um número singular ou um produto/divisão,
//e retorna o número ou produto/quociente
//double parcela(char operando[]){
    
//}