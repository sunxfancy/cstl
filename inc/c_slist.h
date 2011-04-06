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
    clib_type elem;
    struct __c_slist_node *next;
}c_slist_node;

typedef c_slist_node         clib_slist_node;
typedef c_slist_node*        clib_slist_node_ptr;
#define clib_slist_node_null (clib_slist_node_ptr)0

typedef struct __c_slist {
    clib_slist_node_ptr head;
    clib_destroy destruct_fn;
    clib_compare compare_key_fn;
    int size;
}c_slist;

typedef c_slist          clib_slist;
typedef c_slist*         clib_slist_ptr;
#define clib_slist_null (clib_slist_ptr)0

extern clib_slist_ptr new_c_slist(clib_destroy, clib_compare);
extern void           delete_c_slist   (clib_slist_ptr );
extern void           insert_c_slist   (clib_slist_ptr, clib_type, int );
extern void           push_back_c_slist(clib_slist_ptr, clib_type);
extern void           remove_c_slist   (clib_slist_ptr, int );
extern void           for_each_c_slist (clib_slist_ptr, void (*)(void*));
extern clib_type      find_c_slist     (clib_slist_ptr, clib_type);

#endif