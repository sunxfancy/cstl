#ifndef __VECTOR_H_
#define __VECTOR_H_

#include "iterator.h"


typedef void (*DESTROY)(void*);

typedef struct __vector {
    int size;
    int capacity;
    void **elements;
    DESTROY _elem_delete;
}vector;

#define VECTOR_NULL (vector*)0

vector *vector_new(int, DESTROY);
void vector_clear ( vector *);

void vector_push_back ( vector *, void *);
void *vector_element_at ( vector *, int );
int vector_size(vector*);

iterator vector_iterator_begin( vector *);
iterator vector_iterator_end( vector *);

#endif /* __VECTOR_H_ */
