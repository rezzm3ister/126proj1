#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"

using namespace std;

int getInput(char input[])
{
  string tempin;
  cout<<"shell>";
  cin.getline(input,80);
  tempin=string(input);
  if(tempin!="!!")
  {
    return 1;
  }
  else if(tempin=="exit")
  {
    return 0;
  }
  
  return -1;
  
}

int parseInput(char* args[], char input[])
{
    int count = 0;
    char *token = strtok(input," ");
    while(token != NULL){
        args[count++] = token;
        token = strtok(NULL, " ");
    }
    args[count] = token;
    return count;
}


//The function checks whether the passed argument uses a pipe or not
int checkPipe(char* args[], int len)
{
    for(int i = 0; i < len; i++)
    {
        if(strcmp(args[i],"|")==0)
        {
          return i;
        }
    }
    return -1;
}


//takes the input line and checks for pipes
void executeOrder66(char* args[], int len)
{
  int flag=0;
  int ipipe = checkPipe(args,len);
  if(ipipe==-1)
  {
    execnopipe(args,len);
  }
  else
  {
    //vector<string> marios; //pipe args is mario because mario goes in pipe
    //also no vectors because linux mad
    int i;
    char* marios[40];
    for(i=0;i<len-ipipe-1;i++)
    {
      //marios.push_back(args[ipipe+i+1]);
      marios[i] = args[ipipe+i+1];
    }
  marios[i]=NULL;
  if(marios[i-1]=="&")
  {
    flag=1;
    marios[i-1]=NULL;
  }
  args[ipipe]=NULL;
  execwithpipe(args,marios,flag);

  }
}


void execnopipe(char *args[40], int len)
{
    pid_t child1;
    int flag=0;
    
    if(args[len-1]=="&")
    {
        flag=1;
        args[len-1]=NULL;
        len--;
    }
    child1=fork();

    if(child1==0)
    {
        if(len>=3)
        {
            if(strcmp(args[len-2],">")==0)
            {
                args[len-2]=NULL;
                //whatever those arguments for linux open are
                int out = open(args[len-1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                // switch from stdout to file
                dup2(out, STDOUT_FILENO);
                close(out);
            }
            else if(strcmp(args[len-2],"<")==0)
            {
                args[len-2]=NULL;
                // open input file
                int in = open(args[len-1], O_RDONLY);
                //redirect input from converter to get from file
                dup2(in, STDIN_FILENO);
                close(in);
            }
        }
        if (execvp(args[0], args) < 0)
        {
            cout << "\nwell that didnt work";
        }
        exit(1);
    }
    else if(child1 > 0)
    { // if parent is running
    // check if theres no &
    if (flag==0)
    {
        wait(NULL);
    }
        return;
    }
    else {

        cout << "\nL+ratio+no maidens+no children"; //cant split process
        return;
    }
}


void execwithpipe(char* args[],char* marios[],int &flag)
{
  pid_t children;
  
  int fd[2];// not sure if this is right but it works

  if(pipe(fd) < 0)
  {//initialize pipeline
    cout << "\ncant into pipe";
    return;
  }
  children=fork(); //make children
  if(children == 0)
  {
    dup2(fd[1], STDOUT_FILENO);// write to file 
    // closed unused section
    close(fd[0]);
    // Close the used fd[2] part 
    
    close(fd[1]);
    //check if executable
    if(execvp(args[0],args) < 0)
    {
      cout << "\nwarp pipe 1 failed";
    }
    exit(1);
  }
  else if(children >0)
  {//parent program
      
    children = fork();//make another child do the work
    if(children == 0)
    {
      dup2(fd[0], STDIN_FILENO);
      close(fd[1]);
      close(fd[0]);
      if(execvp(marios[0], marios) < 0)
      {
        cout << "\nwarp pipe 2 failed";
      }
        
      exit(1);
    }
    else if(children > 0)
    {
      int state;
      close(fd[0]);
      close(fd[1]);
      if(flag==0)
        waitpid(children, &state, 0);
      return;
    }
    else 
    {
      cout << "\nCan't fork!!!";
      return;
    }
  }
  else
  {
      cout << "\nCan't fork!!!";
      return;
  }
}
