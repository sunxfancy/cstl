#ifndef _C_DEQUE_H_
#define _C_DEQUE_H_
/* ------------------------------------------------------------------------*/
/*                 D O U B L E    E N E D E D     Q U E U E                */
/* ------------------------------------------------------------------------*/
typedef struct __c_deque {
    CLIB_TYPE elements;
    int no_max_elements;
    int head;
    int tail;
    int no_of_elements;
    size_t size_of_element;
    CLIB_COMPARE compare_fn;
    CLIB_DESTROY destruct_fn;
}c_deque;

typedef c_deque          CLIB_DEQUE;
typedef c_deque*         CLIB_DEQUE_PTR;
#define CLIB_DEQUE_NULL  (CLIB_DEQUE_PTR)0

extern CLIB_DEQUE_PTR new_c_deque( int, CLIB_COMPARE,CLIB_DESTROY, CLIB_SIZE);
extern CLIB_ERROR     push_back_c_deque (CLIB_DEQUE_PTR, CLIB_TYPE);
extern CLIB_ERROR     push_front_c_deque(CLIB_DEQUE_PTR, CLIB_TYPE);
extern CLIB_ERROR     front_c_deque     (CLIB_DEQUE_PTR,CLIB_TYPE);
extern CLIB_ERROR     back_c_deque      (CLIB_DEQUE_PTR,CLIB_TYPE);
extern CLIB_ERROR     pop_back_c_deque  (CLIB_DEQUE_PTR,CLIB_TYPE);
extern CLIB_ERROR     pop_front_c_deque (CLIB_DEQUE_PTR,CLIB_TYPE);
extern CLIB_BOOL      empty_c_deque     (CLIB_DEQUE_PTR);
extern int            size_c_deque ( CLIB_DEQUE_PTR);
extern CLIB_ERROR     delete_c_deque ( CLIB_DEQUE_PTR);
extern CLIB_ERROR     element_at_c_deque (CLIB_DEQUE_PTR ,int,CLIB_TYPE);

#endif