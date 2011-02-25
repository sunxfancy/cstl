#ifndef _TREE_H_
#define _TREE_H_
#ifdef bst
  #include "bsttree.h"
  #define tree BSTtree
  #define treeNode BSTtreeNode
  #define newTree NewBSTtree
  #define Insert BSTtreeInsert
  #define Remove BSTtreeRemove
  #define Inorder BSTInorder
#else
  #ifdef avl
    #include "avltree.h"
    #define tree AVLtree
    #define newTree NewAVLtree
    #define Insert AVLtreeInsert
    #define Remove AVLtreeRemove
    #define Inorder AVLInorder
  #else   
    #include "rbtree.h"
    #define tree RBTree
    #define newTree NewRBtree
    #define Insert RBtreeInsert
    #define Remove RBtreeRemove
    #define Inorder RBInorder
  #endif
#endif
void *Search(tree *t, void *key)
{
  void *result[2];
  treeNode *curr=t->root;
  int compRv;
  while(curr)
  {
    compRv = t->comparator(curr->key, key);
    switch(compRv)
    {
      case 0:
        curr=curr->left;
        break;
      case 1:
        curr=curr->right;
        break;
      case 2:
        return curr->data;
    }
  }
  return NULL;
}
#endif
