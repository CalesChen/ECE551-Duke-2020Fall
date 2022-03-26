#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

#define Col 10
#define Row 10
/*void read_check(char matrix[], FILE * f){
    int ch;
    int count_c = 0, count_r = 0;

    for(int j = 0;j< Row;j++){
        ch = fgetc(f);

        if(ch == EOF || ch == '\n'){
            fprintf(stderr, "Missing Row\n");
            exit(EXIT_FAILURE);
        }
        matrix[j] = (char) ch;
    }

    
}
void p90_matrix(char matrix[][10]){
    for(int i = 0; i < Col; i++){
        for(int j = 0; j < Row; j++){
            printf("%c",matrix[Col-1-j][i]); //Transition and Convert
        }
        printf("\n");
    }

}*/
void read_check(char** matrix, FILE * f){
    int ch;
    int count_c = 0, count_r = 0;
    for(int i = 0; i < Col; i ++){
      for(int j = 0;j< Row;j ++){
        ch = fgetc(f); 
        
        if(ch == EOF || ch == '\n'){
            fprintf(stderr, "Missing Row\n");
            exit(EXIT_FAILURE);
        }
        matrix[i][j] = (char) ch;
      }
      int ch = fgetc(f);
      if(ch != '\n'){
        fprintf(stderr, "Additional Column\n");
        exit(EXIT_FAILURE);
      }
    }    
}
void p90_matrix(char** matrix){
    for(int i = 0; i < Col; i++){
        for(int j = 0; j < Row; j++){
            printf("%c",matrix[Col-1-j][i]); //Transition and Convert
        }
        printf("\n");
    }

}
int main(int args, char** argv){
    /*if(args != 2){
        fprintf(stderr, "Too few arguments.\n");
        exit(EXIT_FAILURE);
    }*/

    FILE * f = fopen("D:\\Master of ECE\\ECE551\\049_rot_matrix\\sample.txt", "r");
    if (f == NULL) {
        perror("Could not open file \n");
        getchar();
        exit(EXIT_FAILURE);
    }

    char (*matrix)[10];
    read_check(matrix,f);
    int ch = fgetc(f);
    if(ch != EOF){
        fprintf(stderr, "Additional Column\n");
        exit(EXIT_FAILURE);
    }
    /*char matrix[10][10];
    for(int i = 0; i<Col;i++){
        read_check(matrix[i],f);
        int ch = fgetc(f);
        if(ch != '\n'){
            fprintf(stderr, "Additional Row\n");
            exit(EXIT_FAILURE);
        }
    }

    int ch = fgetc(f);
    if(ch != EOF){
        fprintf(stderr, "Additional Column\n");
        exit(EXIT_FAILURE);
    }*/
    
    p90_matrix(matrix);
    getchar();
    return EXIT_SUCCESS;
}