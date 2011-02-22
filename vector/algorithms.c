#include "algorithms.h"
#include "iterator.h"

#include <stdio.h>

void 
for_each ( iterator start, iterator end, UNARY_FUNCTION fn ) {
    while ( ! ITR_EQUALS ( start, end ) ) {
	void *v = ITR_VALUE(start);
	fn(v);
	start = ITR_NEXT (start);
    }
}
