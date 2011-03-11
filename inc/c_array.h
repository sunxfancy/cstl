#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

typedef void (*destroy)(void*);
typedef int  (*compare)(void*, void *);

typedef struct _c_array {
	void **_elem;
	int  cur_size;
	int  capacity;
	destroy destruct_fn;
	compare compare_fn;
}c_array;

/* 
 * Create, Copy, and Destroy Operations
 */
extern c_array * new_c_array       ( int, destroy, compare );
extern void      delete_c_array    ( c_array *);
/*
 * Nonmodifying Operations
 */
extern int size_c_array        ( c_array * );
extern int empty_c_array       ( c_array *);
extern int capacity_c_array    ( c_array *);
extern void reserve_c_array     ( c_array *, int);
/*
 * Element Access
 */
extern void *front_c_array ( c_array* );
extern void *back_c_array ( c_array* );
extern void *element_at_c_array  ( c_array *, int);
/* 
 * Inserting and Removing Elements
 */ 
extern void push_back_c_array ( c_array *, void *);
extern void pop_back_c_array   ( c_array * );
extern void insert_c_array ( c_array*, int,void *);

/*
 * Comparisons
 */
extern int is_equal_to_c_array ( c_array *, c_array*);

/*
 * Special functions 
 */
extern void for_each_c_array(c_array*, void (*)(void*));

#endif