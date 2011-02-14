#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct __iterator {
    void *ptr_to_container;

    int    ( *end   ) (void*);
    void   ( *next  ) (void*);
    void * ( *value ) (void*);

}iterator;

#endif

