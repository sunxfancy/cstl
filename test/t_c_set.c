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
delete_e ( clib_type ptr ) {
    if ( ptr ) 
	free ( ptr );
}
static clib_int
compare_e ( clib_type left, clib_type right ) {
    char *l = (char*)left;
    char *r = (char*)right;
    return strcmp ( (const char *)l, (const char *) r );
}
static clib_int 
compare_int ( clib_type left, clib_type right ) {
    clib_int *l = (clib_int*)left;
    clib_int *r = (clib_int*)right;

    if ( *l < *r ) 
        return -1;
    else if ( *l > *r ) 
        return 1;
    return 0;
}
void 
test_c_set(){
    {
        clib_int test[] = { 0,1,2,3,4,5,6,7,8,9 };
        clib_int index  = 0;
        clib_int size   = sizeof (test) /sizeof(test[0]);
        clib_type outKey;

        clib_set_ptr pSet = new_c_set ( compare_int, NULL);

        for ( index = 0; index < size; index++ ) {
            clib_int v = test[index];
            insert_c_set ( pSet, &v, sizeof(clib_int));
        }
        for ( index = 0; index < size; index++ ) {
            clib_int v = test[index];
            assert ( clib_true == exists_c_set ( pSet, &v));
        }

        index = 9;
        find_c_set ( pSet, &index, &outKey);
        assert ( 9 == *(int*)outKey);
        clib_free ( outKey );
        delete_c_set(pSet);
    }
    {
        typedef struct test {
            char *string;
        } TEST_INPUT;

        clib_int index = 0;
        clib_int size = 0;
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
            char *temp = clib_strdup ( ti[index].string );
            insert_c_set ( pSet, temp, strlen(temp) + 1 );
            clib_free ( temp );
        }
        for ( index = 0; index < size; index++ ){
            v = ti[index].string;
            assert ( clib_true == exists_c_set ( pSet, v));
        }
        delete_c_set(pSet);
    }
}
