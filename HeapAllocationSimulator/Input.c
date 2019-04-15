#include "Input.h"

FILE* open_file(char* filename)
{
	FILE *fp;
	errno_t  err;

	err = fopen_s(&fp, filename, "r");

	if (err == 0)
	{
		printf("The file '%s' was opened\n", filename);
		return fp;
	}
	else
	{
		printf("The file '%s' was not opened\n", filename);
		return 0;
	}

}

MyAllocCommand parse_line(char line[20])
{
	MyAllocCommand cmd;
	char seps[] = ", ";
	char *token = NULL;
	char *ptr = NULL;

	ptr = strtok_s(line, seps, &token);
	int args_num = 0;

	while (ptr != NULL)
	{
		args_num++;
		switch (args_num)
		{
		case 1:
			cmd.param1 = ptr[0];
			break;
		case 2:
			cmd.param2 = atoi(ptr);
			break;
		case 3:
			cmd.param3 = atoi(ptr);
			break;
		case 4:
			cmd.param4 = atoi(ptr);
			break;
		default:
			break;
		}

		ptr = strtok_s(NULL, seps, &token);
		//printf("%s\n", ptr);
	}

	//printf("%s\n", cmd.param1);
	return cmd;
}