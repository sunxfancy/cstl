#include "c_lib.h"
#include <string.h>
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

void 
clib_copy( void *destination, void *source, size_t size ) {
    clib_memcpy ( (char*)destination, source, size);
}
void
clib_get ( void *destination, void *source, size_t size) {
    clib_memcpy ( destination, (char*)source, size);
}

char*
clib_strdup ( char *ptr ) {
    #ifdef WIN32
        return _strdup (ptr);
    #else
        return strdup (ptr);
    #endif
}