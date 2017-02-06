/* Example code for Think OS.
Copyright 2014 Allen Downey
License: GNU GPLv3
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    //Declares an array on the stack and int on the stack 
    int i;
    int array[SIZE];
    //Print pointer to said array. (still on stack)
    printf("%p\n", array);

    //Set values of arrays -> all values are still on stack.
    for (i=0; i<SIZE; i++) {
    array[i] = 42;
    }
    //Return pointer value. But also pop everything off the stack that is 
    //a part of the function, including the data associated with that part
    //of the stack -> no guarantees anymore. 
    return array;
}

void bar() {
    //Also declares an array and int. Given that there is no additional 
    //code that can alter the stack inbetween the calls of foo() and bar()
    //Then the memory locations of the following are likely to be the same 
    //memory location that was used for foo(). 
    int i;
    int array[SIZE];
    //Hence why we get the same value when we print this pointer. 
    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
    array[i] = i;
    }
}

int main()
{
    int i;
    //Trying to get a pointer to an array. 
    int *array = foo();
    // Calling a function and generating a local array probably. 
    bar();

    //Trying to print the array. 
    for (i=0; i<SIZE; i++) {
    printf("%d\n", array[i]);
    }

    return 0;
}