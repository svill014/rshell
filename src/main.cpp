#include <iostream>
#include <unistd.h>
//#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 1024
using namespace std;


int main()
{
	string s ="";
	while (s!="exit")
	{
	//	cout << BUFSIZE<< endl;
		char *mech=new char[BUFSIZE];
		string user = getlogin();
		//put tests for getlogin and gethostname
		int h = gethostname(mech,BUFSIZE );
	//may cause a seg fault
	//have define bufsize 1024 at the top for  the max
	//char buf[bufsize]
	//or
	//char *mech = new char[bufsize]
	//delete[] mech;



		cout <<user<<"@"<<mech<< "$ ";
		delete[] mech;

		int numC=0;
		string inpt="";
		getline(cin,inpt);
		string com="";
		string arg="";
		for(int i=0; i<inpt.size();i++)
		{
			if(inpt[i]=='#')
			{
				i=inpt.size();
			}
			else if(inpt[i]==' ')
			{
				for(int j=i+1; j<inpt.size();j++)
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
	/*	while(arg!="")
		{
			while(arg[arg.size())
		}*/
		cout << "argumentList: "<<arg<<endl;
		cout << "last of arg:  " << arg[arg.size()-1] << endl;

	//	string* arg2;
		char ** arg2;
	//	arg2 = new string[BUFSIZE];
		arg2 = new char*[BUFSIZE];
//		arg2 = (char**)malloc(100);
		int num=0;
		string  word="";
//		arg2[0]=(char*)malloc(str.length()+1);
//		strcpy(arg2[0],str2.c_str() );
		arg2[0]=new char[str.size()+1];
		strcpy(arg2[num], str.c_str() );

		bool andFnd=false;
		for(int i=0; i<=arg.size(); i++)
		{
			if(arg[i]=='#')
			{
				
//				arg2[num+1]=(char*)malloc(str.length()+1);
//				strcpy(arg2[0],str2.c_str() );
				strcpy(arg2[num+1], word.c_str() );
				
				//arg2[num]=word;
				num++;
				word="";
				i=arg.size();
			}
			else if(i==arg.size()-1)
			{
				word=word+arg[i];
//				arg2[num+1]=(char*)malloc(str.length()+1);
//                              strcpy(arg2[0],str2.c_str() );

				arg2[num+1]=new char[word.size()+1];
				strcpy(arg2[num+1], word.c_str() );

				//arg2[num]=word;
				num++;
				word="";
			}
			else if(arg[i]==' ')
			{
//				arg2[num+1]=(char*)malloc(str.length()+1);
//                              strcpy(arg2[0],str2.c_str() );

				arg2[num+1]=new char[word.size()+1];
				strcpy(arg2[num+1], word.c_str() );

				//arg2[num]=word;
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
	//	cout << "OUTPUT THIS\n";
		cout << "><><><><><><><  " << num << "  ?|??|??|?|?|?|?|" << endl;
		int res=fork();
		if(res==0)
		{//does not work when it is looped
			if(-1==execv(str2, arg2))
			{
				perror("execv failed");
				exit(0);
			}
	//		if(-1==execl(str2,str2,NULL))
	//			perror("execl failed");
		}
		wait(0);
	//	cout<< "><> ><> ><> ><> ><>"<< endl;
		//delete[] mech;

	//	int cnt=0;
	/*	while(cnt<=num)
		{
			cout << "num/cnt:" << num << "/" << cnt << endl;
			cout << arg2[cnt] << endl;
			cnt++;
		}*/
		for(int i=0; i<BUFSIZE; i++)
		{
			if(arg2[i]=="")
				i=BUFSIZE;
		//	cout << "[" << i << "]:  " << arg2[i] << "\n____\n";
			delete arg2[i];
		}
/*		delete[] arg2;*/
	//	if(s=="exit")
		//	exit(0);
		cout << "END OF THE CODE\n\n\n><>\n\n";
	}
	return 0;
}
