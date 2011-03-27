#ifndef _C_DEQUE_H_
#define _C_DEQUE_H_

#include "c_util.h"

typedef struct __c_deque {
    TYPE* _elements;

    int _size;
    int _front_index;
    int _back_index;
    int _current_size;

    destroy _fn_destroy;
    compare _fn_compare;

}c_deque;

typedef c_deque* DEQUE_PTR;
/* 
 * Create, Copy, and Destroy Operations
 */
extern DEQUE_PTR new_c_deque(int , destroy, compare );
extern void delete_c_deque(DEQUE_PTR);
/*
 * Nonmodifying Operations
 */
extern int size_c_deque( DEQUE_PTR );
extern int empty_c_deque( DEQUE_PTR);
/*
 * Element Access
 */
extern TYPE front_c_deque ( DEQUE_PTR );
extern TYPE back_c_deque ( DEQUE_PTR );
/* 
 * Inserting and Removing Elements
 */ 
extern void push_back_c_deque(DEQUE_PTR, TYPE );
extern void push_front_c_deque(DEQUE_PTR, TYPE );
extern void pop_back_c_deque ( DEQUE_PTR);
extern void pop_front_c_deque ( DEQUE_PTR);

/*
 * Special functions 
 */
extern void for_each_c_deque(DEQUE_PTR, void (*)(void*));

/*
 * Deques are commonly implemented as dynamically allocated arrays that 
 * can grow at both ends. This guarantees constant time access, 
 * amortized constant time insertion and deletion at either end of the deque, 
 * and linear time insertion and deletion from the middle of the deque. 
 */
#endif
