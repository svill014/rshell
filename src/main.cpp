#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
using namespace std;


int main()
{
	string s ="";
	while (s!="exit")
	{
		char *mech=new char[BUFSIZE];
		string user = getlogin();
		gethostname(mech,BUFSIZE );
		
		cout <<user<<"@"<<mech<< "$ ";
		delete[] mech;

		string inpt="";
		getline(cin,inpt);
		string com="";
		string arg="";
		for(unsigned i=0; i<inpt.size();i++)
		{
			if(inpt[i]=='#')
			{
				i=inpt.size();
			}
			else if(inpt[i]==' ')
			{
				for(unsigned j=i+1; j<inpt.size();j++)
				{
					if(inpt[j]=='#')
					{
						j=inpt.size();
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
		cout << str2 << endl;
		cout << "test\n";
		cout << "input: "<< inpt << endl;
		cout << "commandName: "<<com<<endl;
		string temp="";
		cout << "argumentList: "<<arg<<endl;
		cout << "last of arg:  " << arg[arg.size()-1] << endl;

		char ** arg2;
		arg2 = new char*[BUFSIZE];
		int num=0;
		string  word="";
		arg2[0]=new char[str.size()+1];
		strcpy(arg2[num], str.c_str() );

		for(unsigned i=0; i<=arg.size(); i++)
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
			else if(arg[i]==' ')
			{
				arg2[num+1]=new char[word.size()+1];
				strcpy(arg2[num+1], word.c_str() );
				num++;
				word="";
			}
			else
			{
				word=word+arg[i];
			}
		}
		

		int cnt=0;
	        while(cnt<=num)
		{
			cout << "num/cnt:" << num << "/" << cnt << endl;
			cout << arg2[cnt] << endl;
			cnt++;
		}
		int res=fork();
		if(res==0)
		{
			if(-1==execv(str2, arg2))
			{
				perror("execv failed");
				exit(0);
			}
		}
		wait(0);

		for(int i=0; i<BUFSIZE; i++)
		{
			if(arg2[i]=="")
				i=BUFSIZE;
			delete arg2[i];
		}
		cout << "END OF THE CODE\n\n\n><>\n\n";
	}
	return 0;
}
