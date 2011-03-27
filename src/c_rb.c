#include "c_datastructure.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#ifdef _VERIFY_TREE
static CLIB_RB_NODE_PTR debug_grandparent(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static CLIB_RB_NODE_PTR debug_sibling(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static CLIB_RB_NODE_PTR debug_uncle(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static void debug_verify_properties(CLIB_RB_PTR);
static void debug_verify_property_1(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static void debug_verify_property_2(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static int debug_node_color(CLIB_RB_PTR,CLIB_RB_NODE_PTR n);
static void debug_verify_property_4(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static void debug_verify_property_5(CLIB_RB_PTR,CLIB_RB_NODE_PTR);
static void debug_verify_property_5_helper(CLIB_RB_PTR,CLIB_RB_NODE_PTR,int,int*);
#endif

#define RB_SENTINEL &tree->_sentinel

static void
__left_rotate(CLIB_RB_PTR tree, CLIB_RB_NODE_PTR x){
    CLIB_RB_NODE_PTR y;
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
__right_rotate(CLIB_RB_PTR tree, CLIB_RB_NODE_PTR x) {
    CLIB_RB_NODE_PTR y = x->left;
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

CLIB_RB_PTR
new_c_rb(CLIB_DESTROY fn_d, CLIB_COMPARE fn_c, int type){

    CLIB_RB_PTR tree                  = (CLIB_RB_PTR)clib_malloc(sizeof(c_rb));
    tree->compare_fn             = fn_c;
    tree->destroy_fn             = fn_d;
    tree->_root                  = RB_SENTINEL;
    tree->_sentinel.left         = RB_SENTINEL;
    tree->_sentinel.right        = RB_SENTINEL;
    tree->_sentinel.parent       = CLIB_RB_NODE_NULL;
    tree->_sentinel.color        = CLIB_BLACK;
    tree->_type                  = type;
    tree->_sentinel.value._key   = CLIB_NULL;
    tree->_sentinel.value._value = CLIB_NULL;

    return tree;
}
static void
__rb_insert_fixup( CLIB_RB_PTR tree, CLIB_RB_NODE_PTR x ) {
    while (x != tree->_root && x->parent->color == CLIB_RED) {
	/* Remember newly insertly CLIB_RB_NODE_PTR always has color CLIB_RED
	 * If we are here means, color of PARENT of the newly inserted
	 * CLIB_RB_NODE_PTR is also CLIB_RED and we have CLIB_RED->CLIB_RED voialtion
	 */
	if (x->parent == x->parent->parent->left) {
	    /* Identify the orientation of the newly inserted
	     * CLIB_RB_NODE_PTR, whether the CLIB_RB_NODE_PTR is inserted into left or right
	     */
	    CLIB_RB_NODE_PTR y = x->parent->parent->right; /*Get the uncle */
	    if (y->color == CLIB_RED) {
		/* Case : Uncle is CLIB_RED */
		x->parent->color         = CLIB_BLACK;
		y->color                 = CLIB_BLACK;
		x->parent->parent->color = CLIB_RED;
		x = x->parent->parent;
	    } else {
		if (x == x->parent->right){
		    x = x->parent;
		    __left_rotate (tree, x);
		}
		x->parent->color         = CLIB_BLACK;
		x->parent->parent->color = CLIB_RED;
		__right_rotate (tree, x->parent->parent);
	    }
	} else {
	    /* right orientation */
	    CLIB_RB_NODE_PTR y = x->parent->parent->left;
	    if (y->color == CLIB_RED) {
		x->parent->color         = CLIB_BLACK;
		y->color                 = CLIB_BLACK;
		x->parent->parent->color = CLIB_RED;
		x = x->parent->parent;
	    } else {
		if (x == x->parent->left) {
		    x = x->parent;
		    __right_rotate (tree, x);
		}
		x->parent->color         = CLIB_BLACK;
		x->parent->parent->color = CLIB_RED;
		__left_rotate (tree, x->parent->parent);
	    }
	}
    }
    tree->_root->color = CLIB_BLACK;
}
static CLIB_TYPE
__find_c_rb ( CLIB_RB_PTR tree, CLIB_TYPE k ) {
    CLIB_RB_NODE_PTR x = tree->_root;
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
insert_c_rb(CLIB_RB_PTR tree, CLIB_TYPE key , CLIB_TYPE value, int reference) {

    CLIB_ERROR rc = CLIB_SUCCESS;
    CLIB_RB_NODE_PTR x,y,z;

    y = tree->_root;
    z = CLIB_RB_NODE_NULL;
    while (y != RB_SENTINEL)
    {
	int c = (tree->compare_fn) ( key, y->value._key);
	if (c == 0)
	    return CLIB_RBTREE_KEY_DUPLICATE;
	z = y;
	if ( c < 0 )
	    y = y->left;
	else
	    y = y->right;
    }

    x = (CLIB_RB_NODE_PTR)clib_malloc (sizeof(c_rb_node));
    x->parent       = z;
    x->left         = RB_SENTINEL;
    x->right        = RB_SENTINEL;
    x->color        = CLIB_RED;
    x->value._key   = key;
    x->value._value = value;
    /* To handle the case when set theory operation are called
     * Since we are dealing with the void* everywhere 
     * we cannot make the copy of those elements
     * instead of reference is incresed during this time
     */
    if ( reference ) {
	x->reference++;
    } else
	x->reference = 0;


    if (z) {
	if (tree->compare_fn(key, z->value._key) < 0)
	    z->left = x;
	else
	    z->right = x;
    }
    else
	tree->_root = x;
    __rb_insert_fixup (tree, x);

#ifdef _VERIFY_TREE
    debug_verify_properties( tree);
#endif
    return rc;
}
static void
__rb_remove_fixup( CLIB_RB_PTR tree, CLIB_RB_NODE_PTR x ) {
    while (x != tree->_root && x->color == CLIB_BLACK) {
	if (x == x->parent->left) {
	    CLIB_RB_NODE_PTR w = x->parent->right;
	    if (w->color == CLIB_RED) {
		w->color         = CLIB_BLACK;
		x->parent->color = CLIB_RED;
		__left_rotate (tree, x->parent);
		w = x->parent->right;
	    }
	    if (w->left->color == CLIB_BLACK && w->right->color == CLIB_BLACK) {
		w->color = CLIB_RED;
		x = x->parent;
	    } else {
		if (w->right->color == CLIB_BLACK)  {
		    w->left->color = CLIB_BLACK;
		    w->color       = CLIB_RED;
		    __right_rotate (tree, w);
		    w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = CLIB_BLACK;
		w->right->color = CLIB_BLACK;
		__left_rotate (tree, x->parent);
		x = tree->_root;
	    }
	} else {
	    CLIB_RB_NODE_PTR w = x->parent->left;
	    if (w->color == CLIB_RED) {
		w->color = CLIB_BLACK;
		x->parent->color = CLIB_RED;
		__right_rotate (tree, x->parent);
		w = x->parent->left;
	    }
	    if (w->right->color == CLIB_BLACK && w->left->color == CLIB_BLACK) {
		w->color = CLIB_RED;
		x = x->parent;
	    } else {
		if (w->left->color == CLIB_BLACK) {
		    w->right->color = CLIB_BLACK;
		    w->color = CLIB_RED;
		    __left_rotate (tree, w);
		    w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = CLIB_BLACK;
		w->left->color = CLIB_BLACK;
		__right_rotate (tree, x->parent);
		x = tree->_root;
	    }
	}
    }
    x->color = CLIB_BLACK;
}
static CLIB_RB_NODE_PTR  
__remove_c_rb(CLIB_RB_PTR tree, CLIB_RB_NODE_PTR z ) {
    CLIB_RB_NODE_PTR x, y;
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
    if (y->color == CLIB_BLACK)
	__rb_remove_fixup (tree, x);

    if ( y->reference ) {
	y->reference--;
	return CLIB_RB_NODE_NULL;
    }
    return y;
}
CLIB_RB_NODE_PTR
remove_c_rb ( CLIB_RB_PTR tree, CLIB_TYPE key ) {
    CLIB_RB_NODE_PTR z;
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
	return CLIB_RB_NODE_NULL;
    return ( __remove_c_rb(tree, z ));

#ifdef _VERIFY_TREE
    debug_verify_properties( tree);
#endif

    return CLIB_SUCCESS;
}

void  
delete_c_rb(CLIB_RB_PTR tree) {
    CLIB_RB_NODE_PTR z = tree->_root;
    while (z != RB_SENTINEL) {
	if (z->left != RB_SENTINEL)
	    z = z->left;
	else if (z->right != RB_SENTINEL)
	    z = z->right;
	else {
	    if ( z->reference == 0 ) {
		if (tree->destroy_fn){
		    tree->destroy_fn (z->value._key);
		}
	    } else {
		z->reference--;
	    }

	    if (z->parent) {
		z = z->parent;
		if (z->left != RB_SENTINEL){
		    clib_free (z->left);
		    z->left = RB_SENTINEL;
		}
		else if (z->right != RB_SENTINEL){
		    clib_free (z->right);
		    z->right = RB_SENTINEL;
		}
	    } else {
		clib_free (z);
		z = RB_SENTINEL;
	    }
	}
    }
    clib_free ( tree );
}

CLIB_TYPE
find_c_rb(CLIB_RB_PTR tree, CLIB_TYPE key ) {
    return __find_c_rb ( tree, key );
}

CLIB_BOOL 
empty_c_rb(CLIB_RB_PTR tree) {
    if ( tree->_root != RB_SENTINEL )
	return CLIB_TRUE;
    return CLIB_FALSE;
}
CLIB_RB_NODE_PTR
get_next_c_rb(CLIB_RB_PTR tree, CLIB_RB_NODE_PTR *current, CLIB_RB_NODE_PTR *pre) {
    CLIB_RB_NODE_PTR prev_current;
    while((*current) != RB_SENTINEL) {
	if((*current)->left == RB_SENTINEL){
	    prev_current = (*current);
	    (*current) = (*current)->right;
	    return prev_current->value._key;			
	} else {
	    (*pre) = (*current)->left;
	    while((*pre)->right != RB_SENTINEL && (*pre)->right != (*current))
		(*pre) = (*pre)->right; 
	    if((*pre)->right == RB_SENTINEL) {
		(*pre)->right = (*current);
		(*current) = (*current)->left;
	    } else {
		(*pre)->right = RB_SENTINEL;
		prev_current = (*current);
		(*current) = (*current)->right;
		return prev_current->value._key;				
	    }
	} 
    } 
    return CLIB_RB_NODE_NULL;
}
static void
__print_c_rb(CLIB_RB_PTR tree, CLIB_RB_NODE_PTR node, CLIB_TRAVERSAL fn_t ) {
    if ( node ==  RB_SENTINEL ) return;
    __print_c_rb ( tree, node->left, fn_t);
    (fn_t)(node->value._key);
    __print_c_rb ( tree,node->right, fn_t);
}

void
print_c_rb(CLIB_RB_PTR tree,  CLIB_TRAVERSAL fn_t) {
    __print_c_rb(tree,tree->_root,fn_t);

}

#ifdef _VERIFY_TREE
CLIB_RB_NODE_PTR debug_grandparent(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    assert (n != RB_SENTINEL);
    assert (n->parent != RB_SENTINEL); /* Not the _root CLIB_RB_NODE_PTR */
    assert (n->parent->parent != RB_SENTINEL); /* Not child of _root */
    return n->parent->parent;
}

CLIB_RB_NODE_PTR debug_sibling(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    assert (n != RB_SENTINEL);
    assert (n->parent != RB_SENTINEL); /* Root CLIB_RB_NODE_PTR has no sibling */
    if (n == n->parent->left)
	return n->parent->right;
    else
	return n->parent->left;
}

CLIB_RB_NODE_PTR debug_uncle(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    assert (n != RB_SENTINEL);
    assert (n->parent != RB_SENTINEL); /* Root CLIB_RB_NODE_PTR has no uncle */
    assert (n->parent->parent != RB_SENTINEL); /* Children of _root have no uncle */
    return debug_sibling(tree,n->parent);
}

void debug_verify_properties(CLIB_RB_PTR t) {
    debug_verify_property_1(t,t->_root);
    debug_verify_property_2(t,t->_root);
    debug_verify_property_4(t,t->_root);
    debug_verify_property_5(t,t->_root);
}

void debug_verify_property_1(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    assert(debug_node_color(tree,n) == CLIB_RED || debug_node_color(tree,n) == CLIB_BLACK);
    if (n == RB_SENTINEL) return;
    debug_verify_property_1(tree,n->left);
    debug_verify_property_1(tree,n->right);
}

void debug_verify_property_2(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR _root) {
    assert(debug_node_color(tree,_root) == CLIB_BLACK);
}

int debug_node_color(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    return n == RB_SENTINEL ? CLIB_BLACK : n->color;
}

void debug_verify_property_4(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n) {
    if (debug_node_color(tree,n) == CLIB_RED) {
	assert (debug_node_color(tree,n->left)   == CLIB_BLACK);
	assert (debug_node_color(tree,n->right)  == CLIB_BLACK);
	assert (debug_node_color(tree,n->parent) == CLIB_BLACK);
    }
    if (n == RB_SENTINEL) return;
    debug_verify_property_4(tree,n->left);
    debug_verify_property_4(tree,n->right);
}

void debug_verify_property_5(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR _root) {
    int black_count_path = -1;
    debug_verify_property_5_helper(tree,_root, 0, &black_count_path);
}

void debug_verify_property_5_helper(CLIB_RB_PTR tree,CLIB_RB_NODE_PTR n, int black_count, int* path_black_count) {
    if (debug_node_color(tree,n) == CLIB_BLACK) {
	black_count++;
    }
    if (n == RB_SENTINEL) {
	if (*path_black_count == -1) {
	    *path_black_count = black_count;
	} else {
	    assert (black_count == *path_black_count);
	}
	return;
    }
    debug_verify_property_5_helper(tree,n->left,  black_count, path_black_count);
    debug_verify_property_5_helper(tree,n->right, black_count, path_black_count);
}
#endif
