#ifndef _C_MAP_H_
#define _C_MAP_H_

typedef struct __c_map {
    c_rb* root;
}c_map;

typedef c_map          CLIB_MAP;
typedef c_map*         CLIB_MAP_PTR;
#define CLIB_MAP_NULL  (CLIB_MAP_PTR)0 

extern CLIB_MAP_PTR new_c_map    ( CLIB_COMPARE fn_c_k, CLIB_DESTROY fn_k_d,  
                                   CLIB_DESTROY fn_v_d, CLIB_SIZE key_elem_size, 
                                   CLIB_SIZE val_elem_size);
extern CLIB_ERROR   insert_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key, CLIB_TYPE value);
extern CLIB_BOOL    exists_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key);
extern CLIB_ERROR   remove_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key);
extern CLIB_ERROR   delete_c_map ( CLIB_MAP_PTR pMap);

#endif