#ifndef _C_LIB_H_
#define _C_LIB_H_

#include "c_errors.h"
#include <stdlib.h>

/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void*  clib_type;
typedef void   (*clib_destroy)(clib_type);
typedef int    (*clib_compare)(clib_type,clib_type);
typedef void   (*clib_traversal)( clib_type);
typedef int    clib_error;
typedef int    clib_bool;
typedef size_t clib_size;

#define clib_black           0
#define clib_red             1
#define clib_true            1
#define clib_false           0
#define clib_null            (clib_type)0

/* ------------------------------------------------------------------------*/
/*                            P  A  I   R                                  */
/* ------------------------------------------------------------------------*/
typedef struct __c_pair {
    clib_type key;
    clib_type value;
}c_pair;

typedef c_pair         clib_pair;
typedef c_pair*        clib_pair_ptr;
#define clib_pair_null (clib_pair_ptr)0

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
extern void  clib_free (clib_type);
extern void* clib_memcpy(void* , const void* , size_t );
extern void  clib_copy ( void *destination, void *source, size_t size );
extern void  clib_get  ( void *destination, void *source, size_t size);
extern char* clib_strdup ( char *ptr );


#endif