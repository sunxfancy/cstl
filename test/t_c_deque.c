#include "c_datastructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
test_c_deque() {
    int flip = 1;
    int i = 0;
    int limit = 20;

    CLIB_DEQUE_PTR myDeq = new_c_deque ( 10, compare_e, NULL, sizeof(int));
    assert ( CLIB_DEQUE_NULL != myDeq );

    for ( i = 0; i <= limit; i++ ) { 
        if ( flip ) {
            push_back_c_deque ( myDeq, &i );
            flip = 0;
        } else {
            push_front_c_deque ( myDeq, &i );
            flip = 1;
        }
    }
    {
       int element;
       front_c_deque ( myDeq, &element );
       assert ( element == limit - 1 );

       back_c_deque ( myDeq, &element );
       assert ( element == limit);
    }
    {
        int element;
        while ( empty_c_deque(myDeq) != CLIB_TRUE ) {
            pop_front_c_deque ( myDeq, &element );
            printf ( "%d\n", element );
        }
    }
    {
        delete_c_deque(myDeq);
    }
    {
        myDeq = new_c_deque ( 10, compare_e, free_e, sizeof(int*)); 
        for ( i = 0; i <= limit; i ++ ) { 
            int *v = ( int *) malloc ( sizeof ( int ));
            memcpy ( v, &i, sizeof ( int ));
            push_back_c_deque ( myDeq, &v );
        }   
    }
    {
        int i = 0;
        int j = 0;
        for ( i = myDeq->head + 1; i < myDeq->tail; i++ ){
            int *elem;
            if ( element_at_c_deque( myDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                assert ( *elem == j++ );
            }
        }
    }
    {
        delete_c_deque(myDeq);
    }


}
