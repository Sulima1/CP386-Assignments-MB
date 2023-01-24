#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(){

    int fp = open("input.txt", O_RDONLY | O_CREAT);
    if(fp == -1){
        perror("Failed to open 'input.exe' file. \n");
    }
    else {
        printf("File opened successfully");
    }
    
    int creat(const char *output, mode_t mode);

    int errnum = errno;

    if (errnum == EISDIR){
        int remove(const char *output);
        int creat(const char *output, mode_t mode);
    }



}