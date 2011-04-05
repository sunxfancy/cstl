#ifndef _C_SET_H_
#define _C_SET_H_
typedef struct __c_set {
    c_rb* root;
}c_set;

typedef c_set          clib_set;
typedef c_set*         clib_set_ptr;
#define clib_set_null  (clib_set_ptr)0 

extern clib_set_ptr new_c_set    ( clib_compare fn_c, clib_destroy fn_d);
extern clib_error   insert_c_set ( clib_set_ptr pSet, clib_type key, clib_size key_size);
extern clib_bool    exists_c_set ( clib_set_ptr pSet, clib_type key);
extern clib_error   remove_c_set ( clib_set_ptr pSet, clib_type key);
extern clib_error   delete_c_set ( clib_set_ptr pSet);

#endif