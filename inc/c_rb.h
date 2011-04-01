#ifndef _C_RB_H_
#define _C_RB_H_

typedef struct __c_rb_node {
    struct __c_rb_node *left;
    struct __c_rb_node *right;
    struct __c_rb_node *parent;
    int color; 
    int reference;
    c_pair value;
}c_rb_node;

typedef c_rb_node          CLIB_RB_NODE;
typedef c_rb_node*         CLIB_RB_NODE_PTR;
#define CLIB_RB_NODE_NULL  (CLIB_RB_NODE_PTR)0 



typedef struct __c_rb {
    c_rb_node *_root;
    c_rb_node _sentinel;
    int _type ;
    CLIB_DESTROY destroy_key_fn;
	CLIB_DESTROY destroy_val_fn;
    CLIB_COMPARE compare_key_fn;
}c_rb;

typedef c_rb         CLIB_RB;
typedef c_rb*        CLIB_RB_PTR;
#define CLIB_RB_NULL        (CLIB_RB_PTR)0 

extern CLIB_RB_PTR  new_c_rb        (CLIB_DESTROY, CLIB_DESTROY, CLIB_COMPARE, int );
extern void         delete_c_rb     (CLIB_RB_PTR);
extern CLIB_ERROR   insert_c_rb     (CLIB_RB_PTR, CLIB_TYPE, CLIB_TYPE, int);
extern CLIB_RB_NODE_PTR  remove_c_rb    (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_TYPE    find_c_rb       (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_BOOL    empty_c_rb      (CLIB_RB_PTR);
extern CLIB_RB_NODE_PTR get_next_c_rb(CLIB_RB_PTR , CLIB_RB_NODE_PTR *, CLIB_RB_NODE_PTR *);

#endif
