#include<stdlib.h>
#include<stdio.h>

int main(void){
    int a = 0x01020304;
    unsigned char* a1 = (unsigned char*) &a;
    unsigned char* a2 = a1 + 1;
    unsigned char* a3 = a2 + 1;
    unsigned char* a4 = a3 + 1;

    printf("a = %x\n",a);
    printf("%d,%d\n",&a,a2);
    printf("%d\n",(int)*a1);
    printf("%x\n",*(int*)a1);
    //printf('a1 = %d\n',*a1);
    //printf('a2 = %d\n',*a2);
    //printf('a3 = %d\n',*a3);
    //printf('a4 = %d\n',*a4);

    getchar();
    return EXIT_SUCCESS;
}