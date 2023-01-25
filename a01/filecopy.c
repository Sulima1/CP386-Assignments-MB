#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(){

    // open input as rp (readpage) and give it 0777 permission
    int rp = open("input.txt", O_RDONLY | O_CREAT, 0777);
    if(rp == -1){
        // if filename not found
        perror("Insufficient parameters passed. \n");
    }
    else {
        printf("File opened successfully");
    }
    
    // declare permissions for outputFile
    mode_t mode = O_WRONLY | O_CREAT | O_EXCL;
    char *filename = "output.txt";
    // errnum for error handling if file exists 
    int errnum = errno;

    int outputFile = creat(filename, mode);

    // if creat() returns errno EEXIST, remove existing and replace with new
    if (errnum == EEXIST){
        int remove(filename); // warning: parameter names (without types) in function declaration
        int creat(filename, mode);// warning: parameter names (without types) in function declaration
    }

    // open the file (fopen?) and read 
    int wp = fopen("output.txt", mode);  // warning: passing argument 2 of ‘fopen’ makes pointer from integer without a cast
    // + warning: initialization of ‘int’ from ‘FILE *’ makes integer from pointer without a cast

    // not too sure what these do but I think I need them for the while loop
    ssize_t len;
    char buffer[100];

    while ((len = read(wp, buffer, 50))){
        // loop through file and write to wp (writepage)
        write(wp, buffer, len);
    }

    // close files at the end
    close(rp);
    close(wp);

}