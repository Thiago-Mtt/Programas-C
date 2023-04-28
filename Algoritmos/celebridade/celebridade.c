/* Problema: Encontrar uma celebridade dentro de uma multidão, sendo que todos conhecem a celebridade,
 * mas esta não conhece ninguém
 * 
 * Formulação:  Uma lista com N elementos representando N pessoas.
 * 
 *              Cada pessoa tem registrado se conhecem a pessoa X (1) ou não (0)
 *                  Portanto, cada pessoa tem um registro de N elementos (se incluirem a si) ou de N-1 elementos
 *                      Caso se incluam, seu registro deve ser 'conhecido' (1)
 * 
 *              A celebridade será registrada como conhecida (1) por todos
 *              e terá como não conhecido (0) para todos os outros (exceto para si mesma)
 *              
 *              Problema pode ser formulado como uma matriz NxN
 * 
 *                  Cada elemento P_ij representa se a pessoa i conhece a pessoa j
 *                  Se i == j, P_ij == 1
 * 
 *                  A celebridade será conhecida por todos
 *                      A coluna correspondente possui somente 1, ou seja, P_in = 1 para todo i,
 *                      onde n corresponde ao número da celebridade
 * 
 *                  A celebridade não conhece ninguém
 *                      A linha correspondente possui somente 0, exceto onde i == j
 *                      ou seja, P_nj == 0 para todo j exceto n == j, onde n corresponde
 *                      ao número da celebridade
 *  
 *                  Sabendo que a celebridade conhece ninguém na multidão, pode-se deduzir que
 *                  só há 1 celebridade na multidão
 * 
 * Complexidade:    
 *                  Melhor Caso: 
 *                      É possível encontrar a celebridade verificando somente 1 coluna preenchida com '1'
 *                      Com o mesmo resultado, verificando uma linha com somente um  único elemento com '1'
 *                      N operações de verificar se P1 conhece P2
 *                  Pior Caso:
 *                      Pode ser necessárrio varrer toda a matriz
 *                      NxN operações de verificar se P1 conhece P2
 *
 * Algoritmo N (2N):
 *                 Verifica-se se a pessoa 2 conhece a pessoa 1
 *                      Conhece: Considera-se por enquanto que pessoa 1 é a celebridade
 *                      Não conhece: Considera-se por enquanto que a pessoa 2 é a celebridade
 *                  Agora, verifica-se se a pessoa 3 conhece a pessoa tida atualmente como a celebridade
 *                      Conhece: Mantém-se o chute atual de quem é a celebridade
 *                      Não conhece: Troca-se o chute pela pessoa 3
 *                  Repete-se até a ultima pessoa
 *                      N operações de vericar se P1 conhece P2
 *                  É necessário verificar se a pessoa é mesmo uma celebridade
 *                      Verifica-se a coluna correspondente, sendo celebridade caso todos seus
 *                      elementros sejam '1'
 *                      N operações de vericar se P1 conhece P2
 * 
 *                  Total de N + N operações
 *                      Para um número grande de pessoas -> N
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10            // Número de pessoas na multidão

int matriz_P[N][N];     // Matriz formulando os dados do problema

int (*f_rand)();        // Ponteiro da função rand() para ser utilizado em todas as funções

// Inicializar matriz com valores aleatórios (0 ou 1)
void matriz_init()
{

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            matriz_P[i][j] = f_rand() % 2;
        }
    }
}

void print_matriz()
{
    printf("Matriz do problema:\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d  ", matriz_P[i][j]);
        }
        printf("\n");
    }
}

// Introduzir celebridade na matriz
void put_celebridade()
{
    int celeb_ind = f_rand() % N;

    for(int i = 0; i < N; i++)
    {   
        // É importante manter a ordem das operações de inserção de 0 e 1
        // a fim de garantir que a coluna tenha somente '1's e a linha tenha N-1 zeros
        matriz_P[celeb_ind][i] = 0;
        matriz_P[i][celeb_ind] = 1;
    }
    
}

int algorit()
{
    // Retorna o indice da celebridade na matriz [0, N-1]
    // Retorna -1 caso celebridade não exista
    int celeb = 0;
    for (int i = 1; i < N; i++)
    {
        if (matriz_P[i][celeb] == 0)        // Se pessoa i não conhece o chute de celebridade atual
        {
            celeb = i;                      // Essa se torna o novo chute de celebridade
        }
    }

    // Verificar se tal pessoa é uma celebridade
    for (int i = 0; i < N; i++)
    {
        if (matriz_P[i][celeb] == 0)
        {
            celeb = -1;
            break;
        }
    }

    return celeb;
}


int main()
{
    
    // Inicializar função geradora de número aleatório
    time_t t;
    srand((unsigned) time(&t));
    f_rand = rand;
    
    matriz_init();


    if ((f_rand() % 2) == 1)
    {
        put_celebridade();
        printf("Celebridade inserida\n");
    }
    else printf("Sem celebridade\n");

    print_matriz();

    int celeb = algorit() + 1;

    if (celeb)
    {
        printf("A celebridade é a pessoa %d\n", celeb);
    }
    else
    {
        printf("Não há celebridade na multidão\n");
    }


}