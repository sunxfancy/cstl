#include "c_datastructure.h"
#include <stdio.h>
#include <string.h>


/* Private Helper Function */
static void 
__in_order(CLIB_BST_NODE_PTR node, CLIB_TRAVERSAL fn_t){
    if ( node ==  CLIB_BST_NODE_NULL ) return;
    __in_order ( node->left, fn_t);
    (fn_t)(node->_key);
    __in_order ( node->right, fn_t);
}
static void 
__pre_order(CLIB_BST_NODE_PTR node, CLIB_TRAVERSAL fn_t){
    if ( node ==  CLIB_BST_NODE_NULL ) return;
    (fn_t)(node->_key);
    __pre_order ( node->left, fn_t);
    __pre_order ( node->right, fn_t);
}
static void 
__post_order(CLIB_BST_NODE_PTR node, CLIB_TRAVERSAL fn_t){
    if (node ==  CLIB_BST_NODE_NULL ) return;
    __post_order ( node->left, fn_t);
    __post_order ( node->right, fn_t);
    (fn_t)(node->_key);
}

static CLIB_BST_NODE_PTR
__find_c_bst ( CLIB_BST_NODE_PTR node, CLIB_COMPARE fn_c, CLIB_TYPE key ) {
    int compare_result = (fn_c)(key, node->_key);
    while ((node != CLIB_BST_NODE_NULL) && 
	   (compare_result = (fn_c)(key, node->_key)) != 0 ){
	if ( compare_result < 0 ) {
	    node = node->left;
	} else {
	    node = node->right;
	}
    } /* while loop ends here */
    return node;
}
static CLIB_BST_NODE_PTR  
minimum_c_bst(CLIB_BST_NODE_PTR node) {
    while ( node->left!= CLIB_BST_NODE_NULL )
	node = node->left;
    return node;
}

static CLIB_BST_NODE_PTR  
successor_c_bst(CLIB_BST_NODE_PTR node ) {
    CLIB_BST_NODE_PTR parent = CLIB_BST_NODE_NULL;
    if ( node->right != CLIB_BST_NODE_NULL )
	return minimum_c_bst (node->right);
    parent = node->parent;
    while ( parent != CLIB_BST_NODE_NULL && node == parent->right ) {
	node   = parent;
	parent = parent->parent;
    }
    return parent;
}

static CLIB_BST_NODE_PTR
__allocate_tree_node( CLIB_TYPE key) {
    CLIB_BST_NODE_PTR node = (CLIB_BST_NODE_PTR)clib_malloc ( sizeof ( CLIB_BST_NODE ));
    node->_key       = key;
    node->left         = CLIB_BST_NODE_NULL;
    node->parent         = CLIB_BST_NODE_NULL;
    node->right         = CLIB_BST_NODE_NULL;
    return node;
}

/* External Interfaces Implementation */
CLIB_BST_PTR 
new_c_bst(CLIB_DESTROY fn_d, CLIB_COMPARE fn_c, CLIB_TRAVERSAL fn_t){
    CLIB_BST_PTR tree        = (CLIB_BST_PTR)clib_malloc( sizeof ( CLIB_BST )); 
    tree->compare_fn   = fn_c;
    tree->destroy_fn   = fn_d;
    tree->traversal_fn = fn_t;
    tree->_root        = CLIB_BST_NODE_NULL;
    return tree;
}
static void
delete_all_node ( CLIB_BST_NODE_PTR node, CLIB_DESTROY fn_d) {
    if ( node->left )
	delete_all_node ( node->left, fn_d);
    if ( node->right )
	delete_all_node ( node->right, fn_d);
    (fn_d)(node->_key);
}
void   
destroy_c_bst(CLIB_BST_PTR tree){
    if (tree->_root ==  CLIB_BST_NODE_NULL ) return;
    delete_all_node( tree->_root, tree->destroy_fn);
}
void   
insert_c_bst(CLIB_BST_PTR tree, CLIB_TYPE key ) {
    CLIB_BST_NODE_PTR y   = CLIB_BST_NODE_NULL;
    CLIB_BST_NODE_PTR x   = tree->_root;
    CLIB_BST_NODE_PTR node = __allocate_tree_node ( key );

    if ( node == CLIB_BST_NODE_NULL ) return;

    while ( x != CLIB_BST_NODE_NULL ) {
	int compare_result = (tree->compare_fn)(key, x->_key);
	y = x;		
	if ( compare_result < 0 )
	    x = x->left;
	else
	    x = x->right;
    }
    node->parent = y;

    if (y == CLIB_BST_NODE_NULL ) {
	tree->_root = node;
    } else {
	int compare_result = (tree->compare_fn)(key, y->_key);
	if ( compare_result < 0 ) {
	    y->left = node;
	}
	else {
	    y->right = node;
	}
    }
}
void   
delete_c_bst(CLIB_BST_PTR tree, CLIB_TYPE key ){
    CLIB_BST_NODE_PTR z = find_c_bst ( tree, key );
    CLIB_BST_NODE_PTR y = CLIB_BST_NODE_NULL;
    CLIB_BST_NODE_PTR x = CLIB_BST_NODE_NULL;

    if ( z  == CLIB_BST_NODE_NULL ) return;

    if ( z->left == CLIB_BST_NODE_NULL || z->right == CLIB_BST_NODE_NULL )
	y = z;
    else
	y = successor_c_bst ( z );

    if ( y->left != CLIB_BST_NODE_NULL )
	x  = y->left;
    else
	x  = y->right;

    if ( x != CLIB_BST_NODE_NULL )
	x->parent = y->parent;

    if ( y->parent == CLIB_BST_NODE_NULL ) {
	tree->_root = x;
    } else {
	if ( y == y->parent->left ) {
	    y->parent->left = x;
	} else {
	    y->parent->right = x;
	}
    }
    if ( y != z ) {
	(tree->destroy_fn)(z->_key);
	z->_key =  y->_key;
    } else 
	(tree->destroy_fn)(y->_key);
}

void   
walk_c_bst_r(CLIB_BST_PTR tree, int type){
    switch ( type ) {
      case 0:
	  __in_order( tree->_root, tree->traversal_fn );
	  break;
      case 1:
	  __pre_order( tree->_root, tree->traversal_fn );
	  break;
      case 2:
	  __post_order( tree->_root, tree->traversal_fn );
	  break;
      default:
	  break;
    }
}
CLIB_BST_NODE_PTR
find_c_bst(CLIB_BST_PTR tree, CLIB_TYPE key ) {
    return __find_c_bst ( tree->_root, tree->compare_fn, key );
}


