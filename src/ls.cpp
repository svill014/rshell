#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

//stat
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

using namespace std;

void fun(dirent *drentp, DIR *drp)
{
	//reversed what this ouput but it was not in the right order to begin 
	//with
	if(drentp = readdir(drp))
	{
		fun(drentp, drp);
		cout << drentp->d_name << endl;
	}
}




int main()
{
	char *dirName = ".";
	DIR *dirp;
	if (!(dirp  = opendir(dirName)))
	{
		cerr << "Error(" << errno << ") opening " << dirName << endl;
		return errno;
	}


	//delete after, made for testing
	char *dirName2 =".";
	DIR *dirp2;
	if (!(dirp2  = opendir(dirName2)))
        {
                cerr << "Error(" << errno << ") opening " << dirName2 << endl;
                return errno;
        }

	cout << endl;
	struct stat s;
	///-l
	cout << "\n-l\n\n";
	stat("a.out",&s);

	cout << "s.st_size = " << s.st_size << endl;
	cout << "\n-l\n\n";
	///


	dirent *direntp;
	dirent *direntp2;

	///-r
	cout << "\n-r\n\n";
	fun(direntp2, dirp2);
	/*while ((direntp2 = readdir(dirp2)))
        {
                cout << direntp2->d_name << endl;
                //recursively
        }*/
	cout << "\n-r\n\n";
	///
	while ((direntp = readdir(dirp)))
	{
		//not outputting in abc order
		cout << direntp->d_name << endl;
		// use stat here to find attributes of file
		
	}
	closedir(dirp);

	return 0;
}


