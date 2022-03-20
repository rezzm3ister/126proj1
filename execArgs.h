#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>
#include <iostream>
using namespace std;

#define MAX_LINE 80
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
            cout << "\nCould not execute in command...";
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

        cout << "\nCan't fork!!!"; //cant split process
        return;
    }
}