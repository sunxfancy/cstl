#include "c_bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int compare_e ( void* l, void *r ) {
	int left = *(int*)l;
	int right = *(int*)r;
	if ( left < right ) return -1;
	if ( left == right ) return 0;
	return 1;
}
void free_e ( void *p ) {
	if ( p ) {
		free ( p );
	}
}
void traversal_e ( void *p ) {
	if ( p ) 
		printf ( "%d ", *(int*)p);
}
typedef struct test_data_tree {
	int element;
	int left;
	int right;
	int parent;
} TS;

static void update_values ( BST_NODE_PTR v, int *l, int *r, int *p , int *e ) {
	
	if ( get_key_c_bst(v) ) 
		*e = *(int*)get_key_c_bst (v);
	if ( get_left_c_bst(v) ) 
		*l = *(int*)get_key_c_bst(get_left_c_bst(v));
	if ( get_right_c_bst(v) ) 
		*r = *(int*)get_key_c_bst(get_right_c_bst(v));
	if ( get_parent_c_bst(v) ) 		
		*p = *(int*)get_key_c_bst(get_parent_c_bst(v));
}
static void 
test_each_elements(int l,int r, int p, int e,BST_NODE_PTR v, TS ts[], int i) {
	assert ( ts[i].element == e);
	if (ts[i].left != 0 ) 
		assert ( ts[i].left == l);
	else
		assert ((void*)0 == (void*)get_key_c_bst(get_left_c_bst(v)));
	if ( ts[i].right != 0 ) 
		assert (ts[i].right == r);
	else
		assert ((void*)0 == (void*)get_key_c_bst(get_right_c_bst(v)));
	if (ts[i].parent != 0 ) 
		assert (ts[i].parent == p);
	else
		assert ((void*)0 == (void*)get_key_c_bst(get_parent_c_bst(v)));
}
static void
test_all_elements(BST_PTR tree, TS ts[], int size) {
	int i = 0;
	for ( i = 0; i < size; i++) {
		BST_NODE_PTR v = BST_NODE_NULL;
		int l,r,p,e;
		v = find_c_bst ( tree, &ts[i].element);
		update_values( v, &l,&r,&p,&e);
		test_each_elements(l,r,p,e,v, ts, i);
	}
}

static BST_PTR 
create_tree(TS ts[], int size) {
	int i = 0;
	BST_PTR tree = new_c_bst( free_e, compare_e, traversal_e);
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
			{17,0,0,18},{20,0,0,18},{2,0,0,3},{4,0,0,3},{13,9,0,7},	{9,0,0,13}
		};
		int size = (sizeof(ts)/sizeof(TS));

		BST_PTR tree = create_tree(ts,size);
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

		BST_PTR tree = create_tree(ts,size);
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
		walk_c_bst_r(tree,BST_INORDER);
		printf ( "\nPOSTORDER -> :\n");
		walk_c_bst_r(tree,BST_POSTORDER);
		printf ( "\nPREORDER -> :\n");
		walk_c_bst_r(tree,BST_PREORDER);
		printf("\n");
		
		assert ( 23 == *(int*)get_key_c_bst(maximum_c_bst( tree->_root )));
		assert ( 3 == *(int*)get_key_c_bst(minimum_c_bst( tree->_root )));

		destroy_c_bst(tree);


	}
}
