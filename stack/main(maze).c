#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE	100
#define MAZE_SIZE	6

typedef struct StackObjectRec {
	short r;
	short c;
}StackObject;

StackObject stack[STACK_SIZE];
int top = -1;
StackObject here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

int init() {
	return(top == -1);
}

int isEmpty() {
	return(top == -1);
}

int isFull() {
	return (top == STACK_SIZE - 1);
	
}

int Push(StackObject item) {
	if (isFull()) {
		printf("\n\nStack is full\n");
	}
	else {
		stack[++top] = item;
	}
}

StackObject pop() {
	if (isEmpty()) {
		printf("\n\nStack is empty!\n");
	}
	else {
		return stack[top--];
	}
}

void printStack() {
	int i;
	for (i = MAZE_SIZE-1; i > top; i--) {
		printf("|    |\n");
	}
	for (i = top; i >= 0; i--) {
		printf("|(%01d,%01d)| \n", stack[i].r,stack[i].c);
	}
	printf("-----\n");
}

void pushloc(int r, int c) {
	if (r < 0 || c < 0) {
		return;
	}
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		StackObject temp;
		temp.r = r;
		temp.c = c;
		Push(temp);
	}
}
void printMaze(char m[MAZE_SIZE][MAZE_SIZE]) {
	int r, c;
	printf("\n\n");

	for (r = 0; r < MAZE_SIZE; r++) {
		for (c = 0; c < MAZE_SIZE; c++) {
			if (c == here.c && r == here.r) {
				printf("m ");
			}
			else {
				if (m[r][c] == 0) {
					printf("0 ");
				}
				else {
					printf("%c ", m[r][c]);
				}
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
void findroot() {
	short r, c;
	here = entry;
	printMaze(maze);
	printStack();
	while (maze[here.r][here.c] != 'x') {
		printMaze(maze);
		r = here.r;
		c = here.c;
		maze[r][c] = '.';

		pushloc(r - 1, c);
		pushloc(r + 1, c);
		pushloc(r, c-1);
		pushloc(r, c+1);
		printStack();
		if (isEmpty()) {
			printf("FAILURE\n");
			return;
		}
		else {
			here = pop();
			
		}
		printMaze(maze);
		printStack();
	}
	printf("SUCCESS!\n");
}
int main() {
	findroot();
	getchar();
	return 0;
} 