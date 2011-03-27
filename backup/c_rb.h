#ifndef _C_RB_T_
#define _C_RB_T_

#include "c_util.h"

typedef struct _c_pair {
    TYPE _key;
    TYPE _value;
}c_pair;

typedef struct __c_rb_node {
    struct __c_rb_node *left;
    struct __c_rb_node *right;
    struct __c_rb_node *parent;
    int color; 
    c_pair value;
}c_rb_node;

#define RB_NODE_NULL (RB_NODE_PTR)0

typedef struct _c_rb {
    c_rb_node *_root;
    c_rb_node _sentinel;
    destroy destroy_fn;
    compare compare_fn;
    /* 0 for normal Red Black Tree 
     * 1 for set or map 
     * 2 for multimap or multiset 
     */
    int _type ;
}c_rb;

typedef c_rb* RB_PTR;
typedef c_rb_node* RB_NODE_PTR;

#define RB_INORDER 0
#define RB_PREORDER 1
#define RB_POSTORDER 2

extern RB_PTR new_c_rb(destroy, compare, int );
extern void   delete_c_rb(RB_PTR);

extern CLIB_ERROR   insert_c_rb(RB_PTR, TYPE, TYPE);
extern CLIB_ERROR   remove_c_rb(RB_PTR, TYPE);

extern TYPE  find_c_rb(RB_PTR, TYPE);
extern RB_NODE_PTR  minimum_c_rb(RB_NODE_PTR);
extern RB_NODE_PTR  maximum_c_rb(RB_NODE_PTR);
extern RB_NODE_PTR  successor_c_rb(RB_NODE_PTR);
extern RB_NODE_PTR  predecessor_c_rb(RB_NODE_PTR);

#endif

