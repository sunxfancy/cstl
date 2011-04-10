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

clib_type 
clib_malloc( size_t size ) {
    clib_type t = malloc ( size );
    if ( !t ) {
	    return (clib_type )0;
    }
    return t;
}
void
clib_free ( clib_type ptr ) {
    if ( ptr )
	    free ( ptr );
}

clib_type  
clib_memcpy(clib_type  dest, const clib_type  src, size_t count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;

	while (count--) {
		*dst8++ = *src8++;
	}
	return dest;
}

void 
clib_copy( clib_type destination, clib_type source, size_t size ) {
    clib_memcpy ( (char*)destination, source, size);
}
void
clib_get ( clib_type destination, clib_type source, size_t size) {
    clib_memcpy ( destination, (char*)source, size);
}

clib_object_ptr
new_clib_object(clib_type inObject, size_t obj_size) {
    clib_object_ptr tmp = (clib_object_ptr)malloc(sizeof(clib_object));   
    if ( ! tmp )
        return clib_object_null;
    tmp->size        = obj_size;
    tmp->raw_data    = (clib_type)clib_malloc(obj_size);
    if ( !tmp->raw_data ) {
        clib_free ( tmp );
        return clib_object_null;
    }
    memcpy ( tmp->raw_data, inObject, obj_size);
    return tmp;
}

clib_error
get_raw_clib_object ( clib_object *inObject, clib_type *elem) {
    *elem = (clib_type)clib_malloc(inObject->size);
    if ( ! *elem )
        return CLIB_ELEMENT_RETURN_ERROR;
    memcpy ( *elem, inObject->raw_data, inObject->size );

    return CLIB_ERROR_SUCCESS;
}

void 
delete_clib_object ( clib_object_ptr inObject ) {
    if (inObject) {
        clib_free (inObject->raw_data);
        clib_free (inObject);
    }
}

char*
clib_strdup ( char *ptr ) {
    #ifdef WIN32
        return _strdup (ptr);
    #else
        return strdup (ptr);
    #endif
}
