#ifndef _AVLTREE_H_
#define _AVLTREE_H_
typedef int (* f_comparator)(void *, void *);
typedef int (* f_deleteKey)(void *);
typedef int (* f_deleteData)(void *);
typedef void (* f_printKey)(void *);
typedef void (* f_printData)(void *);


typedef struct avltreeNode
{
  struct avltreeNode *left;
  struct avltreeNode *right;
  struct avltreeNode *parent;
  unsigned int height[2];
  void *key;
  void *data;
}AVLtreeNode;

typedef struct avltree
{
  struct avltreeNode *root;
  f_comparator comparator;
  f_deleteKey deleteKey;
  f_deleteData deleteData;
  f_printKey printKey;
  f_printData printData;
}AVLtree;
#endif

