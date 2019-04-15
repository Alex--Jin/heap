#include "Heap.h"
#include "Logger.h"

char fitType;

// Maximum heap size
int heap_size = 1000 * sizeof(WORD);

WORD heap[MAX_HEAP];

typedef struct _block
{
	size_t      size;  /* Size of the allocated block of memory in bytes */
	struct _block *next;  /* Pointer to the next block of allcated memory */
	struct _block *prev;  /* Pointer to the next block of allcated memory */
	bool        free;  /* Is this block free? */
	unsigned int	payloadIdx; /* Pointer to payload in heap */
} Block;

Block* head = 0;
Block* tail = 0;

// Set Fit type
void setFitType(char c)
{
	fitType = c;
}

void __split(Block* block, size_t size)
{
	unsigned int left_footer = block->payloadIdx + size / sizeof(WORD); // new footer
	if (size / sizeof(WORD) > 0)
		left_footer++;

	unsigned int next_header = left_footer + 1; // new header is next to footer
	if (next_header % 2 == 0) // maybe one more next to footer
		next_header++;

	unsigned int next_footer = block->payloadIdx + block->size / sizeof(WORD); // original footer
	if (block->size % sizeof(WORD) > 0) // +1 for padding
		next_footer++;

	unsigned int next_size = (next_footer - next_header) * sizeof(WORD);

	if (next_size < sizeof(WORD) * 2)
		return;

	Block* nblock = malloc(sizeof(Block)); // create a free block
	nblock->size = next_size;
	nblock->free = 1;
	nblock->payloadIdx = next_header + 1;
	block->free = 0;
	block->size = size;

	nblock->next = block->next; // update chains
	nblock->prev = block;
	block->next->prev = nblock;
	block->next = nblock;
}

Block* ___merge(Block* block)
{
	if (block->free && block->prev->free)
	{
		unsigned int sz = block->prev->size / sizeof(WORD);
		if (block->prev->size % sizeof(WORD) > 0)
			sz++;
		if ((block->prev->payloadIdx + sz + 1) % 2 == 0) // is header one more next to prev's footer?
			sz++;
		sz += 2; // increase for footer and header size
		sz += block->size / sizeof(WORD);
		if (block->size % sizeof(WORD) > 0)
			sz++;

		block->prev->size = sz * sizeof(WORD); // merged size

									// update chain
		block->prev->next = block->next;
		if (block->next != 0)
			block->next->prev = block->prev;
		Block* prev = block->prev;
		free(block);
		return prev;
	}
	return block;
}

Block* __coalesce(Block* block)
{
	if (block->prev != 0)
	{
		block = ___merge(block);
	}
	if (block->next != 0)
	{
		block = ___merge(block->next);
	}
	return block;
}

void __alloc_in_heap(Block* block)
{
	int sz = block->size / sizeof(WORD);
	if (block->size % sizeof(WORD) > 0) // padding
		sz++;
	for (int i = 0; i < sz; i++)
		heap[block->payloadIdx + i] = 0xffffffff; // fill payload
	heap[block->payloadIdx - 1] = (unsigned int)block; // fill header as actual address of related block 
	heap[block->payloadIdx + sz] = 0; // fill footer
}

bool ___check_availability(size_t size)
{
	unsigned int start = 0;
	if (tail)
	{
		start = tail->payloadIdx;
	}
	else
	{
		start = 2;
	}
	unsigned int new_footer = size / sizeof(WORD);
	if (size % sizeof(WORD) > 0)
		new_footer++;
	new_footer++;
	if (heap_size > new_footer)
		return true;
	return false;
}

Block* __alloc(Block* block, size_t size)
{
	if (block == 0) // should allocate to tail
	{
		if (!___check_availability(size))
			return 0;
		block = malloc(sizeof(Block));
		block->size = size;
		block->free = 0;
		block->next = 0;

		if (tail != 0) // allocate after tail
		{
			int sz = tail->size / sizeof(WORD);
			if (tail->size % sizeof(WORD) > 0) // padding
				sz++;

			tail->next = block;
			unsigned int newPayloadIdx = tail->payloadIdx + sz + 1; // possible header position
			if (newPayloadIdx % 2 == 0)
				newPayloadIdx += 2; // header should be located to one more next, and payload is located next to header
			else
				newPayloadIdx += 1; // correct place for header. payload is located next to header
			block->next = 0;
			block->payloadIdx = newPayloadIdx;
			block->prev = tail;
			tail = block;
		}
		else // brand new allocation ---> first allocation in heap
		{
			block->prev = 0;
			block->payloadIdx = 2;
			block->size = size;
			tail = block;
			head = block;
		}
	}
	else // found fit space.
	{
		if (block->size - size > 2) // found block is big enough to split
		{
			__split(block, size);
		}
		else
		{
			block->size = size;
		}
	}
	return block;
}

Block* ___find_first_fit(size_t sz)
{
	Block* block = head;
	Block* candidate = 0;
	if (head == 0)
		return 0;
	while (block != 0)
	{
		if (block->free)
		{
			if (block->size > sz)
			{
				return block;
			}
		}
		block = block->next;
	}

	return block;
}

Block* ___find_best_fit(size_t sz)
{
	Block* block = head;
	Block* candidate = 0;
	if (head == 0)
		return 0;
	while (block != 0)
	{
		if (block->free)
		{
			if (block->size > sz)
			{
				if (candidate == 0)
					candidate = block;
				else
				{
					if (block->size - sz < candidate->size - sz)
						candidate = block;
				}
			}
		}
		block = block->next;
	}

	return candidate;
}

Block* __find_new_block(size_t sz)
{
	Block* block = 0;
	if (fitType == 'b' || fitType == 'B')
	{
		block = ___find_best_fit(sz);
	}
	else if (fitType == 'f' || fitType == 'F')
	{
		block = ___find_first_fit(sz);
	}
	return block;
}

bool __grow_heap(size_t size)
{
	if (heap_size + size > MAX_HEAP)
	{
		printf("Heap size can't exceed 100000.\n");
		return false;
	}
	heap_size += size + 3;
	return true;
}


Block* _myalloc(size_t sz)
{
	Block* block = __find_new_block(sz);
	block = __alloc(block, sz);
	if (block == 0)
	{
		if (!__grow_heap(sz))
		{
			printf("System Halt. Exiting...\n");
			exit(1);
		}
		else
		{
			block = __alloc(block, sz);
		}
	}
	__alloc_in_heap(block);
	return block;
}

Block* _myfree(Block* block)
{
	block->free = 1;
	return __coalesce(block);
}

void* _myrealloc(Block* block, size_t sz)
{
	_myfree(block);
	return _myalloc(sz);
}

void *myalloc(size_t size)
{
	Block* block = _myalloc(size);
	return (void*)block->payloadIdx;
}

void myfree(void *ptr)
{
	int payloadIdx = (unsigned int)ptr;
	Block* block = (Block*)heap[payloadIdx - 1];
	_myfree(block);
}

void *myrealloc(void *ptr, size_t size)
{
	int payloadIdx = (unsigned int)ptr;
	Block* block = (Block*)heap[payloadIdx - 1];
	block = _myrealloc(block, size);
	return block->payloadIdx;
}


void gc()
{
	Block* block = head;
	while (block)
	{
		block = _myfree(block);
		if (block->next == 0)
		{
			free(block);
			head = 0;
			tail = 0;
			return;
		}
	}
}

void display_heap(char* filename)
{
	flush(filename);
	Block* block = head;
	while (block)
	{
		if (block->free)
		{
			block = block->next;
			continue;
		}
		char buf[30];
		sprintf_s(buf, 30, "%d, %08xx", block->payloadIdx - 1, heap[block->payloadIdx - 1]);
		printf("\n%s\n", buf);
		log(filename, buf);

		int len = block->size / sizeof(WORD);
		if (block->size % sizeof(WORD) > 0)
			len++;

		for (int i = 0; i <= len; i++) {
			sprintf_s(buf, 30, "%d, %08xx", block->payloadIdx + i, heap[block->payloadIdx + i]);
			printf("%s\n", buf);
			log(filename, buf);
		}
			
		block = block->next;
		
	}
}
