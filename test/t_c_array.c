#include "c_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ARRAY_PTR  test_array;
ARRAY_PTR  test_array1;
int i = 0;

static void 
free_element ( void *ptr ) {
    if ( ptr )
	free ( ptr);
}
static int 
compare_element ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}
static int 
compare_element1 ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}

static void 
function_for_each ( void *ptr ) {
    int i = *(int*) ptr ;
    printf ( "%d\n", 2 * i );
}


#define ADD_ELEMENTS( x, y ) \
    test_array = new_c_array ( 10, free_element, compare_element ); \
for ( i = (x); i <= (y); i ++ ) { \
    int *v = ( int *) malloc ( sizeof ( int ));\
    memcpy ( v, &i, sizeof ( int ));\
    push_back_c_array ( test_array, v );\
}
#define ADD_ELEMENTS1( x, y ) \
    test_array1 = new_c_array ( 10, free_element, compare_element ); \
for ( i = (x); i <= (y); i ++ ) { \
    int *v = ( int *) malloc ( sizeof ( int ));\
    memcpy ( v, &i, sizeof ( int ));\
    push_back_c_array ( test_array1, v );\
}
#define ADD_ELEMENTS2( x, y ) \
    test_array1 = new_c_array ( 10, free_element, compare_element1 ); \
for ( i = (x); i <= (y); i ++ ) { \
    int *v = ( int *) malloc ( sizeof ( int ));\
    memcpy ( v, &i, sizeof ( int ));\
    push_back_c_array ( test_array1, v );\
}

#define ADD_ONE_ELEMENT(x) \
{\
    int *v = ( int *) malloc ( sizeof ( int ));\
    memcpy ( v, &(x), sizeof ( int )); \
    push_back_c_array ( test_array, v ); \
}
#define INSERT_ELEMENT(x,pos) \
{\
    int *v = ( int *) malloc ( sizeof ( int ));\
    memcpy ( v, &(x), sizeof ( int )); \
    insert_c_array ( test_array, (pos),v ); \
}


#define DELETE_ARRAY \
    delete_c_array ( test_array );

#define DELETE_ARRAY1 \
    delete_c_array ( test_array1 );

#define PRINT_ELEMENT \
    for ( i = 0; i < size_c_array( test_array ); i++) { \
	printf ( "%d\n", *((int*)element_at_c_array ( test_array, i ))); \
    }
#define TEST_VALUE( RESULT, EXPECTED_VALUE) \
    if ( (RESULT) == (EXPECTED_VALUE)) { \
	printf ( "PASS \n"); \
    }else {\
	printf ( "FAIL \n");\
    }
#define PRINT_TEST_CASE(x) \
    printf ( "Testing  %-20s .....   ", (x));


void
t_size_c_array(){
    const int size = 10;
    int result = 0;
    PRINT_TEST_CASE("size_c_array");
    ADD_ELEMENTS ( 0, 9 );
    result = size_c_array ( test_array );
    TEST_VALUE(result, size);
    DELETE_ARRAY;
}

void
t_empty_c_array(){
    int result = 0;
    PRINT_TEST_CASE("empty_c_array");
    ADD_ELEMENTS ( 0, 9 );
    result = empty_c_array ( test_array );
    TEST_VALUE(result, 0 );
    DELETE_ARRAY;
}
void
t_capacity_c_array() {
    int i = 33;
    int result = 0;
    PRINT_TEST_CASE("capacity_c_array");
    ADD_ELEMENTS ( 0, 9 );
    result = capacity_c_array ( test_array );
    TEST_VALUE(result, 10 );

    ADD_ONE_ELEMENT(i);
    PRINT_TEST_CASE("capacity_c_array");
    result = capacity_c_array ( test_array );
    TEST_VALUE(result, 20 );
    DELETE_ARRAY;
}
void
t_reserve_c_array() {
    int result = 0;
    PRINT_TEST_CASE("reserve_c_array");
    ADD_ELEMENTS ( 0, 9 );
    reserve_c_array(test_array,100);
    result = capacity_c_array ( test_array );
    TEST_VALUE(result, 100 );
    DELETE_ARRAY;
}
void
t_front_c_array() {
    int result = 0;
    void *elem = ( void *) 0;
    PRINT_TEST_CASE("front_c_array");
    ADD_ELEMENTS ( 0, 9 );
    elem = (void*)front_c_array( test_array );
    result = *(int*)(elem);
    TEST_VALUE(result, 0 );
    DELETE_ARRAY;
}
void
t_back_c_array() {
    int result = 0;
    void *elem = ( void *) 0;
    PRINT_TEST_CASE("back_c_array");
    ADD_ELEMENTS ( 0, 9 );
    elem = (void*)back_c_array( test_array );
    result = *(int*)(elem);
    TEST_VALUE(result, 9 );
    DELETE_ARRAY;
}
void
t_element_at_c_array() {
    int result = 0;
    void *elem = ( void *) 0;
    int i = 0;

    ADD_ELEMENTS ( 0, 9 );

    PRINT_TEST_CASE("element_at_c_array");
    elem = (void*)element_at_c_array(test_array, 1 );
    result = *(int*)(elem);
    TEST_VALUE(result, 1);

    PRINT_TEST_CASE("element_at_c_array");
    elem = (void*)element_at_c_array(test_array, 5 );
    result = *(int*)(elem);
    TEST_VALUE(result, 5 );

    PRINT_TEST_CASE("element_at_c_array");
    elem = (void*)element_at_c_array(test_array, 6 );
    result = *(int*)(elem);
    TEST_VALUE(result, 6 );

    PRINT_TEST_CASE("element_at_c_array");
    elem = (void*)element_at_c_array(test_array, 9 );
    result = *(int*)(elem);
    TEST_VALUE(result, 9 );

    for ( i = 0; i < size_c_array ( test_array ); i++) {
	elem = (void*)element_at_c_array(test_array, i );
	result = *(int*)(elem);
	PRINT_TEST_CASE("element_at_c_array");
	TEST_VALUE(result, i );
    }

    DELETE_ARRAY;
}
void
t_push_back_c_array() {
    int i = 100;
    int *elem = 0;
    int result = 0;

    PRINT_TEST_CASE("push_back_c_array");

    ADD_ELEMENTS ( 0, 9 );
    ADD_ONE_ELEMENT(i);

    elem = ( int *) back_c_array ( test_array );
    result = *(int*)(elem);
    TEST_VALUE(result, i );

    DELETE_ARRAY;
}
void
t_pop_back_c_array() {
    int *elem = 0;
    int result = 0;

    PRINT_TEST_CASE("pop_back_c_array");

    ADD_ELEMENTS ( 0, 9 );
    pop_back_c_array(test_array);

    elem = ( int *) back_c_array ( test_array );
    result = *(int*)(elem);
    TEST_VALUE(result, 8);

    result = size_c_array ( test_array );
    PRINT_TEST_CASE("pop_back_c_array");
    TEST_VALUE(result, 9);

    DELETE_ARRAY;
}
void
t_insert_c_array(){
    int i = 0;
    void *elem = ( void *) 0;
    int result = 0;

    PRINT_TEST_CASE("insert_c_array");
    ADD_ELEMENTS ( 0, 9 );

    i = 100;
    INSERT_ELEMENT(i,5);

    elem = (void*)element_at_c_array(test_array, 5 );
    result = *(int*)(elem);
    TEST_VALUE(result, 100);

    DELETE_ARRAY;

}
void
t_for_each_c_array() {
    PRINT_TEST_CASE("for_each_c_array");
    printf ( "\n");
    ADD_ELEMENTS ( 0, 9 );
    for_each_c_array( test_array, function_for_each);
    TEST_VALUE(1,1);
    DELETE_ARRAY;
}
void
t_is_equal_to_c_array() {
    int result = 0;
    PRINT_TEST_CASE("is_equal_to_c_array");
    ADD_ELEMENTS ( 0, 9 );
    ADD_ELEMENTS1 ( 0, 9 );
    result = is_equal_to_c_array( test_array, test_array1 );
    TEST_VALUE(result,0);
    DELETE_ARRAY;
    DELETE_ARRAY1;

    PRINT_TEST_CASE("is_equal_to_c_array");
    ADD_ELEMENTS ( 0, 9 );
    ADD_ELEMENTS1 ( 0, 19 );
    result = is_equal_to_c_array( test_array, test_array1 );
    TEST_VALUE(result,1);
    DELETE_ARRAY;
    DELETE_ARRAY1;

    PRINT_TEST_CASE("is_equal_to_c_array");
    ADD_ELEMENTS ( 0, 9 );
    ADD_ELEMENTS1 ( 1, 10 );
    result = is_equal_to_c_array( test_array, test_array1 );
    TEST_VALUE(result,1);
    DELETE_ARRAY;
    DELETE_ARRAY1;

    PRINT_TEST_CASE("is_equal_to_c_array");
    ADD_ELEMENTS ( 0, 9 );
    ADD_ELEMENTS2 ( 0, 9 );
    result = is_equal_to_c_array( test_array, test_array1 );
    TEST_VALUE(result,1);
    DELETE_ARRAY;
    DELETE_ARRAY1;


}
void 
test_c_array(){
    t_size_c_array();
    t_empty_c_array();
    t_capacity_c_array();
    t_reserve_c_array();
    t_front_c_array();
    t_back_c_array();
    t_element_at_c_array();
    t_push_back_c_array();
    t_pop_back_c_array();
    t_insert_c_array();
    t_for_each_c_array();
    t_is_equal_to_c_array();
}
