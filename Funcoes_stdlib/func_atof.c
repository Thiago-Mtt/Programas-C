/*
Implementação da função atof, da biblioteca stdlib.h
Recebe um ponteiro pra uma string, com um valor fracionado em ponto flutuante (double)
Tolera espaços antes do número, suporta sinais(+-), aceita ponto ou virgula
    como separador entre inteiro e fração
*/

#include <stdio.h>

//Binary exponentiation ou Exponentiation by Squaring
double potencia(double base, int expoente){
    if (expoente < 0) return potencia(1/base, -expoente);
    else if (expoente == 0) return 1;
    else if (expoente == 1) return base;
    else if (expoente % 2 == 1) return base*potencia(base*base, (expoente-1)/2);
    else if (expoente % 2 == 0) return potencia(base*base, expoente/2);
}

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
                digito_fracao *= potencia(10, -fracao);
                numero_float += digito_fracao;
                fracao++;
            }
        }
        string_float++;
    }

    //Caso 'e' ou 'E' esteja no fim do número, indicando notação científica.
    if(string_float[0] == 'e' || string_float[0] == 'E'){
        string_float++;

        //Coleta do sinal do expoente
        int exp_sinal = 1;
        if(string_float[0] == '+') string_float++; 
        else if(string_float[0] == '-'){
            exp_sinal = -1;
            string_float++;
        }

        int expoente = 0;
        while(string_float[0] >= 48 && string_float[0] <= 57){
            expoente *= 10;
            expoente += string_float[0] - 48;
            string_float++;
        }

        expoente *= exp_sinal;
        numero_float *= potencia(10, expoente);
    }

    //Aplicar sinal
    numero_float *= sinal;
    return numero_float; 
    
}


int main (){
    printf("numero float = %f", func_atof("  12.3241"));
    return(0);
}