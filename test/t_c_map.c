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
#include <string.h>
#include <assert.h>

static clib_int
compare_e ( clib_type left, clib_type right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
char *char_value[] = {  "A","B","C","D","E","F","G","H","I","J","K","L","M"
                        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
clib_int int_value[] = { 1,2,3,4,5,6,7,8,9,10,
                      11,12,13,14,15,16,17,18,19,20,
                      21,22,23,24,25,26};

static void 
insert_all ( clib_map_ptr myMap) {
    clib_int size = sizeof(char_value)/sizeof(char_value[0]);
    clib_int i = 0;
    for ( i = 0; i < size; i++ ) {
        char *key = clib_strdup( char_value[i]);
        clib_int key_length = (clib_int)strlen ( key ) + 1;
        clib_int value = int_value[i];
        insert_c_map ( myMap, key, key_length, &value, sizeof(clib_int)); 
        clib_free ( key );
    }
}
static void 
check_exists_all( clib_map_ptr myMap) {
    clib_int size = sizeof(char_value)/sizeof(char_value[0]);
    clib_int i = 0;
    for ( i = 0; i < size; i++ ) {
        clib_type value ;
        assert ( clib_true == exists_c_map ( myMap, char_value[i]));
        assert ( clib_true == find_c_map( myMap, char_value[i], &value));
        assert ( *(int*)value == int_value[i]);
        clib_free ( value );
    }
}

static void 
remove_some_exist(clib_map_ptr myMap) {
    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "A"));
    assert ( clib_false == exists_c_map ( myMap, "A"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "X"));
    assert ( clib_false == exists_c_map ( myMap, "X"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "Z"));
    assert ( clib_false == exists_c_map ( myMap, "Z"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "H"));
    assert ( clib_false == exists_c_map ( myMap, "H"));
}
static void
add_removed_check_all(clib_map_ptr myMap) {

    char *key       = clib_strdup ("A");
    clib_int  key_length = (clib_int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length , &int_value[0], sizeof(clib_int)); 
    clib_free ( key );

    key        = clib_strdup ("X");
    key_length = (clib_int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[22], sizeof(clib_int)); 
    clib_free ( key );

    key        = clib_strdup ("Z");
    key_length = (clib_int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[24], sizeof(clib_int)); 
    clib_free ( key );

    key        = clib_strdup ("H");
    key_length = (clib_int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[7 ], sizeof(clib_int)); 
    clib_free ( key );

    check_exists_all(myMap);
}

void 
test_c_map() {
    clib_map_ptr myMap = new_c_map ( compare_e, NULL, NULL);
    insert_all(myMap);
    check_exists_all(myMap);   
    remove_some_exist(myMap);
    add_removed_check_all(myMap);
    delete_c_map(myMap);
}
