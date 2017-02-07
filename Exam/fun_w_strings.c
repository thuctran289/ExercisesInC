//For the following code, print the output, and approximate locations in memory for each 
//variable that begins with an s!
//Most of this should be doable using HFC2.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * s1 = "hello world1";
char s2[] = "hello world2";

char * foo(char str[]){
	char * data = malloc(sizeof(str));
	memcpy(data, str, sizeof(str));

	return data;
}

char * bar(){
	char * data = "hello";
	return data;
}



int main(int argc, char ** argv)
{
	char * s3 = "Oh hello world3";
	char s4[] = "Oh hello world4";
	printf("%s\n",s2);
	printf("%d\n", sizeof(s3));
	printf("%d\n", sizeof(s4));
	char * s5 = foo(s3);
	char * s6 = foo(s4);
	printf("%s\n", s5);
	printf("%s\n", s6);
	char * s7 = bar();
	printf("%s\n", s7);

	return 0;
}
