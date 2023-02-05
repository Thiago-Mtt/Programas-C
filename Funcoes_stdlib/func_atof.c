/*
Implementação da função atof, da biblioteca stdlib.h
Recebe um ponteiro pra uma string, com um valor fracionado em ponto flutuante (double)
Tolera espaços antes do número, suporta sinais(+-), aceita ponto ou virgula
    como separador entre inteiro e fração
*/

#include <stdio.h>

double func_atof(char *string_float){
    //Pular caracteres de espaço no início da entrada
    while(string_float[0] == ' ' || string_float[0] == '\t'){
        string_float++;
    }

    //Retorna zero caso primeiro caractere diferente de um espaço não seja um número nem um sinal + ou -
    int continuar = 0;
    const char white_list[] = "0123456789+-";
    for (int i = 0; i <= 11; i++){
        if(white_list[i] == string_float[0]) continuar = 1;
    }
    if (!continuar) return 0;

    //Define sinal a ser multiplicado no fim da função
    int sinal = 1;
    if(string_float[0] == '+') string_float++; 
    else if(string_float[0] == '-'){
        sinal = -1;
        string_float++;
    }

    //A cada número antes do '.' ou ','(fracao = 0), multiplica o resultado atual e soma o número atual ao resultado
    //A cada número depois do '.' ou ','(fracao >= 1), divide o número atual por 10 n=fracao vezes,
    //  soma o número atual ao resultado e incrementa fracao.
    int fracao = 0;
    double numero_float = 0;
    double digito_fracao = 0;
    //Equanto o caractere atual entiver entre '0' e '9' ou for igual a '.' ou ','
    while((string_float[0] >= 48 && string_float[0] <= 57) || string_float[0] == '.' || string_float[0] == ','){
        if (string_float[0] == '.' || string_float[0] == ','){
            if(!fracao) fracao = 1;
            else break;
        }
        else if (string_float[0] >= 48 && string_float[0] <= 57){
            if(!fracao){
                numero_float *= 10;
                numero_float += string_float[0] - 48;
            }
            else{
                digito_fracao = string_float[0] - 48;
                for(int i = 0; i < fracao; i++){
                    digito_fracao /= 10;
                }
                numero_float += digito_fracao;
                fracao++;
            }
        }
        string_float++;
    }

    //Aplicar sinal
    numero_float *= sinal;
    return numero_float; 
    
}

int main (){
    printf("numero float = %f", func_atof("  -12.312E12"));
    
    return(0);
}