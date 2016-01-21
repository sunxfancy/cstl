## Data Structure definition ##
```
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
```

### Creating a deque instance ###
```
c_deque * new_c_deque(int size , destroy fn_destroy, compare fn_compare)
```

### Delete a deque ###
```
void delete_c_deque ( c_deque *_DQ ) 
```

### Get the first element in the deque ###
```
void *front_c_deque ( c_deque* _DQ)
```

### Get the last element in the deque ###
```
void *back_c_deque ( c_deque* _DQ)
```

### Push a element at the back of the deque ###
```
void push_back_c_deque(c_deque* _DQ, void* value) 
```

### Push a element at the front of the deque ###
```
void push_front_c_deque(c_deque* _DQ, void* value) 
```

### Removes the last element from the deque ###
```
void pop_back_c_deque ( c_deque* _DQ )
```

### Remove the first element from the deque ###
```
void pop_front_c_deque ( c_deque* _DQ )
```

### Perform operation on each element of the deque ###
```
void  for_each_c_deque(c_deque* _DQ, void (*fn)(void*))
```