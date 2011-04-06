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