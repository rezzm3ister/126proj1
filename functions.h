#include <iostream>
#include<string>
#include<vector>

using namespace std;
int getInput(char input[]);

int parseInput(char* args[], char input[]);

int checkPipe(char* args[], int len);

void executeOrder66(char* args[], int len);

void execnopipe(char* args[], int len);

void execwithpipe(char* args[],char* marios[],int &flag);

