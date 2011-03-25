#include "c_bst.h"
#include "c_util.h"
#include <stdio.h>
#include <string.h>


/* Private Helper Function */
static void 
__in_order(BST_NODE_PTR node, traversal fn_t){
    if ( node ==  BST_NODE_NULL ) return;
    __in_order ( node->left, fn_t);
    (fn_t)(node->_key);
    __in_order ( node->right, fn_t);
}
static void 
__pre_order(BST_NODE_PTR node, traversal fn_t){
    if ( node ==  BST_NODE_NULL ) return;
    (fn_t)(node->_key);
    __pre_order ( node->left, fn_t);
    __pre_order ( node->right, fn_t);
}
static void 
__post_order(BST_NODE_PTR node, traversal fn_t){
    if (node ==  BST_NODE_NULL ) return;
    __post_order ( node->left, fn_t);
    __post_order ( node->right, fn_t);
    (fn_t)(node->_key);
}

static BST_NODE_PTR
__find_c_bst ( BST_NODE_PTR node, compare fn_c, TYPE key ) {
    int compare_result = (fn_c)(key, node->_key);
    while ((node != BST_NODE_NULL) && 
	                (compare_result = (fn_c)(key, node->_key)) != 0 ){
	if ( compare_result < 0 ) {
	    node = node->left;
	} else {
	    node = node->right;
	}
    } /* while loop ends here */
    return node;
}
static BST_NODE_PTR  
minimum_c_bst(BST_NODE_PTR node) {
    while ( node->left!= BST_NODE_NULL )
	node = node->left;
    return node;
}

static BST_NODE_PTR  
successor_c_bst(BST_NODE_PTR node ) {
    BST_NODE_PTR parent = BST_NODE_NULL;
    if ( node->right != BST_NODE_NULL )
	return minimum_c_bst (node->right);
    parent = node->parent;
    while ( parent != BST_NODE_NULL && node == parent->right ) {
	node   = parent;
	parent = parent->parent;
    }
    return parent;
}

static BST_NODE_PTR
__allocate_tree_node( TYPE key) {
    BST_NODE_PTR node = (BST_NODE_PTR)c_malloc ( sizeof ( c_bst_node ));
    node->_key       = key;
    node->left         = BST_NODE_NULL;
    node->parent         = BST_NODE_NULL;
    node->right         = BST_NODE_NULL;
    return node;
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
    if ( node->left )
	delete_all_node ( node->left, fn_d);
    if ( node->right )
	delete_all_node ( node->right, fn_d);
    (fn_d)(node->_key);
}
void   
destroy_c_bst(BST_PTR tree){
    if (tree->_root ==  BST_NODE_NULL ) return;
    delete_all_node( tree->_root, tree->destroy_fn);
}
void   
insert_c_bst(BST_PTR tree, TYPE key ) {
    BST_NODE_PTR y   = BST_NODE_NULL;
    BST_NODE_PTR x   = tree->_root;
    BST_NODE_PTR node = __allocate_tree_node ( key );

    if ( node == BST_NODE_NULL ) return;

    while ( x != BST_NODE_NULL ) {
	int compare_result = (tree->compare_fn)(key, x->_key);
	y = x;		
	if ( compare_result < 0 )
	    x = x->left;
	else
	    x = x->right;
    }
    node->parent = y;

    if (y == BST_NODE_NULL ) {
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
delete_c_bst(BST_PTR tree, TYPE key ){
    BST_NODE_PTR z = find_c_bst ( tree, key );
    BST_NODE_PTR y = BST_NODE_NULL;
    BST_NODE_PTR x = BST_NODE_NULL;

    if ( z  == BST_NODE_NULL ) return;

    if ( z->left == BST_NODE_NULL || z->right == BST_NODE_NULL )
	y = z;
    else
	y = successor_c_bst ( z );

    if ( y->left != BST_NODE_NULL )
	x  = y->left;
    else
	x  = y->right;

    if ( x != BST_NODE_NULL )
	x->parent = y->parent;

    if ( y->parent == BST_NODE_NULL ) {
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
walk_c_bst_r(BST_PTR tree, int type){
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
BST_NODE_PTR
find_c_bst(BST_PTR tree, TYPE key ) {
    return __find_c_bst ( tree->_root, tree->compare_fn, key );
}

