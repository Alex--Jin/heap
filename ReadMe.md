Your Heap
•	Start your heap at address 0
•	Assume a 32-bit system (so each word is 4 bytes)
•	Assume double-word alignment of all allocated blocks
•	Calls to myalloc and myrealloc take an input parameter indicating the size of the allocation in bytes
•	Invalid calls to any of your primary functions will give an error but not crash your simulator (though they may have no effect on the heap)
•	Your initial heap size will be 1000 words, and you may expand your heap to 100,000 words maximum
As an example, your heap would start at word 0. If your first call is myalloc(5), then you would start the header at word 1, your payload at word 2, and your footer at word 4 to meet alignment requirements. This is because the payload would have to start at an address divisible by 8, and take up two words, 5 bytes for the payload and 3 bytes of padding. So, your header would start at word 1 (address 4), the payload would start at word 2 (address 8), and your footer would start at word 4 (address 16). This would allow your next header to start at word 5 (address 20) and the next payload to start at word 6 (address 24). 


Primary Functions
You will have four primary functions in your assignment, which MUST be named as follows:
•	myalloc(size)
o	takes an integer value indicating the number of bytes to allocate for the payload of the block
o	returns a "pointer" to the starting address of the payload of the allocated block
The "pointer" above can take any form you like, depending on the data structure you use to represent your heap
•	myrealloc(pointer, size)
o	takes a pointer to an allocated block and an integer value to resize the block to
o	returns a "pointer" to the new block 
o	frees the old block
o	a call to myrealloc with a size of zero is equivalent to a call to myfree
•	myfree(pointer)
o	frees the block pointed to by the input parameter "pointer"
o	returns nothing
o	only works if "pointer" represents a previously allocated or reallocated block that has not yet been freed otherwise, does not change the heap
•	mysbrk(size)
o	grows or shrinks the size of the heap by a number of words specified by the input parameter "size"
o	you may call this whenever you need to in the course of a simulation, as you need to grow the heap
o	this call will return an error and halt the simulation if your heap would need to grow past the maximum size of 100,000 words
User Options
The user must be able to specify the following (either in a GUI or on the command line) for each run of your simulator:
•	Input text file
•	Implicit or Explicit free list
•	First-fit or Best-fit allocation
Input
You will process a text file to get the series of allocation, reallocation, and free calls that your simulator should make on your simulated heap. The input file will be in the form of a simple comma-separated value format in which each line describes a single call.
Example:
a, 5, 0
a, 25, 1
a, 1, 2
r, 10, 1, 3
f, 2
Calls to myalloc will be indicated in the input file as follows:
•	An "a" to indicate that this is an allocation call
•	An integer to indicate the "size" parameter
•	An integer between 0 and 999 to act as a reference the block allocated by the call
o	This value will be used to tie future calls to "myfree" and "myrealloc"
o	You may use this value any way you wish. It can be used to name pointers returned by your simulator, as the key to key-value pairs that keep track of your simulated "pointer"s, etc. It is simply there to ensure that we are calling "myrealloc" and "myfree" on the correct blocks
Calls to myrealloc will be indicated in the input file as follows:
•	An "r" to indicate that this is a reallocation call
•	An integer to indicate the "size" parameter
•	An integer between 0 and 999 to reference which block created by a previous call to myalloc we are resizing
•	An integer between 0 and 999 to reference the new block allocated by the call
Calls to myfree will be indicated in the input file as follows:
•	An "f" to indicate that this is a free call
•	An integer between 0 and 999 to specify the allocation call that this call is freeing
So, let's break down the example above:
a, 5, 0      // ptr0 = myalloc(5)
a, 25, 1     // ptr1 = myalloc(25)
a, 1, 2      // ptr2 = myalloc(2)
r, 10, 1, 3  // ptr3 = myrealloc(ptr1, 10)
f, 2         // myfree(ptr2)
The above example assumes that you use the reference number appended to the string "ptr" as your returned pointer names, but, again, this is not required. You may use the reference numbers however you wish, but this is one example of how you can use them to make sure that you are calling your functions on the correct blocks.
You do not need to validate the input for this project. You may assume that all input files are formatted correctly when you process them.
 Output
Your output from each run will be another comma-separated value text file called "output.txt"
Simply indicate the value of each word in your simulated heap in hexadecimal format. Start with word 0 and work your way up to whatever the last word in your heap ends up being after the simulation run. 
0, 0x00000000
1, 0xfe54cb43
2, 0x002365cd
etc.
The first value indicates the word in question, and the second indicates the contents of that word (represented in hexadecimal). That is why there are 8 hexadecimal digits for each entry in the example above. Each word will contain 4 bytes since this is a 32-bit system. Your output file will be checked to ensure that the heap contains the correct headers, footers, and pointers (in the case of explicit free lists) for the simulation that has just been run.
