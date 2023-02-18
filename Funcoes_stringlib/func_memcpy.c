#include <stdio.h>

void *func_memcpy(void *str1, const void *str2, size_t n){
    unsigned char * p1 = (unsigned char *)str1;
    const unsigned char * p2 = (const unsigned char *)str2;
    for(;n--;p1++,p2++){
        *p1 = *p2;
    }
    return str1;
}



int main(){
    char str1[40];
    char str2[] = "ABCD";
    int n = 2;

    func_memcpy(str1, str2, n);
    str1[n] = '\0';
    printf("string 1 = %s", str1);
    
    return 0;
}