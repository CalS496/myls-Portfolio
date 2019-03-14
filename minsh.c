/*
9.15.17
Final Assignment Submission v2
FOR PORTFOLIO PURPOSES

Context: This is the final submission for the myls assignment. Later assignments
will require further building upon this code to incorporate even more features
to resemble a functioning Linux Shell. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int verbose_flag = 1; //by default, program should be in verbose mode
int redirection_flag = 0; //if there is redirection, then parsing will detect it and flip the bit
//when flipped, execution will check it and perform redirection appropriately. Once complete, it will
//flip it back to normal; a simple form of redirection, only ">" form
char *outputFile;

void parse(char* input, char** output){
	//parsing assuming a maximum sized array for the arguments
	//memory will be wasted, but hopefully not too much

	char delimit[] = " \t\n\v";
	char *p = strtok(input, delimit);
	int i = 0;
	//inspiration for following for loop form from the following
	//stack post:
	//https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c

	for(; p != NULL; p = strtok(NULL, delimit)){
		if(strcmp(p, ">") == 0) {//so > will not be included in arguments
			redirection_flag = 1;
			p = strtok(NULL, delimit); //bit of a stretch, but always assumes that next work is output file
			outputFile = p;
		}else {
			output[i++] = p;
		}
	}
	output[i] = NULL;

	//following are for testing purposes:
	//int a = 0;
	//printf("YOLO: %s", commands[0]);
	//for(; a < i; a++)
		//printf("%s<\n", output[a]); //extra carrot chara to make sure no newline

	//*output = *commands;
	//return *commands;
}

void execution(char **commands){
	/*int i = 0;
	for (; i < 5; i++){
		printf("%s\n", commands[i]);
	}*/

	//from textbook, Chapter 5, code example
	//Cite: pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf
	int rc = fork();
	if(rc < 0){ //fork failure; exit
		fprintf(stderr, "fork failed\n");
		exit(1);

	} else if (rc == 0) {//child new process
		if(verbose_flag){
			printf("hello, I am child (pid: %d)\n", (int) getpid());
			printf("I will execute a new process\n");
		}

		if(redirection_flag){
			if(verbose_flag)
				printf("Redirection in progress:\n");

			//Citations: pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf pg 7
			close(STDOUT_FILENO);
			open(outputFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		}
			//now exec normally
			execvp(commands[0], commands);

	} else{
		int wc = wait(NULL);
		if(verbose_flag)
			printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
	}
}

int main(int argc, char* argv[]){
	int should_run = 1;
	char input[80];
	char* commands[10];
	//printf("%s", argv[1]); //verifying how to use argv[]

	//To enable verbose mode or not
	if(argc > 1 && strcmp(argv[1], "-v")==0)
		verbose_flag = 0;
	//if condition needs argc > 1, otherwise second condition results in
	//segmentation fault

	if(verbose_flag){
		printf("Welcome to the Mini Shell!\n");
		printf("This Shell is being run under Verbose Mode currently\n");
		printf("To disable, please execute the program again with the flag '-v' \n");
	}

	while(should_run){
		printf("minsh> ");

		fgets(input, 80, stdin);

		//call "exit" or "quit" to quit the minsh
		if(strcmp(input, "exit\n")==0 || strcmp(input, "quit\n")==0)
			exit(0);

		parse(input, commands);
		//printf("r-flag: %d\n", redirection_flag);
		execution(commands);
		//always assures that after redirection, flag turns off
		redirection_flag = 0;
		//printf("r-flag2: %d\n", redirection_flag);
		/*int i = 0;
		printf("\n");
		for(; i < 7; i++){
			printf("%s>\n", commands[i]);
		}*/ //test to make sure proper parameter output

		//execvp(commands[0], commands); //This works alone

		//printf("%s", argv);
		fflush(stdout);
		/*
		(0) Read user input, e.g. with fgets()
		(1) fork a child process
		(2) the child process will invoke execvp()
		(3) the parent will invoke wait()
		*/

	if(verbose_flag)
		printf("\nAwaiting further instructions!\n");

	} //end while
	return 0;
}
