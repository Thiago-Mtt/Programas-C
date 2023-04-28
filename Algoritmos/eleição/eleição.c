/*
 * Problema: Verificar qual candidato (se houver) ganhou a eleição por maioria dos votos (50% + 1) 
 * 
 * Formulação:
 *              Há N votos e M candidatos
 *              Lista com N votos, cada um direcionada para um dos candidatos
 *              Candidatos são representados por números de 1 até M
 * 
 * Algoritmo N (2N):
 *              Itera-se pela lista de votos uma vez, mantendo dois números ('i' e 'candidato')
 *                  i: variável de contagem, começa com
 *                  candidato: guarda o número de um dos candidatos
 *                  ambos começam com zero
 *              Caso i seja zero:
 *                  guarda-se o número do candidato para o qual o voto atual é direcionado
 *                  incrementa-se a variável i++
 *                  segue-se para o próximo voto imediatamente
 *              Caso 'candidato' seja equivalente ao número de candidato do voto atual
 *                  incrementa-se i
 *              Caso contrário:
 *                  decrementa-se i
 * 
 *              O candidato mantido no fim da iteração é o possível vencedor por maioria
 *              Verifica-se por meio de outra iteração, contando somente os votos deste
 *              
 *                  

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100       // Numero de votos
#define M 5         // Numero de candidatos
#define VENCENDOR_GARANTIDO 0

int (*f_rand)();            // Ponteiro da função rand() para ser utilizado em todas as funções
int votos[N];
int votos_por_candidato[M];

void print_votos()
{
    int total_votos = 0;

    for (int i = 0; i < M; i++)
    {
        printf("Votos do candidato %d: %d\n", i+1, votos_por_candidato[i]);
        total_votos += votos_por_candidato[i];
    }
    printf("Total de votos = %d\n", total_votos);
}

void init_rand()
{
    // Inicializar função geradora de número aleatório
    time_t t;
    srand((unsigned) time(&t));
    f_rand = rand;
}

void init_votos()
{
    // Retorna 0 caso votos sejam distribuidos aleatoriamente
    // Retorna 1 caso tenha garantia de que um candidato ganha por maioria
    // Para garantir um candidato vencedor, alteram-se votos aleatórios de outros candidatos
    //  pelo do vencedor até que este possua a maioria dos votos
    //  Este método não cobre vitórias por grande maioria
    
    // Iniciar vetor com zero votos para cada candidato
    for (int i = 0; i < M; i++)
    {
        votos_por_candidato[i] = 0;
    }
    
    // Distribuir votos aleatoriamente
    int voto;
    for (int i = 0; i < N; i++)
    {
        voto = f_rand() % M;
        votos[i] = voto;
        votos_por_candidato[voto]++;

    }
    
    if (VENCENDOR_GARANTIDO == 0)
    {   
        printf("Votos totalmente aleatórios\n");
        return;
    }



    int maioria = (N/2) + 1;
    
    for (int i = 0; i < M; i++)
    {
        if (votos_por_candidato[i] >= maioria)
        {
            printf("Vencedor já presente\n");
            return;
        }
    }

    int vencedor = f_rand() % M;
    
    int voto_aleatorio;
    int candidato_do_voto_aleatorio;
    while (votos_por_candidato[vencedor] < maioria)
    {
        voto_aleatorio = f_rand() % N;
        candidato_do_voto_aleatorio = votos[voto_aleatorio];
        if (candidato_do_voto_aleatorio != vencedor)
        {
            votos_por_candidato[candidato_do_voto_aleatorio]--;
            votos[voto_aleatorio] = vencedor;
            votos_por_candidato[vencedor]++;
        }
    }

    printf("Vencedor inserido\n");
    return;
}


int algoritmo()
{
    int candidato = -1, v = 0;

    // Parte 1: Obter o possível candidato vencedor por maioria
    for (int i = 0; i < N; i++)
    {
        if (v == 0)
        {
            candidato = votos[i];
            v++;
            continue;
        }

        if      (votos[i] == candidato)     v++;
        else                                v--;
    }


    // Parte 2: Verificação
    v = 0;
    for (int i = 0; i < N; i++)
    {
        if (votos[i] == candidato) v++;
    }

    if      (v >= (N / 2) + 1)  return candidato;
    else                        return -1;

}

int main()
{
    init_rand();
    init_votos();

    print_votos();

    int candidato_vencedor = algoritmo();

    if      (candidato_vencedor != -1)   printf("Candidato vencedor: %d\n", candidato_vencedor + 1);
    else                                 printf("Não houve vencedor por maioria\n");


}