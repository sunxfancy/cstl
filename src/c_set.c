#include "c_datastructure.h"
#include <stdio.h>

#define VALIDATE_SET_PTR if ( x == CLIB_SET_NULL ) return 0;
#define VALIDATE_KEY_PTR if ( !k ) return 0;	

CLIB_SET_PTR 
new_c_set( CLIB_DESTROY fn_d, CLIB_COMPARE fn_c) {

    CLIB_SET_PTR x  =  (CLIB_SET_PTR ) clib_malloc ( sizeof ( CLIB_SET ));

    x->fn_destroy =  fn_d;
    x->fn_compare =  fn_c;

    x->root  = new_c_rb ( fn_d, fn_c, 1);
    return x;
}
CLIB_ERROR    
delete_c_set ( CLIB_SET_PTR x) {
    CLIB_ERROR rc =  CLIB_SUCCESS;
    VALIDATE_SET_PTR;

    delete_c_rb ( x->root );
    clib_free ( x );

    return rc;
}
CLIB_ERROR 
insert_c_set ( CLIB_SET_PTR x, CLIB_TYPE k, int reference) {
    CLIB_ERROR rc =  CLIB_SUCCESS;
    VALIDATE_SET_PTR;
    VALIDATE_KEY_PTR;

    rc = insert_c_rb ( x->root, k, CLIB_NULL, reference );

    return rc;
}
CLIB_TYPE
remove_c_set ( CLIB_SET_PTR x, CLIB_TYPE k ) {
    CLIB_RB_NODE_PTR t_node;
    CLIB_TYPE key;

    VALIDATE_SET_PTR;
    VALIDATE_KEY_PTR;

    t_node = remove_c_rb ( x->root, k );
    if ( !t_node ) {
	return CLIB_NULL;
    }
    key = t_node->value._key;
    clib_free ( t_node );
    return key;
}
CLIB_BOOL
exists_c_set( CLIB_SET_PTR x, CLIB_TYPE k ) {
    CLIB_TYPE y ;
    VALIDATE_SET_PTR;
    VALIDATE_KEY_PTR;

    y = find_c_rb ( x->root, k );

    if ( y == CLIB_NULL )
	return CLIB_FALSE;	
    return CLIB_TRUE;
}
CLIB_BOOL
empty_c_set ( CLIB_SET_PTR x ) {
    VALIDATE_SET_PTR;
    return empty_c_rb(x->root);
}

CLIB_ERROR
union_c_set(CLIB_SET_PTR t,CLIB_SET_PTR s, CLIB_SET_PTR *rs) {
    CLIB_RB_NODE_PTR pre     = CLIB_RB_NODE_NULL;
    CLIB_RB_NODE_PTR current = CLIB_RB_NODE_NULL;
    CLIB_TYPE cur_elem       = CLIB_NULL;
    /* Both the operand set should be of the same type
     * We check for the destroy and compare funciton 
     */
    if ((t->fn_compare != s->fn_compare) || (t->fn_destroy != s->fn_destroy))
	return CLIB_SET_INVALID_INPUT;
    /* Add all the elements from first set to this
     * new lement 
     */
    current = t->root->_root;
    cur_elem = get_next_c_rb ( t->root,&current, &pre);
    while ( cur_elem ) {
	insert_c_set ( *rs, cur_elem, CLIB_RB_REFER_COPY);
	cur_elem = get_next_c_rb ( t->root,&current, &pre);				
    }
    pre = CLIB_RB_NODE_NULL;
    current = s->root->_root;
    /* Add all the elements from the second set
     * but before search for its existance in the
     * resulting set */
    cur_elem = get_next_c_rb ( s->root,&current, &pre);
    while ( cur_elem ) {
	if ( exists_c_set( *rs, cur_elem) == CLIB_FALSE )
	    insert_c_set ( *rs, cur_elem, CLIB_RB_REFER_COPY);
	cur_elem = get_next_c_rb ( s->root,&current, &pre);		
    }
    return CLIB_SUCCESS;
}
CLIB_ERROR    
intersection_c_set(CLIB_SET_PTR t,CLIB_SET_PTR s, CLIB_SET_PTR *rs) {
    CLIB_RB_NODE_PTR pre     = CLIB_RB_NODE_NULL;
    CLIB_RB_NODE_PTR current = CLIB_RB_NODE_NULL;
    CLIB_TYPE cur_elem       = CLIB_NULL;

    if ((t->fn_compare != s->fn_compare) || (t->fn_destroy != s->fn_destroy))
	return CLIB_SET_INVALID_INPUT;

    current = t->root->_root;
    cur_elem = get_next_c_rb ( t->root,&current, &pre);
    while ( cur_elem ) {
	if ( exists_c_set( s, cur_elem) == CLIB_TRUE )
	    insert_c_set ( *rs, cur_elem, CLIB_RB_REFER_COPY);
	cur_elem = get_next_c_rb ( t->root,&current, &pre);		
    }
    return CLIB_SUCCESS;
}
CLIB_ERROR    
difference_c_set(CLIB_SET_PTR t,CLIB_SET_PTR s, CLIB_SET_PTR *rs) {
    CLIB_RB_NODE_PTR pre     = CLIB_RB_NODE_NULL;
    CLIB_RB_NODE_PTR current = CLIB_RB_NODE_NULL;
    CLIB_TYPE cur_elem       = CLIB_NULL;

    if ((t->fn_compare != s->fn_compare) || (t->fn_destroy != s->fn_destroy))
	return CLIB_SET_INVALID_INPUT;

    current = t->root->_root;
    cur_elem = get_next_c_rb ( t->root,&current, &pre);
    while ( cur_elem ) {
	if ( exists_c_set( s, cur_elem) == CLIB_FALSE )
	    insert_c_set ( *rs, cur_elem, CLIB_RB_REFER_COPY);
	cur_elem = get_next_c_rb ( t->root,&current, &pre);		
    }
    return CLIB_SUCCESS;
}

CLIB_BOOL  
subset_c_set(CLIB_SET_PTR t,CLIB_SET_PTR s) {
    CLIB_RB_NODE_PTR pre     = CLIB_RB_NODE_NULL;
    CLIB_RB_NODE_PTR current = CLIB_RB_NODE_NULL;
    CLIB_TYPE cur_elem       = CLIB_NULL;
    CLIB_BOOL result         = CLIB_TRUE;

    current = t->root->_root;
    cur_elem = get_next_c_rb ( t->root,&current, &pre);
    while ( cur_elem ) {
	if ( exists_c_set( s, cur_elem) == CLIB_FALSE ) {
	    result = CLIB_FALSE;
	    break;
	}
	cur_elem = get_next_c_rb ( t->root,&current, &pre);		
    }
    return result;
}

extern void       
print_c_set(CLIB_SET_PTR x, CLIB_TRAVERSAL fn_t) {	
    print_c_rb( x->root, fn_t);
}

