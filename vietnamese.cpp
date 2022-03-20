#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>

#define MAX_LINE 80

//input function
int getInput(char input[], char history[]){
    printf("osh>");
    fflush(stdout);
    
     fgets(input,MAX_LINE,stdin);// khong nen dung gets vi tu C11 da bi xoa so roi
    // xoa dau \n cuoi cung
    input[strlen(input)-1]='\0';
    if(strcmp(input, "!!") == 0){
        if(strlen(history) != 0){
            printf("%s\n", history);
            strcpy(input, history);
        }
        else{
            printf("No command in history!!!\n");
            return -1;
        }
    }
    else if(strcmp(input,"exit")==0)
        return 0;
    if(strlen(input) > 0){
        strcpy(history, input);
    }
    return 1;
}

//non-pipe regular function
void execArgs(char *args[], int len){
    // processes split
    __pid_t child_pid;
    int flag=0;
    // check if last element has a &
    if(*args[len-1]=='&'){
        flag=1;
        args[len-1]=NULL;
        len--;
    }
    child_pid=fork();
    // check if the proceess is child or parent
    if(child_pid == 0) {// if child is running
        if(len >= 3){
            if(strcmp(args[len - 2], ">" ) == 0){//output redirect
                args[len - 2] = NULL;
                // open file to write to
                int out = open(args[len - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                // switch from stdout to file
                dup2(out, STDOUT_FILENO);
                
                close(out);
            }            
            else if(strcmp(args[len- 2], "<" ) == 0){ //input redirect
                args[len - 2] = NULL;
                // open input file
                int in = open(args[len - 1], O_RDONLY);
                //redirect input from converter to get from file
                dup2(in, STDIN_FILENO);
                
                close(in);
            }
        }
        // if error or wrong input
        if (execvp(args[0], args) < 0){
            printf("\nCould not execute in command...");
        }
        exit(1);

    }
    else if(child_pid > 0){ // if parent is running
    // check if theres no &
    if (flag==0)
    {
        wait(NULL);
    }
        return;
    }else {

        printf("\nCan't fork!!!"); //cant split process
        return;
    }
}

//parse function
int parseInput(char *args[], char input[]){
    int count = 0;
    char *tok = strtok(input," ");
    while(tok != NULL){
        args[count++] = tok;
        tok = strtok(NULL, " ");
    }
    args[count] = tok;
    return count;
}

//The function checks whether the passed argument uses a pipe or not
int checkPipe(char *args[], int len){
    for(int i = 0; i < len; i++){
        if(strcmp(args[i], "|") == 0)
            return i;
    }
    return -1;
}

// execute function uses pipe()
void execArgsPipe(char *args[], char *argsPipe[], int flag){
    __pid_t pid;

    int fd[2];// file decription
    if(pipe(fd) < 0){//initialize pipeline
        printf("\nCan't init pipe!!!!");
        return;
    }
    // process split
    pid = fork();

    if(pid == 0){// Tiến trình con
        dup2(fd[1], STDOUT_FILENO);// write to file 
        // closed unused section
        close(fd[0]);
        // Close the used fd[2] part 
        close(fd[1]);
        //check if executable
        if(execvp(args[0],args) < 0){
            printf("\nCan't execute pipe 1...");
        }
        exit(1);
    }else if(pid >0){//parent program
        
        pid = fork();
        if(pid == 0){
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            if(execvp(argsPipe[0], argsPipe) < 0){
                printf("\nCan't execute pipe 2...");
            }
            
            exit(1);
        }
        else if(pid > 0){
            int status;
            close(fd[0]);
            close(fd[1]);
            if(flag==0)
                waitpid(pid, &status, 0);
            return;
        }
        else {
            printf("\nCan't fork!!!");
            return;
        }
    }
    else{
        printf("\nCan't fork!!!");
        return;
    }
}

//general execute function
void exec(char *args[], int len){
    int flag=0;
    int iPipe = checkPipe(args, len);
    if(iPipe == -1){
        execArgs(args, len);
        return;
    } else {
        char *argsPipe[MAX_LINE / 2 + 1];
        int i;
        for(i = 0; i < len - iPipe - 1; i++){
            argsPipe[i] = strdup(args[iPipe + i +1]);
        }

        argsPipe[i] = NULL; 
        if(*argsPipe[i-1]=='&'){
            flag=1;
            argsPipe[i-1] = NULL;
        }
        args[iPipe] = NULL;
        execArgsPipe(args, argsPipe,flag);
        return;
    }
}

int main(void)
{
    char *args[MAX_LINE / 2 + 1];
    char history[100];
    history[0] = '\0';
    int shouldRun = 1;
    int status = 0;

    while(shouldRun) {
        char input[100];
        int len;
        int res=getInput(input, history);
        if( res== 1){//execute command
            len = parseInput(args, input);
            exec(args, len);
        }
        else if(res==0)// exit
        {
            shouldRun=0;
        }
    }
    return 0;
}