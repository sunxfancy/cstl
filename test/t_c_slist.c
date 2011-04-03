#include "c_lib.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static void 
free_element ( void *ptr ) {
    if ( ptr )
        free ( ptr);
}

void
add_elements_to_list( CLIB_SLIST_PTR ll, int x, int y ) {
    int i = 0;
    for ( i = x; i <= y; i++ ) { 
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));
        push_back_c_slist ( ll, v );
    }
}
void
print_e ( void *ptr ) {
    if ( ptr )
        printf ( "%d\n", *(int*)ptr);
}

static int 
compare_element ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}


void
test_c_slist() {
    CLIB_SLIST_PTR list = new_c_slist(free_element,compare_element);
    add_elements_to_list(list,1, 10 );
    for_each_c_slist(list, print_e);
    {
        int i = 55;
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));

        insert_c_slist(list,v,5);
        for_each_c_slist(list, print_e);
    }
    {
        remove_c_slist(list,5);
        for_each_c_slist(list, print_e);
    }
    {
        remove_c_slist(list,1);
        for_each_c_slist(list, print_e);
    }
    {
        remove_c_slist(list,100);
        for_each_c_slist(list, print_e);
    }
    {
        int i = 1;
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));

        insert_c_slist(list,v,1);
        for_each_c_slist(list, print_e);
    }
    {
        int i = 11;
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));

        insert_c_slist(list,v,11);
        for_each_c_slist(list, print_e);
    }
    {
        int i = 12;
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));

        insert_c_slist(list,v,200);
        for_each_c_slist(list, print_e);
    }
    {
        remove_c_slist(list,list->size);
        for_each_c_slist(list, print_e);
    }
    {
        int i = 10;
        int find = *(int*)find_c_slist ( list, &i);
        assert ( find == i );
    }
    {
        int i = 100;
        CLIB_TYPE find = find_c_slist ( list, &i);
        assert ( find ==  CLIB_NULL );
    }
    {
        delete_c_slist ( list );
    }
}
