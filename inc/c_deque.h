#ifndef _C_DEQUE_H_
#define _C_DEQUE_H_

typedef void (*destroy)(void*);
typedef int  (*compare)(void*, void *);

typedef struct __c_deque {
	void **_EL;

	int _size;
	int _F_I;
	int _B_I;
	int _current_size;

	destroy _fn_destroy;
	compare _fn_compare;
	
}c_deque;
/* 
 * Create, Copy, and Destroy Operations
 */
extern c_deque * new_c_deque(int , destroy, compare );
extern void delete_c_deque(c_deque *);
/*
 * Nonmodifying Operations
 */
extern int size_c_deque( c_deque * );
extern int empty_c_deque( c_deque *);
/*
 * Element Access
 */
extern void *front_c_deque ( c_deque* );
extern void *back_c_deque ( c_deque* );
/* 
 * Inserting and Removing Elements
 */ 
extern void push_back_c_deque(c_deque*, void *);
extern void push_front_c_deque(c_deque*, void *);
extern void pop_back_c_deque ( c_deque*);
extern void pop_front_c_deque ( c_deque*);

/*
 * Special functions 
 */
extern void for_each_c_deque(c_deque*, void (*)(void*));

/*
 * Deques are commonly implemented as dynamically allocated arrays that 
 * can grow at both ends. This guarantees constant time access, 
 * amortized constant time insertion and deletion at either end of the deque, 
 * and linear time insertion and deletion from the middle of the deque. 
*/
#endif
