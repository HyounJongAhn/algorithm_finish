#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE	100
typedef int element;

element stack[STACK_SIZE];
int top = -1;

void init() {
	top = -1;
}

int isEmpty() {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFull() {
	if (top == STACK_SIZE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int Push(element item) {
	if (isFull()) {
		printf("\n\nStack is full\n");
		return;
	}
	else {
		stack[++top] = item;
	}
}

element pop() {
	if (isEmpty()) {
		printf("\n\nStack is empty!\n");
		return 0;
	}
	else {
		return stack[top--];
	}
}

element pek() {
	if (isEmpty()) {
		printf("\n\nStack is empty!\n");
		exit(1);
	}
	else {
		return stack[top--];
	}
}

void printStack() {
	int i;

	printf("\n STACK [ ");
	for (i = top; i >= 0; i--) {
		printf("%d ", stack[i]);
	}
	printf("]");
}

void stack_array_test1() {
	int i = 0;
	element item;

	printf("\n** 순차 스택 연산 **\n");
	printStack();

	for (i = 0; i < 10; i++) {
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
	item = pop();
	printStack();
	printf("\t pop => %d", item);
	item = pop();
}
int main() {
	stack_array_test1();
	getchar();
	return 0;
}