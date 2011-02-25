#include "vector.h"
#include <malloc.h>

/* Vector Iterator implementation */
iterator 
vector_iterator_next(iterator *cur ) {
    void **pn = cur->_l;
    ++pn;
    cur->_l = pn;
    return *cur;
}
iterator 
vector_iterator_prev(iterator *cur ) {
    void **pn = cur->_l;
    --pn;
    cur->_l = pn;
    return *cur;
}
void *
vector_iterator_value ( iterator *pos ) {
    return *(void**)pos->_l;
}
int 
vector_iterator_equals ( iterator *left, iterator *right ) {
    return (left->_l == right->_l && left->ptr_ft == right->ptr_ft );
}
void
vector_iterator_value_assign ( iterator *pos, void *value) {
    *(void**)pos->_l =  value;
}
static iterator_ft vector_iterator_ft = {
    vector_iterator_next,
    vector_iterator_prev,
    vector_iterator_value,
    vector_iterator_equals
};
iterator 
vector_iterator_begin( vector *vec ) {
    iterator itr;
    itr.ptr_ft = &vector_iterator_ft;
    itr._l   = &vec->elements[0];
    return itr;
}
iterator 
vector_iterator_end( vector *vec){
    iterator itr;
    itr.ptr_ft = &vector_iterator_ft;
    itr._l   = &vec->elements[vec->size ];
    return itr;
}
/* ------------------------------------------------- */

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
