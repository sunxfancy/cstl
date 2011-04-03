#ifndef _C_DATASTRUCTURE_H_
#define _C_DATASTRUCTURE_H_

#include "c_errors.h"
#include <stdlib.h>

/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void*  CLIB_TYPE;
typedef void   (*CLIB_DESTROY)(CLIB_TYPE);
typedef int    (*CLIB_COMPARE)(CLIB_TYPE,CLIB_TYPE);
typedef void   (*CLIB_TRAVERSAL)( CLIB_TYPE);
typedef int    CLIB_ERROR;
typedef int    CLIB_BOOL;
typedef size_t CLIB_SIZE;

#define CLIB_BLACK           0
#define CLIB_RED             1
#define CLIB_SET_TYPE        0
#define CLIB_MAP_TYPE        1
#define CLIB_GRAPH_TYPE      2
#define CLIB_TRUE            1
#define CLIB_FALSE           0
#define CLIB_NULL            (CLIB_TYPE)0
#define CLIB_INORDER		 0
#define CLIB_PREORDER        1
#define CLIB_POSTORDER       2
#define CLIB_RB_VALUE_COPY   0
#define CLIB_RB_REFER_COPY   1

/* ------------------------------------------------------------------------*/
/*                            P  A  I   R                                  */
/* ------------------------------------------------------------------------*/
typedef struct __c_pair {
    CLIB_TYPE key;
    CLIB_TYPE value;
}c_pair;

typedef c_pair         CLIB_PAIR;
typedef c_pair*        CLIB_PAIR_PTR;
#define CLIB_PAIR_NULL (CLIB_PAIR_PTR)0

#include "c_array.h"
#include "c_deque.h"
#include "c_rb.h"
#include "c_set.h"
#include "c_map.h"
#include "c_slist.h"
#include "c_map.h"

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

extern void *clib_malloc(size_t);
extern void  clib_free (CLIB_TYPE);
extern void* clib_memcpy(void* , const void* , size_t );


#endif