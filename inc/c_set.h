#ifndef _C_SET_H_
#define _C_SET_H_
/* ------------------------------------------------------------------------*/
/*                               S E T                                     */
/* ------------------------------------------------------------------------*/
typedef struct __c_set {
    c_rb* root;
}c_set;

typedef c_set          CLIB_SET;
typedef c_set*         CLIB_SET_PTR;
#define CLIB_SET_NULL  (CLIB_SET_PTR)0 


extern CLIB_SET_PTR new_c_set    ( CLIB_DESTROY, CLIB_COMPARE , size_t);
extern void         delete_c_set ( CLIB_SET_PTR );
extern void         insert_c_set ( CLIB_SET_PTR, CLIB_TYPE, int );
extern void         remove_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    exists_c_set ( CLIB_SET_PTR, CLIB_TYPE );
extern CLIB_BOOL    empty_c_set  ( CLIB_SET_PTR);
extern CLIB_ERROR   union_c_set  ( CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   intersection_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_ERROR   difference_c_set (CLIB_SET_PTR, CLIB_SET_PTR, CLIB_SET_PTR*);
extern CLIB_BOOL    subset_c_set (CLIB_SET_PTR, CLIB_SET_PTR);

#endif