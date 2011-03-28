#include "c_datastructure.h"
#include <stdio.h>

CLIB_SET_PTR 
new_c_set( CLIB_DESTROY fn_d, CLIB_COMPARE fn_c) {

    CLIB_SET_PTR x  =  (CLIB_SET_PTR ) clib_malloc ( sizeof ( CLIB_SET ));
    x->root  = new_c_rb ( fn_d, CLIB_NULL, fn_c, CLIB_SET_TYPE);
    return x;
}
void    
delete_c_set ( CLIB_SET_PTR x) {
    if ( x != CLIB_SET_NULL ){
	delete_c_rb ( x->root );
	clib_free ( x );
    }
}
void
insert_c_set ( CLIB_SET_PTR x, CLIB_TYPE k, int reference) {
    if ( x != CLIB_SET_NULL && k ){
	insert_c_rb ( x->root, k, CLIB_NULL, reference );
    }
}
void
remove_c_set ( CLIB_SET_PTR x, CLIB_TYPE k ) {
    CLIB_RB_NODE_PTR t_node;
    CLIB_TYPE key;

    if ( x != CLIB_SET_NULL && k ){
	t_node = remove_c_rb ( x->root, k );
	if ( !t_node ) {
	    return;
	}
	key = t_node->value._key;
	clib_free ( key );
	clib_free ( t_node );
    }
}

CLIB_BOOL
exists_c_set( CLIB_SET_PTR x, CLIB_TYPE k ) {
    if ( x != CLIB_SET_NULL && k ){
	return ( find_c_rb ( x->root, k ) == CLIB_NULL ) ?
	    CLIB_FALSE : CLIB_TRUE;
    }
    return CLIB_FALSE;
}
CLIB_BOOL
empty_c_set ( CLIB_SET_PTR x ) {

    if ( x != CLIB_SET_NULL ) {
	return empty_c_rb(x->root);
    }
    return CLIB_FALSE;
}

CLIB_ERROR
union_c_set(CLIB_SET_PTR t,CLIB_SET_PTR s, CLIB_SET_PTR *rs) {
    CLIB_RB_NODE_PTR pre     = CLIB_RB_NODE_NULL;
    CLIB_RB_NODE_PTR current = CLIB_RB_NODE_NULL;
    CLIB_TYPE cur_elem       = CLIB_NULL;
    /* Both the operand set should be of the same type
     * We check for the destroy and compare funciton 
     */
    if ((t->root->compare_key_fn != s->root->compare_key_fn) || 
	(t->root->destroy_key_fn != s->root->destroy_key_fn))
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

    if ((t->root->compare_key_fn != s->root->compare_key_fn) || 
	(t->root->destroy_key_fn != s->root->destroy_key_fn))

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

    if ((t->root->compare_key_fn != s->root->compare_key_fn) || 
	(t->root->destroy_key_fn != s->root->destroy_key_fn))

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


