#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <signal.h>


using namespace std;
    
bool ext=false;
int res=-1;


void pc(int x)
{
	if(res==-1)
	{
	}
	else if(res!=0)
	{
		kill(res, 0);
	}
}

void pz(int x)
{
	if(res==-1)
        {
        }
        else if(res!=0)
        {
                kill(res, SIGSTOP);
        }
       // pid_t pid = getpid();
	//kill(pid,SIGSTOP);
}


int main()
{
	res=-1;
	signal(SIGINT, pc);
        signal(SIGTSTP, pz);
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

/////////////////////////////////////////////////////////////////
		bool cd =false;
		if(com=="cd")// does not work for just cd
		{
			cd=true;
			int argSize=arg.size()+1;
			//char dir[argSize];
			char dir[BUFSIZE];
			dir[argSize]='\0';
			for(unsigned i=0; i<arg.size(); i++)
			{
				dir[i]=arg.at(i);
			}
			dir[arg.size()] = '\0';
			if (arg.size()==0)
			{
				if(chdir(getenv("HOME"))==-1)
                        	{
                                	perror("cannot open:");
				}
			}
			if(chdir(dir)==-1)
			{
				perror("cannot open:");
			}
		}
		string str="";//"/bin/";
/////////////////////////////////////////iwanttobehere
		if(getenv("PATH")==NULL)
		{
			perror("getenv failed:");
			exit(1);
		}
		string path1=getenv("PATH");
		string path2[BUFSIZE];
//		strcpy(arg2[num], str.c_str() );

		int pathNum=0;
		for(unsigned i=0; i<path1.size(); i++)
		{
			if(path1.at(i)==':')
                        {
                                pathNum++;
                        }
                        else
                        {
                                path2[pathNum]=path2[pathNum]+path1.at(i);
                        }
		}
		bool inPath=false;
		string str0="";
		for(int i=0;(  (i<=pathNum)&&(!inPath) ) ; i++)
		{
			str0=path2[i];
			if(str0.at(str0.size()-1 ) != '/')
                                str0=str0+'/';
			str0=str0+com;
			if(access(str0.c_str(), X_OK) ==0)
			{
                                inPath=true;
                                pathNum=i;
			}
			else if ((i==pathNum)&&(inPath))//ask professor about this part
			{
				perror("command not found");
			}
		}
		if(!inPath)
		{
		}
		else
		{
			str=str0;
		}
/////////////////////////////////////////
		if(!inPath)
			str = str + com;
		const char* str2 =str.c_str();
		////////////////////////////////////////////
	/*	cout << str2 << endl;
		cout << "input: "<< inpt << endl;
		cout << "commandName: "<<com<<endl;
		cout << "argumentList: "<<arg<<endl;
	*/	////////////////////////////////////////////
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
		string str3="";//"/bin/";
		//cout << endl << cnt << ":"<<num << endl;
		//while(cnt<=num)
		//
			res=fork();
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
			//	
			//		st=arg2[j];
					if(num>1)//
						st=arg2[1];//
					if(st=="|")
					{
						com2=arg2[2];

						st2=true;
						if(-1==pipe(pfd))
						{
							perror("pipe failed");
							exit(1);
						}
						int pid1=fork();
						if(pid1==-1)
						{
							perror("fork failed");
							exit(1);
						}
						if(pid1==0)
						{
							if(close(1)==-1)
                		                        {
		                                                perror("close failed");
                                                		exit(1);
		                                        }
							int fd3 =dup(pfd[1]);
							if(fd3==-1)
                                		        {
                		                                perror("dup failed");
		                                                exit(1);
                                        		}
							for(int k=0; k<num-2; k++)
							{
								arg3[k]=arg2[k];
							}
							if (-1==execv(str2, arg3))
							{
                        			                perror("execv failed");
			                                        exit(0);
			                                }
						}
						else
						{
							if (close(0)==-1)
							{
								perror("close failed");
								exit(1);
							}
							int fd3 = dup(pfd[0]);
							if(fd3==-1)
                                                        {
                                                                perror("dup failed");
                                                                exit(1);
                                                        }
							string s1=arg2[num-1];
							//s1="/bin/" + s1;
							/////////////////////////////////////////////////////////////////////////////////////
		if(getenv("PATH")==NULL)
		{
			perror("getenv failed:");
			exit(1);
		}
		string path3=getenv("PATH");
		string path4[BUFSIZE];
//		strcpy(arg2[num], str.c_str() );

		int pathNum2=0;
		for(unsigned i=0; i<path3.size(); i++)
		{
			if(path3.at(i)==':')
                        {
                                pathNum2++;
                        }
                        else
                        {
                                path4[pathNum2]=path4[pathNum2]+path3.at(i);
                        }
		}
		bool inPath2=false;
		string str00="";
		for(int i=0;(  (i<=pathNum2)&&(!inPath2) ) ; i++)
		{
			str00=path4[i];
			if(str00.at(str00.size()-1 ) != '/')
                                str00=str00+'/';
			//str00=str00+com;/////////////////////////////////////////////////////////////////////////////
			str00=str00+s1;
			if(access(str00.c_str(), X_OK) ==0)
			{
                                inPath2=true;
                                pathNum=i;
			}
			else if ((i==pathNum2)&&(inPath))//ask professor about this part
			{
				perror("command not found");
			}
		}
		if(!inPath2)
		{
		}
		else
		{
			//str3=str00;
			s1=str00;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////iwanttobehere
							char* s2="";
							char c[BUFSIZE];
							c[s1.size()+1]='\0';
							s2=c;
							copy(s1.begin(), s1.end(), c);
							c[s1.size()] = '\0';
							arg4[0]=s2;
							arg4[1]=arg2[num];
							if(-1==execv(s2, arg4))
							{
                                                                perror("execv failed");
                                                                exit(1);
                                                        }
							//program freezes but will work if the user types cntrl z and then fg, This only works for the format [command] [nothing] | [command] [one argument here]
						}
						wait(0);
					}
					wait(0);
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
					if(remove("<")!=0) //bug, input redirection makes a file called '<' which has no permissions. This does not let me call input redirection again. Removing this file somes the problem, but it may output"<: No such file or directory"
					{
						perror("remove failed");
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
			//	cerr <<"\nThis is the end\n\n";
					if(-1==execv(str2, arg3))
					{
						if(!cd)
							perror("execv failed");
						exit(0);
					}
			}
			else 
			{
				if(-1==waitpid(v.at(0),0,WUNTRACED | WCONTINUED) )
				{
					perror("waitpid failed");
					exit(1);
				}
			}
			cnt++;
		if(ext)
			exit(0);
	}
	return 0;
}
