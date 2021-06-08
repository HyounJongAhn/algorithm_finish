#define _CRT_SECURRE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
//#define TRAVERSE_DEBUG


typedef struct _NODEMAP_ {
    int flag;
    NodeData data;
}NODEMAP;

TREENODE* makerootNode(NodeData data, TREENODE* leftNode, TREENODE* rightNode) {
    TREENODE* root = NULL;
    root = (TREENODE*)calloc(1, sizeof(TREENODE));
    assert(root != NULL);

    root->data = data;
    root->left = leftNode;
    root->right = rightNode;

    return root;
}

void makeLeftSubTree(TREENODE* root, TREENODE* leftSub) {
    root->left = leftSub;
}

void makeRightSubTree(TREENODE* root, TREENODE* rightSub) {
    root->right = rightSub;
}

NodeData getData(TREENODE* node) {
    return(node->data);
}

void setData(TREENODE* node, NodeData data) {
    node->data = data;
}

TREENODE* getLeftSubTree(TREENODE* node) {
    return(node->left);
}

TREENODE* getRightSubTree(TREENODE* node) {
    return(node->right);
}

int getMax(int a, int b)
{
    return ((a > b) ? a : b);
}

int countNode(TREENODE* node) {
    if (node == NULL) return 0;
    return 1 + countNode(node->left) + countNode(node->right);
}

int getHeight(TREENODE* node) {
    int hLeft, hRight;
    if (node == NULL) return 0;
    hLeft = getHeight(node->left);
    hRight = getHeight(node->right);
    return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}

void printGivenLevel(TREENODE* root, int level, NODEMAP* map, int pos)
{
    if (root == NULL)
    {
        return;
    }
    if (level == 1) {
        map[pos].data = root->data;
        map[pos].flag = TRUE;
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level - 1, map, pos * 2);
        printGivenLevel(root->right, level - 1, map, pos * 2 + 1);
    }
}

void showTree(TREENODE* node)
{
    int height = 0;
    int numOfNodes = 0;
    NODEMAP* treeArray = NULL;
    char** square = NULL;
    static int pos = 0;
    int cnt_i;
    int cnt_j;
    int position;
    int start, term, index;

    height = getHeight(node);
    if (height != 0) {
        numOfNodes = (1 << height);
    }
    treeArray = (NODEMAP*)calloc(numOfNodes, sizeof(NODEMAP));
    assert(treeArray != NULL);

    square = (char**)calloc(height, sizeof(char*));
    for (cnt_i = 0; cnt_i < height; cnt_i++)
    {
        square[cnt_i] = (char*)calloc(numOfNodes, sizeof(char));
        memset(square[cnt_i], '.', numOfNodes);
    }

    // level order 순으로 treeArray에 노드의 데이터 삽입
    pos = 1;
    for (cnt_i = 1; cnt_i <= height; cnt_i++) {
        printGivenLevel(node, cnt_i, treeArray, pos);
    }

    // 한칸씩 왼쪽으로 이동
    for (cnt_i = 1; cnt_i <= numOfNodes; cnt_i++)
    {
        treeArray[cnt_i - 1] = treeArray[cnt_i];
    }

    pos = 0;
    start = (1 << (height - 1)) - 1;
    term = (1 << (height));
    index = (1 << (height - 2));
    for (cnt_i = 0; cnt_i < height; cnt_i++)
    {
        for (cnt_j = start; cnt_j < numOfNodes; cnt_j += term)
        {
            if (treeArray[pos].flag == TRUE) {
                if (treeArray[pos].data >= 0 && treeArray[pos].data <= 9) {
                    square[cnt_i][cnt_j] = (treeArray[pos].data + '0');
                }
                else {
                    square[cnt_i][cnt_j] = (treeArray[pos].data);
                }
            }
            else {
                square[cnt_i][cnt_j] = '.';
            }
            pos += 1;
        }
        term >>= 1;
        start -= index;
        index >>= 1;
    }

    printf("\n");
    for (cnt_i = 0; cnt_i < height; cnt_i++)
    {
        for (cnt_j = 0; cnt_j < numOfNodes; cnt_j++)
        {
            printf("%c", square[cnt_i][cnt_j]);
        }
        printf("\n");
    }

    if (treeArray != NULL) {
        free(treeArray);
    }
    if (square != NULL)
    {
        for (cnt_i = 0; cnt_i < height; cnt_i++)
        {
            if (square[cnt_i] != NULL)
            {
                free(square[cnt_i]);
            }
        }
        free(square);
    }
}

void showNodeData(int data) {
    if (data >= 0 && data <= 9) {
        printf("%d ", data);
    }
    else {
        printf("%c ", data);
    }
}

void preorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }

    showNodeData(node->data);    
    preorderTraverse(node->left);
    preorderTraverse(node->right);


}

void inorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }


    inorderTraverse(node->left);
    showNodeData(node->data);
    inorderTraverse(node->right);


}

void postorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }

    postorderTraverse(node->left);
    postorderTraverse(node->right);
    showNodeData(node->data);

}

TREENODE* makeExpTree(char* exp) {
    int i;
    TREENODE* node = NULL;
    int expLen = strlen(exp);

    init();
    for (i = 0; i < expLen; i++) {
        if (isdigit(exp[i])) {
            node = makerootNode(exp[i] - '0', NULL, NULL);
            Push(node);
        }
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%'){
            node = makerootNode(exp[i], NULL, NULL);
            makeRightSubTree(node, pop());
            makeLeftSubTree(node, pop());
            Push(node);
        }
    }
    return pop();
}

void showInfixTypeExp(TREENODE* node) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL || node->right != NULL) {
        printf(" ( ");
    }
    showInfixTypeExp(node->left);
    showNodeData(node->data);
    showInfixTypeExp(node->right);
    if (node->left != NULL || node->right != NULL) {
        printf(" ) ");
    }
}

int evaluateExpTree(TREENODE* node) {
    int op1, op2;

    if (node->left == NULL && node->right == NULL) {
        return getData(node);
    }

    op1 = evaluateExpTree(node->left);
    op2 = evaluateExpTree(node->right);

    switch (getData(node)) {
    case '+':
        return op1 + op2;
        break;
    case '-':
        return op1 - op2;
        break;
    case '*':
        return op1 * op2;
        break;
    case '/':
        return op1 / op2;
        break;
    default:
        break;
    }
    return;
}
void expression_tree_test() {
    char exp[] = "4 2 + 4 / 4 7 7 5 * / + -";
    int ret;
    TREENODE* eTree = makeExpTree(exp);

    printf("[전위 표기법]\n");
    preorderTraverse(eTree);

    printf("\n\n[후위 표기법]\n");
    postorderTraverse(eTree); 

    printf("\n\n[중위 표기법]\n");
    showInfixTypeExp(eTree);

    showTree(eTree);
    ret = evaluateExpTree(eTree);

    printf("ret : %d\n", ret);
}
int main() {
    expression_tree_test();

    getchar();

    return 0;
}