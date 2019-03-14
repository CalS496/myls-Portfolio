/* minsh.c Ver 1.0. To be further reviewed.
9.14.17

FOR PORTFOLIO PURPOSES, AN EARLIER VERSION OF THE CODE I EVENTUALLY SUBMITTED
THEREFORE THERE IS A CHANCE THAT THERE IS A PROBLEM WITH THIS VERSION OF THE
CODE (DOESN'T COMPILE, DOESN'T READ, ERRORS)

Programmer: Calvin H
CS215
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int verbose_flag = 1; //by default, program should be in verbose mode

/*char* parse(char* input){
//parsing input to shell using strtok
//printf("%s", input); //test to make sure input is actual user input
//attempt to dynamically build our char arrays
char *p = strtok(input, " ");
char buffer[3];
int i = 0;
int max = 3;
for (; p != NULL; p = strtok(NULL, " ")){
  //puts(p);
buffer[i++] = p;
if(i == (2*max)/3){
//if 2/3 the max size of array, resize array
}
}
}*/
void parse(char* input, char** output){
//parsing assuming a maximum sized array for the arguments
//memory will be wasted, but hopefully not too much
//char* commands[10];
//char **commands = malloc(10 * sizeof(char *));
char delimit[] = " \t\n\v";
char *p = strtok(input, delimit);
int i = 0;
for(; p != NULL; p = strtok(NULL, delimit)){
output[i++] = p;
}
output[i] = NULL;
int a = 0;
//printf("YOLO: %s", commands[0]);
//for testing purposes
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
if(verbose_flag)
printf("hello, I am child (pid: %d)\n", (int) getpid());
execvp(commands[0], commands);
} else{
int wc = wait(NULL);
if(verbose_flag)
printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
}
//return 0;
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
if(verbose_flag)
printf("Welcome to the Mini Shell!\n");
while(should_run){
printf("minsh> ");
fgets(input, 80, stdin);
//call "exit" or "quit" to quit the minsh
if(strcmp(input, "exit\n")==0 || strcmp(input, "quit\n")==0)
exit(0);
printf("\n");
/*test[0] = strdup("ls");
test[1] = strdup("-la");
test[2] = NULL;*/
parse(input, commands);
execution(commands);
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
