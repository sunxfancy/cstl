#include "c_datastructure.h"
#include <stdlib.h>

void *
clib_malloc( size_t size ) {
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

void* 
clib_memcpy(void* dest, const void* src, size_t count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;

	while (count--) {
		*dst8++ = *src8++;
	}
	return dest;
}