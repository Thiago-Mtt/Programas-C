/*
O programa implementa uma calculadora capaz de resolver equações com operações de soma, subtração,
multiplicação de divisão, com suporte ao uso de parênteses
*/

/*
Algoritmo do programa
    Apresentação do programa
    Loop
        Recebimento e sanitização de entrada
            Remoção do caracter new line '\n' no fim da entrada se houver
            Simplificação de múltiplos sinais de soma/subtração
            Eliminação de Espaços
        Erro em caso de 
            Caractere inválido
            Parênteses não fechado
            Operação inválida (Ex: +*-2)
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

const char white_list[] = "0123456789+-/* ().";
const char white_list_numeros[] = "0123456789";


int main()
{
    //Acentos e 'ç' não reconhecidos
    printf("Calculadora Basica {+, -, *, /, ()}");

    while (1){
        printf("\nInserir equacao: ");

        fgets(entrada, MAX_DIG_ENTR, stdin);
        int len = strlen(entrada);

        //Simplificação (sanitização) da entrada
        //1.Remoção de caracter newline '\n'
        if(entrada[len-1] == '\n'){
        entrada[len-1] = '\0';
        len -= 1;
        }

        //2.Simplificação de múltiplos sinais de soma/subtração consecutivos
        for (int i = 0; i < len; i++){
            if (entrada[i] == entrada[i+1] && (entrada[i]=='+' || entrada[i]=='-')){
                entrada[i] = ' ';
                entrada[i+1] = '+';
            }
            if ((entrada[i] == '+' && entrada[i+1]=='-')|| (entrada[i] == '-' && entrada[i+1]=='+')){
                entrada [i] = ' ';
                entrada[i+1] = '-';
            }
        }


        //3.Remoção de espaço ' '
        char *p_ponto_de_anexo = entrada;
        char *p_anexo = entrada;
        p_ponto_de_anexo = (strchr(entrada, ' '));
        if (p_ponto_de_anexo){
            int tamanho_principal_inicial = len - strlen(p_ponto_de_anexo);
            int tamanho_anexo = 0;
            int anexo = 0;
            for (int i = tamanho_principal_inicial; i <= len; i++){
                if(anexo == 0 && entrada[i] != ' '){
                    anexo = 1;
                    p_anexo = (entrada) + i;
                    tamanho_anexo++;
                }
                else if (anexo == 1 && (entrada[i] != ' ' && i != len)) {
                    tamanho_anexo++;
                }
                else if (anexo == 1 && (entrada[i] == ' ' || i == len)){
                    memcpy(p_ponto_de_anexo, p_anexo, tamanho_anexo);
                    p_ponto_de_anexo += tamanho_anexo;
                    anexo = 0;
                    tamanho_anexo = 0;
                }
            }
            memset(p_ponto_de_anexo, '\0', strlen(p_ponto_de_anexo));
            len = strlen(entrada);
        }

        
        

        //Verificação de entrada inválida
        //1.Caractere inválido:
        if (strspn(entrada, white_list) != len){
            printf("Erro: Caractere inválido na entrada.\n"
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
            printf("Erro: Parênteses não fechado na entrada");
            continue;
        }

        //3.Operação inválida
        //3.1.Múltiplos sinais de multiplicação/divisão consecutivos
        //3.2.Sinais de soma/subtração não seguidos de um número
        //3.3.Ponto não entre números
        //3.4.Parênteses vazio
        err = 0;
        for (int i=0; i < len; i++){
            if((entrada[i] == '*' || entrada[i] == '/') && (entrada[i+1] == '*' || entrada[i+1] == '/')){
                printf("Erro: Operação inválida, sinais de multiplicacao/divisao consecutivos\n");
                err = 1;
                break;
            }
            //Aponta um erro caso tenham múltiplos sinais de soma/subtração consecutivos
            //Entrada deve ser simplificado anteriormente a esta verificação
            if((entrada[i] == '+' || entrada[i] == '-') && (!strchr(white_list_numeros, entrada[i+1]) || i == (len-1))){
                printf("Erro: Operação inválida, sinal de soma/subtração não seguido de um número\n");
                err = 1;
                break;
            }

            if(entrada[i] == '.') printf("Verdadeiro\n");
            if(entrada[i] == '.' && (!strchr(white_list_numeros, entrada[i-1]) || !strchr(white_list_numeros, entrada[i+1]))){
                printf("Erro: Operação inválida, o caractere '.' deve ser antecedido e seguido por um número\n");
                err = 1;
                break; 
            }

            if(entrada[i] == '(' && entrada[i] == ')'){
                printf("Erro: Operação inválida, não deve haver parênteses vazio na entrada\n");
                err = 1;
                break;
            }

        }

        if (err) continue;

        
        
    }


    return (0);
}