#include<iostream>
#include<sstream>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<fcntl.h>
#include<cstdlib>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<vector>
#include<stdio.h>
using namespace std;
void printL( struct stat &buf)
{
	cout << endl;
	if(buf.st_mode & S_IFREG)
	{
		cout << '-';
	}
	else if(buf.st_mode & S_IFDIR)
	{
		cout << 'd';
	}
	else if(buf.st_mode & S_IFLNK)
	{
		cout << 'l';
	}
	else if(buf.st_mode & S_IFSOCK)
	{
		cout << 's';
	}
	else if(buf.st_mode & S_IFBLK)
	{
		cout << 'b';
	}
	else if(buf.st_mode & S_IFIFO)
	{
		cout << 'f';
	}
	else if(buf.st_mode & S_IFCHR)
	{
		cout << 'c';
	}
	else
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

	if(buf.st_mode & S_IXUSR)
	{
		cout << "\033[38;5;34m" << direntp->d_name << "\033[0;00m" << " ";
	}
	else if(buf.st_mode & S_IFDIR)
	{
		cout << "\033[38;5;32m" << direntp->d_name << "\33[0;00m" << " ";
	}
	else if(direntp->d_name[0] == '.' && (buf.st_mode & S_IFDIR))
	{
		cout << "]033[47m\033[38;5;32m" << direntp->d_name << "\033[0;00m" << " ";		
	}
	else if(direntp->d_name[0] == '.')//gray background
	{
		cout << "\033[47m" << direntp->d_name << "\033[0;00m" << " ";
	}
	else
	{
		cout << direntp->d_name << " ";
	}
}
int aflags(string dirName)
{
//	if((strcmp(dirName.c_str(),"")) == 0)
//	{
		dirName = ".";
//	}
	DIR *dirp;
	dirent *direntp;
//	cout << "line 140" << endl;
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
	//	cout << "line 160" << endl;
		strcpy(path,dirName.c_str());
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
	cout << direntp->d_name << " ";
	}	

//	cout << "line 168" << endl;

	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;
}
int lflags(string dirName)
{
	dirName = ".";
	DIR *dirp;
	dirent *direntp;

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
		char *path = new char[dirName.length()+100];

		strcpy(path,dirName.c_str());
		strcat(path, "/");
		strcat(path, direntp->d_name);
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		if(direntp->d_name[0] == '.')
		{
			continue;
		}
		printL(buf);//prints file permissions
		cout << buf.st_nlink << " ";

		struct passwd *pawd;
		string user;
		if(!(pawd = getpwuid(buf.st_uid)))
		{
			perror("did not get id");
		}


		user = pawd->pw_name;
		cout << user << " ";
		struct group *gid;//gid
		string getID;//groupid
		if(!(gid = getgrgid(buf.st_gid)))
		{
			perror("Error with getgrid");
		}

		getID = gid->gr_name;
		cout << getID << " ";
		
		int bytesize = buf.st_size;
		cout << bytesize << " ";
		 //printing out time
		 time_t t = buf.st_mtime;
		 struct tm *time= localtime(&t);
		 char timebuffer[100];

		 strftime(timebuffer, 100, "%h %d %R", time);
		 cout << timebuffer  << " ";
		print(buf,direntp);
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
int rflags(string dirName)
{
	vector<char*>directory;
	if((strcmp(dirName.c_str(),"")) == 0)
	{
		dirName = ".";
	}
	DIR *dirp;
	dirent *direntp;
//	cout << "line 140" << endl;
	if(!(dirp = opendir(dirName.c_str())))
	{
		perror("opendir error line 141");
	}
	if((strcmp(dirName.c_str(),".")))
	{
		cout << ".:" << endl;
	}
	else
	{
		cout << dirName  <<":" << endl;
	}
	while((direntp = readdir(dirp)))
	{
		if(errno != 0)
		{
			perror("readdir failed");
		}
		struct stat buf;
		char *path = new char[dirName.length()+100];
//		cout << "line 160" << endl;
		strcpy(path,dirName.c_str());
		strcat(path,"/");
		strcat(path, direntp->d_name);
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		if(direntp->d_name[0] == '.')
		{
			continue;
		}

	cout << direntp->d_name << " ";

		if(S_ISDIR(buf.st_mode))
		{
			directory.push_back(direntp->d_name);
		}
	}	

	for(unsigned p = 0; p < directory.size();p++)
	{
		rflags(dirName + "/" + directory.at(p));
	}
	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;

}
int alflag(string dirName)
{
		dirName = ".";
	DIR *dirp;
	dirent *direntp;

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
		char *path = new char[dirName.length()+100];

		strcpy(path,dirName.c_str());
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		printL(buf);//prints file permissions
		cout << buf.st_nlink << " ";

		struct passwd *pawd;
		string user;
		if(!(pawd = getpwuid(buf.st_uid)))
		{
			perror("did not get id");
		}


		user = pawd->pw_name;
		cout << user << " ";
		struct group *gid;//gid
		string getID;//groupid
		if(!(gid = getgrgid(buf.st_gid)))
		{
			perror("Error with getgrid");
		}

		getID = gid->gr_name;
		cout << getID << " ";
		
		int bytesize = buf.st_size;
		cout << bytesize << " ";
		 //printing out time
		 time_t t = buf.st_mtime;
		 tm *tminfo = localtime(&t);
		 char string[100];

		 strftime(string, 100, "%b %d %R", tminfo);
		 cout << string  << " ";
		print(buf,direntp);
	}
	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;



}
int aRflags(string dirName)
{
	vector<char*>directory;
		dirName = ".";
	DIR *dirp;
	dirent *direntp;
//	cout << "line 140" << endl;
	if(!(dirp = opendir(dirName.c_str())))
	{
		perror("opendir error line 141");
	}
	if((strcmp(dirName.c_str(),".")))
	{
		cout << ".:" << endl;
	}
	else
	{
		cout << dirName  <<":" << endl;
	}
	while((direntp = readdir(dirp)))
	{
		if(errno != 0)
		{
			perror("readdir failed");
		}
		struct stat buf;
		char *path = new char[dirName.length()+1];
//		cout << "line 160" << endl;
		strcpy(path,dirName.c_str());
		strcat(path,"/");
		strcat(path, direntp->d_name);
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		if(direntp->d_name[0] == '.')
		{
			continue;
		}

	cout << direntp->d_name << " ";

		if(S_ISDIR(buf.st_mode))
		{
			directory.push_back(direntp->d_name);
		}
	}	

//	cout << "line 168" << endl;
	for(unsigned p = 0; p < directory.size();p++)
	{
		rflags(dirName + "/" + directory.at(p));
	}
	cout << endl;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;


}
int rlflags(string dirName)
{
	vector<char*>directory;

	if((strcmp(dirName.c_str(),"")) == 0)
	{
		dirName = ".";
	}
	DIR *dirp;
	dirent *direntp;

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
		char *path = new char[dirName.length()+100];

		strcpy(path,dirName.c_str());
		strcat(path,"/");
		strcat(path, direntp->d_name);
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		if(direntp->d_name[0] == '.')
		{
			continue;
		}
		printL(buf);//prints file permissions
		cout << buf.st_nlink << " ";

		struct passwd *pawd;
		string user;
		if(!(pawd = getpwuid(buf.st_uid)))
		{
			perror("did not get id");
		}


		user = pawd->pw_name;
		cout << user << " ";
		struct group *gid;//gid
		string getID;//groupid
		if(!(gid = getgrgid(buf.st_gid)))
		{
			perror("Error with getgrid");
		}

		getID = gid->gr_name;
		cout << getID << " ";
		
		int bytesize = buf.st_size;
		cout << bytesize << " ";
		 //printing out time
		 time_t t = buf.st_mtime;
		 tm *tminfo = localtime(&t);
		 char string[100];

		 strftime(string, 100, "%b %d %R", tminfo);
		 cout << string  << " ";
		print(buf,direntp);
		if(S_ISDIR(buf.st_mode))
		{
			directory.push_back(direntp->d_name);
		}

	}
	cout << endl;
	for(unsigned p = 0; p < directory.size();p++)
	{
		rflags(dirName + "/" + directory.at(p));
	}
	return 0;
	if(closedir(dirp) == -1)
	{
		perror("closedir failed line 36");
	}
	return 0;


}
int allflags(string dirName)
{
	vector<char*>directory;

	dirName = ".";
	DIR *dirp;
	dirent *direntp;

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
		char *path = new char[dirName.length()+100];
		strcpy(path,dirName.c_str());
		strcat(path,"/");
		strcat(path, direntp->d_name);
		if(stat(path, &buf) == -1)
		{
			perror("stat did not work ln 32");
		}
		printL(buf);//prints file permissions
		cout << buf.st_nlink << " ";

		struct passwd *pawd;
		string user;
		if(!(pawd = getpwuid(buf.st_uid)))
		{
			perror("did not get id");
		}


		user = pawd->pw_name;
		cout << user << " ";
		struct group *gid;//gid
		string getID;//groupid
		if(!(gid = getgrgid(buf.st_gid)))
		{
			perror("Error with getgrid");
		}

		getID = gid->gr_name;
		cout << getID << " ";
		
		int bytesize = buf.st_size;
		cout << bytesize << " ";
		 //printing out time
		 time_t t = buf.st_mtime;
		 tm *tminfo = localtime(&t);
		 char string[100];

		 strftime(string, 100, "%b %d %R", tminfo);
		 cout << string  << " ";
		print(buf,direntp);
		if(S_ISDIR(buf.st_mode))
		{
			directory.push_back(direntp->d_name);
		}

	}
	cout << endl;
	for(unsigned p = 0; p < directory.size();p++)
	{
		rlflags(dirName + "/" + directory.at(p));
	}
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
		else if(strcmp(v.at(a), "-al") == 0 || (strcmp(v.at(a),"-la") == 0))
		{
			aflag = true;
			lflag = true;
		}
		else if(strcmp(v.at(a), "-aR") == 0 || (strcmp(v.at(a), "-Ra") == 0))
		{
			rflag = true;
			aflag = true;
		}
		else if(strcmp(v.at(a), "-lR") == 0 || (strcmp(v.at(a), "-Rl") == 0 ))
		{
			rflag = true;
			lflag = true;
		}
		else if(strcmp(v.at(a), "-alR") == 0 || (strcmp(v.at(a), "-aRl") == 0) || (strcmp(v.at(a), "-Ral") == 0) || (strcmp(v.at(a), "-Rla") == 0) ||
		(strcmp(v.at(a), "-lRa") == 0) || (strcmp(v.at(a), "laR") == 0))
		{
			rflag = true;
			lflag = true;
			aflag = true;
		}
			
	
	}

	if(!aflag && !rflag && !lflag)
	{
		noflags(directoryName);
	}
	if(lflag && !aflag && !rflag)
	{
		lflags(directoryName);
	}
	if(aflag && !lflag && !rflag)
	{
		aflags(directoryName);
	}
	if(!aflag && !lflag && rflag)
	{
		rflags(directoryName);
	}
	if(lflag && aflag && !rflag)
	{
		alflag(directoryName);
	}
	if(aflag && rflag && !lflag)
	{
		aRflags(directoryName);
	}
	if(rflag && lflag && !aflag)
	{
		rlflags(directoryName);
	}
	if(rflag && lflag && aflag)
	{
		allflags(directoryName);
	}
return 0;
}

