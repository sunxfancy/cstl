#ifndef _C_SET_H_
#define _C_SET_H_

#include "c_rb.h"
#include "c_util.h"

typedef struct __c_set {
    RB_PTR root;
    destroy fn_destroy;
    compare fn_compare;
}c_set;

typedef c_set * SET_PTR;
#define SET_NULL (SET_PTR)0

SET_PTR     new_c_set( destroy, compare );
CLIB_ERROR  delete_c_set ( SET_PTR );

CLIB_ERROR  insert_c_set ( SET_PTR, TYPE );
CLIB_ERROR  remove_c_set ( SET_PTR, TYPE );
int         exists_c_set ( SET_PTR, TYPE );

#endif
