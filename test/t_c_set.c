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
static int 
compare_int ( void *left, void *right ) {
    int *l = (int*)left;
    int *r = (int*)right;

    if ( *l < *r ) 
        return -1;
    else if ( *l > *r ) 
        return 1;
    return 0;
}
void 
test_c_set(){
    {
        int test[] = { 0,1,2,3,4,5,6,7,8,9 };
        int index =0;
        int size = sizeof (test) /sizeof(test[0]);
        clib_set_ptr pSet = new_c_set ( compare_int, NULL);

        for ( index = 0; index < size; index++ ){
            int v = test[index];
            insert_c_set ( pSet, &v, sizeof(int));
        }
        for ( index = 0; index < size; index++ ){
            int v = test[index];
            assert ( clib_true == exists_c_set ( pSet, &v));
        }
        delete_c_set(pSet);
    } 
    {
        typedef struct test {
            char *string;
        } TEST_INPUT;

        int index = 0;
        int size = 0;
        char *v;

        TEST_INPUT ti[] ={
            {"A for APPLE"},{"B for BALL"},{"C for CAT"}, {"D for DOG"},
            {"E for ELEPHANT"},{"F for FISH"},{"G for GOAT"},
            {"H for HORSE"},{"I for ICECREAM"},{"J for JOKER"},
            {"K for KITE"},{"L for LAMB"},{"M for MONKEY"},
            {"N for NEST"},{"O for ORANGE"},{"P for POT"},
            {"Q for QUEEN"},{"R for RAT"},{"S for SHEEP"},
            {"T for TABLE"},{"U for UMBRELLA"},{"V for VIOLIN"},{"W for WAX"},
            {"X for XEROX"},{"Y for YUMMY"},{"Z for ZEBRA"}
        };
        clib_set_ptr pSet = new_c_set ( compare_e, delete_e);
        size = sizeof ( ti ) / sizeof ( ti[0]);
        
        for ( index = 0; index < size; index++ ){
            char *temp;
            int length = 0;
            v = ti[index].string;
            temp = clib_strdup (v);
            length = (int)strlen ( temp ) + 1;
            insert_c_set ( pSet, temp, length);
            free ( temp );
        }
        for ( index = 0; index < size; index++ ){
            v = ti[index].string;
            assert ( clib_true == exists_c_set ( pSet, v));
        }
        delete_c_set(pSet);
    }
}
