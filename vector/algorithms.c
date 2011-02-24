#include "algorithms.h"
#include "iterator.h"

#include <stdio.h>

void 
for_each ( iterator start, iterator finish, UNARY_FUNCTION function_ptr ) {
    while ( ! ITR_EQUALS ( start, finish ) ) {
	void *v = ITR_VALUE(start);
	function_ptr(v);
	start = ITR_NEXT (start);
    }
}
int 
count(iterator start, iterator finish ) {
    int cnt = 0;
    while ( ! ITR_EQUALS ( start, finish ) ) {
	cnt++;
	start = ITR_NEXT (start);
    }
    return cnt;
}
int 
count_if(iterator start, iterator finish , UNARY_PREDICATE function_ptr) {
    int cnt = 0;
    while ( ! ITR_EQUALS ( start, finish ) ) {
	void *v = ITR_VALUE(start);
	int result = function_ptr(v);
	if ( result ) {
	    cnt++;
	}
	start = ITR_NEXT (start);
    }
    return cnt;
}
iterator 
min_element (iterator start, iterator finish, COMP_FUNCTION function_ptr) {
    iterator result  = start; 
    start = ITR_NEXT ( start ); 
    while ( ! ITR_EQUALS ( start, finish ) ) {
	void *left  = ITR_VALUE(result);
	void *right = ITR_VALUE(start);

	if ( !function_ptr ( left, right )) {
	    result = start;
	}

	start = ITR_NEXT ( start );
    }
    return result;
}
iterator 
max_element (iterator start, iterator finish, COMP_FUNCTION function_ptr) {
    iterator result  = start; 
    start = ITR_NEXT ( start ); 
    while ( ! ITR_EQUALS ( start, finish ) ) {
	void *left  = ITR_VALUE(result);
	void *right = ITR_VALUE(start);

	if ( function_ptr ( left, right )) {
	    result = start;
	}
	start = ITR_NEXT ( start );
    }
    return result;
}
iterator 
find_if (iterator start, iterator finish, UNARY_PREDICATE function_ptr) {
    while ( ! ITR_EQUALS ( start, finish ) ) {
	void *v = ITR_VALUE(start);
	int result = function_ptr(v);
	if ( result ) {
	    return start;
	}
    }
    return finish;
}
