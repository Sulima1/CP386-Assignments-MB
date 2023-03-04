#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int grid[9][9];
int scanner = 0;

void* validate_rows_cols(void* arg) {
    bool is_row = *((bool*)arg);
    for (int i = 0; i < 9; i++) {
        bool used[9] = {false};
        for (int j = 0; j < 9; j++) {
            int digit = is_row ? grid[i][j] - 1 : grid[j][i] - 1;
            if (used[digit]) {
                scanner = 1;
                pthread_exit(NULL);
            }
            used[digit] = true;
        }
    }
    pthread_exit(NULL);
}

void* validate_subgrid(void* arg) {
    int subgrid_num = *((int*)arg);
    int start_row = (subgrid_num / 3) * 3;
    int start_col = (subgrid_num % 3) * 3;
    
    bool used[9] = {false};
    for (int row = start_row; row < start_row + 3; row++) {
        for (int col = start_col; col < start_col + 3; col++) {
            int digit = grid[row][col] - 1;
            if (used[digit]) {
                scanner = 1;
                pthread_exit(NULL);
            }
            used[digit] = true;
        }
    }

    pthread_exit(NULL);
}

int main() {
    int row, column;
    FILE *fp = fopen("sample_in_sudoku.txt", "r");

    if (fp == NULL){
        printf("file open error, make sure it exists");
        exit(1);
    }

    for (row = 0; row < 9; row++){
        for (column = 0; column < 9; column++){
            fscanf(fp, "%d", &grid[row][column]);
        }
    }
    
    printf("Sudoku Puzzle Solution is:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    // Create threads to validate the rows, columns, and subgrids
    pthread_t threads[1 + 1 + 3 * 3];
    int subgrid_args[3 * 3];
    bool is_row = true;

    pthread_create(&threads[0], NULL, validate_rows_cols, (void*)&is_row);
    is_row = false;
    pthread_create(&threads[1], NULL, validate_rows_cols, (void*)&is_row);
    for (int i = 0; i < 3 * 3; i++) {
        subgrid_args[i] = i;
        pthread_create(&threads[i + 2], NULL, validate_subgrid, (void*)&subgrid_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 1 + 1 + 3 * 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // If all threads finish successfully, the Sudoku solution is valid
    if (scanner == 1){
        printf("The Sudoku solution is invalid.\n");
    }
    else{
        printf("The Sudoku solution is valid.\n");
    }

    return 0;
}