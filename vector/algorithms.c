#include "algorithms.h"
#include "iterator.h"

#include <stdio.h>

void 
for_each ( iterator start, iterator finish, UNARY_FUNCTION function_ptr ) {
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	void *v = ITR_VALUE(start);
	function_ptr(v);
    }
}
int 
count(iterator start, iterator finish ) {
    int cnt = 0;
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	cnt++;
    }
    return cnt;
}
int 
count_if(iterator start, iterator finish , UNARY_PREDICATE function_ptr) {
    int cnt = 0;
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	void *v = ITR_VALUE(start);
	int result = function_ptr(v);
	if ( result ) {
	    cnt++;
	}
    }
    return cnt;
}
iterator 
min_element (iterator start, iterator finish, COMP_FUNCTION function_ptr) {
    iterator result  = start; 
    start = ITR_NEXT ( start ); 
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	void *left  = ITR_VALUE(result);
	void *right = ITR_VALUE(start);
	if ( !function_ptr ( left, right )) {
	    result = start;
	}
    }
    return result;
}
iterator 
max_element (iterator start, iterator finish, COMP_FUNCTION function_ptr) {
    iterator result  = start; 
    start = ITR_NEXT ( start ); 
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	void *left  = ITR_VALUE(result);
	void *right = ITR_VALUE(start);

	if ( function_ptr ( left, right )) {
	    result = start;
	}
    }
    return result;
}
iterator 
find_if (iterator start, iterator finish, UNARY_PREDICATE function_ptr) {
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	void *v = ITR_VALUE(start);
	int result = function_ptr(v);
	if ( result ) {
	    return start;
	}
    }
    return finish;
}
void fill (iterator start, iterator finish, void* value) {
    for( ;!ITR_EQUALS (start,finish); ITR_NEXT(start)) {
	ITR_VALUE_ASSIGN ( start, value);
    }
}
