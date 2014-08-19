#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
using namespace std;
    
bool ext=false;

int main()
{
	string s ="";
	while (s!="exit")
	{
		char *mech=new char[BUFSIZE];
		string user;
		if(( getlogin() )==NULL)
		{
			perror("getlogin failed");
                        exit(0);
		}
		else
			user = getlogin();
		if(gethostname(mech,BUFSIZE)==-1)
		{
			perror("gethostname failed");
			exit(0);
		}
		
		cout <<user<<"@"<<mech<< "$ ";
		delete[] mech;

		string inpt="";
		if(!getline(cin,inpt) )
		{
			perror("getline failed");
			exit(0);
		}
		string com="";
		string com2="";
		string arg="";

		bool skip1=false;
		bool skip2=false;// used to help "<<<" and ">>" work

		for(unsigned i=0; i<inpt.size();i++)
		{
			if(inpt[i]=='#')
			{
				i=inpt.size();
			}
			else if( (isspace(inpt[i])) || (inpt[i]=='<')|| (inpt[i]=='>')|| (inpt[i]=='|'))
			{
				if(inpt[i]=='<')//< or <<<
				{
					if(inpt.size()-i >=3)
					{
						if( (inpt[i+1]=='<')&&(inpt[i+2]=='<' ))
						{
							skip2=true;
							arg= " <<< ";
						}
						else
						{
							arg = " < ";
						}
					}
					else
						arg = " < ";
				}
				else if(inpt[i]=='>')//> or >>
				{
					if(inpt.size()-i >=2)
					{
						if(inpt[i+1]=='>')
						{
							skip1=true;
							arg= " >> ";
						}
						else
						{
							arg = " > ";
						}
					}
					else
						arg = " > ";
				}
				else if(inpt[i]=='|')// |
				{
					arg = " | ";
				}
				for(unsigned j=i+1; j<inpt.size();j++)
				{
					if(skip2)
					{
						skip2=false;
						j=j+2;
					}
					if(skip1)
					{
						skip1=false;
						j++;
					}
					if( inpt[j]=='#')
					{
						j=inpt.size();
					}
					else if(inpt[j]=='<')//< or <<<
					{
						if(inpt.size()-j >=3)
						{
							if( ((inpt[j+1])=='<')&&(inpt[j+2]=='<') )
							{
								arg=arg+ " <<< ";
								j=j+2;
							}
							else
							{
								arg =arg+" < ";
							}
						}
						else
							arg = arg+ " < ";
					}
					else if(inpt[j]=='>')//> or >>
					{
						if(inpt.size()-j >=2)
						{
							if ((inpt[j+1])=='>')
							{
								arg=arg+ " >> ";
								j=j+1;
							}
							else
							{
								arg =arg+" > ";
							}
						}
						else
							arg = arg+ " > ";
					}
					else if(inpt[j]=='|')// |
					{
						arg = arg+ " | ";
					}
					else
					{
						arg=arg+inpt[j];
					}
				}
				i=inpt.size();
			}
			else
			{
				com=com+inpt[i];
			}
		}
		if(com=="exit")
		{
			s="exit";
			exit (0);
		}
		string str="/bin/";
		str = str + com;
		const char* str2 =str.c_str();
		////////////////////////////////////////////
	//	cout << str2 << endl;
	//	cout << "input: "<< inpt << endl;
	//	cout << "commandName: "<<com<<endl;
	//	cout << "argumentList: "<<arg<<endl;
		////////////////////////////////////////////
		string temp="";
		char ** arg2;
		arg2 = new char*[BUFSIZE];
		int num=0;
		string  word="";
		arg2[0]=new char[str.size()+1];
		strcpy(arg2[num], str.c_str() );

		unsigned i=0;
		for(i=0; i<=arg.size(); i++)
		{
			if(arg[i]=='#')
			{
				
				strcpy(arg2[num+1], word.c_str() );
				num++;
				word="";
				i=arg.size();
			}
			else if(i==arg.size()-1)
			{
				word=word+arg[i];
				arg2[num+1]=new char[word.size()+1];
				strcpy(arg2[num+1], word.c_str() );
				num++;
				word="";
			}
			else if(isspace(arg[i]))
			{
				if(i!=0)
				{
					if(!isspace(arg[i-1]))
					{
					arg2[num+1]=new char[word.size()+1];
					strcpy(arg2[num+1], word.c_str() );
						num++;
						word="";
					}
				}
			}
			else
			{
				word=word+arg[i];
			}
		}
		bool f=false;
		for(unsigned j=0;f==false&&arg2[num][j]!='\0'; j++)
		{
			if(arg2[num][j]=='&')
			{
				f=true;
				arg2[num][j]='\0';
			}
			else if(isspace(arg2[num][j]))
			{
				arg2[num][j]='\0';
				j--;
			}
			
		}
		//////////////////////////////////////////////////////////
	//	for(int j=1; j<=num; j++)
	//	{
	//		cout <<"::::" <<arg2[j]<<":::" << endl;
	//	}
	//	cout << endl;
		///////////////////////////////////////////////////////////
		
		vector<int> v;
		int cnt = 0;
		
		char ** arg3;
	        arg3 = new char*[BUFSIZE];
		char ** arg4;
                arg4 = new char*[BUFSIZE];
		


		int pfd[2];
		string str3="/bin/";
		//cout << endl << cnt << ":"<<num << endl;
		//while(cnt<=num)
		//{
			int res=fork();
			string st="";
			bool  st2=false;
			if(res==-1)
			{
				perror("fork failed");
				exit(1);
			}
			v.push_back(res);
			if(res==0)
			{
			//	for(int j=1; j< num; j++)
			//	{
			//		st=arg2[j];
					if(num>1)//
						st=arg2[1];//
					if(st=="|")
					{
						//com2=arg2[j+1];
						com2=arg2[2];
						st2=true;
						pipe(pfd);
						int pid1=fork();
						if(pid1==-1)
						{
							perror("fork failed");
							exit(1);
						}
						if(pid1==0)
						{
							close(1);/////////////////////////////error check this
							dup(pfd[1]);
							for(int k=0; k<num-2; k++)
							{
								arg3[k]=arg2[k];
							}
							execv(str2, arg3);
							//execlp("ls", "ls", NULL);
							//abort();
						}
						else
						{
							close(0);
							dup(pfd[0]);
							string s1=arg2[num-1];
							s1="/bin/" + s1;
							
							char* s2;// =s1.c_str();
							strcpy(s2, s1.c_str() );
							arg4[0]=s2;
							arg4[1]=arg2[num];
							execv(s2, arg4);
							//abort();//////////////////////////////program freezes, this only works for ls | grep i
						}
						wait(0);
					}
				if(num>1)
				{
					st=arg2[1];
				}
				if(st== "<")
				{
					int fd = open(arg2[1], O_RDONLY|O_CREAT);
					if(fd==-1)
					{
						perror("open failed");
						exit(1);
					}
					if(close(0)==-1)
                                        {
                                                perror("close failed");
                                                exit(1);
                                        }
                                        int fd2=dup(fd);
                                        if(fd2==-1)
                                        {
                                                perror("dup failed");
                                                exit(1);
                                        }
				}
				
				if(num>cnt)
					st=arg2[num-1];
			//	if(cnt==(num-1) )
			//	{
				if(st== ">")
				{
					int fd = open(arg2[num], O_WRONLY|O_CREAT);
					//bug, any new file will have no permissions
					if(fd==-1)
					{
						perror("open failed");
						exit(1);
					}
					if(-1==ftruncate(fd, 1) )
					{
						perror("ftruncate failed");
						exit(1);
					}
					if(close(1)==-1)
					{
						perror("close failed");
						exit(1);
					}
					int fd2=dup(fd);
					if(fd2==-1)
					{
						perror("dup failed");
						exit(1);
					}
					for(int k=0;k<num-1; k++)
					{
						arg3[k]=arg2[k];
					}
				}
				else if(st==">>")
				{
					int fd = open(arg2[num], O_WRONLY|O_CREAT|O_APPEND);
					//bug, any new file will not have any permission
					if(fd==-1)
					{
						perror("open failed");
						exit(1);
					}
					if(close(1)==-1)
					{
						perror("close failed");
						exit(1);
					}
					int fd2=dup(fd);
					if(fd2==-1)
					{
						perror("dup failed");
						exit(1);
					}
					for(int k=0;k<num-1; k++)
					{
						arg3[k]=arg2[k];
					}
				}
				else
				{
					if(!st2)
						for(int m=0;m<=num; m++)
                                        	{
                                                	arg3[m]=arg2[m];
	                                        }
				}
			//	}
				cerr <<"\nThis is the end\n\n";
				if(-1==execv(str2, arg3))
				{
					perror("execv failed");
					exit(0);
				}
			}
			else
			{
				//if(v.size()==1)
			//		cnt=num;
				if(-1==waitpid(v.at(0),0,WUNTRACED | WCONTINUED) )
				{
					perror("waitpid failed");
					exit(1);
				}
			}
			cnt++;
		for(int i=0; i<BUFSIZE; i++)
		{
			if(arg2[i]=="")
				i=BUFSIZE;
			delete arg2[i];
		}
	/*	for(int i=0; i<BUFSIZE; i++)
		{
			if(arg3[i]=="")
				i=BUFSIZE;
			delete arg3[i];
		}
		for(int i=0; i<BUFSIZE; i++)
		{
			if(arg4[i]=="")
				i=BUFSIZE;
			delete arg4[i];
		}*/
		if(ext==true)
			exit(0);
	}
	return 0;
}
