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
            Eliminação de Espaços
            Simplificação de múltiplos sinais de soma/subtração
        Erro em caso de 
            Caractere inválido
            Parênteses não fechado
            Operação inválida (Ex: +*-2)
        Resolver equação do começo ao fim da entrada
            Aplicar recursividade em caso de parênteses
        Devolver resposta
    */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIG_ENTR 32

char entrada[MAX_DIG_ENTR+1];

const char white_list[] = "0123456789+-/* ().";
const char white_list_somasub_direita[] = "0123456789(";
const char white_list_numeros[] = "0123456789";
const char white_list_multdiv_esquerda[] = "0123456789)";
const char white_list_multdiv_direita[] = "0123456789+-(";

double resolverEquacao(char *p_equacao);
double f_strtod(char *p_equacao,char **p_p_equacao);
double processarParenteses(char *p_equacao, char **p_p_equacao);


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

        //2.Remoção de espaço ' '
        //Detecta se há espaço na entrada, caso sim:
        //  Posiciona um ponteiro (p_ponto_de_anexo) no primeiro espaço detectado
        //  Começa a iterar a entrada a partir do primeiro espaço
        //  Ao detectar algo diferente de um espaço, posiciona outro ponteiro (p_anexo) no inicio do segmento
        //e adiciona +1 ao tamanho do segmento a cada caractere diferente de espaço
        //  Ao detectar um outro espaço, ou o fim da entrada, anexa o segmento definido por p_anexo e o tamanho
        //do anexo à posição do primeiro espaço (apontado por p_ponto_de_anexo). Redefinir p_ponto_de_anexo
        //para o novo espaço encontrado
        //  Repetir até alcançar o fim da entrada
        //Substituição dos caracteres sobrados por null '\0'
        char *p_ponto_de_anexo;
        p_ponto_de_anexo = (strchr(entrada, ' '));
        if (p_ponto_de_anexo){
            char *p_anexo = entrada;
            int pos_primeiro_espaco = len - strlen(p_ponto_de_anexo); //Tamanho do segmento até o primeiro espaço
            int tamanho_anexo = 0;
            int anexo = 0; 
            for (int i = pos_primeiro_espaco; i <= len; i++){
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

        //3.Simplificação de múltiplos sinais de soma/subtração consecutivos
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
        //3.1.Sinais de multiplicação/divisão em posições inválidas
        //3.2.Sinais de soma/subtração em posições inválidas
        //3.3.Ponto não entre números
        //3.4.Parênteses vazio
        err = 0;
        for (int i=0; i < len; i++){
            //Aponta erro caso os sinais * ou / estejam em posições inválidas (análise de caracteres à esquerda
            //e à direita do sinal) ou no inicio/fim da entrada
            if((entrada[i] == '*' || entrada[i] == '/') && (!strchr(white_list_multdiv_esquerda,entrada[i-1]) || 
            !strchr(white_list_multdiv_direita,entrada[i+1]) || i == 0 || i == len-1)){
                printf("Erro: Operação inválida, operação de multiplicação/divisão inválida\n");
                err = 1;
                break;
            }

            //Aponta um erro caso os sinais + ou - não sejam seguidos por um número ou termo em parênteses
            //Entrada deve ser simplificado anteriormente a esta verificação
            if((entrada[i] == '+' || entrada[i] == '-') && (!strchr(white_list_somasub_direita, entrada[i+1]) || i == (len-1))){
                printf("Erro: Operação inválida, sinal de soma/subtração não seguido de um número\n");
                err = 1;
                break;
            }

            if(entrada[i] == '.' && (!strchr(white_list_numeros, entrada[i-1]) || !strchr(white_list_numeros, entrada[i+1]))){
                printf("Erro: Operação inválida, o caractere '.' deve ser antecedido e seguido por um número\n");
                err = 1;
                break; 
            }

            if(entrada[i] == '(' && entrada[i+1] == ')'){
                printf("Erro: Operação inválida, não deve haver parênteses vazio na entrada\n");
                err = 1;
                break;
            }

        }

        if (err) continue;

        printf("Resultado = %f\n", resolverEquacao(entrada));

    }


    return (0);
}


/*
Função é resolvida coletando os números da entrada num vetor (num_vect)
Em caso de soma/subtração, o número a ser somado/subtraido é adicionado ao vetor
Em caso de multiplicação/divisão, a operação é realizada entre o último termo adicionado ao vetor
e o próximo na entrada
Em caso de parênteses, a função é chamada novamente para resolver a equação dentro do parênteses (recursivo)
*/

//Tamanho inicial do vetor usado para guardar os números da entrada.
//Multiplicandos/Dividendos e Multiplicadores/Divisores são processados antes de entrarem no vetor
int num_vect_tam_ini = 5;

//Tamanho a ser incrementado ao vetor que guarda os números da entrada caso o espaço não seja o bastante
int num_vect_tam_incr = 2; 

double resolverEquacao(char *p_equacao){
   double *num_vect, mult_div_or;
   char *p_pntr, sinal;

   num_vect = (double *) malloc(num_vect_tam_ini*sizeof(double));

   //Iterador do vetor num_vect no while loop
   int iterator = -1;
   //Inteiro que guarda o espaço (em double) em num_vect
   int num_vect_tam_atual = num_vect_tam_ini;

   while(strlen(p_equacao) != 0){ 
      printf("p_equacao =%s\n", p_equacao);
      if(iterator == num_vect_tam_atual){
         num_vect = (double*) realloc(num_vect, sizeof(double)* (num_vect_tam_atual+num_vect_tam_incr));
         num_vect_tam_atual += num_vect_tam_incr;
      }

      //Verifica se ponteiro aponta para um valor a ser somado/subtraido. Se for um número, é o inicio da entrada.
      if(p_equacao[0] == '+' || p_equacao[0] == '-' || iterator == -1){
         iterator++;
         num_vect[iterator] = f_strtod(p_equacao, &p_equacao);
      } 

      //Verifica se o ponteiro aponta para um sinal de multiplicação/divisão. Neste caso, realiza a operação entre
      //o valor à direita do sinal com o último valor guardado no vetor num_vect, ou seja, o valor à esquerda do sinal.
      else if(p_equacao[0] == '*' || p_equacao[0] == '/'){
         sinal = p_equacao[0];
         p_equacao++;
         mult_div_or = f_strtod(p_equacao, &p_equacao);
         if(sinal == '*') num_vect[iterator] = num_vect[iterator]*mult_div_or;
         else if(sinal == '/') num_vect[iterator] = num_vect[iterator]/mult_div_or;
      }
      else{
        printf("Erro no programa\n");
        printf("p_equacao[0] não é um sinal +-*/, p_equacao = %s\n", p_equacao);
        return 0;

      } 

   }

   double res = 0;
   for (int i = 0; i <= iterator; i++){
      res += num_vect[i];
   }

   free(num_vect);

   return res;
}

//Verifica se o termo a ser somado/subtraido ou multiplicado/dividido está envolto de parênteses
//Se estiver, a equação é enviada para a função resolverEquacao
double f_strtod(char *p_equacao, char **p_p_equacao){
    if(p_equacao[0] == '(') return processarParenteses(p_equacao, p_p_equacao);
    else if(p_equacao[1] == '('){
        p_equacao++;
        *p_p_equacao += 1;
        if(p_equacao[-1] == '-') return -1*processarParenteses(p_equacao, p_p_equacao);
        else return processarParenteses(p_equacao, p_p_equacao);
    }
    else{
        double res = strtod(p_equacao, p_p_equacao);
        return res;
    }
   
   
   
}

double processarParenteses(char *p_equacao, char**p_p_equacao){
    printf("Processando parênteses\n");
    int paren = 0;
    int len;
    double res;
    for(int i = 0; i < strlen(p_equacao); i++){
        if(p_equacao[i] == ')') paren--;
        if(p_equacao[i] == '(') paren++;
        if(paren == 0) {
           len = i+1;
           break;
        }
    }
    char equacao_paren[len-2+1]; //Excluir parênteses, adicionar caractere de término de string
    p_equacao++;
    memcpy(equacao_paren, p_equacao, len-2);
    equacao_paren[len-2] = '\0';
    *p_p_equacao += len;
    return resolverEquacao(equacao_paren);
}