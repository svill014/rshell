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
        bool a=true;
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
//	stat("a.out",&s);
//	int mode = s.st_mode;
	int color =0;//if 1 it will be blue, if 2 it will be green

	dirent *direntp;
	


	while ((direntp = readdir(dirp)))
	{
		stat(direntp->d_name,&s);
	        int mode = s.st_mode;
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
			if(l)
			{
				//if d then make the color = 1 (blue)
				//cout << '-';
				//if(S_ISDIR)
				if(S_ISDIR(s.st_mode))
                                {
                                        color =1;
                                        cout << 'd';
                                }
                                else
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
					cout << '-';

				cout << " " << s.st_nlink << " ";
				struct passwd *name;
				if (getpwuid(s.st_uid)==NULL)
				{
					perror("getpwuid failed");
					exit(0);
				}
				name = getpwuid(s.st_uid);
				cout << name->pw_name<<" ";
				
				string temp = name->pw_dir;
				string temp2="";
				int slash =0;
				int i=0;
				while(slash<3)
				{
					if(temp[i]=='/')
					{
						slash++;
					}
					else if(slash==2)
					{
						temp2=temp2+temp[i];
					}
					i++;
				}
				cout << temp2 << ' ';
				int size=s.st_size;
				if(size>10000)
					cout << size << ' ';
				else if (size>=1000)
					cout <<" " << size << ' ';
				else if (size>=100)
					cout <<"  " << size << ' ';
				else if (size>=10)
					cout <<"   " << size << ' ';
				else if (size>=0)
					cout <<"    " << size << ' ';
				struct tm* time;
				char buff[20];
				time = localtime(&(s.st_mtime));
				strftime(buff,20, "%b %d %H:%M", time);
				printf("%s",buff);
				cout << ' ';
				if(color==0)
				{
					if(direntp->d_name[0]=='.')
                	                	printf("%c[%dm", 0x1B,47);
		                        cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
                                        printf("%c[%dm", 0x1B,49);
                                        cout << "\n";
				}
				else if(color==1)
				{
					if(direntp->d_name[0]=='.')
                		                printf("%c[%dm", 0x1B,47);
					printf("%c[%dm", 0x1B,34);
					cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
                                        printf("%c[%dm", 0x1B,49);
                                        cout << "/\n";
				}
				else if(color==2)
				{
					if(direntp->d_name[0]=='.')
                                                printf("%c[%dm", 0x1B,47);
                                        printf("%c[%dm", 0x1B,32);
                                        cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
		                        printf("%c[%dm", 0x1B,49);
					cout << "*\n";
				}
				color =0;
			}
		/*	
			if(direntp->d_name[0]=='.')
				printf("%c[%dm", 0x1B,47);
			cout << direntp->d_name;
		// use stat here bbto find attributes of file
			printf("%c[%dm", 0x1B,39);
			printf("%c[%dm", 0x1B,49);
			cout << " ";*/
		}
	}
	cout << endl << endl;

	closedir(dirp);

	return 0;
}


