#include "c_util.h"
#include <stdlib.h>

void *
c_malloc( int size ) {
    void *t = malloc ( size );
    if ( !t ) {
	abort();
    }
    return t;
}
void
c_free ( void *ptr ) {
    if ( ptr )
	free ( ptr );
}
