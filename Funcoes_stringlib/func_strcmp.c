#include <stdio.h>


//Compara caracteres até encontrar uma diferença, o fim de uma ou de ambas as strings
//Em caso do fim de ambas as strings, retorna 0
//Ao encontrar uma diferença, retorna o valor do caractere da str1 subtraido do caractere da str2
int func_strcmp(const char *str1, const char *str2){
    while(*str1 == *str2 && *str1 != '\0'){
        str1++; str2++;
    }
    return (int)(*str1 - *str2);
}


int main(){
    char str1[] = "ABCdef";
    char str2[] = "ABCf";
    int ret;

    ret = func_strcmp(str1, str2);
    printf("ret = %d\n", ret);

    if(ret < 0) {
        printf("str1 is less than str2");
    } else if(ret > 0) {
        printf("str2 is less than str1");
    } else {
        printf("str1 is equal to str2");
    }

    return(0);
}