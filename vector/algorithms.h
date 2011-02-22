#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "iterator.h"

typedef void (*UNARY_FUNCTION) ( void *);

void for_each ( iterator , iterator , UNARY_FUNCTION );
int count ( iterator , iterator , int );


#endif /* _ALGORITHMS_H_ */

