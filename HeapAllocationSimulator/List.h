#pragma once
#ifndef STDLIB
#include <stdlib.h>
#define STDLIB
#endif // !STDLIB

#include <stdbool.h>


struct node {
	void* data;
	int key;
	struct node *next;
};

void insert(int key, void* data);
struct node* deleteFirst();
bool isEmpty();
int length();
struct node* find(int key);

void clear();