#ifndef STDIO
#include <stdio.h>
#define STDIO
#endif


typedef struct _MyAllocCommand
{
	char param1;
	int param2;
	int param3;
	int param4;
} MyAllocCommand;


FILE* open_file(char* filename);

MyAllocCommand parse_line(char line[20]);
