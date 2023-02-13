#include<stdio.h>

void * func_memchr(const void *str, char ch, int n){
    const char *p = (const char *)str;
    while(n){
        if (*p == ch) return (void*)p;
        p++;
        n--;
    }
    return NULL;
}

int main(){
    char string[] = "ABCDEFG";
    printf("Resultado = %s\n", func_memchr(string, 'E', 3));

}