#define TRUE   1
#define FALSE   0

typedef int NodeData;

typedef struct _TREENODE_ {
    NodeData data;
    struct _TREENODE_* left;
    struct _TREENODE_* right;

}TREENODE;

