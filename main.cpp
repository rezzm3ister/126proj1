//alvarez angeles tuyay 126 proj 1

/*DELETE THIS BLOCK LATER
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
//#include <sys/wait.h> 
#include <sys/stat.h>
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//include header file
#include "execArgsPipe.h"
#include "execArgs.h"



using namespace std;

//#define MAX_LINE 80

//input function
int getInput(string &input){
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



  /*
    cout << "execute";
    //fflush(stdout);
    
     fgets(input,MAX_LINE,stdin);
    
    input[strlen(input)-1]='\0';
    if(strcmp(input, "!!") == 0){
        if(strlen(his) != 0){
            cout << "%s\n" << his;
            strcpy(input, his);
        }
        else{
            cout << "No command in history!!!\n";
            return -1;
        }
    }
    else if(strcmp(input,"exit")==0)
        return 0;
    if(strlen(input) > 0){
        strcpy(his, input);
    }
    return 1;
    */
}


/*
//parse function
int parseInput(string args, char input[]){
    int count = 0;
    char *tok = strtok(input," ");
    while(tok != NULL){
        args[count++] = tok;
        tok = strtok(NULL, " ");
    }
    args[count] = tok;
    return count;
}
*/
//done
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
//todo
//The function checks whether the passed argument uses a pipe or not
int checkPipe(vector<string> args, int len){
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


/*
//general execute function
void genExec(char *args[], int len){
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
*/
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
    vector<string> pipeargs;
    int i;
    for(i=0;i<len-ipipe-1;i++)
    {
      pipeargs.push_back(args[ipipe+i+1])
    }
  pipeargs[i]=NULL;
  if(pipeargs[i-1]=='&'){
    flag=1;
    pipeargs[i-1]=NULL;
  }
  args[ipipe]=NULL;
  pipesinvietnam(args,pipeargs,flag);

  }
}


int main(void)
{
    //char *args[MAX_LINE / 2 + 1];
    vector<string> args;
    //char his[100];
    //his[0] = '\0';
    int run = 1;
    int state = 0;

    while(run) {
        //char input[100];
        string input=""; //init input
        int len;
        int res=getInput(input);
        if( res== 1){//execute command
            len = parseInput();
            //genExec(args, len);
            executeOrder66(args,len);
        }
        else if(res==0)// exit
        {
            run=0;
        }
    }
    return 0;
}
