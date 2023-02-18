#include <stdio.h>

void *func_memcpy(void *dest, const void *src, size_t n){
    unsigned char * p1 = (unsigned char *)dest;
    const unsigned char * p2 = (const unsigned char *)src;
    for(;n--;p1++,p2++){
        *p1 = *p2;
    }
    return dest;
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