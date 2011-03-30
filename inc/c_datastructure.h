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
#define CLIB_SET_TYPE        0
#define CLIB_MAP_TYPE        1
#define CLIB_GRAPH_TYPE      2
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
    CLIB_COMPARE compare_key_fn;
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

/* ------------------------------------------------------------------------*/
/*                               S E T                                     */
/* ------------------------------------------------------------------------*/
typedef struct __c_set {
    c_rb* root;
}c_set;

typedef c_set        CLIB_SET;
typedef c_set*       CLIB_SET_PTR;
#define CLIB_SET_NULL       (CLIB_SET_PTR)0 

#define CLIB_SET_INVALID_INPUT 501

extern CLIB_SET_PTR new_c_set    ( CLIB_DESTROY, CLIB_COMPARE );
extern void         delete_c_set ( CLIB_SET_PTR );
extern void         insert_c_set ( CLIB_SET_PTR, CLIB_TYPE, int );
extern void         remove_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    exists_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    empty_c_set  ( CLIB_SET_PTR);
extern CLIB_ERROR   union_c_set  ( CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   intersection_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   difference_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_BOOL    subset_c_set (CLIB_SET_PTR, CLIB_SET_PTR);
/* ------------------------------------------------------------------------*/
/*                        M A P                                            */
/* ------------------------------------------------------------------------*/
typedef struct __c_map {
    c_rb* root;
}c_map;

typedef c_map         CLIB_MAP;
typedef c_map*        CLIB_MAP_PTR;
#define CLIB_MAP_NULL (CLIB_MAP_PTR)0 

extern CLIB_MAP_PTR new_c_map    ( CLIB_DESTROY, CLIB_DESTROY,CLIB_COMPARE);
extern void         delete_c_map ( CLIB_MAP_PTR);
extern void         insert_c_map ( CLIB_MAP_PTR, CLIB_TYPE, CLIB_TYPE);
extern void         remove_c_map ( CLIB_MAP_PTR, CLIB_TYPE );
extern CLIB_BOOL    empty_c_map  ( CLIB_MAP_PTR );
extern CLIB_TYPE    find_c_map   ( CLIB_MAP_PTR, CLIB_TYPE );

/* ------------------------------------------------------------------------*/
/*       S I N G L Y    L I N K E D   L I S T                              */
/* ------------------------------------------------------------------------*/
typedef struct __c_slist_node {
    CLIB_TYPE elem;
    struct __c_slist_node *next;
}c_slist_node;
typedef c_slist_node         CLIB_SLIST_NODE;
typedef c_slist_node*        CLIB_SLIST_NODE_PTR;
#define CLIB_SLIST_NODE_NULL (CLIB_SLIST_NODE_PTR)0

typedef struct __c_slist {
    CLIB_SLIST_NODE_PTR head;
    CLIB_DESTROY destruct_fn;
    CLIB_COMPARE compare_key_fn;
    int size;
} c_slist;

typedef c_slist          CLIB_SLIST;
typedef c_slist*         CLIB_SLIST_PTR;
#define CLIB_SLIST_NULL (CLIB_SLIST_PTR)0

extern CLIB_SLIST_PTR new_c_slist(CLIB_DESTROY, CLIB_COMPARE);
extern void           delete_c_slist   (CLIB_SLIST_PTR );
extern void           insert_c_slist   (CLIB_SLIST_PTR, CLIB_TYPE, int );
extern void           push_back_c_slist(CLIB_SLIST_PTR, CLIB_TYPE);
extern void           remove_c_slist   (CLIB_SLIST_PTR, int );
extern void           for_each_c_slist (CLIB_SLIST_PTR, void (*)(void*));
extern CLIB_TYPE      find_c_slist     (CLIB_SLIST_PTR, CLIB_TYPE);

/* ------------------------------------------------------------------------*/
/*                        G R A P H                                        */
/* ------------------------------------------------------------------------*/
/* Graph Implementation is done as a adjancency list */
typedef struct __c_graph {
    CLIB_BOOL is_directed;
    CLIB_RB_PTR graph;
}c_graph;

typedef c_graph  CLIB_GRAPH;
typedef c_graph* CLIB_GRAPH_PTR;
#define CLIB_GRAPH_NULL (CLIB_MAP_PTR)0

#define CLIB_GRAPH_UNDIRECTED 1
#define CLIB_GRAPH_DIRECTED   2

extern CLIB_GRAPH_PTR new_c_graph(CLIB_DESTROY, CLIB_DESTROY,CLIB_COMPARE, CLIB_BOOL);
extern void           delete_c_graph();
extern void add_edge_c_graph ( CLIB_GRAPH_PTR, CLIB_TYPE, CLIB_TYPE );

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

extern void *clib_malloc(int);
extern void clib_free (CLIB_TYPE);

#endif
