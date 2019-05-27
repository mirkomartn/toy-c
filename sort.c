// Reads an unlimited number of strings (max 63 chars) from stdin until EOF or STOP. The words are then printed in alphabetical order.
// The implementation uses a linked list structure to dynamically store the words and an implementation of the merge-sort algorithm.
// Written by Gašper Štukelj.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WORD 64 // in addition to this, the number in the scanf() call in the get_word() needs to be changed as well
#define TRUE -1
#define FALSE 0
#define STOP "."

typedef struct linked_list {
	char myword[WORD];
	struct linked_list *next;
} list_t;


void check_ptr(list_t *ptr);
void get_words(list_t *root, int *count);
list_t* sort_words(list_t* list, int len);
list_t* partition_list(list_t* list, int len);
list_t* merge(list_t *L, list_t *R);
int is_smaller(const char *str1, const char *str2);
void print_words(list_t *head);
void free_mem(list_t *node);


int main(void) {
	int count = 0;
	list_t *head = NULL;

	// root is alocated on the heap, to simplify the free_mem function the word stored at root could appear in
	// the middle of the sorted list, hence making it tricky to traverse through the final list calling free()
	list_t *root = (list_t *) malloc(sizeof(list_t));
	check_ptr(root);
	root->next = NULL;

	get_words(root, &count);

	if (count == 0)
        return 0;

    head = sort_words(root, count);

    print_words(head);

    free_mem(head);

	return 0;
}

/****
	FUNCTION: void check_ptr(list_t *ptr);
	RETURNS: /
	SIDE-EFFECTS: Checks if malloc() failed to allocate requested space. If so, terminates the program with a designated error code.
 ****/
void check_ptr(list_t *ptr) {
	if (ptr == NULL) {
		printf("Error, not enough memory. Exiting the program now.");
		exit(ENOMEM);
	}
}


/****
	FUNCTION: void get_word(list_t *root, int *count);
	RETURNS: /
	SIDE-EFFECTS: if not STOP or EOF, create a new node in the linked list structure, save the string in it, and increment the counter by 1
 ****/
void get_words(list_t *root, int *count) {
	char word[WORD];
    list_t *node = root;
    list_t *previous = NULL;

    while (scanf("%63s", word) != EOF) {

        if (!strcmp(word, STOP)) break;

        // create a new node in the linked list
		node->next = (list_t *) malloc(sizeof(list_t));
		check_ptr(node->next);

		// store the scanned word, and increment the counter
		strcpy(node->myword, word);
		(*count)++;

		previous = node;
		node = node->next;
	}

	// remove the last node, because its "empty", and change the attribute next of the previous node to a NULL pointer
	// if NULL is passed to free, nothing occurs, if no words are read, previous == NULL, so the if block is not executed
	if (previous) {
		free(node);
		previous->next = NULL;
	}
}

/****
	FUNCTION: list_t* sort_words(list_t* list);
	RETURNS: a pointer to a sorted linked list
	SIDE-EFFECTS: /
 ****/
list_t* sort_words(list_t* list, int len) {
    int len1 = len / 2;
    int len2 = len - len1;
    list_t *list2 = NULL;

	// if list only contains one word, it's already sorted, otherwise, break in two halfs, then sort and merge them
	// most of the actual sorting is done by the merge()
	if (len == 1) {
		return list;
	} else {
		list2 = partition_list(list, len1);
		return merge(sort_words(list, len1), sort_words(list2, len2));
	}
}

/****
	FUNCTION: list_t* partition_list(list_t *list, int len);
	RETURNS: a pointer to a second part of the linked list, such that the input pointer now points to the first half, which is
             of the length specified by the integer passed as a second argument
	SIDE-EFFECTS: "breaks" the linked list, by setting the next pointer of the last node in the first half of the list to NULL
 ****/
list_t* partition_list(list_t *list, int len) {
    list_t *retval = list->next;
    list_t *control = list;

    for (int i = 1; i < len; i++) {
        retval = retval->next;
        control = control->next;
    }

    control->next = NULL;

    return retval;
}

/****
	FUNCTION: list_t* merge(list_t *L, list_t *R);
	RETURNS: a pointer to a sorted linked list that merges the passed linked lists L and R
	SIDE-EFFECTS: /
 ****/
list_t*  merge(list_t *L, list_t *R) {
	list_t *left = L;
	list_t *right = R;
	list_t *retval = NULL;
	list_t *node = NULL;

    if (is_smaller(left->myword, right->myword)) {
        retval = left;
        left = left->next;
    } else {
        retval = right;
        right = right->next;
    }

	node = retval;

	while (TRUE) {

        if (left == NULL) {
			node->next = right;
			break;
		}

		if (right == NULL) {
			node->next = left;
			break;
		}

		if (is_smaller(left->myword, right->myword)) {
			node->next = left;
			left = left->next;
		} else {
			node->next = right;
			right = right->next;
		}

		node = node->next;
	}

	return retval;
}

/****
	FUNCTION: int is_smaller(char *str1, char *str2);
	RETURNS: TRUE if str2 >= str1, FALSE otherwise
	SIDE-EFFECTS: /
 ****/
int is_smaller(const char *str1, const char *str2) {

	int j, len;

	len = (strlen(str1) < strlen(str2)) ? strlen(str2) : strlen(str2);

    for (int i = 0; i < len; i++) {
    	j = (str1[i] % 32) - (str2[i] % 32); // modulo is used to ignore the upper/lower case differences
        if (j > 0) return FALSE;
        if (j < 0) return TRUE;
    }

	// if the strings share all the first characters, but the first string is longer, return FALSE
    if (len < strlen(str1))
        return FALSE;

    return TRUE; // if they're the same return TRUE to ensure stability of the sort
}


/****
	FUNCTION: void print_words(list_t *node);
	RETURNS: /
	SIDE-EFFECTS: prints all the words stored in a linked list structure starting with head
 ****/
void print_words(list_t *head) {
    list_t *node = head; // by copying the pointer, it's easier to call free_mem later
    while (node) {
            printf("%s\n", node->myword);
            node = node->next;
        }
}


/****
	FUNCTION: void free_mem(list_t *node);
	RETURNS: /
	SIDE-EFFECTS: frees all the heap memory allocated to the linked list structure
 ****/
void free_mem(list_t *node) {
	if (node->next == NULL) {
        free(node);
	} else {
        free_mem(node->next);
        free(node);
	}
}

