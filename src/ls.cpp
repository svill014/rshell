#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <pwd.h>

//color
#include <cstdio>

//stat
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

using namespace std;


int main()
{
	bool l=true;
        bool a=false;
        bool R=false;


	char *dirName = ".";
	DIR *dirp;
	if (!(dirp  = opendir(dirName)))
	{
		cerr << "Error(" << errno << ") opening " << dirName << endl;
		return errno;
	}


	cout << endl;
	struct stat s;
	///-l
	cout << "\n-l\n\n";
	stat("a.out",&s);
	///
//	cout << s.st_dev;     /* ID of device containing file */
//	cout << s.st_ino;     /* inode number */
	int mode = s.st_mode;
int color =0;//if 1 it will be blue, if 2 it will be green
if(l)
{
	//if d then make the color = 1 (blue)
	cout << '-';
	if(mode&S_IRUSR)
		cout << 'r';
	else
		cout << '-';
	if(mode&S_IWUSR)
                cout << 'w';
        else 
                cout << '-';
	if(mode&S_IXUSR)
	{
		if( color==0)
		{
			color =2;
		}
                cout << 'x';
	}
        else 
                cout << '-';
	if(mode&S_IRGRP)
                cout << 'r';
        else 
                cout << '-';
        if(mode&S_IWGRP)
                cout << 'w';
        else 
                cout << '-';
        if(mode&S_IXGRP)
        {
                if( color==0)
                {
                        color =2;
                }
                cout << 'x';
        }
        else
                cout << '-';
	if(mode&S_IROTH)
                cout << 'r';
        else
                cout << '-';
        if(mode&S_IWOTH)
                cout << 'w';
        else
                cout << '-';
        if(mode&S_IXOTH)
        {
                if( color==0)
                {
                        color =2;
                }
                cout << 'x';
        }
        else
                cout << "- ";

	///user id/name?

	struct passwd *name;
        if (getpwuid(s.st_uid)==NULL)
        {
               	perror("getpwuid failed");
		exit(0);
        }
        name = getpwuid(s.st_uid);
	cout << name->pw_name<< endl;

	///
	cout << "color: " << color << endl;
	color =0;
}	/* protection */
//	cout << s.st_nlink;   /* number of hard links */
//	cout << s.st_uid;     /* user ID of owner */
//	cout << s.st_gid;     /* group ID of owner */
//	cout << s.st_rdev;    /* device ID (if special file) */
//	cout << s.st_size;    /* total size, in bytes */
//	cout << s.st_blksize; /* blocksize for file system I/O */
//	cout << s.st_blocks;  /* number of 512B blocks allocated */
//	cout << s.st_atime;   /* time of last access */
//	cout << s.st_mtime;   /* time of last modification */
//	cout << s.st_ctime;
	///
	cout << endl;
	cout << "s.st_size = " << s.st_size << endl;
	cout << "\n-l\n\n";
	///


	dirent *direntp;
	

/*
	while ((direntp = readdir(dirp)))
	{
		if(!a)
		{
			if(direntp->d_name[0]!='.')
			{
				cout << direntp->d_name;
				printf("%c[%dm", 0x1B,39);
        	                printf("%c[%dm", 0x1B,49);
	                        cout << " ";

			}
		}
		else
		{
			
			//if executable then green
				//printf("%c[%dm", 0x1B,32);
			//if folder then blue
				//printf("%c[%dm", 0x1B,34);
			if(direntp->d_name[0]=='.')
				printf("%c[%dm", 0x1B,47);
			cout << direntp->d_name;
		// use stat here to find attributes of file
			printf("%c[%dm", 0x1B,39);
			printf("%c[%dm", 0x1B,49);
			cout << " ";
		}
	}
	cout << endl << endl;
*/
	closedir(dirp);

	return 0;
}


