
all :#rshell
	echo "building rshell"
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
