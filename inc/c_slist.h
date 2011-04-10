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

#ifndef _C_SLIST_H_
#define _C_SLIST_H_

typedef struct __c_slist_node {
    clib_object_ptr elem;
    struct __c_slist_node *next;
}clib_slist_node,*clib_slist_node_ptr;


typedef struct __c_slist {
    clib_slist_node_ptr head;
    clib_destroy destruct_fn;
    clib_compare compare_key_fn;
    clib_int size;
}clib_slist,*clib_slist_ptr;


extern clib_slist_ptr new_c_slist(clib_destroy fn_d, clib_compare fn_c);
extern void           delete_c_slist   (clib_slist_ptr pSlist);
extern clib_error     insert_c_slist   (clib_slist_ptr pSlist, clib_int pos, clib_type elem, clib_size elem_size);
extern clib_error     push_back_c_slist(clib_slist_ptr pSlist, clib_type elem, clib_size elem_size);
extern void           remove_c_slist   (clib_slist_ptr pSlist, clib_int pos);
extern void           for_each_c_slist (clib_slist_ptr pSlist, void (*fn)(clib_type ));
extern clib_bool      find_c_slist     (clib_slist_ptr pSlist, clib_type find_value, clib_type *out_value);

#endif