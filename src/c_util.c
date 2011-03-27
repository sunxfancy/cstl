#include "c_datastructure.h"
#include <stdlib.h>

void *
clib_malloc( int size ) {
    void *t = malloc ( size );
    if ( !t ) {
	abort();
    }
    return t;
}
void
clib_free ( void *ptr ) {
    if ( ptr )
	free ( ptr );
}
