#ifndef _C_SLIST_H_
#define _C_SLIST_H_

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

#endif