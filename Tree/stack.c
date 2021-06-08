#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stackNode* top;

int precedence(char op) {
	switch (op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}
 
void init() {
	top = NULL;
}

int Push(element item) {
	stackNode* temp = (stackNode*)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

int isEmpty() {
	if (top == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
element pop() {
	element item;
	stackNode* temp = top;
	if (top = NULL) {
		printf("\n\nStack is empty!\n");
		return;
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}

element peek() {
	if (top == NULL) {
		printf("\n\nStack is empty!\n");
		return 0;
	}
	else {
		return (top->data);
	}
}

void printStack() {
	int i;
	stackNode* p = top;
	printf("\n STACK [ ");
	while (p) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf("]");
}

void freeStack() {
	stackNode* pre = NULL;
	stackNode* cur = NULL;

	pre = cur = top;
	while (cur != NULL) {
		pre = cur;
		cur = cur->link;
		free(pre);
		pre = NULL;
	}
}
