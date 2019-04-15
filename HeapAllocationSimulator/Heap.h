#include <assert.h>
#ifndef STDIO
#include <stdio.h>
#define STDIO
#endif
#include <stdbool.h>
#ifndef STDLIB
#include <stdlib.h>
#define STDLIB
#endif // !STDLIB


// define WORD as 4byte
#define WORD unsigned int

// Maximum heap limit
#define MAX_HEAP 100000

// word size
#define WORDSIZE 4

// Get the required size of blocks in byte to cover given size of bytes
#define PAYLOADSIZEINWORD(s)         (((((s) - 1) >> 2) << 2) + WORDSIZE)

// Get the payload pointer from block pointer
#define BLOCK_PAYLOAD(block_ptr)      ((char*)(block_ptr) + WORDSIZE)

// Get the block pointer from payload pointer
#define PAYLOAD_BLOCK(payload_ptr)   ((char*)(payload_ptr) - WORDSIZE) 

// wrapper functions
void *myalloc(size_t size);
void myfree(void *ptr);
void *myrealloc(void *ptr, size_t size);
void setFitType(char fitType);
void gc();

void display_heap();