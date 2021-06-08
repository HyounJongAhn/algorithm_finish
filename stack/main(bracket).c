#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE	1
#define FALSE	0

typedef char element;

typedef struct stackNode {
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
	if (top = NULL) {
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
	while (p) {
		printf("%c ", p->data);
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
int test_pair(char* exp) {
	char symbol, open_pair;
	int i, len;
	init();
	len = strlen(exp);
	for (i = 0; i < len; i++) {
		symbol = exp[i];
		switch (symbol) {
		case '(':
		case '{':
		case '[':
			Push(symbol);
			break;

		case ')':
		case '}':
		case ']':
			if (isEmpty()) {
				return FALSE;
			}
			else {
				open_pair = pop();
				if ((open_pair == '(' && symbol != ')') ||
					(open_pair == '{' && symbol != '}') ||
					(open_pair == '[' && symbol != ']')){
					return FALSE;
				}
			}
			break;
		}
	}
	if (isEmpty()) {
		return TRUE;
	}
	else {
return FALSE;
	}
}
int precedence(char op) {
	switch (op) {
	case '(':
	case')':
		return 0;
	case'+':
	case'-':
		return 1;
	case'*':
	case'/':
	case'%':
		return 2;

	}
	return -1;
}
void infix_to_postfix(char* infix, char* postfix) {
	int i = 0;
	int j = 0;
	char c, op;

	while (infix[i] != '\0') {
		c = infix[i++];

		if (c >= '0' && c <= '9') {
			postfix[j++] = c;
			while (infix[i] >= '0' && infix[i] <= '9') {
				postfix[j++] = infix[i++];
			}
			postfix[j++] = ' ';
		}
		else if (c == '(') {
			Push(c);
		}
		else if (c == ')') {
			while (!isEmpty()) {
				op = pop();
				if (op == '(') {
					break;
				}
				else {
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
			}
		}
		else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '%') {
			while (!isEmpty()) {
				op = pek();
				if (precedence(c) <= precedence(op)) {
					op = pop();
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
				else {
					break;
				}
			}
			Push(c);
		}
	}
	while (!isEmpty()) {
		postfix[j++] = pop();
		postfix[j++] = ' ';
	}
	postfix[j] = '\0';
}
element evalPostfix(char* exp) {
	int opr1, opr2, value, i;
	int len = strlen(exp); 
	char symbol;

	init();

	for (i = 0; i < len; i++) {
		symbol = exp[i];
		if (symbol >= '0' && symbol <= '9') {
			value = symbol - '0';
			i += 1;
			while (exp[i] >= '0' && symbol <= '9') {
				value *= 10;
				value += (exp[i] - '0');
				i += 1;
			}
			Push(value);
		}
		else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%') {
			opr2 = pop();
			opr1 = pop();

			switch (symbol) {
			case'+': Push(opr1 + opr2); break;
			case'-': Push(opr1 - opr2); break;
			case'*': Push(opr1 * opr2); break;
			case'%': Push(opr1 % opr2); break;
			case'/': Push(opr1 / opr2); break;
			}
		}
	}
	return pop();
}

void postfix_eval_test() {
	int result;
	int i;
	char infix_expr[13][80] = { "3*5-6/2",
		"((4+2)/4)-(3+70/(7*5))",
		"(((5*6)+7)-8)*9))"
	};

	char postfix_expr[320] = { 0x00, };

	for (i = 0; i < 4; i++) {
		printf("[%02d]-th 수식 평가\n", i);
		if (test_pair(infix_expr[i]) == 1) {
			printf("괄호 개수가 일치함\n");
		}
		else {
			printf("괄호 개수가 불일치함\n");
		}

		memset(postfix_expr, 0, sizeof(postfix_expr));

		init();
		infix_to_postfix(infix_expr[i], postfix_expr);

		printf("\n\ninfix: %s -> postfix: %s\n", infix_expr[i], postfix_expr);

		printf("후위 표기식 : %s\n", postfix_expr);

		result = evalPostfix(postfix_expr);

		printf("\n\n연산결과 => %d\n\n", result);

		freeStack();
		getchar();
	}
}


void bracket_test() {
	int ret;

	char* express = "{(A+B)-3}*5+[{cos(x+y)+7}-1]*4";
	ret = test_pair(express);

	if (ret == TRUE) {
		printf("옳은 수식");
	}
	else {
		printf("틀린 수식");

	}
}

int main() {
	//bracket_test();
	postfix_eval_test();
	getchar();
	return 0;
}