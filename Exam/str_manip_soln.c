#include "stdlib.h"
#include "stdio.h"
#include "string.h"
//The intended points of focus is basically getting students to figure out how to
//manipulate strings well, and the potential pitfalls in interacting with them.
//Write a function that returns a c style string that strips out any 
//puncuation as given by the following delimiting string
//DELIMITERS: '!.?, '

//Key point here is to think about how you can get size implicitly with c-style 
//strings. Possible question enhancement is to talk about a string with no null 
//terminator

//Give them this function prototype
char * delimit_string(char * original_string, char * delimiters)
{
	//Iterate over the original string to find its size.
	int original_string_size = 0;
	while(*(original_string+original_string_size)!=0)
	{
		original_string_size++;
	}
	//Iterate over delimiter string to find its size.
	int delimiters_size = 0;
	while(*(delimiters+delimiters_size)!=0)
	{
		delimiters_size++;	
	}
	//Remember to allocate memory -> Note that this is non-optimal use of space. 
	char * delimitedstring = malloc((original_string_size)*sizeof(char));
	
	//This part is trickier because of multiple delimiters. 
	int i = 0;
	int index =0 ;
	for(i=0; i<original_string_size;i++)
	{
		int j = 0;
		int has_char = 0;
		//Check to see if the char is part of the delimiting string. 
		for(j = 0; j<delimiters_size; j++)
		{
			if(*(original_string+i)==*(delimiters+j))
				has_char = 1;
		}
		//If so continue.
		if(has_char == 1)
			continue;
		else
		{
			//Otherwise, just print it. 
			memcpy(delimitedstring+index, original_string+i, sizeof(char));
			index++;
		}



	}
		return delimitedstring;
}

int main(int argc, char ** argv)
{
	char delimiters[] = "!.?, ";
	printf("%s\n", delimit_string("I am the walrus! So who are you?", delimiters));


	return 0;
}
