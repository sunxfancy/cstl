#ifndef __ITERATOR_H_
#define __ITERATOR_H_

#define ITERATOR struct __iterator

typedef struct __iterator_ft {
    ITERATOR (*next)         (ITERATOR * );
    ITERATOR (*prev)         (ITERATOR * );
    void *   (*value)        (ITERATOR * );
    int      (*equals)       (ITERATOR *, ITERATOR *);
    void     (*value_assign) (ITERATOR *, void *);
}iterator_ft;

typedef struct __iterator {
    void *_l;
    iterator_ft *ptr_ft;
}iterator;

#define ITERATOR_NULL (iterator*)0
void *iterator_value(iterator );

#define ITR_VALUE(I)          (I).ptr_ft->value(&(I))
#define ITR_NEXT(I)           (I).ptr_ft->next(&(I))
#define ITR_EQUALS(I,J)       (I).ptr_ft->equals(&(I),&(J))
#define ITR_VALUE_ASSIGN(I,J) (I).ptr_ft->value_assign(&(I),(J))

#endif  /* __ITERATOR_H_ */

