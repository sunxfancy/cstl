#ifndef __ITERATOR_H_
#define __ITERATOR_H_

typedef struct __iterator_ft {
    struct __iterator (*next)(struct __iterator );
    struct __iterator (*prev)(struct __iterator );
    int (*equals)(struct __iterator, struct __iterator);
}iterator_ft;

typedef struct __iterator {
    void *_l;
    iterator_ft *ptr_ft;
}iterator;

#define ITERATOR_NULL (iterator*)0
void *iterator_value(iterator );

#define ITR_VALUE(I) *(void**)(I)._l 
#define ITR_NEXT(I)  (I).ptr_ft->next((I))
#define ITR_EQUALS(I,J)  (I).ptr_ft->equals((I),(J))

#endif  /* __ITERATOR_H_ */

