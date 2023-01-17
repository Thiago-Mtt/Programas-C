/*
Calculadora que recebe 2 operandos (A e B) mais um operador (+, -, *, /, >, < ou =) e escreve
o resultado
*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
    float op1,op2;
    char operador;
    printf("Inserir numero A: \n");
    scanf("%f", &op1);
    printf("Inserir numero B: \n");
    scanf("%f", &op2);
    printf("Operacao (+, -, *, /, >, <, =): \n");
    scanf(" %c", &operador); 
    //Espaço antes de %c. O input anterior contem o operando 'b' e um caracter 
    //new line. Sem o espaço, o scanf lê o newline ainda guardado no buffer. Recomenda-se usar scanf
    //apenas para inputs sanitizados (não do teclado) e usar fgets() para esse caso
    printf("Operador escolhido: %c \n", operador);

    switch (operador)
    {
    case '+':
        printf("%f", op1+op2);
        break;
    case '-':
        printf("%f", op1-op2);
        break;
    case '*':
        printf("%f", op1*op2);
        break;
    case '/':
        printf("%f", op1/op2);
        break;
    case '>':
        if (op1 > op2) printf("V");
        else printf("F");
        break;
    case '=':
        if (op1 == op2) printf("V");
        else printf("F");
        break;
    default:
        break;
    }

}