#include "Heap.h"
#include "Input.h"
#include "List.h"

#define NAMELEN	256

int main()
{
	char mode;
	char filename[NAMELEN];
	printf("Memory allocation simulation\n\n\n");
	printf("Input File Name: ");
	FILE* fp = 0;
	while (true)
	{
		gets_s(filename, NAMELEN - 1);
		fp = open_file(filename);
		if (fp) break;
		printf("No such file. Input File Name Again: ");
	}

	printf("Choose Fit Type (B/b - Best Fit, F/f - First Fit): ");
	while (true)
	{
		scanf("%c", &mode);
		if (mode == 'B' || mode == 'b' || mode == 'f' || mode == 'F')
			break;
		printf("Wrong Format. Input Again (B/b - Best Fit, F/f - First Fit): ");
	}

	setFitType(mode);

	int free_mode;
	_flushall();
	printf("Run Explicit Free List Mode? (Yes=1, No=2): ");
	scanf("%d", &free_mode);


	char line[21];
	while (!feof(fp))
	{
		fgets(line, 20, fp);
		MyAllocCommand cmd = parse_line(line);

		void* ptr;

		switch (cmd.param1)
		{
		case 'a':
			ptr = find(cmd.param3);
			if (ptr)
			{
				printf("Invalid input - key already taken as %d.\n", cmd.param3);
				continue;
			}
			ptr = myalloc(cmd.param2);

			insert(cmd.param3, ptr);

			break;
		case 'r':
			ptr = find(cmd.param3);
			if (!ptr)
			{
				printf("Invalid input - no matching key %d exists to resize.\n", cmd.param3);
				continue;
			}
			if (find(cmd.param4))
			{
				printf("Invalid input - key already exists as %d for new resized block.\n", cmd.param4);
			}
			if (cmd.param2 > 0)
			{
				ptr = myrealloc(ptr, cmd.param2);
				insert(cmd.param4, ptr);
			}
			else
				myfree(ptr);
			break;
		case 'f':
			ptr = find(cmd.param2);
			if (ptr)
				myfree(ptr);
			else
				printf("Invalid input - no matching key %d exists to remove.\n", cmd.param2);
			break;
		case 'g':
			gc();
			clear();
			break;
		}
	}
	printf("In scope heap status\n\n");
	display_heap("output.txt");
	if (free_mode == 2)
	{
		gc();
		clear();
	}

	printf("\n\nOut of scope heap status\n\n");
	display_heap("output_final.txt");
	scanf("%d", &free_mode);
}