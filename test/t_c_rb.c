#include "c_datastructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BLACK 0
#define RED   1

#define RB_SENTINEL &tree->_sentinel 

static CLIB_TYPE
get_key ( CLIB_RB_PTR tree, CLIB_RB_NODE_PTR node) {
    if ( node ) 
	return node->value._key;
    return CLIB_NULL;
}

static CLIB_RB_NODE_PTR
get_left (CLIB_RB_PTR tree, CLIB_RB_NODE_PTR node ) {
    if ( node->left != RB_SENTINEL && node->left != CLIB_RB_NODE_NULL)
	return node->left;
    return CLIB_RB_NODE_NULL;
}
static CLIB_RB_NODE_PTR
get_right (CLIB_RB_PTR tree, CLIB_RB_NODE_PTR node ){
    if ( node->right != RB_SENTINEL && node->right != CLIB_RB_NODE_NULL)
	return node->right;
    return CLIB_RB_NODE_NULL;
}
static CLIB_RB_NODE_PTR
get_parent ( CLIB_RB_PTR tree,CLIB_RB_NODE_PTR node ) {
    if ( node->parent != RB_SENTINEL && node->parent != CLIB_RB_NODE_NULL)
	return node->parent;
    return CLIB_RB_NODE_NULL;
}

int 
compare_rb_e ( void* l, void *r ) {

    int left =  0;
    int right = 0;

    if ( l ) left  = *(int*)l;
    if ( r ) right = *(int*)r;

    if ( left < right ) return -1;
    if ( left == right ) return 0;

    return 1;
}
void 
free_rb_e ( void *p ) {
    if ( p ) {
	free ( p );
    }
}

typedef struct test_data_tree {
    int element;
    int left;
    int right;
    int parent;
    int color;
} TS;


static CLIB_RB_NODE_PTR
__find_c_rb ( CLIB_RB_PTR tree, CLIB_COMPARE fn_c, CLIB_TYPE key ) {
    CLIB_RB_NODE_PTR node = tree->_root;
    int compare_result = (fn_c)(key, node->value._key);
    while ((node != RB_SENTINEL) && 
	   (compare_result = (fn_c)(key, node->value._key)) != 0 ){
	if ( compare_result < 0 ) {
	    node = node->left;
	} else {
	    node = node->right;
	}
    } /* while loop ends here */
    return node;
}
CLIB_RB_NODE_PTR
find(CLIB_RB_PTR tree, CLIB_TYPE key ) {
    return __find_c_rb ( tree, tree->compare_key_fn, key );
}

static void update_values ( CLIB_TYPE v, int *l, int *r, int *p , int *e, 
			    CLIB_RB_PTR tree ) {
    CLIB_RB_NODE_PTR x;
    if ( get_key(tree,v)) 
	*e = *(int*)get_key (tree,v);
    x = get_left(tree,v);
    if ( x )
	*l = *(int*)get_key(tree,x);
    x = get_right(tree,v);
    if (x) 
	*r = *(int*)get_key(tree,x);
    x = get_parent ( tree, v );
    if (x) 		
	*p = *(int*)get_key(tree,x);
}
static void 
test_each_elements(int l,int r, int p, int e,CLIB_TYPE v, TS ts[], int i, 
		   CLIB_RB_PTR tree) {
    assert ( ts[i].element == e);
    if (ts[i].left != 0 ) 
	assert ( ts[i].left == l);
    else
	assert ((void*)0 == (void*)get_key(tree,get_left(tree,v)));
    if ( ts[i].right != 0 ) 
	assert (ts[i].right == r);
    else
	assert ((void*)0 == (void*)get_key(tree,get_right(tree,v)));
    if (ts[i].parent != 0 ) 
	assert (ts[i].parent == p);
    else
	assert ((void*)0 == (void*)get_key(tree,get_parent(tree,v)));
}
static void
test_all_elements(CLIB_RB_PTR tree, TS ts[], int size) {
    int i = 0;
    for ( i = 0; i < size; i++) {
	CLIB_TYPE v = CLIB_NULL;
	int l,r,p,e;
	v = find ( tree, &ts[i].element);
	update_values( v, &l,&r,&p,&e, tree);
	test_each_elements(l,r,p,e,v, ts, i, tree);
    }
}

static CLIB_RB_PTR 
create_tree(TS ts[], int size) {
    int i = 0;
    CLIB_RB_PTR tree = new_c_rb( free_rb_e, CLIB_NULL, compare_rb_e, 0);
    for ( i = 0; i < size; i++) {
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &(ts[i].element), sizeof ( int ));
	insert_c_rb( tree, v ,NULL, CLIB_RB_VALUE_COPY);
    }
    return tree;
}

void 
test_c_rb() {
    int size;
    int size_after_delete;
    int i = 0;
    CLIB_RB_PTR tree;
    CLIB_RB_NODE_PTR node;

    TS ts[] = {
	{15,6,18,0,BLACK},{6,3,9,15,RED},{18,17,20,15,BLACK},
	{3,2,4,6,BLACK},{7,0,0,9,RED},{17,0,0,18,RED},
	{20,0,0,18,RED},{2,0,0,3,RED},{4,0,0,3,RED},{13,0,0,9,RED},	
	{9,7,13,6,BLACK}
    };
    TS ts_delete_leaf_13[] = {
	{15,6,18,0,BLACK},{6,3,9,15,RED},{18,17,20,15,BLACK},
	{3,2,4,6,BLACK},{7,0,0,9,RED},{17,0,0,18,RED},
	{20,0,0,18,RED},{2,0,0,3,RED},{4,0,0,3,RED},
	{9,7,0,6,BLACK}
    };	
    TS ts_delete_9[] = {
	{15,6,18,0,BLACK},{6,3,7,15,RED},{18,17,20,15,BLACK},
	{3,2,4,6,RED},{7,0,0,6,RED},{17,0,0,18,RED},
	{20,0,0,18,RED},{2,0,0,3,RED},{4,0,0,3,RED}
    };	
    TS ts_delete_15[] = {
	{6,3,7,17,RED},{18,0,20,17,BLACK},
	{3,2,4,6,RED},{7,0,0,6,RED},{17,6,18,0,RED},
	{20,0,0,18,RED},{2,0,0,3,RED},{4,0,0,3,RED}
    };			
    TS ts_insert_1[] = {
	{6,3,17,0,BLACK},{18,0,20,17,BLACK},
	{3,2,4,6,RED},{7,0,0,17,RED},{17,7,18,6,RED},
	{20,0,0,18,RED},{2,1,0,3,BLACK},{4,0,0,3,BLACK},
	{1,0,0,2,RED}
    };			


    size = (sizeof(ts)/sizeof(TS));
    tree = create_tree(ts,size);
    test_all_elements(tree, ts, size); 

    i = 13;	
    size = (sizeof(ts)/sizeof(TS));
    size_after_delete = (sizeof(ts_delete_leaf_13)/sizeof(TS));
    node = remove_c_rb( tree, &i);
    if ( node->value._key )  {
	free ( node->value._key);
	free ( node );
    }

    test_all_elements(tree, ts_delete_leaf_13, size_after_delete);

    i = 9;	
    size_after_delete = (sizeof(ts_delete_9)/sizeof(TS));
    node = remove_c_rb( tree, &i);
    if ( node->value._key )  {
	free ( node->value._key);
	free ( node );
    }
    test_all_elements(tree, ts_delete_9, size_after_delete);

    i = 15;	
    size_after_delete = (sizeof(ts_delete_15)/sizeof(TS));
    node = remove_c_rb( tree, &i);
    if ( node->value._key )  {
	free ( node->value._key);
	free ( node );
    }
    test_all_elements(tree, ts_delete_15, size_after_delete);

    {
	int i = 1;
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &i, sizeof ( int ));
	insert_c_rb( tree, v, NULL , CLIB_RB_VALUE_COPY);
	size_after_delete = (sizeof(ts_insert_1)/sizeof(TS));
	test_all_elements(tree, ts_insert_1, size_after_delete);
    } 
    delete_c_rb(tree);
}
