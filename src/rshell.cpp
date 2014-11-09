#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

//test
void login()
{
		char username[128];
		char hostname[128];
		if(getlogin_r(username,128) != 0)
		{
			perror("Could not get username");
		}	
		if(gethostname(hostname,128) != 0)
		{
			perror("Could not get hostname");
		}
		cout << username << "@" << hostname << "$";


}
int main(int argc, char *argv[])
{
	bool nonstop = true;
	while(nonstop)
	{
		char token[1024] = {0};
		login();
		cin.getline(token,128);
		if(strcmp(token,"exit") == 0)
		{	
			exit(0);//if user typed exit, it exits the program.
		}	
	//	unsigned l = 0; //attempt at comments
	//	while(token[l] != '\0')
	//	{
	//		if(token[l] == '#');
	//		{
	//			token[l] = '\0';
	//		//	cout << "hello" << endl;
	//		}	
	//	   ++l;
	//	}
		char **argument;
		argument = new char *[1024];//creates array of pointers

		unsigned position = 0;//counts when it gets to end of line using cstring;
						
	         
		char *cmptoken = strtok(token, " ;#|");
		while( cmptoken != NULL)
		{
			argument[position] = cmptoken;
			position = position + 1;
			cmptoken = strtok(NULL," ;#|");//continues parsing the line
		}
		argument[position] = NULL;//ends the strtok with a null to make sure it doesn't seg fault
		
		int forkvar = fork();//uses pid to identify processes
		if(forkvar)//parent process which runs 
		{
			wait(0);
		}	
		else if(forkvar == 0)//child process which lets us run exec
		{
			wait(0);
			if(execvp(argument[0], argument) == -1)//takes in the argument from array.
			{
				perror("execvp did not run");
			}
			delete[] argument;
			exit(1);//exits when fails
			
		}
		else
		{
			perror("Fork failed");//error flag when forking fails
			return 0;
		}
	}
	return 0;

}

