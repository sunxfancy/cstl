#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "iterator.h"


typedef void (*pfnDestruct) ( void *);

typedef struct _vector {
    void **elem     ;
    int    capacity ;
    int    cur_size ;

    iterator *f_iterator;
    pfnDestruct _destroy;

    void   (*push_back  ) ( struct _vector *, void *);
    void * (*element_at ) ( struct _vector *, int   );
    int    (*size       ) ( struct _vector * );
    int    (*empty      ) ( struct _vector * );
    void   (*reserve    ) ( struct _vector *,int );
    void * (*front      ) ( struct _vector *);
    void * (*back       ) ( struct _vector *);
    iterator *(*get_f_iterator) ( struct _vector *);
}VECTOR;
VECTOR   * vector_new            ( int, pfnDestruct); 
void       vector_push_back      ( VECTOR *, void *);
int        vector_size           ( VECTOR *        );
int        vector_empty          ( VECTOR *        );
void       vector_reserve        ( VECTOR *, int   );
void     * vector_element_at     ( VECTOR *, int   );
void     * vector_front          ( VECTOR *        );
void     * vector_back           ( VECTOR *        );
void     * vector_begin          ( void *          ); 
void     * vector_end            ( void *          ); 
void       vector_next           ( void *          );
void       vector_prev           ( void *          ); 
int        vector_is_end         ( void *          );
void     * vector_get_value      ( void *          );
iterator * vector_f_iterator     ( VECTOR *        );
iterator * vector_get_f_iterator ( VECTOR *        );
void       vector_destroy        ( VECTOR *        );

#endif

