#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>

void writeOuput(char *command, char *output) {
	//pointer pointing to a file
	FILE *file;
    //open output.txt
	file = fopen("output.txt", "a");
    //print out the format for what output.txt will look like without infromation filled in
	fprintf(file, "The output of: %s : is\n", command);
	
	fprintf(file, ">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
    //close the file
	fclose(file);
}
//main method takes two parameters a integer and a char pointer
int main(int argc, char *argv[]) {
	//remove output.txt
	remove("output.txt");
	//interger value that will open and work with output.txt
	int output_f = open("output.txt", O_WRONLY | O_CREAT,
	S_IRUSR | S_IWUSR);
    //constant int of SIZE 4096 for temporary storing of information
	const int SIZE = 4096;
    //declaration of child process
	pid_t child;
    //char pointer fo that is making use of the char pointer originally declared in the paraters
	char *fo = argv[1];
    //int array of size 2
	int fd[2];
    //declaring new char pointer called dynamic_array which is set to NULL to intially work with
	char *dynamic_array = NULL;
	//shared memory
	int s;
    //new constant 
	const char *name = "OS";
    //new char pointer called am_st for later use
	char *am_st;
    //char pointer called ptr for later use
	char *ptr;
	s = shm_open(name, O_CREAT | O_RDWR, 0666);
    //use this command to work with a file and a given size
	ftruncate(s, SIZE);

	am_st = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, s , 0);
    //new process made if negative 1 throw error and return 1
	child = fork();
	if (child == -1)
	{
		printf("File opening error");
		return 1;
	}
    //if not 0 keep continuing with the process
	else if (child == 0) {

		char buff[255];

		FILE *folder;

		folder = fopen(fo, "r");

		ptr = am_st;

		while (fgets(buff, 255, folder) != NULL) 
		{
			sprintf(ptr, "%s", buff);

			ptr = ptr + strlen(buff);
		}
		fclose(folder);

	} else 
	{
		dynamic_array = (char*) calloc(strlen(am_st), sizeof(char));

		strcpy(dynamic_array, am_st);

	}

	char c[20], c_1[20];

	char *com = strtok(dynamic_array, "\n");

	char buffer_reader[4096];

	while (com != NULL) {
		pipe(fd);

		child = fork();

		if (child == -1)
		{
			printf("fork error");

		}
		else if (child == 0) {

			strcpy(c_1, " ");

			close(fd[0]);

			dup2(fd[1], STDOUT_FILENO);

			char total[20];

			strcpy(total, com);

			char *p = strtok(total, " ");

			strcpy(c, p);

			while (p != NULL) 
			{
				strcat(c_1, strcat(p, " "));

				p = strtok(NULL, " ");
			}
			char *args_l[2] = {c_1, NULL };

			execvp(c, args_l);
		}
		if (strcmp(com, ">") == 0)
		 {
			int output_f = open("redirected_output", O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR);

			dup2(output_f, STDOUT_FILENO);

			char c[20];

			strcpy(c, com);

			char *l = strtok(c, " ");
			strcpy(c, l);

			while (l != NULL) {
				strcat(c_1, strcat(l, " "));

				l = strtok(NULL, " ");
			}
			//new char pointer that is the list of the argument 
			char *argument_lst[2] = {c_1, NULL };
            //use exec call on argument_lst
			execvp(c, argument_lst);

		}

		else {
			//wait till all process terminate
			wait(NULL);

			memset(buffer_reader, 0, 4096);

			close(fd[1]);

			read(fd[0], buffer_reader, sizeof(buffer_reader));

			writeOuput(com, buffer_reader);

		}
		com = strtok(NULL, "\n");
	}

	return 0;
}