#ifndef _C_DATASTRUCTURE_H_
#define _C_DATASTRUCTURE_H_

typedef void* CLIB_TYPE;
typedef void  (*CLIB_DESTROY)(CLIB_TYPE);
typedef int   (*CLIB_COMPARE)(CLIB_TYPE,CLIB_TYPE);
typedef void  (*CLIB_TRAVERSAL)( CLIB_TYPE);
typedef int   CLIB_ERROR;
typedef int   CLIB_BOOL;


/* Dynamic Arrray */
typedef struct __c_array {
    CLIB_TYPE *_elem;
    int  cur_size;
    int  capacity;
    CLIB_DESTROY destruct_fn;
    CLIB_COMPARE compare_fn;
}c_array;
/* Deque */
typedef struct __c_deque {
    CLIB_TYPE* _elements;
    int _size;
    int _front_index;
    int _back_index;
    int _current_size;
    CLIB_DESTROY _fn_destroy;
    CLIB_COMPARE _fn_compare;
}c_deque;
/* binary Search Tree */
typedef struct __c_bst_node {
    struct __c_bst_node *left;
    struct __c_bst_node *right;
    struct __c_bst_node *parent;
    CLIB_TYPE _key;
}c_bst_node;
typedef struct __c_bst {
    c_bst_node *_root;
    CLIB_DESTROY destroy_fn;
    CLIB_COMPARE compare_fn;
    CLIB_TRAVERSAL traversal_fn;
}c_bst;
/* Read Black Tree */
typedef struct __c_pair {
    CLIB_TYPE _key;
    CLIB_TYPE _value;
}c_pair;
typedef struct __c_rb_node {
    struct __c_rb_node *left;
    struct __c_rb_node *right;
    struct __c_rb_node *parent;
    int color; 
    int reference;
    c_pair value;
}c_rb_node;

typedef struct __c_rb {
    c_rb_node *_root;
    c_rb_node _sentinel;
    CLIB_DESTROY destroy_fn;
    CLIB_COMPARE compare_fn;

    /* 0 for normal Red Black Tree 
     * 1 for set or map 
     * 2 for multimap or multiset 
     */
    int _type ;
}c_rb;
/* Set declaration */
typedef struct __c_set {
    c_rb* root;
    CLIB_DESTROY fn_destroy;
    CLIB_COMPARE fn_compare;
}c_set;

typedef c_array      CLIB_ARRAY;
typedef c_deque      CLIB_DEQUE;
typedef c_bst_node   CLIB_BST_NODE;
typedef c_bst        CLIB_BST;
typedef c_pair       CLIB_PAIR;
typedef c_rb_node    CLIB_RB_NODE;
typedef c_rb         CLIB_RB;
typedef c_set        CLIB_SET;

typedef c_array*     CLIB_ARRAY_PTR;
typedef c_deque*     CLIB_DEQUE_PTR;
typedef c_bst_node*  CLIB_BST_NODE_PTR;
typedef c_bst*       CLIB_BST_PTR;
typedef c_pair*      CLIB_PAIR_PTR;
typedef c_rb_node*   CLIB_RB_NODE_PTR;
typedef c_rb*        CLIB_RB_PTR;
typedef c_set*       CLIB_SET_PTR;

#define CLIB_ARRAY_NULL    (CLIB_ARRAY_PTR)0
#define CLIB_DEQUE_NULL    (CLIB_DEQUE_PTR)0
#define CLIB_BST_NODE_NULL (CLIB_BST_NODE_PTR)0
#define CLIB_BST_NULL      (CLIB_BST_PTR)0
#define CLIB_RB_NODE_NULL  (CLIB_RB_NODE_PTR)0 
#define CLIB_RB_NULL       (CLIB_RB_PTR)0 
#define CLIB_SET_NULL      (CLIB_SET_PTR)0 

#define CLIB_BLACK           0
#define CLIB_RED             1
#define CLIB_MAP_TYPE        1
#define CLIB_MULTI_MAP_TYPE  2
#define CLIB_SET_TYPE        1
#define CLIB_MULTI_SET_TYPE  2
#define CLIB_TRUE            0
#define CLIB_FALSE           1
#define CLIB_NULL            (CLIB_TYPE)0
#define CLIB_INORDER		 0
#define CLIB_PREORDER        1
#define CLIB_POSTORDER       2
#define CLIB_RB_VALUE_COPY   0
#define CLIB_RB_REFER_COPY   1

/* Common Error codes */
#define CLIB_SUCCESS 0

/* Red Black Tree Error Codes 
 * Range is between 100 to 200 
 */
#define CLIB_RBTREE_KEY_DUPLICATE 100
#define CLIB_RBTREE_KEY_NOT_FOUND 101
/* Error Message set 
 * Range from 201 to 300 
 */
#define CLIB_SET_INVALID_INPUT 201


/* Interface Declaration from here */
/* Dynamic Array */
extern CLIB_ARRAY_PTR new_c_array     ( int, CLIB_DESTROY, CLIB_COMPARE );
extern void           delete_c_array  ( CLIB_ARRAY_PTR);
extern int            size_c_array        ( CLIB_ARRAY_PTR );
extern int            empty_c_array       ( CLIB_ARRAY_PTR);
extern int            capacity_c_array    ( CLIB_ARRAY_PTR);
extern void           reserve_c_array     ( CLIB_ARRAY_PTR, int);
extern void*          front_c_array ( CLIB_ARRAY_PTR );
extern void*          back_c_array ( CLIB_ARRAY_PTR );
extern void*          element_at_c_array  ( CLIB_ARRAY_PTR, int);
extern void           push_back_c_array ( CLIB_ARRAY_PTR, void *);
extern void           pop_back_c_array   ( CLIB_ARRAY_PTR );
extern void           insert_c_array ( CLIB_ARRAY_PTR, int,void *);
extern int            is_equal_to_c_array ( CLIB_ARRAY_PTR, CLIB_ARRAY_PTR);
extern void           for_each_c_array(CLIB_ARRAY_PTR, void (*)(void*));
/* Deque */
extern CLIB_DEQUE_PTR new_c_deque(int , CLIB_DESTROY, CLIB_COMPARE );
extern void           delete_c_deque(CLIB_DEQUE_PTR);
extern int            size_c_deque( CLIB_DEQUE_PTR );
extern int            empty_c_deque( CLIB_DEQUE_PTR);
extern CLIB_TYPE      front_c_deque ( CLIB_DEQUE_PTR );
extern CLIB_TYPE      back_c_deque ( CLIB_DEQUE_PTR );
extern void           push_back_c_deque(CLIB_DEQUE_PTR, CLIB_TYPE );
extern void           push_front_c_deque(CLIB_DEQUE_PTR, CLIB_TYPE );
extern void           pop_back_c_deque ( CLIB_DEQUE_PTR);
extern void           pop_front_c_deque ( CLIB_DEQUE_PTR);
extern void           for_each_c_deque(CLIB_DEQUE_PTR, void (*)(void*));
/* Binary Search Tree */
extern CLIB_BST_PTR      new_c_bst    (CLIB_DESTROY, CLIB_COMPARE, CLIB_TRAVERSAL );
extern void              destroy_c_bst(CLIB_BST_PTR);
extern void              insert_c_bst (CLIB_BST_PTR, CLIB_TYPE);
extern void              delete_c_bst (CLIB_BST_PTR, CLIB_TYPE);
extern void              walk_c_bst_r (CLIB_BST_PTR, int );
extern CLIB_BST_NODE_PTR find_c_bst   (CLIB_BST_PTR, CLIB_TYPE);
/* Red Black Tree */
extern CLIB_RB_PTR  new_c_rb        (CLIB_DESTROY, CLIB_COMPARE, int );
extern void         delete_c_rb     (CLIB_RB_PTR);
extern CLIB_ERROR   insert_c_rb     (CLIB_RB_PTR, CLIB_TYPE, CLIB_TYPE, int);
extern CLIB_RB_NODE_PTR  remove_c_rb    (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_TYPE    find_c_rb       (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_BOOL    empty_c_rb      (CLIB_RB_PTR);
extern CLIB_RB_NODE_PTR get_next_c_rb(CLIB_RB_PTR , CLIB_RB_NODE_PTR *, CLIB_RB_NODE_PTR *);
extern void print_c_rb(CLIB_RB_PTR,CLIB_TRAVERSAL);

/* Set */
extern CLIB_SET_PTR new_c_set    ( CLIB_DESTROY, CLIB_COMPARE );
extern CLIB_ERROR  delete_c_set ( CLIB_SET_PTR );
extern CLIB_ERROR  insert_c_set ( CLIB_SET_PTR, CLIB_TYPE, int );
extern CLIB_TYPE   remove_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL   exists_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL   empty_c_set  ( CLIB_SET_PTR);
extern CLIB_ERROR union_c_set        (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR intersection_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR difference_c_set   (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_BOOL  subset_c_set       (CLIB_SET_PTR, CLIB_SET_PTR);
extern void       print_c_set        (CLIB_SET_PTR, CLIB_TRAVERSAL);

/* some utility interfaces */
extern void *clib_malloc(int);
extern void clib_free (CLIB_TYPE);

#endif
