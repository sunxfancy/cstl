#ifndef _C_DATASTRUCTURE_H_
#define _C_DATASTRUCTURE_H_

/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void* CLIB_TYPE;
typedef void  (*CLIB_DESTROY)(CLIB_TYPE);
typedef int   (*CLIB_COMPARE)(CLIB_TYPE,CLIB_TYPE);
typedef void  (*CLIB_TRAVERSAL)( CLIB_TYPE);
typedef int   CLIB_ERROR;
typedef int   CLIB_BOOL;

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

#define CLIB_SUCCESS 0

/* ------------------------------------------------------------------------*/
/*                     D Y N A M I C    A R R A Y                          */
/* ------------------------------------------------------------------------*/
typedef struct __c_array {
    CLIB_TYPE *_elem;
    int  cur_size;
    int  capacity;
    CLIB_DESTROY destruct_fn;
    CLIB_COMPARE compare_fn;
}c_array;

typedef c_array      CLIB_ARRAY;
typedef c_array*     CLIB_ARRAY_PTR;
#define CLIB_ARRAY_NULL     (CLIB_ARRAY_PTR)0

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

/* ------------------------------------------------------------------------*/
/*                 D O U B L E    E N E D E D     Q U E U E                */
/* ------------------------------------------------------------------------*/
typedef struct __c_deque {
    CLIB_TYPE* _elements;
    int _size;
    int _front_index;
    int _back_index;
    int _current_size;
    CLIB_DESTROY _fn_destroy;
    CLIB_COMPARE _fn_compare;
}c_deque;

typedef c_deque          CLIB_DEQUE;
typedef c_deque*         CLIB_DEQUE_PTR;
#define CLIB_DEQUE_NULL  (CLIB_DEQUE_PTR)0

extern CLIB_DEQUE_PTR new_c_deque       (int , CLIB_DESTROY, CLIB_COMPARE );
extern void           delete_c_deque    (CLIB_DEQUE_PTR);
extern int            size_c_deque      (CLIB_DEQUE_PTR );
extern int            empty_c_deque     (CLIB_DEQUE_PTR);
extern CLIB_TYPE      front_c_deque     (CLIB_DEQUE_PTR );
extern CLIB_TYPE      back_c_deque      (CLIB_DEQUE_PTR );
extern void           push_back_c_deque (CLIB_DEQUE_PTR, CLIB_TYPE );
extern void           push_front_c_deque(CLIB_DEQUE_PTR, CLIB_TYPE );
extern void           pop_back_c_deque  (CLIB_DEQUE_PTR);
extern void           pop_front_c_deque (CLIB_DEQUE_PTR);
extern void           for_each_c_deque  (CLIB_DEQUE_PTR, void (*)(void*));

/* ------------------------------------------------------------------------*/
/*             B I N A R Y      S E A R C H     T R E E                    */ 
/* ------------------------------------------------------------------------*/
typedef struct __c_bst_node {
    struct __c_bst_node *left;
    struct __c_bst_node *right;
    struct __c_bst_node *parent;
    CLIB_TYPE _key;
}c_bst_node;

typedef c_bst_node   CLIB_BST_NODE;
typedef c_bst_node*  CLIB_BST_NODE_PTR;
#define CLIB_BST_NODE_NULL  (CLIB_BST_NODE_PTR)0


typedef struct __c_bst {
    c_bst_node *_root;
    CLIB_DESTROY destroy_fn;
    CLIB_COMPARE compare_fn;
    CLIB_TRAVERSAL traversal_fn;
}c_bst;

typedef c_bst           CLIB_BST;
typedef c_bst*          CLIB_BST_PTR;
#define CLIB_BST_NULL   (CLIB_BST_PTR)0

extern CLIB_BST_PTR      new_c_bst    (CLIB_DESTROY, CLIB_COMPARE, CLIB_TRAVERSAL );
extern void              destroy_c_bst(CLIB_BST_PTR);
extern void              insert_c_bst (CLIB_BST_PTR, CLIB_TYPE);
extern void              delete_c_bst (CLIB_BST_PTR, CLIB_TYPE);
extern void              walk_c_bst_r (CLIB_BST_PTR, int );
extern CLIB_BST_NODE_PTR find_c_bst   (CLIB_BST_PTR, CLIB_TYPE);
/* ------------------------------------------------------------------------*/
/*             P  A  I   R                                                 */
/* ------------------------------------------------------------------------*/
typedef struct __c_pair {
    CLIB_TYPE _key;
    CLIB_TYPE _value;
}c_pair;

typedef c_pair         CLIB_PAIR;
typedef c_pair*        CLIB_PAIR_PTR;
#define CLIB_PAIR_NULL (CLIB_PAIR_PTR)0

/* ------------------------------------------------------------------------*/
/*             R E D     B L A C K      T R E E                            */ 
/* ------------------------------------------------------------------------*/
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

#define CLIB_RBTREE_KEY_DUPLICATE 400
#define CLIB_RBTREE_KEY_NOT_FOUND 401


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

typedef c_rb         CLIB_RB;
typedef c_rb*        CLIB_RB_PTR;
#define CLIB_RB_NULL        (CLIB_RB_PTR)0 

extern CLIB_RB_PTR  new_c_rb        (CLIB_DESTROY, CLIB_COMPARE, int );
extern void         delete_c_rb     (CLIB_RB_PTR);
extern CLIB_ERROR   insert_c_rb     (CLIB_RB_PTR, CLIB_TYPE, CLIB_TYPE, int);
extern CLIB_RB_NODE_PTR  remove_c_rb    (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_TYPE    find_c_rb       (CLIB_RB_PTR, CLIB_TYPE);
extern CLIB_BOOL    empty_c_rb      (CLIB_RB_PTR);
extern CLIB_RB_NODE_PTR get_next_c_rb(CLIB_RB_PTR , CLIB_RB_NODE_PTR *, CLIB_RB_NODE_PTR *);
extern void print_c_rb(CLIB_RB_PTR,CLIB_TRAVERSAL);

/* ------------------------------------------------------------------------*/
/*                               S E T                                     */
/* ------------------------------------------------------------------------*/
typedef struct __c_set {
    c_rb* root;
    CLIB_DESTROY fn_destroy;
    CLIB_COMPARE fn_compare;
}c_set;

typedef c_set        CLIB_SET;
typedef c_set*       CLIB_SET_PTR;
#define CLIB_SET_NULL       (CLIB_SET_PTR)0 

#define CLIB_SET_INVALID_INPUT 501

extern CLIB_SET_PTR new_c_set    ( CLIB_DESTROY, CLIB_COMPARE );
extern CLIB_ERROR   delete_c_set ( CLIB_SET_PTR );
extern CLIB_ERROR   insert_c_set ( CLIB_SET_PTR, CLIB_TYPE, int );
extern CLIB_TYPE    remove_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    exists_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    empty_c_set  ( CLIB_SET_PTR);
extern CLIB_ERROR   union_c_set  ( CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   intersection_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   difference_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_BOOL    subset_c_set (CLIB_SET_PTR, CLIB_SET_PTR);
extern void         print_c_set  (CLIB_SET_PTR, CLIB_TRAVERSAL);
/* ------------------------------------------------------------------------*/
/*                        M U L T I     S E T                              */
/* ------------------------------------------------------------------------*/
typedef struct __c_multi_set {
    c_rb* root;
    CLIB_DESTROY fn_destroy;
    CLIB_COMPARE fn_compare;
}c_multi_set;

typedef c_multi_set  CLIB_MULTI_SET;
typedef c_multi_set* CLIB_MULTI_SET_PTR;
#define CLIB_MULTI_SET_NULL (CLIB_MULTI_SET_PTR)0 

extern CLIB_MULTI_SET_PTR new_c_multiset    ( CLIB_DESTROY, CLIB_COMPARE);
extern void               delete_c_multiset ( CLIB_MULTI_SET_PTR);
extern CLIB_ERROR         insert_c_multiset ( CLIB_MULTI_SET_PTR, CLIB_TYPE, int );
extern CLIB_TYPE          remove_c_multiset ( CLIB_MULTI_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL          exists_c_multiset ( CLIB_MULTI_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL          empty_c_multiset  ( CLIB_MULTI_SET_PTR );

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

extern void *clib_malloc(int);
extern void clib_free (CLIB_TYPE);

#endif
