//code
//alvarez angeles tuyay 126 proj 1
#include <iostream>
#include <Bits.h>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int main(){
  bool run=1;
  string in,tempstr;
  vector<string> cmdvec;

  while(run!=0){
    getline(cin,in);
    stringstream cmd(in);
    cmdvec.clear();
    while(cmd>>tempstr){
      cmdvec.push_back(tempstr);
    }

    
  }

}