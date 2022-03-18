//code
//alvarez angeles tuyay 126 proj 1
#include <iostream>
#include <Bits.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void fillparams(vector<string> &cmdlist, vector<char> &operators,vector<char> &arguments){
  cmdlist.push_back("commands"); //populate this with our commands
  cmdlist.push_back("end");


  operators.push_back('<'); //populate this with the operators
  operators.push_back('>');
  operators.push_back('|');
}



int main(){
  bool run=1;
  string in,tempstr;
  vector<string> cmdvec;
  vector<string> cmdlist;
  vector<string> arguments;
  vector<char> operators;
  fillparams(cmdlist,operators,arguments);

  while(run!=0){
    getline(cin,in);
    stringstream cmd(in);
    cmdvec.clear();
    while(cmd>>tempstr){
      cmdvec.push_back(tempstr);
    }

    if(find(cmdlist.begin(),cmdlist.end(),cmdvec[0])!=cmdlist.end()){
      string command=cmdvec[0];
      cout<<cmdvec[0]<<" valid";
    }
    else{
      cout<<cmdvec[0]<<" invalid";
    }

    

    
  }

}