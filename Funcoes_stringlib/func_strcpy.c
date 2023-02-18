#include <stdio.h>

char *func_strcpy(char *str1, const char *str2){
    char *str_rtrn = str1;
    while(*str2 != '\0'){
        *str1 = *str2;
        str1++; str2++;
    }
    *str1 = '\0';
    return str_rtrn;
}



int main(){
    char str1[40];
    char str2[] = "ABC";

    func_strcpy(str1, str2);
    printf("string 1 = %s", str1);
    
    return 0;
}