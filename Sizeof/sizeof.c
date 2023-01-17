//Escreve o número de bytes dentro das variáveis

#include <stdio.h>

void main()
{
    printf("Size of char: %d bytes\n", sizeof(char));
    printf("Size of short: %d bytes\n", sizeof(short));
    printf("Size of int: %d bytes\n", sizeof(int));
    printf("Size of long: %d bytes\n", sizeof(long));
    printf("Size of float: %d bytes\n", sizeof(float));
    printf("Size of double: %d bytes\n", sizeof(double));
    printf("Size of long double: %d bytes\n", sizeof(long double));

    unsigned char a = 167;
    printf("%c", a);
}