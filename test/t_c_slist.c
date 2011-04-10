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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static void 
free_element ( clib_type ptr ) {
    if ( ptr )
        free ( ptr);
}

void
add_elements_to_list( clib_slist_ptr ll, clib_int x, clib_int y ) {
    clib_int i = 0;
    for ( i = x; i <= y; i++ ) { 
        clib_int *v = ( clib_int *) malloc ( sizeof ( clib_int ));
        memcpy ( v, &i, sizeof ( clib_int ));
        push_back_c_slist ( ll, v , sizeof(v));
        clib_free ( v );
    }
}
void
print_e ( clib_type ptr ) {
    if ( ptr )
        printf ( "%d\n", *(clib_int*)ptr);
}

static clib_int 
compare_element ( clib_type left, clib_type right ) {
    clib_int *l = (clib_int*) left;
    clib_int *r = (clib_int*) right;
    return *l == *r ;
}


void
test_c_slist() {
    clib_int i = 0;
    clib_int *v;
    clib_type outValue;
    clib_slist_ptr list = new_c_slist(free_element,compare_element);

    add_elements_to_list(list,1, 10 );
    for_each_c_slist(list, print_e);

    i = 55;
    v = ( clib_int *) malloc ( sizeof ( clib_int ));
    memcpy ( v, &i, sizeof ( clib_int ));
    insert_c_slist(list,5, v,sizeof(v));
    clib_free ( v );
    for_each_c_slist(list, print_e);

    remove_c_slist(list,5);
    for_each_c_slist(list, print_e);

    remove_c_slist(list,0);
    for_each_c_slist(list, print_e);

    remove_c_slist(list,100);
    for_each_c_slist(list, print_e);

    i = 1;
    v = ( clib_int *) malloc ( sizeof ( clib_int ));
    memcpy ( v, &i, sizeof ( clib_int ));
    insert_c_slist(list,1,v,sizeof(v));
    clib_free ( v );
    for_each_c_slist(list, print_e);

    i = 11;
    v = ( clib_int *) malloc ( sizeof ( clib_int ));
    memcpy ( v, &i, sizeof ( clib_int ));
    insert_c_slist(list,11,v,sizeof(v));
    clib_free ( v );
    for_each_c_slist(list, print_e);

    i = 12;
    v = ( clib_int *) malloc ( sizeof ( clib_int ));
    memcpy ( v, &i, sizeof ( clib_int ));
    insert_c_slist(list,200,v,sizeof(v));
    clib_free ( v );
    for_each_c_slist(list, print_e);

    remove_c_slist(list,list->size);
    for_each_c_slist(list, print_e);

    i = 10;
    if ( clib_true == find_c_slist ( list, &i, &outValue)) {
        assert ( i == *(clib_int*)outValue );
        clib_free ( outValue );
    }
    i = 100;
    assert ( clib_false == find_c_slist ( list, &i, &outValue));

    delete_c_slist ( list );
}
