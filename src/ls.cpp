#include<iostream>
#include<sstream>
#include<string>
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
void printL(struct stat &buf)
{ //prints the permissions and mode
	if(buf.st_mode & S_IFREG)
	{
		cout << '-';
	}
	if(buf.st_mode & S_IFDIR)
	{
		cout << 'd';
	}
	if(buf.st_mode & S_IFLNK)
	{
		cout << 'l';
	}
	if(buf.st_mode & S_IFSOCK)
	{
		cout << 's';
	}
	if(buf.st_mode & S_IFBLK)
	{
		cout << 'b';
	}
	if(buf.st_mode & S_IFIFO)
	{
		cout << 'f';
	}
	if(buf.st_mode & S_IFCHR)
	{
		cout << 'c';
	}
	cout << '-';

//user permissions
	if(buf.st_mode & S_IRUSR)
	{
		cout << 'r';
	}
	else
	{
		cout << '-';
	}
	
	if(buf.st_mode & S_IWUSR)
	{
		cout << 'w';
	}
	else
	{
		cout << '-';
	}
	if(buf.st_mode & S_IXUSR)
	{
		cout << 'x';
	}
	else
	{
		cout << '-';
	}


//group permissions

	if(buf.st_mode & S_IRGRP)
	{
		cout << 'r';
	}
	else
	{
		cout << '-';
	}
	if(buf.st_mode & S_IWGRP)
	{
		cout << 'w';
	}
	else
	{
		cout << '-';
	}
	if(buf.st_mode & S_IXGRP)
	{
		cout << 'x';
	}
	else
	{
		cout << '-';
	}

	//other permissions
	if(buf.st_mode & S_IROTH)
	{
		cout << 'r'; 
	}
	else
	{
		cout << '-';
	}
	if(buf.st_mode & S_IWOTH)
	{
		cout << 'w';
	}
	else
	{
		cout << '-';
	}
	if(buf.st_mode & S_IXOTH) 
	{
		cout << 'x';
	}
	else
	{
		cout << '-';
	}
}

void print(struct stat buf, dirent *direntp)
{

	cout << direntp->d_name << " ";

}
int aflags(string dirName)
{
if((strcmp(dirName.c_str(),"")) == 0)
	{
		dirName = ".";
	}
	DIR *dirp;
	dirent *direntp;
	cout << "line 140" << endl;
	if(!(dirp = opendir(dirName.c_str())))
	{
		perror("opendir error line 141");
	}
	while((direntp = readdir(dirp)))
	{
		if(errno != 0)
		{
			perror("readdir failed");
		}
		struct stat buf;
		char *path = new char[dirName.length()+1];
		strcpy(path,dirName.c_str());
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
	cout << direntp->d_name << " ";
	}	
	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;
}

int noflags(string dirName)
{	if((strcmp(dirName.c_str(),"")) == 0)
	{
		dirName = ".";
	}
	DIR *dirp;
	dirent *direntp;
	cout << "line 140" << endl;
	if(!(dirp = opendir(dirName.c_str())))
	{
		perror("opendir error line 141");
	}
	while((direntp = readdir(dirp)))
	{
		if(errno != 0)
		{
			perror("readdir failed");
		}
		struct stat buf;
		char *path = new char[dirName.length()+1];
		strcpy(path,dirName.c_str());
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		if(direntp->d_name[0] == '.')
		{
			continue;
		}
	cout << direntp->d_name << " ";
	}	
	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;


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
	char *h;
	vector<char*>v;
	string directoryName = "";
	vector<string> files;

	for(int i = 1; i < argc;i++) //pushes user input into vector
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
		else
		{
			directoryName = string(h);
		}
			
	
	}

	int fsize = files.size();
	if(!aflag && !rflag && !lflag)
	{
		noflags(directoryName);
	}
	if(lflag && !aflag && !rflag)
	{
		//lflag function
	}
	if(aflag && !lflag && !rflag)
	{
		aflags(directoryName);
	}
	if(lflag && aflag && !rflag)
	{
		//alflag function
	}
	if(aflag && rflag && !lflag)
	{
		//arflag function
	}
	if(rflag && lflag && !aflag)
	{
		//rlflag function
	}
	if(rflag && lflag && aflag)
	{
		//allflagfunction
	}
return 0;
}

