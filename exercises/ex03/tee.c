//Thuc Tran, tee.c implementation

// Some notes for comparison against professional code, as given in the following:
//https://opensource.apple.com/source/shell_cmds/shell_cmds-81/tee/tee.c
//One key thing that was noticable is that the professional implmemntation used a linked list 
//structure to deal w/ both file descriptors + name in one element Furthermore,  they have more
//error handling, which is probably something that I should definitely take care of more 
//considering the cases of production code. 
//The implementation in terms of options was similar, but the implementation in terms of reading 
//was different in that the professional implementation used read, wheras I used fgets. 
//Definitely, the main overall difference that I am noticing is that the professional implementation
//deals w/ a lot more error handling and handles things with more portable approach, and a more linked_list oriented structure.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define TRUE 0
#define FALSE 1

int main(int argc, char ** argv)
{
	//Declar a buffer + a character for options. 
	char ch;
	char buffer[BUFSIZ];
	// Declare a variable to store setting for append flag option
	int appendSetting = FALSE;
	// Iterator variable used in loops
	int j = 0;
	//Code for dealing w/ options. Only option in this case is a.
	//Surprisingly effective, and worked out of box. 
	while((ch = getopt(argc, argv, "a")) != EOF){
		switch(ch)
		{
			case 'a': 
				appendSetting = TRUE;
				break;
			default:
				break;
		};
	}
	//setting the indexes of the arguments to exclude options. 
	argc -= optind;
	argv += optind;

	int x = 0;
	//alocating space for storing all the file streams
	FILE ** files = malloc(sizeof(FILE*) * argc);
	//setting up the file streams
	for(x; x<argc; x++)
		{
			if(appendSetting)
			{
				*(files+x) = fopen(argv[x], "w");
			}
			else{
				*(files+x) = fopen(argv[x], "wa");
			}
		}

	// While not EOF or other interrupts, write to filestreams + stdout
	//Not a lot of experience using stdout + input outputs, so this took a bit
	// of time to try to figure out the ideal way of handling 
	while(fgets(buffer, BUFSIZ, stdin)!= 0)
	{
		j = 0;
		printf("%s\n", buffer);
		for(j; j<x; j++)
		{	
			//Most errors here, previously used x, instead of j -> cauased 
			//lots of segfaults. When I figured that out, I fixed it. 
			fprintf(*(files+j), "%s", buffer);
		}

	}
	//Close files streams when done. 
	j = 0;
	for(j; j<x; j++)
	{
		fclose(*(files+j));
	}
	//Clean up memory. yy
	free(files);
	return 0;
}