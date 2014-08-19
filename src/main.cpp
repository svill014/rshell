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
		}/////////// added perror
		else
			user = getlogin();///////////////////////ask professor
		if(gethostname(mech,BUFSIZE)==-1)
		{
			perror("gethostname failed");
			exit(0);
		}/////////////////////// added perror
		
		cout <<user<<"@"<<mech<< "$ ";
		delete[] mech;

		string inpt="";
		if(!getline(cin,inpt) )
		{
			perror("getline failed");
			exit(0);
		}////////////////////////////////////// added perror
		string com="";
		string arg="";

		bool skip1=false;
		bool skip2=false;// used to help "<<<" and ">>" work

		for(unsigned i=0; i<inpt.size();i++)
		{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		cout << str2 << endl;
		cout << "input: "<< inpt << endl;
		cout << "commandName: "<<com<<endl;
		cout << "argumentList: "<<arg<<endl;
		////////////////////////////////////////////
		string temp="";
		char ** arg2;
		arg2 = new char*[BUFSIZE];
		int num=0;
		string  word="";
		arg2[0]=new char[str.size()+1];
		strcpy(arg2[num], str.c_str() );///////////////////////////////////////////////////////////////////////////////

		unsigned i=0;
		for(i=0; i<=arg.size(); i++)
		{
			if(arg[i]=='#')
			{
				
				strcpy(arg2[num+1], word.c_str() );//////////////////////////////////////////////////////////////////////////////////
				num++;
				word="";
				i=arg.size();
			}
			else if(i==arg.size()-1)
			{
				word=word+arg[i];
				arg2[num+1]=new char[word.size()+1];
				strcpy(arg2[num+1], word.c_str() );////////////////////////////////////////////////////////////
				num++;
				word="";
			}
			else if(isspace(arg[i]))/////////////////////////////////////////////////////////////////
			{
				if(i!=0)
				{
					if(!isspace(arg[i-1]))
					{
					arg2[num+1]=new char[word.size()+1];						strcpy(arg2[num+1], word.c_str() );////////////////////////////////////////////////////////////
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
		for(int j=1; j<=num; j++)
		{
			cout <<"::::" <<arg2[j]<<":::" << endl;
		}
		cout << endl;
		///////////////////////////////////////////////////////////
		
		vector<int> v;
		int cnt = 0;
		
		char ** arg3;
	        arg3 = new char*[BUFSIZE];


		cout << endl << cnt << ":"<<num << endl;
		//while(cnt<=num)
		//{
			cout << "::" << cnt << "::" << arg2[cnt] <<"::"<< num<< endl;
			int res=fork();
			v.push_back(res);
			string st="";
			if(res==-1)
			{
				perror("fork failed");
				exit(1);
			}
			if(res==0)
			{
				cout << arg2[1]<< "TTTTTTTTTTTTTT\n";
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
					arg2[1]="";
					arg3[1]="";
					arg2[2]="";
					arg3[2]="";
				}
				
				if(num>cnt)
					st=arg2[num-1];
			//	if(cnt==(num-1) )
			//	{
				if(st== ">")
				{
					int fd = open(arg2[num], O_WRONLY|O_CREAT);
					//bug, any new file will have only read permission
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
					for(int m=0;m<=num; m++)
                                        {
                                                arg3[m]=arg2[m];
                                        }
				}
			//	}
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
		//}
//			if(-1==wait(0))
//			{
//				perror("wait failed");
//				exit(1);
//			}
/////////////////////////
			/*if(( (cnt==(num-1)) )&&(arg2[num-1]==">") )
			{
				cout << "pasta" << endl;
				cout << arg2[cnt];
				if(arg2[cnt] == ">")
				{
					cout << "power" << endl;
/////////////////////////////////////////
					int fd = open(arg2[cnt+1], O_RDWR|O_CREAT);
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
				}
			}*/
	//		cnt++;
	//	}
	//	waitpid(v.at(0));



	
/*
		int res=fork();
		if(res==-1)
		{
			perror("fork failed");
			exit(1);
		}
		if(res==0)
		{
			///////////////////////////////////////
			
			
			///////////////////////////////
			
	//		if(f)
	//		{
	//			int res2=fork();
	//			if(res2==0)
	//			{
	//				cout << arg2[1]<<endl;
	//				if(arg2[2][0]=='>')
	//					cout << "found it\n";
	//				if(-1==execv(str2, arg2))
	//				{
	//					perror("execv failed");
	//					exit(0);
	//				}
//
//				}
//				ext=true;
//			}

			/////
			char ** arg3;
	                arg3 = new char*[BUFSIZE];
			/////
			


			bool norm = true;
			for(unsigned j=1; j<num; j++)
			{
				cout << "NNNNNNNNNNNNNNNNN" << endl;
				cout << arg2[j] << endl;
				string st = arg2[j];
				
				if(st=="<")
				{
					//norm=false;
					cout << "< < < < < < < < "<<endl;
					if(close(0)==-1)
					{
						perror("close failed");
						exit(1);
                                        }
					int fd = open(arg2[j+1], O_RDONLY|O_CREAT);
					if(fd==-1)
					{
						perror("open failed");
						exit(1);
					}
/////////////////////////////////////////////////
					int fd2=dup(fd);
					if(fd2==-1)
					{
						perror("dup failed");
						exit(1);
					}
					unsigned l=0;
					unsigned m=0;
					for(;m<j; m++, l++)
					{
						arg3[m]=arg2[m];
					}
					m=j+2;
					for(;m<=num;m++, l++)
					{
						arg3[l]=arg2[m];
					}
			//		if(-1==execv(str2,arg3))
			//		{
			//			perror("execv failed");
			//			exit(1);
			//		}
					arg2=arg3;
					j=1;
			//		arg2[j]="";
			//		arg2[j+1]="";
					cout << num << endl;
					num=num-2;
					cout << num << endl;
/////////////////////////////////////////////////
				}
				st=arg2[j];
				cout << "dfdfdfdf"<< endl<< st << endl;
				if(st==">")
				{
					norm=false;
					cout << "LLLLLLLLLLLLLLLLLLLLLL"<<endl;
					int res2=fork();
					if(res2==-1)
					{
						perror("fork failed");
						exit(1);
					}
					if(res==0)
					{
						int fd = open(arg2[j+1], O_RDWR|O_CREAT);
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
						
			//			if(-1==write(fd,"",1))
			//			{
			//				perror("write failed");
			//				exit(1);
			//			}
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
						for(unsigned k=0;k<j; k++)
						{
							arg3[k]=arg2[k];
						}
						if(-1==execv(str2,arg3))
						//does not work with <
						{
							perror("execv failed");
							exit(1);
						}
					}
					if(-1==wait(0))
					{
						perror("wait failed");
						exit(1);
					}
				}
			////////////////////////	
				else if(st==">>")//does it twice
				{
					cout << "TTTTTTTT" << endl;
					norm=false;
					cout << ">> >> >> >> >> >>"<<endl;
					int res2=fork();
					if(res2==-1)
					{
						perror("fork failed");
						exit(1);
					}
					if(res2==0)
					{
						int fd = open(arg2[j+1], O_RDWR|O_CREAT|O_APPEND);
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
						for(unsigned k=0;k<j; k++)
						{
							arg3[k]=arg2[k];
						}
						if(-1==execv(str2,arg3))
						{
							perror("execv failed");
							exit(1);
						}
					}
					if(-1==wait(0))
					{
						perror("wait failed");
						exit(1);
					}
					exit(0);
				}
			}
			if(norm)
			{
		cout << "afadfadf"<< endl;
				if(-1==execv(str2, arg2))
				//else if(-1==execv(str2, arg2))
				{
					perror("execv failed");
					exit(0);
				}
			}
		}
		if(-1==wait(0))
		{
			perror("waitddd failed");
			exit(1);
		}
		
	//	if(f)
         //       {
         //               wait(0);
         //       }
*/
		for(int i=0; i<BUFSIZE; i++)
		{
			if(arg2[i]=="")
				i=BUFSIZE;
			delete arg2[i];
		}
		if(ext==true)
			exit(0);
	}
	return 0;
}
