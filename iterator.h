#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct __iterator {
    int cur_position;

    void   (*next)   ( void*);
    void   (*prev)   ( void*);
    void * (*begin)  ( void*);
    int    (*end)    ( void*);
    int    (*is_end) ( void*);

    void * (*get_value) ( void * );

}iterator;
#endif

