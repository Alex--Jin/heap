Your Heap<Br>
•	Start your heap at address 0<Br>
•	Assume a 32-bit system (so each word is 4 bytes)<Br>
•	Assume double-word alignment of all allocated blocks<Br>
•	Calls to myalloc and myrealloc take an input parameter indicating the size of the allocation in bytes<Br>
•	Invalid calls to any of your primary functions will give an error but not crash your simulator (though they may have no effect on the heap)<Br>
•	Your initial heap size will be 1000 words, and you may expand your heap to 100,000 words maximum
As an example, your heap would start at word 0. If your first call is myalloc(5), then you would start the header at word 1, your payload at word 2, and your footer at word 4 to meet alignment requirements. This is because the payload would have to start at an address divisible by 8, and take up two words, 5 bytes for the payload and 3 bytes of padding. So, your header would start at word 1 (address 4), the payload would start at word 2 (address 8), and your footer would start at word 4 (address 16). This would allow your next header to start at word 5 (address 20) and the next payload to start at word 6 (address 24). <Br>
<Br>
<Br>
Primary Functions<Br>
You will have four primary functions in your assignment, which MUST be named as follows:<Br>
•	myalloc(size)<Br>
o	takes an integer value indicating the number of bytes to allocate for the payload of the block<Br>
o	returns a "pointer" to the starting address of the payload of the allocated block<Br>
The "pointer" above can take any form you like, depending on the data structure you use to represent your heap<Br>
•	myrealloc(pointer, size)<Br>
o	takes a pointer to an allocated block and an integer value to resize the block to<Br>
o	returns a "pointer" to the new block <Br>
o	frees the old block<Br>
o	a call to myrealloc with a size of zero is equivalent to a call to myfree<Br>
•	myfree(pointer)<Br>
o	frees the block pointed to by the input parameter "pointer"<Br>
o	returns nothing<Br>
o	only works if "pointer" represents a previously allocated or reallocated block that has not yet been freed otherwise, does not change the heap<Br>
•	mysbrk(size)<Br>
o	grows or shrinks the size of the heap by a number of words specified by the input parameter "size"<Br>
o	you may call this whenever you need to in the course of a simulation, as you need to grow the heap<Br>
o	this call will return an error and halt the simulation if your heap would need to grow past the maximum size of 100,000 words
User Options<Br>
The user must be able to specify the following (either in a GUI or on the command line) for each run of your simulator:<Br>
•	Input text file<Br>
•	Implicit or Explicit free list<Br>
•	First-fit or Best-fit allocation<Br>
Input<Br>
You will process a text file to get the series of allocation, reallocation, and free calls that your simulator should make on your simulated heap. The input file will be in the form of a simple comma-separated value format in which each line describes a single call.<Br>
Example:<Br>
a, 5, 0<Br>
a, 25, 1<Br>
a, 1, 2<Br>
r, 10, 1, 3<Br>
f, 2<Br>
Calls to myalloc will be indicated in the input file as follows:<Br>
•	An "a" to indicate that this is an allocation call<Br>
•	An integer to indicate the "size" parameter<Br>
•	An integer between 0 and 999 to act as a reference the block allocated by the call<Br>
o	This value will be used to tie future calls to "myfree" and "myrealloc"<Br>
o	You may use this value any way you wish. It can be used to name pointers returned by your simulator, as the key to key-value pairs that keep track of your simulated "pointer"s, etc. It is simply there to ensure that we are calling "myrealloc" and "myfree" on the correct blocks<Br>
Calls to myrealloc will be indicated in the input file as follows:<Br>
•	An "r" to indicate that this is a reallocation call<Br>
•	An integer to indicate the "size" parameter<Br>
•	An integer between 0 and 999 to reference which block created by a previous call to myalloc we are resizing<Br>
•	An integer between 0 and 999 to reference the new block allocated by the call<Br>
Calls to myfree will be indicated in the input file as follows:<Br>
•	An "f" to indicate that this is a free call<Br>
•	An integer between 0 and 999 to specify the allocation call that this call is freeing<Br>
So, let's break down the example above:<Br>
a, 5, 0      // ptr0 = myalloc(5)<Br>
a, 25, 1     // ptr1 = myalloc(25)<Br>
a, 1, 2      // ptr2 = myalloc(2)<Br>
r, 10, 1, 3  // ptr3 = myrealloc(ptr1, 10)<Br>
f, 2         // myfree(ptr2)<Br>
The above example assumes that you use the reference number appended to the string "ptr" as your returned pointer names, but, again, this is not required. You may use the reference numbers however you wish, but this is one example of how you can use them to make sure that you are calling your functions on the correct blocks.<Br>
You do not need to validate the input for this project. You may assume that all input files are formatted correctly when you process them.<Br>
 Output<Br>
Your output from each run will be another comma-separated value text file called "output.txt"<Br>
Simply indicate the value of each word in your simulated heap in hexadecimal format. Start with word 0 and work your way up to whatever the last word in your heap ends up being after the simulation run. <Br>
0, 0x00000000
1, 0xfe54cb43
2, 0x002365cd
etc.
The first value indicates the word in question, and the second indicates the contents of that word (represented in hexadecimal). That is why there are 8 hexadecimal digits for each entry in the example above. Each word will contain 4 bytes since this is a 32-bit system. Your output file will be checked to ensure that the heap contains the correct headers, footers, and pointers (in the case of explicit free lists) for the simulation that has just been run.
<Br>
