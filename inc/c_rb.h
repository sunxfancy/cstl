#ifndef _C_RB_H_
#define _C_RB_H_

typedef struct __c_rb_node {
    struct __c_rb_node *left;
    struct __c_rb_node *right;
    struct __c_rb_node *parent;
    int color; 
    CLIB_PAIR data;
}c_rb_node;

typedef c_rb_node          CLIB_RB_NODE;
typedef c_rb_node*         CLIB_RB_NODE_PTR;
#define CLIB_RB_NODE_NULL  (CLIB_RB_NODE_PTR)0 



typedef struct __c_rb {
    CLIB_RB_NODE_PTR root;
    CLIB_RB_NODE sentinel;
    CLIB_DESTROY destruct_k_fn;
	CLIB_DESTROY destruct_v_fn;
    CLIB_COMPARE compare_fn;
    CLIB_SIZE    size_of_key;
    CLIB_SIZE    size_of_value;
    int          type;
}c_rb;

typedef c_rb         CLIB_RB;
typedef c_rb*        CLIB_RB_PTR;
#define CLIB_RB_NULL        (CLIB_RB_PTR)0 

extern CLIB_RB_PTR  new_c_rb(CLIB_DESTROY fn_ed, CLIB_DESTROY fn_vd, CLIB_COMPARE fn_c, CLIB_SIZE key_size, CLIB_SIZE value_size );
extern CLIB_ERROR insert_c_rb(CLIB_RB_PTR tree, CLIB_TYPE k, CLIB_TYPE v);


extern void         delete_c_rb       (CLIB_RB_PTR);

extern CLIB_RB_NODE_PTR  remove_c_rb  (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_TYPE    find_c_rb         (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_BOOL    empty_c_rb        (CLIB_RB_PTR);
extern CLIB_RB_NODE_PTR get_next_c_rb (CLIB_RB_PTR , CLIB_RB_NODE_PTR *, CLIB_RB_NODE_PTR *);

#endif
