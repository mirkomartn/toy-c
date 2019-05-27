// Reads an unlimited number of strings (max 63 chars) from stdin until EOF or STOP. The number of unique strings read is then printed.
// Written by Gašper Štukelj.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD 64 // in addition to this, the number in the scanf() call in the get_word function needs to be changed as well
#define TRUE 1
#define FALSE 0
#define STOP "."

typedef struct linked_list {
	char myword[WORD];
	struct linked_list *next;
} list_t;


int get_word(list_t *root);
void print_words(list_t *root);
void free_mem(list_t *node);


int main(void) {
	list_t *root = (list_t *) malloc(sizeof(list_t));
    root->next = NULL;

	while (get_word(root)) {
		continue;
	}
    
    print_words(root);

    free_mem(root);

	return 0;
}


/****
	FUNCTION: int get_word(list_t *root, int *count);
	RETURNS: FALSE if EOF or STOP character is read, TRUE otherwise
	SIDE-EFFECTS: if a new string is read, create a new node in the linked list structure, save the string in it, and increment the counter by 1
 ****/
int get_word(list_t *root) {
	char word[WORD];
    list_t *node = root;

	if (scanf("%63s", word) == EOF)
		return FALSE;

    if (!strcmp(word, STOP))
        return FALSE;

	// check if the string is already stored, if so terminate the function call by returning TRUE
	while(node->next != NULL) {
		if (strcmp(node->myword, word)) {
			node = node->next;
			continue;
		}
		return TRUE;
	}

	// create a new node in the linked list, store the scanned word, and increment the counter
    node->next = (list_t *) malloc(sizeof(list_t));
    node->next->next = NULL;
    strcpy(node->myword, word);

	return TRUE;
}

/****
	FUNCTION: void print_words(list_t *node);
	RETURNS: /
	SIDE-EFFECTS: prints all the words stored in a linked list structure starting with head
 ****/
void print_words(list_t *root) {
    list_t *node = root; // by copying the pointer, it's easier to call free_mem later
    while (node->next != NULL) {
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

