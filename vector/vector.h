#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "../iterator/iterator.h"


typedef void (*pfnDestruct) ( void *);

typedef struct __vector {
    void **elem     ; /* opeque pointer array */
    int    capacity ; /* Current capacity */
    int    cur_size ; /* number of elements in the vector */
    pfnDestruct _destroy;

    int (*container_end) ( struct __vector *);

    int iter_current_pos;
    int iter_end_pos;
}vector;

vector * vector_new         ( int, pfnDestruct); 
void     vector_push_back   ( vector *, void*);
void   * vector_element_at  ( vector *, int );
int      vector_size        ( vector *);
int      vector_empty       ( vector *);
int      vector_capacity    ( vector *);
void   * vector_front       ( vector *);
void   * vector_back        ( vector *);
void     vector_insert      ( vector *,int,void*);
void     vector_clear       ( vector *);
void     vector_pop_back    ( vector *);
void     vector_erase       ( vector *, int);
void     vector_resize      ( vector *, int);

/* Iterator function */
iterator * vector_new_iterator( vector *);
int        vector_itr_end( void *);
void       vector_itr_next (void *);
void *     vector_itr_get_value ( void *);
void       vector_delete_iterator( vector *);


#endif

