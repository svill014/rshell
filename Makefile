all :#rshell
	echo "updating/making bin folder"
	([ ! -d bin ] && mkdir bin)||[ -d bin ]
	echo "building rshell"
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
	echo "building ls"
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls
bin:
	echo "updating/making bin folder"
	[ ! -d bin ] && mkdir bin
target2:
	echo "building ls"
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls
