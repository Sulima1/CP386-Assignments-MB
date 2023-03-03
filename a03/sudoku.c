#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int **createSudoku(){
    int row, column;
    int **array = malloc(9 * sizeof(int*));

    FILE *fp = fopen("sample_in_sudoku.txt", "r");

    if (fp == NULL){
        printf("file open error, make sure it exists");
        exit(1);
    }

    for (row = 0; row < 9; row++){
        array[row] = malloc(9 * sizeof(int));
        for (column = 0; column < 9; column++){
            fscanf(fp, "%d", &array[row][column]);
        }
    }
    return array;
}

int checkSudoku(int **sudokuArray){
    int *validNumbers = malloc(9 * sizeof(int*));

    for (int i = 1; i <= 9; i++){
        validNumbers[i-1] = i; 
    }
}

int main(char *argv[], int argc){
    int **sudokuArray;

    sudokuArray = createSudoku();

    pthread_t rowThread, columnThread;

    checkSudoku(sudokuArray);

    int i;
    for (i = 0; i < 9; i++) {
        free(sudokuArray[i]);
    }
    free(sudokuArray);
    return 0;
}
