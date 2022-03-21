//alvarez angeles tuyay 126 proj 1
#include <sys/types.h> 
//#include <sys/wait.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


#include "functions.h"

using namespace std;

int main()
{
  //vector<string> args; //cant use vectors because linux gets mad
  char* args[40]; //cant use string here because linux gets mad
  int run = 1;
  int state = 0;

  while(run) 
  {
    char input[100]; //input "string" because linux mad 
    //string input;
    int len;
    int res=getInput(input);
    if( res== 1)
    {//execute command
      len = parseInput(args,input);
      executeOrder66(args,len); 
      }
    else if(res==0)// exit
    {
      run=0;
    }
  }
  return 0;
}
