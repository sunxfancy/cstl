#ifndef _C_SLIST_H_
#define _C_SLIST_H_

typedef struct __c_slist_node {
    clib_type elem;
    struct __c_slist_node *next;
}c_slist_node;

typedef c_slist_node         clib_slist_node;
typedef c_slist_node*        clib_slist_node_ptr;
#define clib_slist_node_null (clib_slist_node_ptr)0

typedef struct __c_slist {
    clib_slist_node_ptr head;
    clib_destroy destruct_fn;
    clib_compare compare_key_fn;
    int size;
}c_slist;

typedef c_slist          clib_slist;
typedef c_slist*         clib_slist_ptr;
#define clib_slist_null (clib_slist_ptr)0

extern clib_slist_ptr new_c_slist(clib_destroy, clib_compare);
extern void           delete_c_slist   (clib_slist_ptr );
extern void           insert_c_slist   (clib_slist_ptr, clib_type, int );
extern void           push_back_c_slist(clib_slist_ptr, clib_type);
extern void           remove_c_slist   (clib_slist_ptr, int );
extern void           for_each_c_slist (clib_slist_ptr, void (*)(void*));
extern clib_type      find_c_slist     (clib_slist_ptr, clib_type);

#endif