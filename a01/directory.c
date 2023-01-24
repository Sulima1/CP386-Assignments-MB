#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>

char* getCurrentDir(){
    char* cwd = NULL;
    size_t size = 0;
    if (getcwd(cwd, size) != NULL) {
        return cwd;
    } 
    else {
        perror("getcwd error");
        return NULL;
    }
}

//implement me with user input
//how to make dynamic string for user input?
int createDir(char* dirName){
    int makeDir = mkdir(dirName, 0777);
    if (makeDir == 0){
        printf("Directory is created successfully.");
        return 0;
    }
    else{
        printf("mkdir error");
    }
    
    return 1;
}

//implement me with user input
//error handling with invalid directories not in ls?
int deleteDir(char* dirName){
    int removeDir = rmdir(dirName);
    if (removeDir == 0){
        printf("Directory is removed successfully.");
        return 0;
    }
    else{
        printf("rmdir error");
    }
    return 1;
}

char *workingDir(){
    static char cwd[250];
	getcwd(cwd,sizeof(cwd));	//function to print current directory
	return cwd;
}

// test me more, doesnt go further back than CP386
int stepBackDir(char* cwd){
    int stepBack = chdir("..");
    printf("Directory changed successfully.\n");
    return 0;
}

int readDir(){
    DIR *directory;
	struct dirent *directoryContent;
	directory = opendir(".");
	if (directory){
		while ((directoryContent = readdir(directory)) != NULL) {

			   printf("%s\n",directoryContent->d_name);
		}
	}
    printf("all directories listed.\n");
    return 0;
}

int closeDir(){
	DIR *currentDir;
	currentDir = opendir(".");
	closedir(currentDir);	
	printf("Directory Closed Successfully.\n");
	return 0;
}



int main(){
    char input;
    char dirName[100];
    char cwd[PATH_MAX];
    char currCwd[PATH_MAX];
    while (1){
        printf("Select the option(s) appropriately by entering the number:\n Enter 1 for creating a directory\n Enter 2 for removing directory\n Enter 3 for printing working directory\n Enter 4 for changing directory one level up\n Enter 5 for reading the contents of directory\n Enter 6 for closing the current directory\n Enter q to exit the program\n ");
        scanf(" %c", &input);
        switch (input){
            case 'q':
                return 0;
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
                printf("Current working directory is: %s \n", workingDir());
                continue;
            case '4':
                printf("Stepping back one directory...\n");
                stepBackDir(cwd);
                continue;
            case '5':
                printf("Reading data on current directory...\n");
                readDir();
                continue;
            case '6':
                printf("Reading data on current directory...\n");
                readDir();
                continue;
            default:
                printf("Invalid input, please follow the commands listed below...");
                continue;
        }
    }
}