#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <fcntl.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>


void columnCounter(char* inputName, int* rows, int* columns) {
  int maxColumns = 0;
  int c;
  FILE *fp;
  

  fp = fopen(inputName, "r");

  if (fp == NULL)
  {
    printf("Error with input file, please try again\n");
  }


  while ((c = fgetc(fp)) != EOF){
      if (fscanf(fp, "%d", &c) == 1)
      {
          if (maxColumns == 0)
          {
              (*rows)++;
          }
          //calculation for maxColumns, increment max columns
          maxColumns = (maxColumns + 1) % (*rows + 1); 
          (*columns)++;

      }
    }

  fclose(fp);
  *columns = *columns / 10;
}


int** formatGrades(char* inputName, int columns, int rows) 
{
  int c;
  FILE *fp;

  // arrays to store the data from the file
  int** matrix = (int**) malloc(rows * sizeof(int*));
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int*) malloc(columns * sizeof(int));
  }

  // open the file for reading
  fp = fopen(inputName, "r");
  if (fp == NULL) {
    printf("Error with input file, please try again\n");
    return NULL;
  }

  int row = 0;
  int col = 0;
  while (fscanf(fp, "%d", &c) == 1) {
    matrix[row][col] = c;
    col++;
    if (col == columns) {
      row++;
      col = 0;
    }
  }

  return 0;
}
int main(int argc, char *argv[]){
    int rows = 0; 
    int columns = 0;

    // get file name from command line and open it for read only
    char *inputName = argv[1];
    int inputFile = open(inputName, O_RDONLY, 0777);

    // function to read the number of columns in text file
    columnCounter(inputName, &rows, &columns);
    
    if (columns % 2 != 0){
      columns--;
    }

      int c;
      FILE *fp;

      // arrays to store the data from the file
      int** matrix = (int**) malloc(rows * sizeof(int*));
      for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) malloc(columns * sizeof(int));
      }

      // open the file for reading
      fp = fopen(inputName, "r");
      if (fp == NULL) {
        printf("Error with input file, please try again\n");
        return 0;
      }

      int row = 0;
      int col = 0;
      while (fscanf(fp, "%d", &c) == 1) {
        matrix[row][col] = c;
        col++;
        if (col == columns) {
          row++;
          col = 0;
        }
      }
    int assignmentNumber = 1, colCount = 0;
    double average = 0;
    pid_t TApid1, TApid2, GTApid;
    while (colCount < columns) {
        GTApid = fork();
        if (GTApid == 0)
        {
          double sum = 0;
          TApid1 = fork();
          if (TApid1 == 0){

            for (int j = 0; j < rows; j++) {
                sum += matrix[j][colCount];
            }                
            average = sum / rows;

            printf("Assignment %d - Average : %.6lf\n", assignmentNumber, average);
            _exit(0);
          }
          else if (TApid1 < 0){
            perror("fork");
            _exit(0);
          }
          else{
            int status;
            wait(&status);
          }
          sum = 0;
          _exit(0);
        // exit code exits the if statement, resume parent process progress
        }
        else if (GTApid < 0){
          perror("fork");
          _exit(0);
        }
        else{
          int gtaStatus;
          wait(&gtaStatus);
        }
        colCount++;
        assignmentNumber++;
  }
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
} 
