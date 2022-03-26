#include<stdio.h>
#include<stdlib.h>

int main(void){
    float a = 3.1;
    float * p = &a;
    float ** pp = &p;
    (*pp) += 3;
    printf("%zu\n",p);
    printf("%zu",&a);
    getchar();
}