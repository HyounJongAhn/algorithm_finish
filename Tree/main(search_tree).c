#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
//#define TRAVERSE_DEBUG
#define TRUE   1
#define FALSE   0



typedef char element;
typedef int NodeData;


typedef struct _TREENODE_ {
    element key;
    struct _TREENODE_* left;
    struct _TREENODE_* right;
}TREENODE;


typedef struct _NODEMAP_ {
    int flag;
    NodeData data;
}NODEMAP;



TREENODE* searchNode(TREENODE* root, char x) {
    TREENODE* p = NULL;
    int count = 0;

    p = root;
    while (p != NULL) {
        count++;
        if (x < p->key) {
            p = p->left;
        }
        else if (x == p->key) {
            printf("%3d��°�� Ž�� ����", count);
            return p;
        }
        else {
            p = p->right;
        }
        
    }
    count++;

    printf("\n %3d��°�� Ž�� ����,ã�� Ű�� �����ϴ�.!\n");
    return p;
}

void insertNode(TREENODE** p, char x) {
    TREENODE* newNode = NULL;
    TREENODE* cur = *p;
    TREENODE* q = NULL;

    while (cur != NULL) {
        if (cur->key == x) {
            printf("�̹� ���� Ű�� �ֽ��ϴ�.\n");
            return;
        }
        q = cur;
        if (x < cur->key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    //x���� ���ٸ� cur=NULL, q�¹ٷ� ���� �ܸ����
    newNode = (TREENODE*)calloc(1, sizeof(TREENODE));
    newNode->key = x;
    newNode->left = NULL;
    newNode->right = NULL;

    if (q != NULL) {
        if (x < q->key) {
            q->left = newNode;
        }
        else {
            q->right = newNode;
        }
    }
    else {
        *p = newNode;
    }
}

void deleteNode(TREENODE** root, element key) {
    TREENODE* parent = NULL, * p = NULL, * succ = NULL, * succ_parent = NULL;
    TREENODE* child = NULL;

    p = *root;

    while ((p != NULL) && (p->key != key)) {
        parent = p;
        if (key < p->key) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }
    if (p == NULL) {
        printf("\n ã�� Ű�� ���� Ʈ���� �����ϴ�.!");
        return;
    }
    if ((p->left == NULL) && (p->right == NULL)) {
        if (parent != NULL) {
            if (parent->left == p) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        
        }
        else {
            *root = NULL;
        }
    }
    else if ((p->left == NULL) || (p->right == NULL)) { // ������1
        if (p->left != NULL) {
            child = p->left;
        }
        else {
            child = p->right;
        }
        if (parent != NULL) {
            if (parent->left == p) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
        else {
            *root = child;
        }
    }
    else { // ������ 2
        succ_parent = p;
        succ = p->left;
        while (succ->right != NULL) {
            succ_parent = succ;
            succ = succ->right;
        }
        if (succ_parent->left == succ) {
            succ_parent->left = succ->left;
        }
        else {
            succ_parent->right = succ->left;
        }
        p->key = succ->key;
        p = succ;
    }
    free(p);
}

void menu() {
    printf("\n*--------------------------*");
    printf("\n\t1 : Ʈ�� ���");
    printf("\n\t2 : ���� ����");
    printf("\n\t3 : ���� ����");
    printf("\n\t4 : ���� �˻�");
    printf("\n\t5 : ����");
    printf("\n*--------------------------*");
    printf("\n�޴��Է� >> ");
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
        map[pos].data = root->key;
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

    // level order ������ treeArray�� ����� ������ ����
    pos = 1;
    for (cnt_i = 1; cnt_i <= height; cnt_i++) {
        printGivenLevel(node, cnt_i, treeArray, pos);
    }

    // ��ĭ�� �������� �̵�
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



void test_bst() {
    TREENODE* root = NULL, *found = NULL;
    char choice, buf, data;
    while (1) {
        menu();
        scanf("%c%c", &choice, &buf);

        switch (choice) {
        case '1':
            printf("[����Ʈ�� ���]\n");
            showTree(root);
            break;
        case '2':
            printf("������ ���ڸ� �Է��ϼ���\n");
            scanf("%c%c", &data, &buf);
            insertNode(&root, data);
            break;
        case '3':
            printf("������ ���ڸ� �Է��ϼ���\n");
            scanf("%c%c", &data, &buf);
            deleteNode(&root,data);
            break;
        case '4':
            printf("ã�� ���ڸ� �Է��ϼ���\n");
            scanf("%C%C", &data, &buf);
            found = searchNode(root, data);
            if (found != NULL) {
                printf("%c�� ã�ҽ��ϴ�.\n", found->key);
            }
            else {
                printf("ã�� ���߽��ϴ�.\n");
            }
            break;
        case '5':
            return;
            break;
        }
    }
}

int main() {

    test_bst();
    getchar();
    return 0;
}