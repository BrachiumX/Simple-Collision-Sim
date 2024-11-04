#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

struct Node {
	struct Node* next;
	struct Node* prev;
	void* value;
};

struct Node* insertNode(struct Node* head, void* value);

struct Node* deleteValue(struct Node* head, void* value);
struct Node* deleteNode(struct Node* head, struct Node* node);

#endif
