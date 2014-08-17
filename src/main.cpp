#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
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
					cout << inpt.size()<< endl;
					cout << i << endl;
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
				////////////////////////////////
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
					else if(inpt[j]=='|')//|
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
		for(unsigned j=1; j<=num; j++)
		{
			cout << arg2[j] << endl;
		}
		cout << endl;
		///////////////////////////////////////////////////////////
		int res=fork();
		if(res==0)
		{
			if(f)
			{
				int res2=fork();
				if(res2==0)
				{
					if(-1==execv(str2, arg2))
					{
						perror("execv failed");
						exit(0);
					}

				}
				ext=true;
			}
			else if(-1==execv(str2, arg2))
			{
				perror("execv failed");
				exit(0);
			}
		}
		wait(0);
		if(f)
                {
                        wait(0);
                }

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
