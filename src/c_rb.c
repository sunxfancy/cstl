#include "c_rb.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>


#define RB_SENTINEL &tree->_sentinel 

static void
__left_rotate(RB_PTR tree, RB_NODE_PTR x){
    RB_NODE_PTR y;
    y = x->right;
    x->right = y->left;
    if (y->left != RB_SENTINEL)
	y->left->parent = x;
    if (y != RB_SENTINEL)
	y->parent = x->parent;
    if (x->parent){
	if (x == x->parent->left)
	    x->parent->left = y;
	else
	    x->parent->right = y;
    }
    else
	tree->_root = y;
    y->left = x;
    if (x != RB_SENTINEL)
	x->parent = y;
}
static void
__right_rotate(RB_PTR tree, RB_NODE_PTR x) {
    RB_NODE_PTR y = x->left;
    x->left = y->right;
    if (y->right != RB_SENTINEL)
	y->right->parent = x;
    if (y != RB_SENTINEL)
	y->parent = x->parent;
    if (x->parent) {
	if (x == x->parent->right)
	    x->parent->right = y;
	else
	    x->parent->left = y;
    }
    else
	tree->_root = y;
    y->right = x;
    if (x != RB_SENTINEL)
	x->parent = y;
}

RB_PTR 
new_c_rb(destroy fn_d, compare fn_c, int type){

    RB_PTR tree                  = (RB_PTR)c_malloc(sizeof(c_rb)); 
    tree->compare_fn             = fn_c;
    tree->destroy_fn             = fn_d;
    tree->_root                  = RB_SENTINEL;
    tree->_sentinel.left         = RB_SENTINEL;
    tree->_sentinel.right        = RB_SENTINEL;
    tree->_sentinel.parent       = RB_NODE_NULL;
    tree->_sentinel.color        = BLACK;
    tree->_type                  = type;
    tree->_sentinel.value._key   = CLIB_NULL;
    tree->_sentinel.value._value = CLIB_NULL;

    return tree;
}
static void 
__rb_insert_fixup( RB_PTR tree, RB_NODE_PTR x ) {
    while (x != tree->_root && x->parent->color == RED) {
	/* Remember newly insertly node always has color RED
	 * If we are here means, color of PARENT of the newly inserted
	 * node is also RED and we have RED->RED voialtion
	 */
	if (x->parent == x->parent->parent->left) {
	    /* Identify the orientation of the newly inserted
	     * node, whether the node is inserted into left or right
	     */
	    RB_NODE_PTR y = x->parent->parent->right; /*Get the uncle */
	    if (y->color == RED) {
		/* Case : Uncle is RED */
		x->parent->color         = BLACK;
		y->color                 = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	    } else {
		if (x == x->parent->right){
		    x = x->parent;
		    __left_rotate (tree, x);
		}
		x->parent->color         = BLACK;
		x->parent->parent->color = RED;
		__right_rotate (tree, x->parent->parent);
	    }
	} else {
	    /* right orientation */
	    RB_NODE_PTR y = x->parent->parent->left;
	    if (y->color == RED) {
		x->parent->color         = BLACK;
		y->color                 = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	    } else {
		if (x == x->parent->left) {
		    x = x->parent;
		    __right_rotate (tree, x);
		}
		x->parent->color         = BLACK;
		x->parent->parent->color = RED;
		__left_rotate (tree, x->parent->parent);
	    }
	}
    }
    tree->_root->color = BLACK;
}
static TYPE
__find_c_rb ( RB_PTR tree, TYPE k ) {
    RB_NODE_PTR x = tree->_root;
    int compare_result;

    while (x != RB_SENTINEL) {
	compare_result = tree->compare_fn (k, x->value._key);
	if (compare_result == 0) {
	    return x->value._key;
	} else {
	    x = compare_result < 0 ? x->left : x->right;
	}
    }
    return CLIB_NULL;
}

CLIB_ERROR   
insert_c_rb(RB_PTR tree, TYPE key , TYPE value) {

    CLIB_ERROR rc = CLIB_SUCCESS;
    RB_NODE_PTR x,y,z;

    y = tree->_root;
    z = RB_NODE_NULL;
    while (y != RB_SENTINEL)
    {
	int c = (tree->compare_fn) (
				    key, 
				    y->value._key);
	if (c == 0)
	    return CLIB_RBTREE_KEY_DUPLICATE;
	z = y;
	if ( c < 0 )
	    y = y->left;
	else
	    y = y->right;
    }

    x = (RB_NODE_PTR)c_malloc (sizeof(c_rb_node));
    x->parent       = z;
    x->left         = RB_SENTINEL;
    x->right        = RB_SENTINEL;
    x->color        = RED;
    x->value._key   = key;
    x->value._value = value;

    if (z) {
	if (tree->compare_fn(key, z->value._key) < 0)
	    z->left = x;
	else
	    z->right = x;
    }
    else
	tree->_root = x;
    __rb_insert_fixup (tree, x);

    return rc;
}
static void
__rb_remove_fixup( RB_PTR tree, RB_NODE_PTR x ) {
    while (x != tree->_root && x->color == BLACK) {
	if (x == x->parent->left) {
	    RB_NODE_PTR w = x->parent->right;
	    if (w->color == RED) {
		w->color         = BLACK;
		x->parent->color = RED;
		__left_rotate (tree, x->parent);
		w = x->parent->right;
	    }
	    if (w->left->color == BLACK && w->right->color == BLACK) {
		w->color = RED;
		x = x->parent;
	    } else {
		if (w->right->color == BLACK)  {
		    w->left->color = BLACK;
		    w->color       = RED;
		    __right_rotate (tree, w);
		    w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->right->color = BLACK;
		__left_rotate (tree, x->parent);
		x = tree->_root;
	    }
	} else {
	    RB_NODE_PTR w = x->parent->left;
	    if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		__right_rotate (tree, x->parent);
		w = x->parent->left;
	    }
	    if (w->right->color == BLACK && w->left->color == BLACK) {
		w->color = RED;
		x = x->parent;
	    } else {
		if (w->left->color == BLACK) {
		    w->right->color = BLACK;
		    w->color = RED;
		    __left_rotate (tree, w);
		    w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->left->color = BLACK;
		__right_rotate (tree, x->parent);
		x = tree->_root;
	    }
	}
    }
    x->color = BLACK;
}
static void   
__remove_c_rb(RB_PTR tree, RB_NODE_PTR z ) {
    RB_NODE_PTR x, y;
    void *tmp;
    if (z->left == RB_SENTINEL || z->right == RB_SENTINEL)
	y = z;
    else {
	y = z->right;
	while (y->left != RB_SENTINEL)
	    y = y->left;
    }
    if (y->left != RB_SENTINEL)
	x = y->left;
    else
	x = y->right;

    x->parent = y->parent;
    if (y->parent)
    {
	if (y == y->parent->left)
	    y->parent->left = x;
	else
	    y->parent->right = x;
    }
    else
	tree->_root = x;
    if (y != z) {
	tmp             = z->value._key;
	z->value._key   = y->value._key;
	y->value._key   = tmp;

	tmp             = z->value._value;
	z->value._value = y->value._value;
	y->value._value = tmp;
    }
    if (y->color == BLACK)
	__rb_remove_fixup (tree, x);
}
CLIB_ERROR
remove_c_rb ( RB_PTR tree, TYPE key ) {
    RB_NODE_PTR z;
    z = tree->_root;
    while (z != RB_SENTINEL)
    {
	if (tree->compare_fn (key, z->value._key) == 0)
	    break;
	else
	    z = (tree->compare_fn (key, z->value._key) < 0) ? 
	                                   z->left : z->right;
    }
    if (z == RB_SENTINEL)
	return CLIB_RBTREE_KEY_NOT_FOUND;
    __remove_c_rb(tree, z );
    return CLIB_SUCCESS;
}

void   
delete_c_rb(RB_PTR tree) {
    RB_NODE_PTR z = tree->_root;
    while (z != RB_SENTINEL) {
	if (z->left != RB_SENTINEL)
	    z = z->left;
	else if (z->right != RB_SENTINEL)
	    z = z->right;
	else {
	    if (tree->destroy_fn){
		tree->destroy_fn (z->value._key);
	    }
	    if (z->parent) {
		z = z->parent;
		if (z->left != RB_SENTINEL){
		    c_free (z->left);
		    z->left = RB_SENTINEL;
		}
		else if (z->right != RB_SENTINEL){
		    c_free (z->right);
		    z->right = RB_SENTINEL;
		}
	    } else {
		c_free (z);
		z = RB_SENTINEL;
	    }
	}
    }
    c_free ( tree );
}

TYPE
find_c_rb(RB_PTR tree, TYPE key ) {
    return __find_c_rb ( tree, key );
}
