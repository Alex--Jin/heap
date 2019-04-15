#pragma once
#include "Logger.h"

#define _CRT_SECURE_NO_WARNINGS

void flush(char* filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "w+");
	fclose(fp);
}

void log(char* filename, char* line)
{
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, filename, "a+");

	if (err == 0)
	{
		//fprintf_s(fp, "%d, 0x%08x\n", line);
		fprintf_s(fp, "%s\n", line);
		//printf("The result is saved in '%s'\n", filename);
	}
	else
	{
		printf("The file '%s' was not opened\n", filename);
	}

	fclose(fp);
	return fp;
}
