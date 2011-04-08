/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "c_lib.h"

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static void 
free_element ( void *ptr ) {
    if ( ptr )
        free ( ptr);
}

void
add_elements_to_list( clib_slist_ptr ll, int x, int y ) {
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
    clib_slist_ptr list = new_c_slist(free_element,compare_element);
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
        clib_type find = find_c_slist ( list, &i);
        assert ( find ==  clib_null );
    }
    {
        delete_c_slist ( list );
    }
}*/
