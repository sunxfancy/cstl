#include "c_lib.h"

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

static int
compare_strings ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
static void
free_strings ( void *ptr) {
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
    {
        typedef struct test {
            char *string;
        } TEST_INPUT;
        int index = 0;
        int size = 0;

        TEST_INPUT ti[] ={
            {"A for APPLE"},
            {"B for BALL"},
            {"C for CAT"},
            {"D for DOG"},
            {"E for ELEPHANT"},
            {"F for FISH"},
            {"G for GOAT"},
            {"H for HORSE"},
            {"I for ICECREAM"},
            {"J for JOKER"},
            {"K for KITE"},
            {"L for LAMB"},
            {"M for MONKEY"},
            {"N for NEST"},
            {"O for ORANGE"},
            {"P for POT"},
            {"Q for QUEEN"},
            {"R for RAT"},
            {"S for SHEEP"},
            {"T for TABLE"},
            {"U for UMBRELLA"},
            {"V for VIOLIN"},
            {"W for WAX"},
            {"X for XEROX"},
            {"Y for YUMMY"},
            {"Z for ZEBRA"}
        };

        CLIB_ARRAY_PTR pArray  = new_c_array (8,compare_strings,free_strings, sizeof(char*));
        size = sizeof ( ti ) / sizeof ( ti[0]);
        for ( index = 0; index < size; index++ ){
            char *temp = strdup ( ti[index].string);
            push_back_c_array ( pArray, &temp);
        }
        for ( index = 0; index < size; index++ ){
            char *temp ;
            element_at_c_array ( pArray, index, &temp);
            assert ( strcmp ( temp, ti[index].string) == 0 );
        }
        delete_c_array ( pArray );
    }

}
