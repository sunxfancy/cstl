#ifndef _C_ERRORS_H_
#define _C_ERRORS_H_

/* ------------------------------------------------------------------------*/
/*                 C O M M O N    E R R O R    C O D E                     */
/* ------------------------------------------------------------------------*/
#define CLIB_ERROR_SUCCESS  0
#define CLIB_ERROR_ERROR    1
#define CLIB_ERROR_MEMORY   2
/* ------------------------------------------------------------------------*/
/*         D Y N A M I C    A R R A Y   E R R O R    C O D E S             */
/* ------------------------------------------------------------------------*/
#define CLIB_ARRAY_NOT_INITIALIZED    101
#define CLIB_ARRAY_INDEX_OUT_OF_BOUND 102

#define CLIB_DEQUE_NOT_INITIALIZED    201
#define CLIB_DEQUE_INDEX_OUT_OF_BOUND 202

#define CLIB_RBTREE_NOT_INITIALIZED   401
#define CLIB_RBTREE_KEY_DUPLICATE     401
#define CLIB_RBTREE_KEY_NOT_FOUND     402

#define CLIB_SET_INVALID_INPUT        501

#endif