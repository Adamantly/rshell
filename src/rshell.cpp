#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;
void doPipes(char** leftpart, char** rightpart);
void noPipes(char **arg2);
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
void check(char** arg) //looks for pipes
{
		bool piping = false;
		int splitting = 0;

		char **left;
		left = new char*[128];
		char **right;
		right = new char*[128];

		for(int i = 0; arg[i] != '\0';i++)
		{
			if(!strcmp(arg[i],"|"))
			{
				piping = true;
				splitting = i;
				break;
			}
		}
		if(piping)
		{
			for(int i = 0; i < splitting;i++)
			{
				left[i] = arg[i];
			}
			int end = 0;
			for(int i = splitting + 1; arg[i] != '\0';i++, end++)
			{
				right[end] = arg[i];
			}
			left[splitting] = '\0';
			right[end] = '\0';
			
			doPipes(left,right);
		}
		else
		{
			noPipes(arg);
		}
		delete []left;
		delete []right;

}
void doPipes(char** leftpart, char** rightpart)
{
			int fd[2];
			if(pipe(fd) == -1)
			{
				perror("Error with pipe function");
			}
			int pid = fork();
			if(pid == -1)
			{
				perror("fork in piping error'd");
			}
			else if(pid == 0)
			{
				if(dup2(fd[1],1) == -1)
				{
					perror("Error with dup2");
				}
				if(close(fd[0]) == -1)
				{
					perror("Error with close");
				}
				if(execvp(leftpart[0],leftpart) == -1)
				{
					perror("Execvp wrong in piping");
				}
				exit(1);
			}
			int savestate = dup(0);
			if((savestate) == -1)
			{
				perror("Error with dup (141)");
			}
			if(dup2(fd[0],0) == -1)
			{
				perror("Error with dup2 (145)");
			}
			if(close(fd[1]) == -1)
			{
				perror("Error with close.(149)");
			}
			if(wait(0) == -1)//change this later
			{
				perror("Error in wait (153)");
			}

			check(rightpart);

			dup2(savestate,0);
}
void noPipes(char **arg2)
{
		int forkvar = fork();//uses pid to identify processes
		if(forkvar == -1)
		{
			perror("Error with fork (130)");
		}
		if(forkvar)//parent process which runs 
		{
			wait(0);
		}	
		else if(forkvar == 0)//child process which lets us run exec
		{

		//Function here
			
			for(int i = 0; arg2[i] != '\0';i++)
			{
				int fd;
				if(!strcmp(arg2[i], ">"))
				{
					arg2[i] = NULL;
					if(((fd = open(arg2[i+1],O_CREAT | O_WRONLY | O_TRUNC, 0666))) == -1)
					{
						perror("There is an error with open(150)");
					}
					if(dup2(fd,1) == -1)
					{
						perror("Error with dup2 (153)");
					}
						break;
				}
				else if(!strcmp(arg2[i],">>"))
				{
					arg2[i] = NULL;
					if((open(arg2[i+1],O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
					{
						perror("There is an error with open(150)");
					}
					if(dup2(fd,1) == -1)
					{
						perror("Error with dup2 (153)");
					}
						break;
				}
				else if(!strcmp(arg2[i],"<"))
				{
					arg2[i] = '\0';
					if((fd = open(arg2[i+1],O_RDONLY)) == -1)
					{
						perror("Error with open (175)");
					}
					if(dup2(fd,0))
					{
						perror("Error with dup2 (180)");
					}
						break;
				}
			}


			
			if(execvp(arg2[0], arg2) == -1)//takes in the argument from array.
			{
				perror("execvp did not run");
			}
		//	delete[] arg2;
			exit(1);//exits when fails
			
		}
		else
		{
			perror("Fork failed");//error flag when forking fails
			exit(1);
		}
	


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
		for(int i = 0;i< 1024; i++)
		{
			if(token[i] == '#')
			{
				token[i] = '\0'; //places null terminating char at the end.
			}
		}

		char **argument;
		argument = new char *[1024];//creates array of pointers

		unsigned position = 0;//counts when it gets to end of line using cstring;
						
	         
		char *cmptoken = strtok(token, " ");
		while( cmptoken != NULL)
		{
			argument[position] = cmptoken;
			position = position + 1;
			cmptoken = strtok(NULL," ");//continues parsing the line
		}
		argument[position] = NULL;//ends the strtok with a null to make sure it doesn't seg fault
		////////////////////////////////////////////
		

		bool backgroundprocess = false;

	/*	for(int i = 0;i < argc ;i++)
		{
			if(strcmp(token,"&"))
			{
				backgroundprocess = true;
				argument[i] = '\0';
			}
		}
*/
		check(argument);

}
	return 0;
}

