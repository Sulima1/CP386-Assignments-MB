#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){

    if (argc == 3) {
        int outputFile;
        int inputFile;

        char *inputName = argv[1];
        char *outputName = argv[2];

        char buffer[1];

        if (access(inputName, F_OK) == -1){
            perror("Missing input file \n");
            exit(1);
        }
        else{
            printf("File opened successfully");
            inputFile = open(inputName, O_RDONLY, 0777);
            
            // if creat() returns errno EEXIST, remove existing and replace with new
            if (access(outputName, F_OK) == 0){
                remove(outputName); 
            }

            // declare permissions for outputFile
            mode_t mode = O_WRONLY | O_CREAT;

            // open the file and read 
            outputFile = open(outputName, mode);

            ssize_t len; // how many characters are written per iteration

            if (len = read(inputFile, buffer, 1)  == -1){
                perror("File reading error");
                exit(1);
            }

            while ((len = read(inputFile, buffer, 1) ) != 0){
                // loop through file and write to wp (writepage)
                write(outputFile, buffer, len);
            }

            // close files at the end
            close(inputFile);
            close(outputFile);

        }
    }
    else{
        printf("Insufficient parameters passed. \n");
    }
    return 0;
}
