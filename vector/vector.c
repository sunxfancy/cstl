#include "vector.h"
#include <malloc.h>

vector *
vector_new(int s, DESTROY fn) {
    int size = s < 8 ? 8 : s;
    vector *t   = (vector*) malloc ( sizeof ( vector ));
    if ( ! t ) return VECTOR_NULL;

    t->size     = 0;
    t->capacity = size;

    t->elements = (void **) malloc ( (sizeof ( void *)) * size );
    t->_elem_delete = fn;

    return t;
}

void 
vector_push_back ( vector *vec, void *elem) {

    int new_size = vec->capacity * 2 ;

    if ( vec->size == vec->capacity ) {
	vec->elements = (void**)realloc ( vec->elements, new_size * 
	                                                   sizeof ( void *));
	vec->capacity = new_size;
    }
    vec->elements[vec->size++] = elem;
}

void *
vector_element_at ( vector *vec, int pos) {
    return ( void*) vec->elements[pos];
}
void
vector_clear ( vector *vec ) {
    int i  = 0;
    if ( vec->_elem_delete ) {
	for ( i = 0; i < vec->size; i++ ) {
	    (vec->_elem_delete)(vec->elements[i]);
	}
    }
    free ( vec->elements );
    free ( vec );
}
int
vector_size ( vector *vec )  {
    return vec->size;
}
/* Vector Iterator implementation */
static iterator_ft vector_iterator_ft = {
    vector_next,
    vector_prev,
    vector_equals
};

iterator 
vector_begin( vector *vec ) {
    iterator itr;
    itr.ptr_ft = &vector_iterator_ft;
    itr._l   = &vec->elements[0];
    return itr;
}
iterator 
vector_end( vector *vec){
    iterator itr;
    itr.ptr_ft = &vector_iterator_ft;
    itr._l   = &vec->elements[vec->size ];
    return itr;
}
iterator 
vector_next(iterator cur ) {
    iterator itr;
    void **pn = cur._l;
    ++pn;
    itr._l = pn;
    itr.ptr_ft = &vector_iterator_ft;
    return itr;
}
iterator 
vector_prev(iterator cur ) {
    iterator itr;
    void **pn = cur._l;
    --pn;
    itr._l = pn;
    itr.ptr_ft = &vector_iterator_ft;
    return itr;
}
int 
vector_equals ( iterator left, iterator right ) {
    return (left._l == right._l && left.ptr_ft == right.ptr_ft );
}
