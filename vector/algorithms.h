#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "iterator.h"

typedef void (*UNARY_FUNCTION) ( void *);
typedef int  (*UNARY_PREDICATE) ( void *);
typedef int  (*COMP_FUNCTION ) ( void *, void *);

/* Non Modifying Algorithms */
/* Performs an operation for each element */
void for_each ( iterator , iterator , UNARY_FUNCTION );
/*Returns the number of elements */
int count(iterator , iterator);
/* Returns the number of elements that match a criterion  */
int count_if(iterator, iterator, UNARY_PREDICATE);

/* Minimum and Maximum 
 * Complexity of following two algorithms is
 * liner 
 */
iterator min_element (iterator , iterator , COMP_FUNCTION );
iterator max_element (iterator , iterator , COMP_FUNCTION );
/*
 * Search First Matching Element
 * Complexity: linear (at most, numberOfElements 
 * comparisons or calls of op() respectively). 
 * Associative containers (sets, multisets, maps, and multimaps) i
 * provide an equivalent member function, find(), i
 * that has logarithmic instead of linear complexity
 * Should be used only for sequence container
 */
iterator find_if (iterator, iterator, UNARY_PREDICATE ); 

/*assigns newValue to each element in the range [beg,end). */
void fill (iterator , iterator , void*);

#endif /* _ALGORITHMS_H_ */

