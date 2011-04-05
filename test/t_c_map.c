#include "c_lib.h"
#include <string.h>
#include <assert.h>

static int
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
char *char_value[] = {  "A","B","C","D","E","F","G","H","I","J","K","L","M"
                        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
int int_value[] = { 1,2,3,4,5,6,7,8,9,10,
                      11,12,13,14,15,16,17,18,19,20,
                      21,22,23,24,25,26};

static void 
insert_all ( clib_map_ptr myMap) {
    int size = sizeof(char_value)/sizeof(char_value[0]);
    int i = 0;
    for ( i = 0; i < size; i++ ) {
        int length = (int)strlen ( char_value[i] ) + 1;
        insert_c_map ( myMap, char_value[i], &int_value[i], length, sizeof(int)); 
    }
}
static void 
check_exists_all( clib_map_ptr myMap) {
    int size = sizeof(char_value)/sizeof(char_value[0]);
    int i = 0;
    for ( i = 0; i < size; i++ ) {
        int value ;
        assert ( clib_true == exists_c_map ( myMap, char_value[i]));
        assert ( clib_true == find_c_map( myMap, char_value[i], &value));
        assert ( value == int_value[i]);
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
    insert_c_map ( myMap, "A", &int_value[0],  strlen("A") + 1, sizeof(int)); 
    insert_c_map ( myMap, "X", &int_value[22], strlen("X") + 1, sizeof(int)); 
    insert_c_map ( myMap, "Z", &int_value[24], strlen("Z") + 1, sizeof(int)); 
    insert_c_map ( myMap, "H", &int_value[7],  strlen("H") + 1, sizeof(int)); 
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