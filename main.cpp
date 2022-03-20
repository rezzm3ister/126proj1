//code
//alvarez angeles tuyay 126 proj 1
#include <iostream>
//#include <Bits.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void fillparams(vector<string> &cmdlist, vector<string> &operators){
  cmdlist.push_back("commands"); //populate this with our commands
  cmdlist.push_back("end");


  operators.push_back("<"); //populate this with the operators
  operators.push_back(">");
  operators.push_back("|");
}



int main(){
  bool run=1,validcmd=0;
  string in,tempstr;
  vector<string> cmdvec;
  vector<string> cmdlist;
  vector<string> cmds;
  vector<string> arguments; //list
  vector<string> operators; //list

  vector<string> ops;
  vector<string> args;

  fillparams(cmdlist,operators);

  while(run!=0){
    cout<<"shell>";
    getline(cin,in);
    stringstream cmd(in);
    cmdvec.clear();
    while(cmd>>tempstr){
      cmdvec.push_back(tempstr);
    }
    if(find(cmdlist.begin(),cmdlist.end(),cmdvec[0])!=cmdlist.end()){
      //cout<<cmdvec[0]<<" valid";
      validcmd=1;
      for(int i=0;i<cmdvec.size();i++){
        cout<<"tite";
        if(find(cmdlist.begin(),cmdlist.end(),cmdvec[i])!=cmdlist.end()){
          cmds.push_back(cmds[i]);
        }
        else{}
        cout<<"penis";
        if(find(operators.begin(),operators.end(),cmdvec[i])!=operators.end()){
          ops.push_back(cmdvec[i]);
          args.push_back(cmdvec[i+1]);
        }
      }
        cout<<"got here";
        /*debug parse checker
        for(int i=0;i<ops.size();i++){
          cout<<ops[i]<<" ";
        }
        cout<<endl;
        for(int i=0;i<args.size();i++){
          cout<<args[i]<<" ";
        }
        */
      }

      else{
        cout<<cmdvec[0]<<"\ninvalid command,";
      }

    







    
  }

}