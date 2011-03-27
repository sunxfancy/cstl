#ifndef _RBTREE_H_
#define _RBTREE_H_

typedef int (* f_comparator)(void *, void *);
typedef int (* f_deleteKey)(void *);
typedef int (* f_deleteData)(void *);
typedef void (* f_printKey)(void *);
typedef void (* f_printData)(void *);

enum colors {red, black};

typedef struct rbtreeNode
{
    struct rbtreeNode *left;
    struct rbtreeNode *right;
    struct rbtreeNode *parent;
    enum colors color;
    void *key;
    void *data;
}RBtreeNode;

typedef struct rbtree
{
    struct rbtreeNode *root;
    f_comparator comparator;
    f_deleteKey deleteKey;
    f_deleteData deleteData;
    f_printKey printKey;
    f_printData printData;
}RBtree;

RBtree *NewRBtree(f_comparator, f_deleteKey, f_deleteData, f_printKey, f_printData); //new rb tree
int RBtreeInsert(RBtree *, void *, void *); //insert a node
int RBtreeRemove(RBtree *, void *); //remove a node
int RBtreeDelete(RBtree *); //deletes a RB tree
int Inorder(RBtree *);

RBtreeNode *getGrandpa(RBtreeNode *);
RBtreeNode *getUncle(RBtreeNode *);
RBtreeNode *getParent(RBtreeNode *);

#endif
