rshell.cpp
======

rshell is a command shell that runs on Linux and will execute the user's commands.  It reads commands on one line. The commands are read in the form ' commandName [argumentList] [&]. 'commandName' is an executable program in '$PATH' and 'argumentList' is a list of zero or more words seperated by whitespace. If '&' is at the end of the command, then it will not wait for the command to finish and return to step 1.

If exit is called, then the program will end. This works no matter what is after exit as long as there is whitespace right after exit. This will not work if exit is not right at the beginning of what the user inputed.

After you are in the directory rshell, the following steps can start the program.
Type [make]
	This will make an executable file named rshell in the folder bin and the executable ls in the same folder.
type [bin/rshell]
	This will start the first program.
type[bin/ls]
	This will start the second program

The user can tell that the program has started running if [username]@[hostname]$ can be seen. (username and hostname will be different depending on the user)


This program has a few bugs within it. The program will not be able to handle any input that normally has the '&' in it or be able to use any files with that character. The program will not understand the input if the & and the word before it has whitespace between them. The & will only work if it is in the argumentList and not the commandName. The program will not understand what to do with a file if it has spaces in it. The program will not understand the input if it has more than one whitespace at the end of it.

update to rshell.cpp
=====
rshell has been updated to include input redirection, output redirection, and piping.  Input redirection can be done by typing: [commandName] [argumentList] ">" [fileName]. fileName is the file you want to send the info to. This will replace any information in the file with the new text. By using ">>" instead of ">", the program will append the information instead of replacig it. There is a bug that makes any new files made using this method will have no permissions. Output redirection can be done by typing: [commandName] [argumentList] "<" [filename]. This will take the text in filename as the input for the program. Input redirection makes a file called '<' which has no permissions. This does not let me call input redirection again. Removing this file somes the problem, but it may output"<: No such file or directory". Input and output redirection can be combined with the following format: [commandName] [argumentList] "<" [fileNameIn] ">" [fileNameOut]. Piping only works with the format: [command1] [nothing] "|" [command2] [one argument here]. There is a bug with piping but typing in a few commands will solve it. Normally, it will freeze the program. This can be fixed with two commands. Typing in cntrl-z will exit the program. Typing fg will make the program run correctly again.

second update to rshell.cpp
=====
rshell now works with many different commands and not just ones in "/bin/". The only new bug is calling "cd" will output an error message even though it works. Calling cntr-C will now kill any program being run in rshell but will not close rshell. cntrl-Z does something similar, but puts the program in the background. rshell does not have a way to bring it back to the forground.

ls.cpp
=====
ls.cpp implements a subset of the GNU ls command. It supports the -l -a and -R flags and can pass in multiple files. The commands are read in the form bin/ls [flags] [files]. The flags and files can be mixed amongst each other and the program will still work as long as there are spaces between them. Flags can be written together, such as -la, and the program will still compile. The program will be unaffected if the flag or files are used multiple times. Executables are outputed to be blue, directories are green, and hidden files that can only be seen using the flag -a have a gray background.

There is a bug with files that have a '-' in the front of them. They will not be seen as flags and not files.

There is a bug with the flag -R and it would not run correctly but the program still recognizes that the user input the flag.


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
bin is a folder that is made if it does not already exist. It contains any executables that these programs may use once the user inputs the command [make]
