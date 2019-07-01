/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  A source file providing an implementation of a stack. See stack.h 
 *    				for an API description.
 *
 *        Version:  1.0
 *        Created:  06/06/2019 06:42:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gs), gasperstukelj@protonmail.com
 *
 * =====================================================================================
 */


#include "stack.h"

typedef struct node {
	long int item;
	struct node *next;
} node_t;

void check_ptr(node_t *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "Not enough memory on the heap.\n");
		exit(ENOMEM);
	} 
} 

node_t * init_stack() {
	node_t *head = (node_t *) malloc(sizeof(node_t)); 
	check_ptr(head);
	head->next = NULL; 
	return head;
}

void push(long int i, node_t **head) {
	node_t *next = (node_t *) malloc(sizeof(node_t));
	check_ptr(next);
	
	next->item = i;
	next->next = *head;
	*head = next;
}

long int pop(node_t **head) {
	
	if ((*head) == NULL) {
		fprintf(stderr, "Stack is empty!\n");
		exit(errno);
	}

	node_t *old = *head;
	long int temp = old->item;

	if (old->next) {
		*head = old->next;
	} else {
		*head = NULL;
	}
	
	free(old);
	return temp;	
}

void free_stack(node_t **head) {
	if ((*head)->next == NULL) {
		free((*head));
	} else {
		free_stack(&((*head)->next));
		free((*head));
	}
}

