#include<stdio.h>

char * func_strchr(const char *str, char ch){
    int i=0;
    while(str[i] != '\0'){
        if(str[i] == ch){
            char *p = ((char *)str)+i;
            return p;
        }
        i++;
    }
    return NULL;
}

int main(){
    char string[] = "ABCD";
    printf("Resultado = %s\n", func_strchr(string, 'B'));

}