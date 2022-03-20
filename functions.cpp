#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"

using namespace std;

int getInput(string &input)
{
  cout<<"shell>";
  getline(cin,input);
  if(input.size()>0&&input.find("exit")!=string::npos)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int parseInput(vector<string> &args, string input)
{
  stringstream tempsstream(input);
  string tempstr;

  while(tempsstream>>tempstr)
  {
    args.push_back(tempstr);
  }
  return args.size();

}


//The function checks whether the passed argument uses a pipe or not
int checkPipe(vector<string> args, int len)
{
    for(int i = 0; i < len; i++){
        if(args[i]=="|"){
          return i;
        }
        /*
        if(strcmp(args.at(i), "|") == 0)
            return i;
        */
    }
    return -1;
}

//rename execargs to invadepoland
//rename execargspipe to pipesinvietnam
//done
void executeOrder66(vector<string> args, int len)
{
  int flag=0;
  int ipipe = checkPipe(args,len);
  if(ipipe==-1)
  {
    invadepoland(args,len);
  }
  else
  {
    vector<string> marios;
    int i;
    for(i=0;i<len-ipipe-1;i++)
    {
      marios.push_back(args[ipipe+i+1]);
    }
  marios[i]="";
  if(marios[i-1]=="&"){
    flag=1;
    marios[i-1]="";
  }
  args[ipipe]="";
  pipesinvietnam(args,marios,flag);

  }
}


void invadepoland(vector<string> &args, int len)
{
    pid_t child1;
    int flag=0;
    if(args[len-1]=="&")
    {
        flag=1;
        args[len-1]="";
        len--;
    }
    child1=fork();

    if(child1==0)
    {
        if(len>=3)
        {
            if(args[len-2]==">")
            {
                args[len-2]="";
                //whatever those arguments for linux open are
                int out = open(args[len - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                // switch from stdout to file
                dup2(out, STDOUT_FILENO);
                close(out);
            }
            else if(args[len-2]=="<")
            {
                args[len-2]="";
                // open input file
                int in = open(args[len - 1], O_RDONLY);
                //redirect input from converter to get from file
                dup2(in, STDIN_FILENO);
                close(in);
            }
        }
        if (execvp(args[0], args) < 0){
            cout << "\nwell that didnt work";
        }
        exit(1);
    }
    else if(child1 > 0){ // if parent is running
    // check if theres no &
    if (flag==0)
    {
        wait(NULL);
    }
        return;
    }else {

        cout << "\nL+ratio+no maidens+split failed"; //cant split process
        return;
    }
}


void pipesinvietnam(vector<string> &args,vector<string> &marios,int &flag)
{
    pid_t children;

    int fd[2];// not sure if this is right
    if(pipe(fd) < 0){//initialize pipeline
        cout << "\ncant into pipe";
        return;
    }
    children=fork();
    if(children == 0){// Tiến trình con
        dup2(fd[1], STDOUT_FILENO);// write to file 
        // closed unused section
        close(fd[0]);
        // Close the used fd[2] part 
        close(fd[1]);
        //check if executable
        if(execvp(args[0],args) < 0){
            cout << "\nwarp pipe 1 failed";
        }
        exit(1);
    }else if(children >0){//parent program
        
        children = fork();
        if(children == 0){
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            if(execvp(marios[0], marios) < 0){
                cout << "\nwarp pipe 2 failed";
            }
            
            exit(1);
        }
        else if(pid > 0){
            int state;
            close(fd[0]);
            close(fd[1]);
            if(flag==0)
                waitpid(children, &state, 0);
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