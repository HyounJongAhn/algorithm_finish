#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int element;

typedef struct stackNode{
	element data;
	struct stackNode* link;
}stackNode;

stackNode* top;

void init() {
	top = NULL;
}

int isEmpty() {
	if (top == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int Push(element item) {
	stackNode* temp = (stackNode*)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stackNode* temp = top;
	if (top=NULL) {
		printf("\n\nStack is empty!\n");
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}

element pek() {
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
	while(p){
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
void stack_array_list() {
	int i;
	element item;
	top = NULL;

	printf("\n** 연결 스택 연산 **\n");
	printStack();

	for (i = 0; i < 100; i++) {
		Push(i);
		printStack();
	}
	Push(i);
	printStack();

	for (i = 0; i < 10; i++) {
		item = pop();
		printStack();
		printf("\t pop => %d", item);
	}
	freeStack();
}
int main() {
	stack_array_list();
	getchar();
	return 0;
}