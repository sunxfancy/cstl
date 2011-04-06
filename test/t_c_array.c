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
static void 
test_with_int() {
    int size = 10;
    int i = 0;
    int rv, rc ;
    clib_array_ptr myArray  = new_c_array (8,compare_e,NULL);
    assert ( clib_true == empty_c_array( myArray ));

    for ( i = 0; i <= size; i++) {
        push_back_c_array ( myArray, &i ,sizeof(int));
    }
    assert ( clib_false == empty_c_array( myArray ));
    assert ( size == size_c_array( myArray ));
	for ( i = 0; i <= size; i++) {	    
        rc = element_at_c_array ( myArray, i , &rv );
	    assert ( rv == i );
    }	
    rc = front_c_array ( myArray, &rv );
    assert ( rv == 0 );
    rc = back_c_array( myArray, &rv );
    assert ( rv == size );

    remove_from_c_array( myArray, 0 );
    assert ( size - 1  == size_c_array( myArray ));
    rc = element_at_c_array ( myArray, 0 , &rv );
    assert ( rv == 1 );

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size/2 );
    assert ( size - 1  == size_c_array( myArray ));
    rc = element_at_c_array ( myArray, size/2 , &rv );
    assert ( rv == size/2 + 2 );

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size );
    assert ( size - 1  == size_c_array( myArray ));
    size = size_c_array( myArray );
    rc = element_at_c_array ( myArray, size , &rv );
    assert ( rv == 9 );

    i = 900;
    insert_at_c_array ( myArray, 5, &i, sizeof(int));
    rc = element_at_c_array ( myArray, 5 , &rv );
    assert ( rv == i );
    rc = element_at_c_array ( myArray, 6 , &rv );
    assert ( rv == 7 );



  
    delete_c_array ( myArray );
}

static void 
test_with_pointers() {
    int size = 10;
    int i = 0;
    int *rv, rc ;
    clib_array_ptr myArray  = new_c_array (8,compare_e,free_e);
    assert ( clib_true == empty_c_array( myArray ));

    for ( i = 0; i <= size; i++) {
        int *v = ( int*) malloc ( sizeof(int));
        memcpy ( v, &i, sizeof(int));
        push_back_c_array ( myArray, &v ,sizeof(int*));
    }
    assert ( clib_false == empty_c_array( myArray ));
    assert ( size == size_c_array( myArray ));
	for ( i = 0; i <= size; i++) {	    
        rc = element_at_c_array ( myArray, i , &rv );
	    assert ( *rv == i );
    }	
    rc = front_c_array ( myArray, &rv );
    assert ( *rv == 0 );
    rc = back_c_array( myArray, &rv );
    assert ( *rv == size );

    remove_from_c_array( myArray, 0 );
    assert ( size - 1  == size_c_array( myArray ));
    rc = element_at_c_array ( myArray, 0 , &rv );
    assert ( *rv == 1 );

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size/2 );
    assert ( size - 1  == size_c_array( myArray ));
    rc = element_at_c_array ( myArray, size/2 , &rv );
    assert ( *rv == size/2 + 2 );

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size );
    assert ( size - 1  == size_c_array( myArray ));
    size = size_c_array( myArray );
    rc = element_at_c_array ( myArray, size , &rv );
    assert ( *rv == 9 );

    
    delete_c_array ( myArray );
}

static void 
test_with_strings() {
    int size = 10;
    char *input_array[11];
    int i = 0;
    char *rv, rc ;
    clib_array_ptr myArray  = new_c_array (8,compare_e,free_e);
    assert ( clib_true == empty_c_array( myArray ));

    input_array[0] = "STRING_0";
    input_array[1] = "STRING_1";
    input_array[2] = "STRING_2";
    input_array[3] = "STRING_3";
    input_array[4] = "STRING_4";
    input_array[5] = "STRING_5";
    input_array[6] = "STRING_6";
    input_array[7] = "STRING_7";
    input_array[8] = "STRING_8";
    input_array[9] = "STRING_9";
    input_array[10] = "STRING_10";


    for ( i = 0; i <= size; i++) {
        char *v  = clib_strdup ( input_array[i]);
        push_back_c_array ( myArray ,&v,  sizeof(char*));
    }
    assert ( clib_false == empty_c_array( myArray ));
    assert ( size == size_c_array( myArray ));
	for ( i = 0; i <= size; i++) {	  
        rc = element_at_c_array ( myArray, i , &rv );
	    assert ( strcmp( rv, input_array[i]) == 0);
    }	
    rc = front_c_array ( myArray, &rv );
    assert ( strcmp( rv, input_array[0]) == 0);
    rc = back_c_array( myArray, &rv );
    assert ( strcmp( rv, input_array[size]) == 0);

    remove_from_c_array( myArray, 0 );
    assert ( size - 1  == size_c_array( myArray ));
    rc = element_at_c_array ( myArray, 0 , &rv );
    assert ( strcmp( rv, input_array[1]) == 0);

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size/2 );
    rc = element_at_c_array ( myArray, size/2 , &rv );
    assert ( strcmp( rv, input_array[size/2 + 2]) == 0);

    size = size_c_array( myArray );
    remove_from_c_array( myArray, size );
    assert ( size - 1  == size_c_array( myArray ));
    size = size_c_array( myArray );
    rc = element_at_c_array ( myArray, size , &rv );
    assert ( strcmp( rv, input_array[9]) == 0);

    delete_c_array ( myArray );
}
void 
test_c_array(){
    test_with_int();
    test_with_pointers();
    test_with_strings();
}
