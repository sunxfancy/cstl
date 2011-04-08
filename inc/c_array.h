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

#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

typedef struct __c_array {

    int              no_max_elements;
    int              no_of_elements;
    clib_object_ptr *pElements;
    clib_compare     compare_fn;
    clib_destroy     destruct_fn;

}clib_array,*clib_array_ptr;



extern clib_array_ptr new_c_array ( int init_size, clib_compare fn_c, clib_destroy fn_d);
extern clib_error     push_back_c_array ( clib_array_ptr pArray, clib_type elem, clib_size elem_size);
extern clib_error     element_at_c_array( clib_array_ptr pArray, int pos, clib_type *e);
extern clib_error     insert_at_c_array ( clib_array_ptr pArray, int index, clib_type elem, clib_size elem_size);
extern int            size_c_array( clib_array_ptr pArray);
extern int            capacity_c_array( clib_array_ptr pArray );
extern clib_bool      empty_c_array( clib_array_ptr pArray);
extern clib_error     reserve_c_array( clib_array_ptr pArray, int pos);
extern clib_error     front_c_array( clib_array_ptr pArray,clib_type elem);
extern clib_error     back_c_array( clib_array_ptr pArray,clib_type elem);
extern clib_error     remove_from_c_array ( clib_array_ptr, int pos);
extern clib_error     delete_c_array( clib_array_ptr pArray);

#endif
