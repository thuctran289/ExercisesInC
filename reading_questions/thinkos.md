## Chapter 1


### Compilation

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.
	Variable names exist at run time for in interpreted langauges. You can also run code in a live way by typing additional lines of code in the interpreter. 

2) Name two advantages of static typing over dynamic typing.
	Can identify what type a variable is by looking at the program.
	More space efficient due to not having to store variable names in memory. 
3) Give an example of a static semantic error.
	Calling a function in your code with the wrong number of arguments (say you call an addition function with only one argument) is a static semantic error.

4) What are two reasons you might want to turn off code optimization?
	If you want to compile something very quickly then you might want to turn it off. Or if you have a subtle bug in the program then optimization can affect the visibility of the bug.  

5) When you run `gcc` with `-S`, why might the results look different on different computers?
	Different computers can have different assembly instructions to implement the code as a consequence of having different ISAs.

6) If you spell a variable name wrong, or if you spell a function name wrong, 
the error messages you get might look very different.  Why?
If you get a variable name wrong, then you get an error on compile time due to the program not knowing where to find it/what it is. (unless you have another similarly spelled variable that was actually declared). In contrast, if you mispell the function name, then you get an error when you try to link everything together in the linker. Basically the difference is due to how the program replaces the variable names with a specific memory address for static memory at compile time, hence the need for the declaration, whereas a function handle can just exist in the code, with the assumption that the linker can deal with interfacing the function handle with the actual body of the function later on. 

7) What is a segmentation fault?
A segfault is when you try to read and write to an invalid place in memory. (e.g. after the break point in the heap)

## Chapter 2


### Processes

1) Give a real-world example of virtualization (ideally not one of the ones in the book).
A form of virtualization is the network of people in a national professional organization. While an individual can more immediately get into contact with people at their local chapter, their effective network of people they can contact can virtually spans the entire country. 

2) What is the difference between a program and a process?
A process represents a set of data, program text, and interactions with hardware that can run independantly of other processes. Programs form the instructions and methods that a process can use, and generally a process will run one program at a time. 

3) What is the primary purpose of the process abstraction?  What illusion does the process abstraction create?

It basically lets each process pretend that it is running on its own dedicated processor, hence generally allowing the process to not have to worry about how other programs are interrupting and using the hardware. This abstraction also lets the operating system be the core mediator/scheduler/orchestrator for the distribution of shared resources on the device while letting the programs keep their illusion.

4) What is the kernel?
It is the part of the operating system responsible for handling things like thread creation, process abstraction, syscalls, etc. 

5) What is a daemon?
 A daemon is a process that runs in the background of the operating system and provides useful services for the operating system.

## Chapter 3


### Virtual memory

1) The Georgian alphabet has 33 letters.  How many bit are needed to specify a letter?
6 bits.

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  
Ignoring the details of the encoding scheme, how many different characters can be represented?
2^32 different characters

3) What is the difference between "memory" and "storage" as defined in Think OS?
Memory is the volatile memory which is lost when the computer is shut down -> see ram and such.
Storage corresponds to the information that is stored on a hard drive disk or solid state drive and is not lost when the computer is reset. (Hence this means that the data is able to be stored in the long term.)

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes?
GiB = 2^30 bytes 
vs. 
GB = 10^9 bytes
Gib/Gb = 1.07, so a GiB is roughly 7 percent greater than a GB.

5) How does the virtual memory system help isolate processes from each other?
Essentially, a process is disallowed from accessing the data belonging to another process because there is no virtual address it generates that can map to the physical memory allocated to another process. The way that this is done is that the process is distributed a specific virtual address by the hardware and operating system which it can use. 

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?
The stack and heap are two different dynamic parts of the program in terms of memory usage, and therefore can be expected to grow in size. By having them at the opposite ends of the address space, you can have them share an unallocated piece of memory, and let them grow towards each other with no conflict unless you are using the entire free memory. 

7) What Python data structure would you use to represent a sparse array?
Because the array is sparse, you probably would not use an actual array. 
I would probably use a binary tree or a linked list where nodes are sorted by their key, and their values is contained. The easiest way of doing it in python would probably be a dictionary though. 

8) What is a context switch?
A context switch is when the operating system interrupts a running process, saves its state, and then switch to another process to run. 


In this directory, you should find a subdirectory named `aspace` that contains `aspace.c`.  Run it on your computer and compare your results to mine.
  
I got:
Address of main is 0x40057d
Address of global is 0x60104c
Address of local is 0x7ffc06511de4
Address of p is 0x16ff010

In terms of a comparison with the values given in ThinkOS, I found that main and global are identical. However the addresses of local and p are different. 

1) Add a second call to `malloc` and check whether the heap on your system grows up (toward larger addresses).  
The addresses that are given by the pointers on the heap do grow up. 

2) Add a function that prints the address of a local variable, and check whether the stack grows down.  
When I used GCC + looking at purely local variables, I actually found that the stack still grew up. When I used clang-3.8 instead, the stack grows down. When researching for why, it appears that in some compilers, a program is set s.t. a chunk of the stack is allocated at once for that function, and the assignment of local variables to that function is done in order of decleration, ascending up through that chunk of the stack. (according to stackoverflow: http://stackoverflow.com/questions/1102049/order-of-local-variable-allocation-on-the-stack)

3) Choose a random number between 1 and 32, and allocate two chunks with that size.  
How much space is there between them?  Hint: Google knows how to subtract hexadecimal numbers.
I will be allocating two chunks of size 1 and 4. (Interpretation of this is of mallocing two pointers to chunks of data) The difference between the location of the actual  values of data was 32 bytes. 
Example given:

Address of p is 0x1b1e010
Address of p2 is 0x1b1e030


## Chapter 4


### Files and file systems

1) What abstractions do file systems provide?  Give an example of something that is logically 
true about files systems but not true of their implementations.

A file system gives you the ability to write and work with data on the byte scale, when the actual implemtnation only works with the block scale of 1-8 KiB. 

2) What information do you imagine is stored in an `OpenFileTableEntry`?
I wouldn't be surprised if it contained metadata about the file such as its name, its size, its last time edited, etc. 

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?
Context switches to another process that is running on the computer until the memory management unit flags another interrupt. Another way is to buffer the operations so that you minimize the amount of disk access needed. Caching is also another useful tool that can be used. Etc. 

4) Suppose your program writes a file and prints a message indicating that it is done writing.  
Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the 
file you wrote is not there.  What happened?
It is likely that the file was written to a buffer that was waiting to actually be written to memory when there was a block to write. The data could have been ready to be flushed to disk, but not actually have been flushed at the time. 

5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?

A FAT file system can have less fragmentation due to the data being assigned in clusters, and we don't necessarily need to know the entire file size ahead of dealing with it. 

Inode file systems can be useful because the inode can be used to store a lot of different metadata about the file. 

6) What is overhead?  What is fragmentation?
Overhead talks about the time used to facilitate the structure of allocating a block and the amount of additional space that is used to store data.

Fragmentation is the unused space leftover when some blocks are not used/partially used. 

7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?
This idea lets us have a very general interface to communicate information between difference processes and computers. As a result, this can be really useful as a general tool when dealing with various ways of dealing with data. 

A reason why it might be bad is that I can imagine some cases where mishandling the abstraction can allow you to do things like buffer overflows if you aren't careful. 

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.  
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then 
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).  
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).


## Chapter 5


### Bits and bytes

1) Suppose you have the value 128 stored as an unsigned 8-bit number.  What happens if you convert 
it to a 16-bit number and accidentally apply sign extension?
Given that 128 is 0b1000000 for unsigned numbers, then sign extension would actually cause the the number to be read as -128. The sign extension would hence cause the value to be 0b1111111110000000, which is still -128.


2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator. 
Try it out and confirm that the result is interpreted as -12.

((12  ^ (-1)) + 1)
This works. 

3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a
sign bit or two's complement?
If I had to take a guess, it is easier to work with a biased integer due to letting things be done symmetrically around 127 on a fpu/hardware level. It may not be as space efficient as just using the already existing ALU, but there is still potential there. 


4) Following the example in Section 5.4, write the 32-bit binary representation of -13 in single precision 
IEEE floating-point.  What would you get if you accidentally interpreted this value as an integer?

Representation is therefore:
0b11000001010100000000000000000000

This is -1051721728 as an integer. 

5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.  
As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one
character at a time.  This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.

void lower_to_upper(char * string, int sizeofstring)
	{
		int x = 0;
		for (x = 0; x<sizeofstrings; x++)
		{
			*(string+x)  = *(string+x)^0b0100000;
		}

	}

The way to do it with operations on 4 or eight bytes would probably be some kind of function that uses a union of an integer/long and the equivalent number of characters.


## Chapter 6


### Memory management

1) Which memory management functions would you expect to take constant time?  Which ones take time proportional to the size of the allocated chunk?
Assuming that sbrk is a constant time function, which I think it is due to it being a location of a stack, then I would expect malloc and free to be constant time due to basically just dealing with the validity of the space. It just handles the address + any metadata associated with it. This is in constrasts to realloc and calloc which would neccesitate actually iterating over each element in memory to either copy/zero it. 


2) For each of the following memory errors, give an example of something that might go wrong:

a) Reading from unallocated memory.
You might be able to get a segfault which indicates access of an unauthorized piece of data. On the case where this doesn't happen, you might get values that are essentially garbage. These garbage values can do really strange stuff to the rest of the program because of the potential for invalid numbers. 

b) Writing to unallocated memory.
This may cause another issues with other memory due to possibly overwriting the data structures used to implement malloc and free ( the metadata).

c) Reading from a freed chunk.
See reading from unallocated memory.
d) Writing to a freed chunk.
See writing to unallocated memory.
e) Failing to free a chunk that is no longer needed.
You might have memory leaks, which if you are using a program that generates a lot of dynamic memory, then your computer can suffer in performance. I.E. malloc fails due to being out of physical memory, paging process pages from memorry to disk, etc. 


3) Run

    ps aux --sort rss

to see a list of processes sorted by RSS, which is "resident set size", the amount of physical 
memory a process has.  Which processes are using the most memory?
Just taking a cursory look, the main processes that are using a lot of memory are programs that have a graphical interface or gui, which makes sense due to them needing to contain the information about every pixel that they are dimensioned for. 
4) What's wrong with allocating a large number of small chunks?  What can you do to mitigate the problem?
You can get issues associated with fragmentation. Esseentially, the heap will be broken up into a bunch of small free pieces due to malloc and freeing pieces. As a result, this can slow programs down by making memory less effective. A way of handling this is minimizing the number of small mallocs you do that are freed at different times. 

If you want to know more about how malloc works, read 
[Doug Lea's paper about dlmalloc](http://gee.cs.oswego.edu/dl/html/malloc.html)



## Chapter 7


### Caching

1) What happens if a program writes a new value into the program counter?

2) What is the fundamental problem caches are meant to solve?

3) If cache access time is 1 ns and memory access time is 10 ns, what is the average
access time of a program with hit rate 50%?  How about 90%?

4) The book gives several examples of programming language features, like loops, that tend 
to improve locality in the access pattern of instructions and/or data.  Can you think of other examples?  
Or counter-examples that might decrease locality?

5)  If you refactor a program to improve locality, would you say the program is "cache aware"?  Why not?

6) See if you can estimate the cost of a memory cache by comparing the prices of two similar CPUs with 
different cache sizes.

7) Why are cache policies generally more complex at the bottom of the memory hierarchy?

8) Can you think of a strategy operating systems could use to avoid thrashing or recover when it occurs?

Run the cache code on your laptop or another computer and see if you can infer the cache size and block size.  
If you can find the technical specifications for your computer, see if your inferences are right.

1) In this directory you should find a subdirectory named `cache` that contains `cache.c` and supporting files.  Read `cache.c`, then run `make` and `./cache`.

2) Run `python graph_data.py` to see the results.  What can you infer about the cache structure on your computer?


## Chapter 8


### Multitasking

1) What is the kernel's most basic task?

2) When an interrupt occurs, what part of the hardware state is saved by hardware?

3) What is the difference between an interrupt and a context switch?

4) Give an example of an event that might cause a process to move from the blocked to the ready state.

5) Why might a scheduler want to give higher priority to an I/O bound process?

When I make French toast, I usually make a batch of 12 slices.  But my griddle only has room for 8 slices.  Each piece of toast has to cook for 5 minutes on each side.  How can I schedule 12 slices onto 8 "cores" to minimize the elapsed time to cook all 12 slices?  (Note: this question is not hypothetical; this is really how I make French toast.)



## Chapter 9


### POSIX threads and mutexes

As you read Chapter 9, you should compile and run the example code.  By the nature of multi-threaded programs, you results will probably be different from mine, possibly in interesting ways.

1) Why does each thread have its own stack?

2) What does the `gcc flag -lpthread` do?

3) What does the argument of `pthread_exit` do?

4) Normally the same thread that created a thread also waits to join it.  What happens if another thread tries to join a thread it did not create?

5) What goes wrong if several threads try to increment a shared integer at the same time?

6) What does it mean to "lock a mutex"?



## Chapter 10


### Condition variables

1) What does it mean to say that a data structure is thread safe?

2) In the circular buffer implementation of a queue, why is the maximum number of elements in the queue `n-1`,
if `n` is the size of the array?

3) If there is no mutex to protect the queue, give an example of a sequence of steps that could leave
the queue in an inconsistent state.

4) When a thread calls cond_wait, why does it have to unlock the mutex before blocking?

5) When a thread returns from cond_wait, what do we know is definitely true?  What do we think is probably true?

6) What happens if you signal a condition variable when there are no waiting threads?

7) Do you have to lock the mutex to signal a condition variable?

8) Does the condition have to be true when you signal a condition variable?


 
## Chapter 11


### Semaphores in C
