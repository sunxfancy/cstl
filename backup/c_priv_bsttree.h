#ifndef _BSTTREE_H_
#define _BSTTREE_H_
typedef int (* f_comparator)(void *, void *);
typedef int (* f_deleteKey)(void *);
typedef int (* f_deleteData)(void *);
typedef void (* f_printKey)(void *);
typedef void (* f_printData)(void *);


typedef struct bsttreeNode
{
    struct bsttreeNode *left;
    struct bsttreeNode *right;
    struct bsttreeNode *parent;
    int removed;
    void *key;
    void *data;
}BSTtreeNode;

typedef struct bsttree
{
    struct bsttreeNode *root;
    f_comparator comparator;
    f_deleteKey deleteKey;
    f_deleteData deleteData;
    f_printKey printKey;
    f_printData printData;
}BSTtree;

BSTtree *NewBSTtree(f_comparator, f_deleteKey, f_deleteData, f_printKey, f_printData);
int BSTtreeInsert(BSTtree *, void *, void *); //insert a node
int BSTtreeRemove(BSTtree *, void *); //remove a node
int BSTtreeDelete(BSTtree *); //deletes a RB tree
//void * BSTtreeSearch(BSTtree *, void *);
int BSTInorder(BSTtree *);

#endif

