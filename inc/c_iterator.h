#ifndef _C_ITERATOR_H_
#define _C_ITERATOR_H_

struct clib_iterator {
	struct clib_object* (*get_next)(struct clib_iterator*);
	void (*replace_value)(struct clib_iterator*,void*,size_t);
	void* (*get_value)(void*);
	void* pContainer;
	int   pCurrent;
	void* pCurrentElement;
};

#endif  /* _C_ITERATOR_H_ */

