#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE	100
typedef int element;

typedef struct _ARRAYT_STACK_ {
	element stackArr[STACK_SIZE];
	int topIndex;
	int stackSize;
}ARRAY_STACK;

void init(ARRAY_STACK* stack, int size) {
	stack->stackSize = size;
	stack->topIndex = -1;
}

int isEmpty(ARRAY_STACK* stack) {
	if (stack->topIndex == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFull(ARRAY_STACK* stack) {
	if (stack->topIndex == (stack->stackSize - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

void Push(ARRAY_STACK* stack, element item) {
	if (isFull(stack)) {
		printf("\n\nStack is full\n");
		return;
	}
	else {
		stack->stackArr[++(stack->topIndex)] = item;
	}
}

element pop(ARRAY_STACK* stack) {
	if (isEmpty(stack)) {
		printf("\n\nStack is empty!\n");
		return 0;
	}
	else {
		return stack->stackArr[(stack->topIndex)--];
	}
}

element pek(ARRAY_STACK* stack) {
	if (isEmpty(stack)) {
		printf("\n\nStack is empty!\n");
		exit(1);
	}
	else {
		return stack->stackArr[(stack->topIndex)--];
	}
}

void printStack(ARRAY_STACK* stack) {
	int i;

	printf("\n STACK [ ");
	for (i = stack->topIndex; i >= 0; i--) {
		printf("%d ", stack->stackArr[i]);
	}
	printf("]");
}
void stack_array_test2() {

	ARRAY_STACK* stack1;
	ARRAY_STACK* stack2;
	int i = 0;
	element item;

	printf("\n** 순차 스택 연산 **\n");
	init(&stack1, 10);
	printStack(&stack1);

	for (i = 0; i < 10; i++) {
		Push(&stack1, i);
		printStack(&stack1);
	}
	Push(&stack1, i);
	printStack(&stack1);

	for (i = 0; i < 10; i++) {
		printf("%d", &stack1->stackArr[i]);
		Push(&stack2, i);
		printStack(&stack2);
	}
	Push(&stack2, &stack1->stackArr[i]);
	printStack(&stack2);

	for (i = 0; i < 10; i++) {
		item = pop(&stack2);
		printStack(&stack2);
		printf("\t pop => %d", item);
	}
	item = pop(&stack2);
}

int main() {
	stack_array_test2();
	getchar();
	return 0;
}