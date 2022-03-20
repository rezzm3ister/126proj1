//alvarez angeles tuyay 126 proj 1

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "functions.h"

using namespace std;

int main()
{
    vector<string> args;
    int run = 1;
    int state = 0;

    while(run) {
        string input; //init input
        int len;
        int res=getInput(input);
        if( res== 1){//execute command
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
