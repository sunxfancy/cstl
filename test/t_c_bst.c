#include "c_datastructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int compare_e ( void* l, void *r ) {
    int left = *(int*)l;
    int right = *(int*)r;
    if ( left < right ) return -1;
    if ( left == right ) return 0;
    return 1;
}
static void free_e ( void *p ) {
    if ( p ) {
	free ( p );
    }
}
static void traversal_e ( void *p ) {
    if ( p ) 
	printf ( "%d ", *(int*)p);
}
typedef struct test_data_tree {
    int element;
    int left;
    int right;
    int parent;
} TS;
static CLIB_TYPE
get_key (  CLIB_BST_NODE_PTR node) {
    if ( node ) 
	return node->_key;
    return CLIB_NULL;
}

static CLIB_BST_NODE_PTR
get_left (CLIB_BST_NODE_PTR node ) {
    if ( node->left != CLIB_BST_NODE_NULL)
	return node->left;
    return CLIB_BST_NODE_NULL;
}
static CLIB_BST_NODE_PTR
get_right (CLIB_BST_NODE_PTR node ){
    if ( node->right != CLIB_BST_NODE_NULL)
	return node->right;
    return CLIB_BST_NODE_NULL;
}
static CLIB_BST_NODE_PTR
get_parent (CLIB_BST_NODE_PTR node ) {
    if ( node->parent != CLIB_BST_NODE_NULL)
	return node->parent;
    return CLIB_BST_NODE_NULL;
}

static void update_values ( CLIB_BST_NODE_PTR v, int *l, int *r, int *p , int *e ) {

    if ( get_key(v) ) 
	*e = *(int*)get_key (v);
    if ( get_left(v) ) 
	*l = *(int*)get_key(get_left(v));
    if ( get_right(v) ) 
	*r = *(int*)get_key(get_right(v));
    if ( get_parent(v) ) 		
	*p = *(int*)get_key(get_parent(v));
}

static void 
test_each_elements(int l,int r, int p, int e,CLIB_BST_NODE_PTR v, TS ts[], int i) {
    assert ( ts[i].element == e);
    if (ts[i].left != 0 ) 
	assert ( ts[i].left == l);
    else
	assert ((void*)0 == (void*)get_key(get_left(v)));
    if ( ts[i].right != 0 ) 
	assert (ts[i].right == r);
    else
	assert ((void*)0 == (void*)get_key(get_right(v)));
    if (ts[i].parent != 0 ) 
	assert (ts[i].parent == p);
    else
	assert ((void*)0 == (void*)get_key(get_parent(v)));
}
static void
test_all_elements(CLIB_BST_PTR tree, TS ts[], int size) {
    int i = 0;
    for ( i = 0; i < size; i++) {
	CLIB_BST_NODE_PTR v = CLIB_BST_NODE_NULL;
	int l,r,p,e;
	v = find_c_bst ( tree, &ts[i].element);
	update_values( v, &l,&r,&p,&e);
	test_each_elements(l,r,p,e,v, ts, i);
    }
}

static CLIB_BST_PTR 
create_tree(TS ts[], int size) {
    int i = 0;
    CLIB_BST_PTR tree = new_c_bst( free_e, compare_e, traversal_e);
    for ( i = 0; i < size; i++) {
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &(ts[i].element), sizeof ( int ));
	insert_c_bst( tree, v );
    }
    return tree;
}

void 
test_c_bst() {
    {/* Test Case 1 */
	TS ts[] = {
	    {15,6,18,0},{6,3,7,15},{18,17,20,15},{3,2,4,6},{7,0,13,6},
	    {17,0,0,18},{20,0,0,18},{2,0,0,3},{4,0,0,3},{13,9,0,7},
	    {9,0,0,13}
	};
	int size = (sizeof(ts)/sizeof(TS));

	CLIB_BST_PTR tree = create_tree(ts,size);
	test_all_elements(tree, ts, size); 
    }
    { 
	TS ts[] = {
	    {15,5,16,0},{5,3,12,15},{16,0,20,15},{3,0,0,5},{12,10,13,5},
	    {20,18,23,16},{10,6,0,12},{13,0,0,12},{18,0,0,20},{23,0,0,20},
	    {6,0,7,10},{7,0,0,6}
	};
	TS ts_delete_leaf_13[] = {
	    {15,5,16,0},{5,3,12,15},{16,0,20,15},{3,0,0,5},{12,10,0,5},
	    {20,18,23,16},{10,6,0,12},{18,0,0,20},{23,0,0,20},
	    {6,0,7,10},{7,0,0,6}
	};	
	TS ts_delete_leaf_16[] = {
	    {15,5,20,0},{5,3,12,15},{3,0,0,5},{12,10,0,5},
	    {20,18,23,15},{10,6,0,12},{18,0,0,20},{23,0,0,20},
	    {6,0,7,10},{7,0,0,6}
	};	
	TS ts_delete_leaf_5[] = {
	    {15,6,20,0},{6,3,12,15},{3,0,0,6},{12,10,0,6},
	    {10,7,0,12},{18,0,0,20},{23,0,0,20},{7,0,0,10},{20,18,23,15}
	};			
	int i = 13;	
	int size = (sizeof(ts)/sizeof(TS));
	int size_after_delete = (sizeof(ts_delete_leaf_13)/sizeof(TS));

	CLIB_BST_PTR tree = create_tree(ts,size);
	test_all_elements(tree, ts, size);

	/* Test case 2 */
	delete_c_bst( tree, &i);
	test_all_elements(tree, ts_delete_leaf_13, size_after_delete);

	/* Test case 3 */
	i = 16;	
	size_after_delete = (sizeof(ts_delete_leaf_16)/sizeof(TS));
	delete_c_bst( tree, &i);
	test_all_elements(tree, ts_delete_leaf_16, size_after_delete);

	/* Test case4 */
	i = 5;	
	size_after_delete = (sizeof(ts_delete_leaf_5)/sizeof(TS));
	delete_c_bst( tree, &i);
	test_all_elements(tree, ts_delete_leaf_5, size_after_delete);

	/* Test Case 5 */
	printf ( "INORDER -> :\n");
	walk_c_bst_r(tree,CLIB_INORDER);
	printf ( "\nPOSTORDER -> :\n");
	walk_c_bst_r(tree,CLIB_POSTORDER);
	printf ( "\nPREORDER -> :\n");
	walk_c_bst_r(tree,CLIB_PREORDER);
	printf("\n");

	destroy_c_bst(tree);


    }
}
