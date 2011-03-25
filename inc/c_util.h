#ifndef _C_UTIL_H_
#define _C_UTIL_H_


typedef void* TYPE;
typedef void (*destroy)(TYPE);
typedef int  (*compare)(TYPE,TYPE);
typedef void (*traversal)( TYPE);
typedef int CLIB_ERROR;

#define BLACK       0
#define RED         1

#define MAP         1
#define MULTI_MAP   2
#define SET         1
#define MULTI_SET   2

#define CLIB_NULL   (TYPE)0

/* Common Error codes */
#define CLIB_SUCCESS 0

/* Red Black Tree Error Codes 
 * Range is between 100 to 200 
 */
#define CLIB_RBTREE_KEY_DUPLICATE 100
#define CLIB_RBTREE_KEY_NOT_FOUND 101

extern void *c_malloc(int);
extern void c_free ( void *);

#endif
