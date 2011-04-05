#ifndef _C_DEQUE_H_
#define _C_DEQUE_H_

typedef struct __c_deque {
    clib_type elements;
    int no_max_elements;
    int head;
    int tail;
    int no_of_elements;
    size_t size_of_element;
    clib_compare compare_fn;
    clib_destroy destruct_fn;
}c_deque;

typedef c_deque          clib_deque;
typedef c_deque*         clib_deque_ptr;
#define clib_deque_null  (clib_deque_ptr)0

extern clib_deque_ptr new_c_deque( int, clib_compare,clib_destroy, clib_size);
extern clib_error     push_back_c_deque (clib_deque_ptr, clib_type);
extern clib_error     push_front_c_deque(clib_deque_ptr, clib_type);
extern clib_error     front_c_deque     (clib_deque_ptr,clib_type);
extern clib_error     back_c_deque      (clib_deque_ptr,clib_type);
extern clib_error     pop_back_c_deque  (clib_deque_ptr,clib_type);
extern clib_error     pop_front_c_deque (clib_deque_ptr,clib_type);
extern clib_bool      empty_c_deque     (clib_deque_ptr);
extern int            size_c_deque ( clib_deque_ptr);
extern clib_error     delete_c_deque ( clib_deque_ptr);
extern clib_error     element_at_c_deque (clib_deque_ptr ,int,clib_type);

#endif