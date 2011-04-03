#include "c_datastructure.h"
#include <string.h>
#include <assert.h>

static int
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}

int array_value[] = { 1,2,3,4,5,6,7,8,9,10,
                      11,12,13,14,15,16,17,18,19,20,
                      21,22,23,24,25,26};

static void 
insert_all ( CLIB_MAP_PTR myMap) {
    insert_c_map ( myMap, "A", &array_value[0]); 
    insert_c_map ( myMap, "B", &array_value[1]); 
    insert_c_map ( myMap, "C", &array_value[2]);
    insert_c_map ( myMap, "D", &array_value[3]); 
    insert_c_map ( myMap, "E", &array_value[4]); 
    insert_c_map ( myMap, "F", &array_value[5]); 
    insert_c_map ( myMap, "G", &array_value[6]); 
    insert_c_map ( myMap, "H", &array_value[7]); 
    insert_c_map ( myMap, "I", &array_value[8]);
    insert_c_map ( myMap, "J", &array_value[9]); 
    insert_c_map ( myMap, "K", &array_value[10]); 
    insert_c_map ( myMap, "L", &array_value[11]);
    insert_c_map ( myMap, "M", &array_value[12]); 
    insert_c_map ( myMap, "N", &array_value[13]); 
    insert_c_map ( myMap, "O", &array_value[14]);
    insert_c_map ( myMap, "P", &array_value[15]); 
    insert_c_map ( myMap, "Q", &array_value[16]); 
    insert_c_map ( myMap, "R", &array_value[17]);
    insert_c_map ( myMap, "S", &array_value[18]); 
    insert_c_map ( myMap, "T", &array_value[19]); 
    insert_c_map ( myMap, "U", &array_value[19]); 
    insert_c_map ( myMap, "V", &array_value[20]);
    insert_c_map ( myMap, "W", &array_value[21]); 
    insert_c_map ( myMap, "X", &array_value[22]); 
    insert_c_map ( myMap, "Y", &array_value[23]);
    insert_c_map ( myMap, "Z", &array_value[24]);
}
static void 
check_exists_all( CLIB_MAP_PTR myMap) {
    assert ( CLIB_TRUE == exists_c_map ( myMap, "A"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "B"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "C"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "D"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "E"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "F"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "G"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "H"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "I"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "J"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "K"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "L"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "M"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "N"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "O"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "P"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "Q"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "R"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "S"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "T"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "U"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "V"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "W"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "X"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "Y"));
    assert ( CLIB_TRUE == exists_c_map ( myMap, "Z"));
}
static void 
remove_some_exist(CLIB_MAP_PTR myMap) {
    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "A"));
    assert ( CLIB_FALSE == exists_c_map ( myMap, "A"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "X"));
    assert ( CLIB_FALSE == exists_c_map ( myMap, "X"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "Z"));
    assert ( CLIB_FALSE == exists_c_map ( myMap, "Z"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "H"));
    assert ( CLIB_FALSE == exists_c_map ( myMap, "H"));
}
static void
add_removed_check_all(CLIB_MAP_PTR myMap) {
    insert_c_map ( myMap, "A", &array_value[0]); 
    insert_c_map ( myMap, "X", &array_value[22]); 
    insert_c_map ( myMap, "Z", &array_value[24]);
    insert_c_map ( myMap, "H", &array_value[7]); 
    check_exists_all(myMap);
}

void 
test_c_map() {
    CLIB_MAP_PTR myMap = new_c_map ( compare_e, NULL, NULL, sizeof( char*), sizeof(int));
    insert_all(myMap);
    check_exists_all(myMap);
    remove_some_exist(myMap);
    add_removed_check_all(myMap);
    delete_c_map(myMap);
}