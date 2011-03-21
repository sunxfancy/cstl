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