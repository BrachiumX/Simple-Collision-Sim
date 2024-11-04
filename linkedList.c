#include "linkedList.h"

struct Node* insertNode(struct Node* head, void* value) {

	if(!head) {
		struct Node* add = (struct Node*) malloc(sizeof(struct Node));
		add->value = value;
		add->next = 0;
		add->prev = 0;
		return add;
	}

	struct Node* curr = head;

	while(curr->next) {
		curr = curr->next;
	}

	struct Node* add = (struct Node*) malloc(sizeof(struct Node));
	add->value = value;
	add->prev = curr;
	add->next = 0;

	curr->next = add;

	return head;
}

struct Node* deleteValue(struct Node* head, void* value) {

	if(head->value == value) {
		if(head->next) {
			head->next->prev = 0;
		}
		struct Node* newhead = head->next;
		free(head);
		return newhead;
	}

	struct Node* curr = head;

	while(curr->value != value) {

		if(!curr->next) {
			return head;
		}

		curr = curr->next;
	}

	curr->prev->next = curr->next;

	if(curr->next) {
		curr->next->prev = curr->prev;
	}

	free(curr);

	return head;
}

struct Node* deleteNode(struct Node* head, struct Node* node) {
	if(!node) {
		return head;
	}

	if(node->next) {
		node->next->prev = node->prev;
	}

	if(node->prev) {
		node->prev->next = node->next;
	}
	else {
		return node->next;
	}

	free(node);

	return head;
}

