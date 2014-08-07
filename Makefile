
all :#rshell
	echo "building rshell"
	g++ -Wall -Werror -ansi src/main.cpp -o bin/rshell
