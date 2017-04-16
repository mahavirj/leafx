#include "DList.h"
#include <iostream>
using namespace std;

#define INIT_HEAD(n) { \
	n->prev = NULL; \
	n->next = NULL; \
}

DList::DList() {
	head = NULL;
}

DList::~DList() {
	while (head) {
		cout << "Delete = " << head << "\n";
		struct List *tmp = head->next;
		delete head;
		head = tmp;
	}
}

int DList::Add(int data) {
	struct List *it = head;
	struct List *node = new struct List;
	if (!node)
		return -1;
	node->data = data;

	cout << "Create = " << node << "\n";

	if (!head || head->data > data) {
		node->next = head;
		node->prev = NULL;
		if (head)
			head->prev = node;
		head = node;		
	} else {
		while (it->next && it->next->data < data)
			it = it->next;
		node->next = it->next;
		node->prev = it;
		it->next = node;
		if (node->next)
			node->next->prev = node;				
	}
	return 0;
}

void *DList::Search(int data) {
	struct List *it = head;
	while (it) {
		if (it->data == data)
			return (void *) it;
		it = it->next;
	}
	return NULL;
}

int DList::Delete(void *node) {
	struct List *d = (struct List *) node;
	if (!d)
		return -1;
	struct List *it = head;
	while (it) {
		if (it == d) {
			if (it == head)
				head = head->next;
			if (it->next)
				it->next->prev = it->prev;
			if (it->prev)
				it->prev->next = it->next;
			delete it;
			return 0;
		}
		it = it->next;
	}
	return -1;
}

int main()
{
	DList *list = new DList;
	list->Add(2);
	list->Add(3);
	list->Add(1);
	list->Add(6);
	list->Add(4);
	void *a = list->Search(1);
	list->Delete(a);
	delete list;	
}
