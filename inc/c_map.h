#ifndef _C_MAP_H_
#define _C_MAP_H_

typedef struct __c_map {
    c_rb* root;
}c_map;

typedef c_map          clib_map;
typedef c_map*         clib_map_ptr;
#define clib_map_null  (clib_map_ptr)0 

extern clib_map_ptr new_c_map    ( clib_compare fn_c_k, clib_destroy fn_k_d, clib_destroy fn_v_d);
extern clib_error   insert_c_map ( clib_map_ptr pMap, clib_type key, clib_type value, clib_size key_size, clib_size value_size);
extern clib_bool    exists_c_map ( clib_map_ptr pMap, clib_type key);
extern clib_error   remove_c_map ( clib_map_ptr pMap, clib_type key);
extern clib_bool    find_c_map   ( clib_map_ptr pMap, clib_type key, clib_type value);
extern clib_error   delete_c_map ( clib_map_ptr pMap);

#endif