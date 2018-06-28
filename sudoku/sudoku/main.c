//
//  main.c
//  sudoku
//
//  Created by Scott on 2018-06-28.
//  Copyright © 2018 Scott. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/* structure for passing data to threads */

typedef struct{
    int row;
    int column;
} parameters;

int main(int argc, const char * argv[]) {
   
    // Get the file and save to file variable
    FILE *file = fopen("/Users/scott/Desktop/sudoku/sudoku/sudokuTestFile.txt", "r");
    
    char input;
    int sudoku[9][9];
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
    
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data->row = 1;
    data->column = 1;
    
    

    return 0;
}
