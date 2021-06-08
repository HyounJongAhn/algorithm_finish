#include "expression_tree.h"

typedef TREENODE* element;

typedef struct stackNode {
	element data;
	struct stackNode* link;
}stackNode;

void init();
void freeStack();

void push(element item);
element pop();
element peek();