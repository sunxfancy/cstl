#include "c_lib.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static void 
delete_e ( void *ptr ) {
    if ( ptr ) 
	free ( ptr );
}
static int
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}

void 
test_c_set(){
    {
        CLIB_SET_PTR pSet = new_c_set ( compare_e, delete_e, sizeof( char*));
        insert_c_set ( pSet, "A"); insert_c_set ( pSet, "B"); insert_c_set ( pSet, "C");
        insert_c_set ( pSet, "D"); insert_c_set ( pSet, "E"); insert_c_set ( pSet, "F"); 
        insert_c_set ( pSet, "G"); insert_c_set ( pSet, "H"); insert_c_set ( pSet, "I");
        insert_c_set ( pSet, "J"); insert_c_set ( pSet, "K"); insert_c_set ( pSet, "L");
        insert_c_set ( pSet, "M"); insert_c_set ( pSet, "N"); insert_c_set ( pSet, "O");
        insert_c_set ( pSet, "P"); insert_c_set ( pSet, "Q"); insert_c_set ( pSet, "R");
        insert_c_set ( pSet, "S"); insert_c_set ( pSet, "T"); insert_c_set ( pSet, "V");
        insert_c_set ( pSet, "W"); insert_c_set ( pSet, "X"); insert_c_set ( pSet, "Y");
        insert_c_set ( pSet, "Z");

        assert ( CLIB_TRUE == exists_c_set ( pSet, "A"));
        assert ( CLIB_ERROR_SUCCESS == remove_c_set ( pSet, "A"));
        assert ( CLIB_FALSE == exists_c_set ( pSet, "A"));
        insert_c_set ( pSet, "A");

        delete_c_set(pSet);
    }
}
