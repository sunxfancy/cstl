#ifndef _C_SET_H_
#define _C_SET_H_
typedef struct __c_set {
    c_rb* root;
}c_set;

typedef c_set          CLIB_SET;
typedef c_set*         CLIB_SET_PTR;
#define CLIB_SET_NULL  (CLIB_SET_PTR)0 

extern CLIB_SET_PTR new_c_set    ( CLIB_COMPARE fn_c, CLIB_DESTROY fn_d, CLIB_SIZE elem_size);
extern CLIB_ERROR   insert_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key);
extern CLIB_BOOL    exists_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key);
extern CLIB_ERROR   remove_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key);
extern CLIB_ERROR   delete_c_set ( CLIB_SET_PTR pSet);

#endif