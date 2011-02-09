#ifndef _VECTOR_H_
#define _VECTOR_H_


typedef void (*pfnDestruct) ( void *);

typedef struct __vector {
    void **elem     ; /* opeque pointer array */
    int    capacity ; /* Current capacity */
    int    cur_size ; /* number of elements in the vector */
    pfnDestruct _destroy;
}vector;

/*
 * Interface Name : vector_new 
 * Parameters     : 1. Size
 *                  2. Function pointers to function which 
 *                     should be responsible for destructing the 
 *                     elements within the contain
 * Return         : 1. On SUCESS returns valid pointer to vector
 *                     container.
 *                  2. On FAILURE return null pointers.
 * Note           : Client should check the validity of the 
 *                  return value from this interface.
 */
vector * 
vector_new ( int, pfnDestruct); 
/*
 * Interface Name : vector_push_back
 * Parameters : 1. pointer to vector
 *		2. void * to the element.
 * Return     : None.
 * Note       :
 */
void
vector_push_back ( vector *, void *);
/* 
 * Interface Name : vector_element_at
 * Parameters     : 1. pointer to vector
 *		    2. position.
 * Return         : 1. On SUCESS Pointer to the element 
 *                     indicated by the position
 *                  2. On Failure Returns NULL Pointer.
 * Note		  : Bounds checking is not done as of now
 */
void *
vector_element_at ( vector *, int );
/*
 * Interface Name : vector_size
 * Parameter      : 1. pointer to vector
 * Return         : Returns the actual number of elements 
 * Note           :
 */
int
vector_size( vector *);
/*
 * Interface Name : vector_empty
 * Parameter      : 1. pointer to vector
 * Return         : Returns whether the container is empty 
 *                  (equivalent to size()==0, but might be faster) 
 *                  1 if the vector is empty
 *                  0 if vector is not empty
 * Note           :
 */
int
vector_empty( vector *);
/*
 * Interface Name : vector_capacity
 * Parameter      : 1. pointer to vector
 * Return         : Returns the maximum possible number of 
 *                  elements without reallocation 
 * Note           : 
 */
int
vector_capacity( vector *);
/*
 * Interface Name : vector_front
 * Parameter      : 1. pointer to vector
 * Return         : Returns the first element 
 * Note           : no check whether a first element exists
 */
void *
vector_front( vector *);
/*
 * Interface Name : vector_back
 * Parameter      : 1. pointer to vector
 * Return         : Returns the last element 
 * Note           : no check whether a last element exists
 */
void *
vector_back( vector *);
/*
 * Interface Name : vector_insert
 * Parameter      : 1. pointer to vector
 *                  2. position where to insert a new element
 *                  3. new element
 * Return         : none
 * Note           : 
 */
void 
vector_insert( vector *,int,void*);
/*
 * Interface Name : vector_clear
 * Parameter      : 1. pointer to vector
 * Return         : none
 * Note           : destroy the vectory elements
 *                  using the destructor function pointer set
 *                  if destructor function pointer is not set
 *                  then there will be memory leak.
 */
void 
vector_clear( vector *);
/*
 * Interface Name : vector_pop_back
 * Parameter      : 1. pointer to vector
 * Return         : None.
 * Note           : 
 */
void 
vector_pop_back( vector *);
/*
 * Interface Name : vector_erase
 * Parameter      : 1. pointer to vector
 *                  2. position of the element to erase
 * Return         : None.
 * Note           : 
 */
void 
vector_erase( vector *, int);
/*
 * Interface Name : vector_resize
 * Parameter      : 1. pointer to vector
 *                  2. New size
 * Return         : Changes the number of elements to new size
 * Note           : All the new elements will be NULL
 */
void 
vector_resize( vector *, int);


    


#endif

