#include <stdio.h>


//Compara caracteres até encontrar uma diferença, o fim de uma ou de ambas as strings
//Em caso do fim de ambas as strings, retorna 0
//Para uma diferença, com o caratere das string 1 sendo o maior(valor em ASCII), retorna 1
//Caso contrario, retorna -1
int func_memcmp(const void *str1, const void *str2, size_t n){
    char *p1 = (char*)str1;
    char *p2 = (char*)str2;
    for (int i; i < n; i++){
        if(*p1 == '\0' && *p2 == '\0') return 0;
        else if(*p1 > *p2) return 1;
        else if(*p1 < *p2) return -1;
        p1++; p2++;
    }
    return 0;
}


int main(){
    char str1[] = "123ABcd";
    char str2[] = "123AbCD";
    int ret;

    ret = func_memcmp(str1, str2, 5);

    if(ret < 0) {
        printf("str1 is less than str2");
    } else if(ret > 0) {
        printf("str2 is less than str1");
    } else {
        printf("str1 is equal to str2");
    }

    return(0);
}