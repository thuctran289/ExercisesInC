/*
Author: Thuc Tran

Refactored version of cards program. 
The focus of refactoring was trying to follow a mindset of minimizing memory 
usage via pointers. 

*/

#include <stdio.h>
#include <stdlib.h>

//Defining a bool type for convenience. 
typedef int bool;
#define true 1
#define false 0
//Creating a global variable, although this is g
bool flag = false;

/* Prompts the user for a card_name input. 
card_name is the output returned. 
*/
void get_card(char* card_name){
	puts("Enter the card_name: ");
	scanf("%2s",card_name);
}

/* Converts a card_name array into an actual value. 
K,Q,J, = 10. A = 11. 
Values that are not the above, nor within the bounds 1-10 are invalid, and 
return a value of zero.
This also frees the card_name memory usage. 
*/
int get_card_val(char* card_name, bool* flag){
	int val = 0;
	switch(card_name[0])
		{
			case 'K':
			case 'Q':
			case 'J':
				val = 10;
				break;
			case 'A':
				val = 11;
				break;
			case 'X':
				*flag = true;
				break;
			default:
				val = atoi(card_name);
				if((val<1)||(val>10)){
					puts("I don't understand that value!");
					val = 0;
				}
		}
	return val;}

/* Changes the count based on the value of val. 
If val is within range 3-6, this increases the count. 
Otherwise, if val == 10, this decreases the count. 
*/ 
void count_cards(int *count, int val){

	if ((val>2) && (val <7)){
		(*count)++;
	} else if(val == 10){
		(*count) --;
	}
	printf("Current Count: %i\n", *count);	
}

int main()
{
	//Allocating some memory a pointer for card_name. 
	// Issues w/ trying to set up card_name as an independant thing. 
	char* card_name = (char *) malloc(sizeof(char)*2);
	int* count = (int *) malloc(sizeof(int));
	bool* flag = (bool*) malloc(sizeof(bool));
	*flag = false;
	//Continue looping through the program.
	while(*flag == false){
		get_card(card_name);
		count_cards(count, get_card_val(card_name, flag));	
	}

	//Cleaning up flag memory usage prior to program end. 
	free(flag);
	free(count);
	free(card_name);
	return 0;

}