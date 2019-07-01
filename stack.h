/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  A header file providing API for stack implementation in stack.c
 *
 *        Version:  1.0
 *        Created:  06/06/2019 06:41:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gs), gasperstukelj@protonmail.com
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#ifndef __STACK_HEADER__
#define __STACK_HEADER__

#ifndef ENOMEM
#define ENOMEM 12
#endif

typedef struct node node_t;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  check_ptr
 *  Description:  Check whether ptr points to a valid address.
 * =====================================================================================
 */
void check_ptr(node_t *ptr); 


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_stack
 *  Description:  Initializes a stack, and returns the address to its top object.
 * =====================================================================================
 */
node_t * init_stack();


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  push
 *  Description:  Pushes i to the stack pointed to by the head pointer.
 * =====================================================================================
 */
void push(long int i, node_t **head);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pop
 *  Description:  Returns the top-most object from the stack.
 * =====================================================================================
 */
long int pop(node_t **head);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  free_stack
 *  Description:  Frees all the dynamically allocated memory used by the stack.
 * =====================================================================================
 */
void free_stack(node_t **head);

#endif 
