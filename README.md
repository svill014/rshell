rshell
======

rshell is a command shell that runs on Linux and will execute the user's commands.  It reads commands on one line. The commands are read in the form ' commandName [argumentList] [&]. 'commandName' is an executable program in '/usr/bin' and 'argumentList' is a list of zero or more words seperated by whitespace. If '&' is at the end of the command, then it will not wait for the command to finish and return to step 1.

If exit is called, then the program will end. This works no matter what is after exit as long as there is whitespace right after exit. This will not work if exit is not right at the beginning of what the user inputed.

After you are in the directory rshell, the following steps can start the program.
Type [make]
	This will make an executable file named rshell in the folder bin.
type [bin/rshell]
	This will start the program.

The user can tell that the program has started running if [username]@[hostname]$ can be seen. (username and hostname will be different depending on the user)

This program has a few bugs within it. The program will not be able to handle any input that normally has the '&' in it or be able to use any files with that character. The program will not understand the input if the & and the word before it has whitespace between them. The & will only work if it is in the argumentList and not the commandName. The program will not understand what to do with a file if it has spaces in it. The program will not understand the input if it has more than one whitespace at the end of it.

LICENSE
======
LICENSE is a text file that contains the text that is needed so others can use this code.

src
======
src is  a folder where the source code is located.

tests
======
tests is a folder that contains a script file that shows some examples of what can be done.

Makefile
======
Makefile contains the code that allows the command [make] to create an executable in the bin folder.

bin
======
bin starts as an empty folder(exept for the file test which exists so this folder can exist) but obtains an executable once the user inputs the command [make]
