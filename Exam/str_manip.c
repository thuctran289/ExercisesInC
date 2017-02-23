#include "stdlib.h"
#include "stdio.h"
#include "string.h"
//The intended points of focus is basically getting students to figure out how to
//manipulate strings well, and the potential pitfalls in interacting with them.
//Write a function that returns a c style string that strips out any 
//puncuation as given by the following delimiting string
//DELIMITERS: "!.?,"


char * delimit_string(char * original_string, char * delimiters)
{
		//Your Code here
}

int main(int argc, char ** argv)
{
	char delimiters[] = "!.?, ";
	printf("%s\n", delimit_string("I am the walrus! So... anyway, Who are you?", delimiters));


	return 0;
}
