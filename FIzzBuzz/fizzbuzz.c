/*
Código que escreve os números de 1 a 100, mas que substitui o número por "Fizz" se este 
for um múltiplo de 3 e "Buzz" se for um múltiplo de 5. Substitui por "FizzBuzz" se o número por um
múltiplo tanto de 3 quanto de 5.
*/
#include <stdio.h>

char fizz[20] = "Fizz";
char buzz[20] = "Buzz";


void main()
{
    for (char i = 1; i < 100; i++){
        if (!(i%3)) printf("%s", fizz);
        if (!(i%5)) printf("%s", buzz);
        if (i%3 && i%5) printf("%d", i);
        printf("\n");
    }
}