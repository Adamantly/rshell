#include<iostream>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

int main(int arc, char *argv[])
{
	while(1)
	{
		bool clause = true;
	//	char *token = strtok(a, ";");
		char token[128] = {};
		cout << "$";
		cin.getline(token, 128);
		if(strcmp(token,"exit") == 0)
		{
			exit(0);//if user typed exit, it exits the program.
		}
		char *cmptoken = strtoken(token, " ");
		for (int i = 0; i < 128 ;i++)
		{
			arg[i] = cmptoken;
			
		}
		int forkvar = fork();
		if(forkvar == 0)
		{
			if(execvp(argv[], arg) == -1)
			{
				perror("execvp did not run");
			}
			
	}

	return 0;
}
