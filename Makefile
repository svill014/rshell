all :#rshell
	echo "building rshell"
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
	echo "building ls"
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls
target2:
	echo "building ls"
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls
