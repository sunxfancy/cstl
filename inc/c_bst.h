#ifndef _C_BST_T_
#define _C_BST_T_

typedef void* T;

typedef void (*destroy)(T);
typedef int  (*compare)(T,T);
typedef void (*traversal)( T);

typedef struct __c_bst_node {
    struct __c_bst_node *_L;
    struct __c_bst_node *_R;
    struct __c_bst_node *_P;
    T _key;
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
extern void   insert_c_bst(BST_PTR, T);
extern void   delete_c_bst(BST_PTR, T);
/* Non-modifying Operations */
extern void   walk_c_bst(c_bst *, int );
extern void   walk_c_bst_r(c_bst *, int );
extern BST_NODE_PTR  find_c_bst(BST_PTR, T);
extern BST_NODE_PTR  minimum_c_bst(BST_NODE_PTR);
extern BST_NODE_PTR  maximum_c_bst(BST_NODE_PTR);
extern BST_NODE_PTR  successor_c_bst(BST_NODE_PTR);
extern BST_NODE_PTR  predecessor_c_bst(BST_NODE_PTR);

extern T get_key_c_bst ( BST_NODE_PTR );
extern BST_NODE_PTR get_left_c_bst ( BST_NODE_PTR );
extern BST_NODE_PTR get_right_c_bst ( BST_NODE_PTR );
extern BST_NODE_PTR get_parent_c_bst ( BST_NODE_PTR );

#endif

