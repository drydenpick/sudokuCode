//
//  main.c
//  sudoku
//
//  Created by Scott and Dryden on 2018-06-28.
//  Copyright © 2018 Scott and Dryden. All rights reserved.
//
//TODO: error handling for thread creation!

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sudoku[9][9];

/* structure for passing data to threads */
typedef struct{
    int row;
    int column;
} parameters;

int rowsValid = 1;
int columnsValid = 1;
int squaresValid = 1;


void* square_check(void* arg){
    parameters *param = (parameters*) arg;
    parameters data = *param;
    int i = data.row;
    int j = data.column;

    int result[] = {0,0,0,0,0,0,0,0,0};

    //assuming all chars are numbers there are two cases. Ether there are 9 distinct numbers, or there are 2 duplicates.
    for(i= data.row; i < data.row + 3; i++){
        for(j= data.column; j < data.column + 3; j++){
            if(result[sudoku[j][i] - 1] != 0 || sudoku[j][i] == 0){
                squaresValid = 0;
               //printf("Not valid square %d %d\n", data.row, data.column);
                break;
            }
            else{
                result[sudoku[j][i] - 1] = sudoku[j][i];
            }
        }
    }
   // printf("Valid square %d %d\n", data.row, data.column);
}

void* column_check(){
    //printf("%d", sudoku[data.column][data.row]);
    
    int i = 0;
    int j = 0;
    int counter = 1;
    int boolean;
    int check = 1;
    
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            boolean = 0;
            
            //printf("%d %d\n", counter, sudoku[j][i]);
            
            if(sudoku[j][i] == counter)
            {
                boolean = 1;
                counter++;
                j = -1;
            }
            
            if(j == 8 && boolean == 0)
            {
              //  printf("Not valid column\n");
                break;
            }
            
            if (counter == 9 && boolean == 1)
            {
              //  printf("Valid column\n");
                counter = 1;
                check++;
                break;
            }
        }
    }
    if(check != 10){
        columnsValid = 0;
    }
}

void* row_check(){
    //printf("%d", sudoku[data.column][data.row]);
    
    int i = 0;
    int j = 0;
    int counter = 1;
    int boolean;
    int check = 1;
    
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            boolean = 0;
            
            //printf("%d %d\n", counter, sudoku[j][i]);
            
            if(sudoku[i][j] == counter)
            {
                boolean = 1;
                counter++;
                j = -1;
            }
            
            if(j == 8 && boolean == 0)
            {
                //printf("Not valid row\n");
                break;
            }
            
            if (counter == 9 && boolean == 1)
            {
                //printf("Valid row\n");
                counter = 1;
                check++;
                break;
            }
        }
    }
    if(check != 10){
        rowsValid = 0;
    }
}

int main(int argc, const char * argv[]) {
   
    // Get the file and save to file variable
    FILE *file = fopen("./sudokuTestFile.txt", "r");
    
    char input;
    int i = 0;
    int j = 0;
    
    //Read file and put values into 2d array. note: 13 is the carrage return charater
    while((input = fgetc(file)) != EOF) {
        if(input != ' ' && input != '\n' && input != 13) {
        int temp = input - '0';
        sudoku[i][j] = temp;
            j++;
            if(j == 9){
                j = 0;
                i++;
            }
        }
    }
    fclose(file);
    
    // TEST TO SEE THE BOARD
    // for(i = 0; i < 9; i++)
    // {
    //     for(j = 0; j < 9; j++)
    //     {
    //         printf("%d", sudoku[i][j]);
    //     }
    //     printf("\n");
    // }
    
    //thread identifers
    pthread_t tid[11];

    int tidIndex = 0;
    int k = 0; 
    int l = 0;

    for(k=0; k < 3; k++){
        for(l = 0; l < 3; l++){
            //Parameter data to check columns and rows for the sudoku grid
            parameters *data = (parameters *) malloc(sizeof(parameters));
            data->row = k*3;
            data->column = l*3;
            pthread_create(&tid[tidIndex], NULL, square_check, data);
            tidIndex++;
        }
    }
    
    pthread_create(&tid[tidIndex], NULL, row_check, NULL);
    tidIndex++;
    pthread_create(&tid[tidIndex], NULL, column_check, NULL);
    tidIndex++;

    
    for(k = 0; k < tidIndex; k++) {
        pthread_join(tid[k], NULL);
    }

    if(rowsValid && columnsValid && squaresValid){
        printf("Sudoku Solution is valid!\n");
    }
    else{
        printf("Sudoku Solution is not valid!\n");
    }
    return 0;
}
