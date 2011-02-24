#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algorithms.h"

vector *vec;

void 
FREE_ELEMENTS ( void *ptr ) {
    if ( ptr ) {
	int*t = (int*) ptr;
	free ( t );
    }
    return;
}

void 
INSERT_ELEMENTS (int first, int last)
{
    int i = 0;
    vec = vector_new ( 10 ,FREE_ELEMENTS);
    for (i=first; i<=last; ++i) {
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &i, sizeof ( int ));
	vector_push_back ( vec, v ); 
    }
}
void 
PRINT_ELEMENTS ()
{
    iterator start = vector_begin( vec);
    iterator end   = vector_end  ( vec );
    while ( ! ITR_EQUALS( start, end )) {
	printf ( "%d\n", *((int*)ITR_VALUE ( start )));
	start = ITR_NEXT ( start );
    }
}

void
test_push_back() {
    INSERT_ELEMENTS (0,9);
    PRINT_ELEMENTS ();
    vector_clear( vec );
}
void
test_algorithms_for_each(){

    void print_elem ( void *v ) {
	if ( v ) {
	    int *t = (int *) v;
	    printf ( "[ for each ]%d\n", *t);
	}
    }
    INSERT_ELEMENTS (0,9);
    for_each ( vector_begin(vec), 
	       vector_end ( vec ), 
	       print_elem);
    vector_clear( vec );
}
void
test_algorithms_count() {
    INSERT_ELEMENTS (0, 9 );
    int cnt = count(vector_begin(vec),
		    vector_end ( vec ));
    printf ( "algorithm count result = %d\n", cnt );
    INSERT_ELEMENTS (10, 19 );
    cnt = count(vector_begin(vec),
		vector_end ( vec ));
    printf ( "algorithm count result = %d\n", cnt );
    vector_clear( vec );
}
void 
test_algorithms_count_if() {
    int isEven (void *v ) {
	int elem = *((int*)v);
	return elem % 2 == 0;
    }
    INSERT_ELEMENTS ( 0, 9 );
    int result = count_if ( vector_begin( vec),
			    vector_end ( vec ), isEven );
    printf ( "[test_algorithms_count_if] Result = %d\n", result );
    vector_clear ( vec );
}
void
test_algorithms_min_max()
{
    int less (void *left, void *right ) {
	return  *((int*)left)  < *((int*)right);
    }
    INSERT_ELEMENTS (0, 9 );

    iterator min = min_element ( vector_begin ( vec ), vector_end ( vec ), less);
    iterator max = max_element ( vector_begin ( vec ), vector_end ( vec ), less);

    printf ( "[ min_element ] Result = %d\n", *(int*)ITR_VALUE(min));
    printf ( "[ max_element ] Result = %d\n", *(int*)ITR_VALUE(max));

    vector_clear ( vec );
}
void
test_algorithms_find_if()
{
    int equal(void *left, void *right ) {
	return  *((int*)left)  == *((int*)right);
    }
    INSERT_ELEMENTS (0, 9 );
    iterator found = find_if ( vector_begin ( vec ), vector_end ( vec ), equal);

    if ( ITR_EQUALS ( found, vector_end( vec ))){
	printf ( "Not Found \n");
    }else {
	printf ( "Found\n");
    }

    vector_clear ( vec );
}


int main ( int argc, char **argv ) {
    test_push_back(); 
    test_algorithms_for_each();
    test_algorithms_count();
    test_algorithms_count_if();
    test_algorithms_min_max();
    return 0;
}

