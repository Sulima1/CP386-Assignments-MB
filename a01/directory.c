#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//implement me with user input
//how to make dynamic string for user input?
int createDir(dirName){
    int makeDir = system("mkdir %s", dirName);
    printf("check directory '%s' has been created. \n", dirName);
    return 0;
}

//implement me with user input
//error handling with invalid directories not in ls?
int deleteDir(dirName){
    int removeDir = system("rmdir testDirectory");
    printf("check directory 'testDirectory' has been removed. \n");
    return 0;
}

int getCurrentDir(){
    printf("the current directory is: \n");
    int currentDir = system("pwd");
    return 0;
}

// test me more, doesnt go further back than CP386
int stepBackDir(){
    int stepBack = system("cd -");
    printf("stepped back one directory.\n");
    return 0;
}

int readDir(){
    int listedDirectories = system("ls");
    printf("all directories listed.\n");
    return 0;
}

int main(){
    printf("----------------------------------------------\n");
    printf("Welcome to Matt's linux terminal!\n");
    printf("----------------------------------------------\n");
    printf("Here are the commands\nTo create a new directory, press 1.\nTo remove an existing directory, press 2.\nTo get the current working directory, press 3.\nTo move one level up from current directory, press 4.\nTo read the current directory, press 5.\nTo close the current directory, press 6.\nPress q to quit.\n");
    char input;
    while (1){
        input = getchar();
        switch (input){
            case 'q':
                printf("Goodbye.\n");
                break;
            case '1':
                printf("Enter a valid name for a new directory.\n");
                char dirName[100];
                scanf("%s", dirName);
                createDir(dirName);
                continue;
            case '2':
                printf("Enter the name of the directory you would like to delete.\n");
                char dirName[100];
                scanf("%s", dirName);
                deleteDir(dirName);
                continue;
            case '3':
                printf("Getting data on current directory...\n");
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