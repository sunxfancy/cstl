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

#ifndef _C_MAP_H_
#define _C_MAP_H_

typedef struct __c_map {
    clib_rb_ptr root;
}clib_map,*clib_map_ptr;
#define clib_map_null  (clib_map_ptr)0 

extern clib_map_ptr new_c_map    ( clib_compare fn_c_k, clib_destroy fn_k_d, clib_destroy fn_v_d);
extern clib_error   insert_c_map ( clib_map_ptr pMap, clib_type key, clib_size key_size, clib_type value,  clib_size value_size);
extern clib_bool    exists_c_map ( clib_map_ptr pMap, clib_type key);
extern clib_error   remove_c_map ( clib_map_ptr pMap, clib_type key);
extern clib_bool    find_c_map   ( clib_map_ptr pMap, clib_type key, clib_type *value);
extern clib_error   delete_c_map ( clib_map_ptr pMap);

#endif