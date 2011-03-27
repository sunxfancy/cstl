#ifndef _C_BST_T_
#define _C_BST_T_

#include "c_util.h"

typedef struct __c_bst_node {
    struct __c_bst_node *left;
    struct __c_bst_node *right;
    struct __c_bst_node *parent;
    TYPE _key;
}c_bst_node;

#define BST_NODE_NULL (BST_NODE_PTR)0

typedef struct _c_bst {
    c_bst_node *_root;

    destroy destroy_fn;
    compare compare_fn;
    traversal traversal_fn;

}c_bst;

typedef c_bst* BST_PTR;
typedef c_bst_node* BST_NODE_PTR;

#define BST_INORDER 0
#define BST_PREORDER 1
#define BST_POSTORDER 2

/* Creation/deletion  */
extern BST_PTR new_c_bst(destroy, compare, traversal );
extern void   destroy_c_bst(BST_PTR);
/* Modifying Operations */
extern void   insert_c_bst(BST_PTR, TYPE);
extern void   delete_c_bst(BST_PTR, TYPE);
/* Non-modifying Operations */
extern void   walk_c_bst_r(c_bst *, int );

extern BST_NODE_PTR  find_c_bst(BST_PTR, TYPE);

#endif

