#include<stdlib.h>
#include<stdio.h>
#define ROW 2
#define COL 3
 
void myputs(char **pos);
 
int main()
{
    //char **p;
    //char (*a)[4]={"abc", "def"};
    //p = a;
    //myputs(p);
    
    double a[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    double ** p = (double **)a;
    
    printf("%f",p[0][0]);
    getchar();
    
    return 0;
}
 
void myputs(char **p)
{
    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
            printf("%c ", p[i][j]);
        printf("\n");
    }
}