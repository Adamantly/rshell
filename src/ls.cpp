#include<iostream>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<fcntl.h>
#include<cstdlib>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<vector>
#include<stdio.h>
using namespace std;

int noflags(string dirName)
{
	DIR *dirp;
	dirent *direntp;
	if(!(dirp = opendir(dirName.c_str())))
	{
		perror("opendir error ln19");
	}
	while((direntp = readdir(dirp))
	{
		struct stat buf
	}	

}

int main(int argc, char *argv[])
{
//	char *dirName = ".";
//	DIR *dirp =  opendir(dirName);
//	dirent *direntp;
//	while((direntp = readdir(dirp)))
//		cout << direntp->d_name << endl;
//	closedir(dirp);

	bool lflag = false;
	bool rflag = false;
	bool aflag = false;
	vector<char*>v;
	struct stat buffer;

	for(int i = 0; i < argc;i++) //pushes user input into vector
	{
		v.push_back(argv[i]);
	}
	int size = v.size();
	for (int a = 0; a < size;a++)
	{
		if(strcmp(v.at(a),"-l") == 0)
		{
			lflag = true;
		}
		else if(strcmp(v.at(a),"-a") == 0)
		{
			aflag = true;
		}
		else if(strcmp(v.at(a),"-R") == 0)
		{
			rflag = true;
		}
	
	
	}
	if(!aflag && !rflag && !lflag)
	{
		//function for no flags;
	}
}
