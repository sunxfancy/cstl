## Dynamic array structure definition ##
```
typedef void (*destroy)(void*);
typedef int  (*compare)(void*, void *);

typedef struct _c_array {
	void **_elem;
	int  cur_size;
	int  capacity;
	destroy destruct_fn;
	compare compare_fn;
}c_array;
```

### Create new array ###
```
c_array * new_c_array( int size, destroy fn_destroy, compare fn_compare)
```

### Delete dynamic array ###
```
void delete_c_array( c_array *_AR)
```

### Push element into the array ###
```
void push_back_c_array ( c_array *_AR, void *value )
```

### Retrieving element from a position ###
```
void * element_at_c_array ( c_array *_AR, int pos )
```

### Performing operation on each element in the array ###
```
void for_each_c_array(c_array* _AR, void (*fn)(void*))
```

### Insert element at any position ###
```
void insert_c_array ( c_array* _AR, int pos, void *value)
```

### Get the first element from the array ###
```
void * front_c_array ( c_array* _AR)
```
### Get the last element from the array ###
```
void * back_c_array ( c_array* _AR)
```