#define _CRT_SECURRE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TRUE   1
#define FALSE   0
#define TRAVERSE_DEBUG
#define SIZE 100

typedef char NodeData;

typedef struct _TREENODE_ {
    NodeData data;
    struct _TREENODE_* left;
    struct _TREENODE_* right;
}TREENODE;

int top = -1;
TREENODE* stack[SIZE];

void push(TREENODE *p) {
    if (top < SIZE - 1) {
        stack[++top] = p;
    }
}

TREENODE* pop() {
    TREENODE* p = NULL;
    if (top >= 0){
        p = stack[top--];

    }
    return p;
}

TREENODE* peek() {
    TREENODE* p = NULL;
    if(top>=0) {
        p = stack[top];

    }
    return p;
}

void preorder_iter(TREENODE* root) {
    while (1) {
        for (; root; root = root->left) {
            printf("[%d] ", root->data);
            push(root);
        }

        root = pop();
        if (!root) {
            break;
        }
        root = root->right;
    }
}

void inorder_iter(TREENODE* root) {
    while (1) {
        for (; root; root = root->left) {
            push(root);
        }

        root = pop();

        if (!root) {
            break;
        }
        printf("[%d] ", root->data);
        root = root->right;
    }
}

void postorder_iter(TREENODE* root) {

    TREENODE* pre = NULL;
    do {
        for (; root; root = root->left) {
            if (root->right) {
                push(root->right);
            }
            push(root);
        }

        root = pop();

        if ((root->right) && (peek() == root->right)) {
            pop();
            push(root);
            root = root->right;
        }
        else {
            printf("[%d] ", root->data);
            root = NULL;
        }

    } while (top != -1);
}

void test_traversal() {
    TREENODE n1 = { 1, NULL, NULL };
    TREENODE n2 = { 4, &n1, NULL };
    TREENODE n3 = { 16, NULL, NULL };
    TREENODE n4 = { 25, NULL, NULL };
    TREENODE n5 = { 20, &n3, &n4 };
    TREENODE n6 = { 15, &n2, &n5 };
    TREENODE* root = &n6;

    printf("[inorderTraverse]\n");
    inorder_iter(root);
    printf("\n");

    printf("[preorderTraverse]\n");
    preorder_iter(root);
    printf("\n");

    printf("[postorderTraverse]\n");
    postorder_iter(root);
    printf("\n");
}

int main() {
    test_traversal();
    getchar();
    return 0;
}