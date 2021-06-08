#define _CRT_SECURRE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#define TRAVERSE_DEBUG
#define TRUE   1
#define FALSE   0

typedef int NodeData;

typedef struct _TREENODE_ {
    NodeData data;
    struct _TREENODE_* left;
    struct _TREENODE_* right;

}TREENODE;

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

void preorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }
#if defined (TRAVERSE_DEBUG)
    printf("\n IN %d\n", node->data);
#endif
    printf("%d\n", node->data);
    preorderTraverse(node->left);
    preorderTraverse(node->right);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %d\n", node->data);
#endif
}

void inorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }

#if defined (TRAVERSE_DEBUG)
    printf("\n IN %d\n", node->data);
#endif
    inorderTraverse(node->left);
    printf("%d\n", node->data);
    inorderTraverse(node->right);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %d\n", node->data);
#endif
}

void postorderTraverse(TREENODE* node) {
    if (node == NULL) {
        return;
    }
#if defined (TRAVERSE_DEBUG)
    printf("\n IN %d\n", node->data);
#endif
    postorderTraverse(node->left);
    postorderTraverse(node->right);
    printf("%d\n", node->data);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %d\n", node->data);
#endif
}

void preorderTraverse_1(TREENODE* node) {
    if (node == NULL) {
        return;
    }
#if defined (TRAVERSE_DEBUG)
    printf("\n IN %c\n", node->data);
#endif
    printf("%c\n", node->data);
    preorderTraverse_1(node->left);
    preorderTraverse_1(node->right);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %c\n", node->data);
#endif
}

void inorderTraverse_1(TREENODE* node) {
    if (node == NULL) {
        return;
    }

#if defined (TRAVERSE_DEBUG)
    printf("\n IN %c\n", node->data);
#endif
    inorderTraverse_1(node->left);
    printf("%c\n", node->data);
    inorderTraverse_1(node->right);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %c\n", node->data);
#endif
}

void postorderTraverse_1(TREENODE* node) {
    if (node == NULL) {
        return;
    }
#if defined (TRAVERSE_DEBUG)
    printf("\n IN %c\n", node->data);
#endif
    postorderTraverse_1(node->left);
    postorderTraverse_1(node->right);
    printf("%c\n", node->data);

#if defined (TRAVERSE_DEBUG)
    printf("\n OUT %c\n", node->data);
#endif
}

void deleteTree(TREENODE* node) {
    if (node == NULL) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    printf("del tree data: %c\n", node->data);
    free(node);
}

void test_tree() {
    TREENODE* bt1 = NULL;
    TREENODE* bt2 = NULL;
    TREENODE* bt3 = NULL;
    TREENODE* bt4 = NULL;
    TREENODE* bt5 = NULL;
    TREENODE* bt6 = NULL;
    TREENODE* bt7 = NULL;
    TREENODE* bt8 = NULL;
    TREENODE* bt9 = NULL;

    bt1 = makerootNode(1, NULL, NULL);
    bt2 = makerootNode(2, NULL, NULL);
    bt3 = makerootNode(3, NULL, NULL);
    bt4 = makerootNode(4, NULL, NULL);
    bt5 = makerootNode(5, NULL, NULL);
    bt6 = makerootNode(6, NULL, NULL);
    bt7 = makerootNode(7, NULL, NULL);
    bt8 = makerootNode(8, NULL, NULL);
    bt9 = makerootNode(9, NULL, NULL);

    makeLeftSubTree(bt1, bt2);
    makeRightSubTree(bt1, bt3);
    makeLeftSubTree(bt2, bt4);
    makeRightSubTree(bt2, bt5);
    makeLeftSubTree(bt3, bt6);
    makeRightSubTree(bt3, bt7);
    makeLeftSubTree(bt4, bt8);
    makeRightSubTree(bt4, bt9);

    printf("height of root node: %d\n", getHeight(bt1));
    getchar();

    printf("%d\n", getData(getLeftSubTree(bt1)));
    printf("%d\n", getData(getLeftSubTree(getLeftSubTree(bt1))));

    showTree(bt1);

    printf("[preorderTraverse]\n");
    preorderTraverse(bt1);

    printf("[inorderTraverse]\n");
    inorderTraverse(bt1);

    printf("[postorderTraverse]\n");
    postorderTraverse(bt1);
}

void test_tree2() {
    // (A*B)-(C/D)
    TREENODE* n7 = makerootNode('D',NULL,NULL);
    TREENODE* n6 = makerootNode('C', NULL, NULL);
    TREENODE* n5 = makerootNode('B', NULL, NULL);
    TREENODE* n4 = makerootNode('A', NULL, NULL);
    TREENODE* n3 = makerootNode('/', n6, n7);
    TREENODE* n2 = makerootNode('*', n4, n5);
    TREENODE* n1 = makerootNode('-', n2, n3);


    printf("height of root node: %d\n", getHeight(n1));
    getchar();

    showTree(n1);

    printf("[preorderTraverse]\n");
    preorderTraverse_1(n1);

    printf("[inorderTraverse]\n");
    inorderTraverse_1(n1);

    printf("[postorderTraverse]\n");
    postorderTraverse_1(n1);

    printf("[deleteTree]\n");

    deleteTree(n1);
}

int main() {

    //test_tree();
    test_tree2();
    getchar();
    return 0;
}