#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

//implement me with user input
//how to make dynamic string for user input?
int createDir(char* dirName){
    int makeDir = mkdir(dirName, 0777);
    printf("Directory is created successfully.");
    return 0;
}

//implement me with user input
//error handling with invalid directories not in ls?
int deleteDir(char* dirName){
    int removeDir = rmdir(dirName);
    printf("Directory is removed successfully.");
    return 0;
}

int getCurrentDir(){
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working Directory is: %s\n", cwd);
   } 
   else {
       perror("getcwd() Directory error");
       return 1;
   }
   return 0;
}

// test me more, doesnt go further back than CP386
int stepBackDir(){
    char cwd[PATH_MAX];
    printf("Working Directory Before Operation: %s\n", cwd);
    int stepBack = chdir("..");
    printf("Working Directory After Operation: %s\n", cwd);
    return 0;
}

int readDir(){
    int listedDirectories = system("ls");
    printf("all directories listed.\n");
    return 0;
}

int main(){
    char input;
    char dirName[100];
    while (1){
        printf("Select the option(s) appropriately by entering the number:\n Enter 1 for creating a directory\n Enter 2 for removing directory\n Enter 3 for printing working directory\n Enter 4 for changing directory one level up\n Enter 5 for reading the contents of directory\n Enter 6 for closing the current directory\n Enter q to exit the program\n");
        input = getchar();
        switch (input){
            case 'q':
                break;
            case '1':
                printf("Enter the Directory name you want to create:\n");
                scanf("%s", dirName);
                createDir(dirName);
                continue;
            case '2':
                printf("Enter the Directory name you want to remove:\n");
                scanf("%s", dirName);
                deleteDir(dirName);
                continue;
            case '3':
                getCurrentDir();
                continue;
            case '4':
                printf("Stepping back one directory...\n");
                stepBackDir();
                continue;
            case '5':
                printf("Reading data on current directory...\n");
                readDir();
                continue;
        }
    }
}