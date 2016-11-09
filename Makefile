test : test.c cstring.c 
	gcc -g -Wall -o $@ $^
