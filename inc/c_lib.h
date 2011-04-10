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

#ifndef _C_LIB_H_
#define _C_LIB_H_

#include "c_errors.h"
#include <stdlib.h>

/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void*     clib_type;
typedef void      (*clib_destroy)(clib_type);
typedef int       clib_int;
typedef clib_int  (*clib_compare)(clib_type,clib_type);
typedef void      (*clib_traversal)( clib_type);
typedef clib_int  clib_error;
typedef clib_int  clib_bool;
typedef size_t    clib_size;


#define clib_black           0
#define clib_red             1
#define clib_true            1
#define clib_false           0
#define clib_null            (clib_type)0

/* ------------------------------------------------------------------------*/
/*                            P  A  I   R                                  */
/* ------------------------------------------------------------------------*/

typedef struct __c_lib__object {
    clib_type raw_data;
    size_t size;
} clib_object, *clib_object_ptr;



typedef struct __c_lib_element {
    clib_type  elem;
    clib_size  size;
}clib_element,*clib_element_ptr;



typedef struct __c_pair {
    clib_type key;
    clib_type value;
}c_pair;

typedef c_pair         clib_pair;
typedef c_pair*        clib_pair_ptr;

#define clib_object_null (clib_object_ptr)0
#define clib_array_null  (clib_array_ptr)0 
#define clib_slist_node_null (clib_slist_node_ptr)0
#define clib_pair_null (clib_pair_ptr)0
#define clib_element_null (clib_element_ptr)0
#define clib_slist_null (clib_slist_ptr)0
#define clib_set_null  (clib_set_ptr)0 
#define clib_rb_node_null  (clib_rb_node_ptr)0 
#define clib_rb_null        (clib_rb_ptr)0 

#include "c_array.h"
#include "c_deque.h"
#include "c_rb.h"
#include "c_set.h"
#include "c_map.h"
#include "c_slist.h"
#include "c_map.h"

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

extern clib_type clib_malloc(size_t size);
extern void  clib_free (clib_type ptr);
extern clib_type  clib_memcpy(clib_type  destination, const clib_type  source, size_t size );
extern void  clib_copy ( clib_type destination, clib_type source, size_t size );
extern void  clib_get  ( clib_type destination, clib_type source, size_t size);
extern char* clib_strdup ( char *ptr );

extern clib_object_ptr new_clib_object     (clib_type inObject, size_t obj_size);
extern clib_error      get_raw_clib_object (clib_object *inObject, clib_type *elem);
extern void            delete_clib_object  (clib_object_ptr inObject );

#endif
