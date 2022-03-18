#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
	pid_t pid;
	
	pid = fork();
	
	if (pid < 0)
	{
		cout << "forking error" << endl;
		return 1;
	}
	
	else if (pid == 0)
	{
		execlp("/bin/ls", "ls", NULL);
		cout << "right here" << endl;
	}
	
	else 
	{
		wait(NULL);
		cout << "child complete" << endl;
	}
	
	return 0;
}