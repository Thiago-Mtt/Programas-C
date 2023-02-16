#include <stdio.h>


//Compara caracteres até encontrar uma diferença, o fim de uma ou de ambas as strings
//Em caso do fim de ambas as strings, retorna 0
//Para uma diferença, com o caratere das string 1 sendo o maior(valor em ASCII), retorna 1
//Caso contrario, retorna -1
int func_strcmp(const char *str1, const char *str2){
    for (;;){
        if(*str1 == '\0' && *str2 == '\0') return 0;
        else if(*str1 > *str2) return 1;
        else if(*str1 < *str2) return -1;
        str1++; str2++;
    }
}


int main(){
    char str1[] = "ABcd";
    char str2[] = "AbCD";
    int ret;

    ret = func_strcmp(str1, str2);

    if(ret < 0) {
        printf("str1 is less than str2");
    } else if(ret > 0) {
        printf("str2 is less than str1");
    } else {
        printf("str1 is equal to str2");
    }

    return(0);
}