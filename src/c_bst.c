#include "c_bst.h"
#include "c_util.h"
#include <stdio.h>
#include <string.h>


/* Private Helper Function */
static void 
__walk_c_bst_r_in_order(BST_NODE_PTR _N, traversal fn_t){
	if ( _N ==  BST_NODE_NULL ) return;
	__walk_c_bst_r_in_order ( _N->_L, fn_t);
	(fn_t)(_N->_key);
	__walk_c_bst_r_in_order ( _N->_R, fn_t);
}
static void 
__walk_c_bst_r_pre_order(BST_NODE_PTR _N, traversal fn_t){
	if ( _N ==  BST_NODE_NULL ) return;
	(fn_t)(_N->_key);
	__walk_c_bst_r_pre_order ( _N->_L, fn_t);
	__walk_c_bst_r_pre_order ( _N->_R, fn_t);
}
static void 
__walk_c_bst_r_post_order(BST_NODE_PTR _N, traversal fn_t){
	if (_N ==  BST_NODE_NULL ) return;
	__walk_c_bst_r_post_order ( _N->_L, fn_t);
	__walk_c_bst_r_post_order ( _N->_R, fn_t);
	(fn_t)(_N->_key);
}
static void 
__walk_c_bst_in_order(BST_NODE_PTR _N, traversal fn_t){
}
static void 
__walk_c_bst_pre_order(BST_NODE_PTR _N, traversal fn_t){
	if ( _N == BST_NODE_NULL ) return;
}
static void 
__walk_c_bst_post_order(BST_NODE_PTR _N, traversal fn_t){
	if ( _N == BST_NODE_NULL ) return;
}
static BST_NODE_PTR
__find_c_bst ( BST_NODE_PTR _N, compare fn_c, T key ) {
	int compare_result = (fn_c)(key, _N->_key);
	while ((_N != BST_NODE_NULL) && (compare_result = (fn_c)(key, _N->_key)) != 0 ){
		if ( compare_result < 0 ) {
			_N = _N->_L;
		} else {
			_N = _N->_R;
		}
	} /* while loop ends here */
	return _N;
}
static BST_NODE_PTR
__allocate_tree_node( T key) {
	BST_NODE_PTR _N = (BST_NODE_PTR)c_malloc ( sizeof ( c_bst_node ));
	_N->_key       = key;
	_N->_L         = BST_NODE_NULL;
	_N->_P         = BST_NODE_NULL;
	_N->_R         = BST_NODE_NULL;
	return _N;
}

/* External Interfaces Implementation */
BST_PTR 
new_c_bst(destroy fn_d, compare fn_c, traversal fn_t){
	BST_PTR tree        = (BST_PTR)c_malloc( sizeof ( c_bst )); 
	tree->compare_fn   = fn_c;
	tree->destroy_fn   = fn_d;
	tree->traversal_fn = fn_t;
	tree->_root        = BST_NODE_NULL;
	return tree;
}
static void
delete_all_node ( BST_NODE_PTR node, destroy fn_d) {
	if ( node->_L )
		delete_all_node ( node->_L, fn_d);
	if ( node->_R )
		delete_all_node ( node->_R, fn_d);
	(fn_d)(node->_key);
}
void   
destroy_c_bst(BST_PTR tree){
	if (tree->_root ==  BST_NODE_NULL ) return;
	delete_all_node( tree->_root, tree->destroy_fn);
}
void   
insert_c_bst(BST_PTR tree, T key ) {
	BST_NODE_PTR _Y   = BST_NODE_NULL;
	BST_NODE_PTR _X   = tree->_root;
	BST_NODE_PTR _N = __allocate_tree_node ( key );

	while ( _X != BST_NODE_NULL ) {
		int compare_result = (tree->compare_fn)(key, _X->_key);
		_Y = _X;		
		if ( compare_result < 0 )
			_X = _X->_L;
		else
			_X = _X->_R;
	}
	_N->_P = _Y;

	if (_Y == BST_NODE_NULL ) {
		tree->_root = _N;
	} else {
		int compare_result = (tree->compare_fn)(key, _Y->_key);
		if ( compare_result < 0 ) {
			_Y->_L = _N;
		}
		else {
			_Y->_R = _N;
		}
	}
}
void   
delete_c_bst(BST_PTR tree, T key ){
	BST_NODE_PTR _Z = find_c_bst ( tree, key );
	BST_NODE_PTR _Y = BST_NODE_NULL;
	BST_NODE_PTR _X = BST_NODE_NULL;

	if ( _Z  == BST_NODE_NULL ) return;

	if ( _Z->_L == BST_NODE_NULL || _Z->_R == BST_NODE_NULL )
		_Y = _Z;
	else
		_Y = successor_c_bst ( _Z );

	if ( _Y->_L != BST_NODE_NULL )
		_X  = _Y->_L;
	else
		_X  = _Y->_R;

	if ( _X != BST_NODE_NULL )
		_X->_P = _Y->_P;

	if ( _Y->_P == BST_NODE_NULL ) {
		tree->_root = _X;
	} else {
		if ( _Y == _Y->_P->_L ) {
			_Y->_P->_L = _X;
		} else {
			_Y->_P->_R = _X;
		}
	}
	if ( _Y != _Z ) {
		(tree->destroy_fn)(_Z->_key);
		_Z->_key =  _Y->_key;
	} else 
		(tree->destroy_fn)(_Y->_key);
}

void   
walk_c_bst(BST_PTR tree, int type){
	switch ( type ) {
		case 0:
			__walk_c_bst_in_order( tree->_root, tree->traversal_fn );
			break;
		case 1:
			__walk_c_bst_pre_order( tree->_root, tree->traversal_fn );
			break;
		case 2:
			__walk_c_bst_post_order( tree->_root, tree->traversal_fn );
			break;
		default:
			break;
	}
}
void   
walk_c_bst_r(BST_PTR tree, int type){
	switch ( type ) {
		case 0:
			__walk_c_bst_r_in_order( tree->_root, tree->traversal_fn );
			break;
		case 1:
			__walk_c_bst_r_pre_order( tree->_root, tree->traversal_fn );
			break;
		case 2:
			__walk_c_bst_r_post_order( tree->_root, tree->traversal_fn );
			break;
		default:
			break;
	}
}
BST_NODE_PTR
find_c_bst(BST_PTR tree, T key ) {
	return __find_c_bst ( tree->_root, tree->compare_fn, key );
}
BST_NODE_PTR  
minimum_c_bst(BST_NODE_PTR _N) {
	while ( _N->_L!= BST_NODE_NULL )
		_N = _N->_L;
	return _N;
}
BST_NODE_PTR  
maximum_c_bst(BST_NODE_PTR _N){
	while (_N->_R != BST_NODE_NULL )
		_N = _N->_R;
	return _N;
}

BST_NODE_PTR  
successor_c_bst(BST_NODE_PTR _N ) {
	BST_NODE_PTR _P = BST_NODE_NULL;
	if ( _N->_R != BST_NODE_NULL )
		return minimum_c_bst (_N->_R);
	_P = _N->_P;
	while ( _P != BST_NODE_NULL && _N == _P->_R ) {
		_N   = _P;
		_P = _P->_P;
	}
	return _P;
}
BST_NODE_PTR  
predecessor_c_bst(BST_NODE_PTR _N) {
	BST_NODE_PTR _P = BST_NODE_NULL;
	if ( _N->_L != BST_NODE_NULL )
		return maximum_c_bst (_N->_L);
	_P = _N->_P;
	while ( _P != BST_NODE_NULL && _N == _P->_L ) {
		_N   = _P;
		_P = _P->_P;
	}
	return _P;
}
T 
get_key_c_bst ( BST_NODE_PTR _N) {
	if ( _N )
		return _N->_key;
	return (T)0;
}

BST_NODE_PTR
get_left_c_bst ( BST_NODE_PTR _N ) {
	if ( _N ) 
		return _N->_L;
	return BST_NODE_NULL;
}
BST_NODE_PTR
get_right_c_bst ( BST_NODE_PTR _N ){
	if ( _N ) 
		return _N->_R;
	return BST_NODE_NULL;
}
BST_NODE_PTR
get_parent_c_bst ( BST_NODE_PTR _N ) {
	if ( _N )
		return _N->_P;
	return BST_NODE_NULL;
}
