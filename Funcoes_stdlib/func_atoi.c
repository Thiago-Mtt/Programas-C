/*
Implementação da função atoi, da biblioteca stdlib.h
Recebe um ponteiro pra uma string, com um número inteiro em formato de texto
Tolera espaços antes do número, suporta sinais(+-)
Em caso de falha, o valor retornado é zero

Código adaptado de func_atof
*/

#include <stdio.h>

int func_atoi(char *string_int){
    while(string_int[0] == ' ' || string_int[0] == '\t'){
        string_int++;
    }

    //Retorna zero caso primeiro caractere diferente de um espaço não seja um número nem um sinal + ou -
    int continuar = 0;
    const char white_list[] = "0123456789+-";
    for (int i = 0; i <= 11; i++){
        if(white_list[i] == string_int[0]) continuar = 1;
    }
    if (!continuar) return 0;

    //Define sinal a ser multiplicado no fim da função
    int sinal = 1;
    if(string_int[0] == '+') string_int++; 
    else if(string_int[0] == '-'){
        sinal = -1;
        string_int++;
    }

    //Tradução de string para número, utilizando a tabela ASCII
    //A cada novo dígito, o resultado atual é multiplicado por 10 e o digito atual é somado ao resultado
    int resultado = 0;
    while(string_int[0] >= 48 && string_int[0] <= 57){
            resultado *= 10;
            resultado += string_int[0] - 48;
            string_int++;
            //Adicionar verificação de overflow
            if(resultado < 0) return -1;
        }

    
    //Aplicar sinal
    resultado *= sinal;
    return resultado; 
}


int main (){
    printf("numero inteiro = %d", func_atoi("  112331222"));
    return(0);
}