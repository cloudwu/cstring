test : test.c cstring.c 
	gcc -g -Wall -march=i686 -o $@ $^
