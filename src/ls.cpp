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


int main(int argv, char* argc[])
{
	
	bool l=false;
        bool a=false;
        bool R=false;
	for(int j=0; j<argv; j++)
	{
		if(argc[j][0]=='-')
		{
			for(int k=0; argc[j][k]!='\0'; k++)
			{
				if(argc[j][k]=='l')
					l=true;
				else if(argc[j][k]=='a')
                                        a=true;
				else if(argc[j][k]=='R')
                                        R=true;
			}
		}
	}


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
			if((l)&&(direntp->d_name[0]!='.'))
			{
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
			else
			{
				if(S_ISDIR(s.st_mode))
                                {
                                        color =1;
                                }
				if(mode&S_IXUSR)
				{
					if( color==0)
					{
						color =2;
					}
				}
				if(mode&S_IXGRP)
				{
					if( color==0)
					{
						color =2;
					}
					cout << 'x';
				}
				if(mode&S_IXOTH)
				{
					if( color==0)
					{
						color =2;
					}
					cout << 'x';
				}
				
				if(color==0)
				{
					if(direntp->d_name[0]!='.')
                                        {
                                                cout << direntp->d_name;
                                                printf("%c[%dm", 0x1B,39);
                                                printf("%c[%dm", 0x1B,49);
                                                cout << " ";
                                        }
				}
				else if(color==1)
				{
					printf("%c[%dm", 0x1B,34);
					if(direntp->d_name[0]!='.')
                                        {
                                                cout << direntp->d_name;
                                                printf("%c[%dm", 0x1B,39);
                                                printf("%c[%dm", 0x1B,49);
                                                cout << "/ ";
                                        }
				}
				else if(color==2)
				{
                                        printf("%c[%dm", 0x1B,32);
					if(direntp->d_name[0]!='.')
		                        {
                		                cout << direntp->d_name;
		                                printf("%c[%dm", 0x1B,39);
		                                printf("%c[%dm", 0x1B,49);
		                                cout << "* ";
                        		}
				}
				color =0;
				printf("%c[%dm", 0x1B,39);
				printf("%c[%dm", 0x1B,49);
			}
/*			if(direntp->d_name[0]!='.')
			{
				cout << direntp->d_name;
				printf("%c[%dm", 0x1B,39);
        	                printf("%c[%dm", 0x1B,49);
	                        cout << " ";

			}
*/		}
		else
		{
			if(l)
			{
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
			else
			{

				
				if(S_ISDIR(s.st_mode))
                                {
                                        color =1;
                                }
				if(mode&S_IXUSR)
				{
					if( color==0)
					{
						color =2;
					}
				}
				if(mode&S_IXGRP)
				{
					if( color==0)
					{
						color =2;
					}
					cout << 'x';
				}
				if(mode&S_IXOTH)
				{
					if( color==0)
					{
						color =2;
					}
					cout << 'x';
				}
				


				if(direntp->d_name[0]=='.')
				printf("%c[%dm", 0x1B,47);
			
				if(color==0)
				{
					if(direntp->d_name[0]=='.')
                	                	printf("%c[%dm", 0x1B,47);
		                        cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
                                        printf("%c[%dm", 0x1B,49);
                                        cout << " ";
				}
				else if(color==1)
				{
					if(direntp->d_name[0]=='.')
                		                printf("%c[%dm", 0x1B,47);
					printf("%c[%dm", 0x1B,34);
					cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
                                        printf("%c[%dm", 0x1B,49);
                                        cout << "/ ";
				}
				else if(color==2)
				{
					if(direntp->d_name[0]=='.')
                                                printf("%c[%dm", 0x1B,47);
                                        printf("%c[%dm", 0x1B,32);
                                        cout << direntp->d_name;
					printf("%c[%dm", 0x1B,39);
		                        printf("%c[%dm", 0x1B,49);
					cout << "* ";
				}
				color =0;
				printf("%c[%dm", 0x1B,39);
				printf("%c[%dm", 0x1B,49);
			}
		}
	}
	cout << endl << endl;

	closedir(dirp);

	return 0;
}


