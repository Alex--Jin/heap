#pragma once
#ifndef STDIO
#include <stdio.h>
#define STDIO
#endif

void flush(char* filename);
void log(char* filename, char* line);
