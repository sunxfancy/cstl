#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

#include "c_util.h"

typedef struct _c_array {
    TYPE *_elem;
    int  cur_size;
    int  capacity;
    destroy destruct_fn;
    compare compare_fn;
}c_array;

typedef c_array* ARRAY_PTR;

/* 
 * Create, Copy, and Destroy Operations
 */
extern ARRAY_PTR new_c_array       ( int, destroy, compare );
extern void      delete_c_array    ( ARRAY_PTR);
/*
 * Nonmodifying Operations
 */
extern int size_c_array        ( ARRAY_PTR );
extern int empty_c_array       ( ARRAY_PTR);
extern int capacity_c_array    ( ARRAY_PTR);
extern void reserve_c_array     ( ARRAY_PTR, int);
/*
 * Element Access
 */
extern void *front_c_array ( ARRAY_PTR );
extern void *back_c_array ( ARRAY_PTR );
extern void *element_at_c_array  ( ARRAY_PTR, int);
/* 
 * Inserting and Removing Elements
 */ 
extern void push_back_c_array ( ARRAY_PTR, void *);
extern void pop_back_c_array   ( ARRAY_PTR );
extern void insert_c_array ( ARRAY_PTR, int,void *);

/*
 * Comparisons
 */
extern int is_equal_to_c_array ( ARRAY_PTR, ARRAY_PTR);

/*
 * Special functions 
 */
extern void for_each_c_array(ARRAY_PTR, void (*)(void*));

#endif
