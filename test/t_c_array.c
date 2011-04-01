#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static int 
compare_e ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}

static void 
free_e ( void *ptr ) {
    if ( ptr )
    free ( ptr);
}

void 
test_c_array(){
    int size = 10;
	int i = 0;
	CLIB_ARRAY_PTR myArray  = new_c_array (8,compare_e,NULL, sizeof(int));

    {
        assert ( CLIB_TRUE == empty_c_array( myArray ));
    }

    {
	    for ( i = 0; i <= size; i++) {
		    push_back_c_array ( myArray, &i );
	    }
        assert ( CLIB_FALSE == empty_c_array( myArray ));
        assert ( size == size_c_array( myArray ));
	    for ( i = 0; i <= size; i++) {
		    int rv, rc ;
            rc = element_at_c_array ( myArray, i , &rv );
		    assert ( rv == i );
	    }
    }    
    {
        int rv,rc;
        rc = front_c_array ( myArray , &rv);
        assert ( 0 == rv );
    }
    {
        int rv,rc;
        rc = back_c_array ( myArray , &rv);
        assert ( 10 == rv );
    }
    {
        int rv,rc;
        rc = pop_back_c_array ( myArray, &rv);
        assert ( 10 == rv );
        assert ( ( size - 1 ) == size_c_array( myArray ));
        rc = back_c_array ( myArray , &rv);
        assert ( 9 == rv );
    }
    {
        int rc, rv;
        int pos = 5;
        i = 500;
        rc = insert_at_c_array( myArray, pos, &i);
        assert ( rc == CLIB_ERROR_SUCCESS );
        rc = element_at_c_array ( myArray, pos , &rv );
		assert ( rv == i );
        rc = element_at_c_array ( myArray, pos - 1 , &rv );
		assert ( rv == pos - 1 );
        rc = element_at_c_array ( myArray, pos + 1 , &rv );
		assert ( rv == pos );
    }
    {
        delete_c_array ( myArray );
    }

    {
        myArray = new_c_array ( 10, compare_e, free_e, sizeof(int*)); 
        for ( i = 0; i <= size; i ++ ) { 
            int *v = ( int *) malloc ( sizeof ( int ));
            memcpy ( v, &i, sizeof ( int ));
            push_back_c_array ( myArray, &v );
        }   
    }
    {
        assert ( CLIB_FALSE == empty_c_array( myArray ));
        assert ( size == size_c_array( myArray ));
	    for ( i = 0; i <= size; i++) {
		    int rc, *rv;
            rc = element_at_c_array ( myArray, i , &rv );
		    assert ( *rv == i );
	    }
    }
    {
        delete_c_array ( myArray );
    }
}
