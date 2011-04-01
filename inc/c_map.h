#ifndef _C_MAP_H_
#define _C_MAP_H_

/* ------------------------------------------------------------------------*/
/*                        M A P                                            */
/* ------------------------------------------------------------------------*/
typedef struct __c_map {
    c_rb* root;
}c_map;

typedef c_map         CLIB_MAP;
typedef c_map*        CLIB_MAP_PTR;
#define CLIB_MAP_NULL (CLIB_MAP_PTR)0 

extern CLIB_MAP_PTR new_c_map    ( CLIB_DESTROY, CLIB_DESTROY,CLIB_COMPARE);
extern void         delete_c_map ( CLIB_MAP_PTR);
extern void         insert_c_map ( CLIB_MAP_PTR, CLIB_TYPE, CLIB_TYPE);
extern void         remove_c_map ( CLIB_MAP_PTR, CLIB_TYPE );
extern CLIB_BOOL    empty_c_map  ( CLIB_MAP_PTR );
extern CLIB_TYPE    find_c_map   ( CLIB_MAP_PTR, CLIB_TYPE );


#endif