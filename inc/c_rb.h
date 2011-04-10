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

#ifndef _C_RB_H_
#define _C_RB_H_

typedef struct __c_rb_node {
    struct __c_rb_node *left;
    struct __c_rb_node *right;
    struct __c_rb_node *parent;
    clib_int color; 

    clib_object_ptr key;
    clib_object_ptr value;

 
}clib_rb_node,*clib_rb_node_ptr;

typedef struct __c_rb {
    clib_rb_node_ptr root;
    clib_rb_node sentinel;
    clib_destroy destruct_k_fn;
	clib_destroy destruct_v_fn;
    clib_compare compare_fn;
}clib_rb,*clib_rb_ptr;

extern clib_rb_ptr new_c_rb(clib_compare fn_c,clib_destroy fn_ed, clib_destroy fn_vd );
extern clib_error  insert_c_rb(clib_rb_ptr pTree, clib_type key, clib_size key_size, clib_type value, clib_size value_size);
extern clib_rb_node_ptr   find_c_rb (clib_rb_ptr pTree, clib_type key);
extern clib_rb_node_ptr remove_c_rb (clib_rb_ptr pTree, clib_type key);
extern clib_error  delete_c_rb (clib_rb_ptr pTree);
extern clib_bool   empty_c_rb  (clib_rb_ptr pTree);
extern clib_rb_node_ptr get_next_c_rb (clib_rb_ptr pTree, clib_rb_node_ptr *, clib_rb_node_ptr *);

#endif