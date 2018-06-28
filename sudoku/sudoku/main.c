//
//  main.c
//  sudoku
//
//  Created by Scott on 2018-06-28.
//  Copyright © 2018 Scott. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sudoku[9][9];

/* structure for passing data to threads */
typedef struct{
    int row;
    int column;
} parameters;

void* column_check(void* arg){
    
    parameters *param = (parameters*) arg;
    parameters data = *param;
    
    printf("%d", data.row);
    
    return 0;
}

int main(int argc, const char * argv[]) {
   
    // Get the file and save to file variable
    FILE *file = fopen("/Users/scott/Desktop/sudokuCode/sudoku/sudoku/sudokuTestFile.txt", "r");
    
    char input;
    int i = 0;
    int j = 0;
    
    //Read file and put values into 2d array.
    
    while((input = fgetc(file)) != EOF){
        if(input != ' ' && input != '\n')
        {
        int temp = input - '0';
        sudoku[i][j] = temp;
            j++;
            if(j == 9)
            {
                j = 0;
                i++;
            }
        }
        }
    fclose(file);
    
    //TEST TO SEE THE BOARD
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            printf("%d", sudoku[i][j]);
        }
        printf("\n");
    }
    
    //Parameter data to check columns and rows for the sudoku grid
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data->row = 1;
    data->column = 1;
    
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_create(&tid, &attr, column_check, data);
    pthread_join(tid, NULL);

    return 0;
}
