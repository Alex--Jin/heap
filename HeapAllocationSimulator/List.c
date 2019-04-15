#pragma once
#include "List.h"

struct node *_list_head = 0;
struct node *current = 0;

//insert link at the first location
void insert(int key, void* data) {
	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));

	link->key = key;
	link->data = data;

	//point it to old first node
	link->next = _list_head;

	//point first to new first node
	_list_head = link;
}

//delete first item
struct node* deleteFirst() {

	//save reference to first link
	struct node *tempLink = _list_head;

	//mark next to first link as first 
	_list_head = _list_head->next;

	//return the deleted link
	return tempLink;
}

//is list empty
bool isEmpty() {
	return _list_head == 0;
}

int length() {
	int length = 0;
	struct node *current;

	for (current = _list_head; current != 0; current = current->next) {
		length++;
	}

	return length;
}

//find a link with given key
struct node* find(int key) {

	//start from the first link
	struct node* current = _list_head;

	//if list is empty
	if (_list_head == 0) {
		return 0;
	}

	//navigate through list
	while (current->key != key) {

		//if it is last node
		if (current->next == 0) {
			return 0;
		}
		else {
			//go to next link
			current = current->next;
		}
	}

	//if data found, return the current Link
	return current->data;
}

//delete a link with given key
struct node* remove(int key) {

	//start from the first link
	struct node* current = _list_head;
	struct node* previous = 0;

	//if list is empty
	if (_list_head == 0) {
		return 0;
	}

	//navigate through list
	while (current->key != key) {

		//if it is last node
		if (current->next == 0) {
			return 0;
		}
		else {
			//store reference to current link
			previous = current;
			//move to next link
			current = current->next;
		}
	}

	//found a match, update the link
	if (current == _list_head) {
		//change first to point to next link
		_list_head = _list_head->next;
	}
	else {
		//bypass the current link
		previous->next = current->next;
	}

	return current;
}

void clear()
{
	while (_list_head)
	{
		deleteFirst();
	}
}