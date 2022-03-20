/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


/*
#define MAX_LINE 80
// execute function uses pipe()
void execArgsPipe(char *args[], char *argsPipe[], int flag){
    __pid_t pid;

    int fd[2];// file decription
    if(pipe(fd) < 0){//initialize pipeline
        cout << "\nCan't init pipe!!!!";
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
            cout << "\nCan't execute pipe 1...";
        }
        exit(1);
    }else if(pid >0){//parent program
        
        pid = fork();
        if(pid == 0){
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            if(execvp(argsPipe[0], argsPipe) < 0){
                cout << "\nCan't execute pipe 2...";
            }
            
            exit(1);
        }
        else if(pid > 0){
            int state;
            close(fd[0]);
            close(fd[1]);
            if(flag==0)
                waitpid(pid, &state, 0);
            return;
        }
        else {
            cout << "\nCan't fork!!!";
            return;
        }
    }
    else{
        cout << "\nCan't fork!!!";
        return;
    }
}
*/