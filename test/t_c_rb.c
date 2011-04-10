/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "c_lib.h"

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BLACK 0
#define RED   1

#define rb_sentinel &tree->sentinel 

static clib_type
    get_key ( clib_rb_ptr tree, clib_rb_node_ptr node) {
        if ( node ) 
            return node->raw_data.key;
        return clib_null;
    }

static clib_rb_node_ptr
    get_left (clib_rb_ptr tree, clib_rb_node_ptr node ) {
        if ( node->left != rb_sentinel && node->left != clib_rb_node_null)
            return node->left;
        return clib_rb_node_null;
    }
static clib_rb_node_ptr
    get_right (clib_rb_ptr tree, clib_rb_node_ptr node ){
        if ( node->right != rb_sentinel && node->right != clib_rb_node_null)
            return node->right;
        return clib_rb_node_null;
    }
static clib_rb_node_ptr
    get_parent ( clib_rb_ptr tree,clib_rb_node_ptr node ) {
        if ( node->parent != rb_sentinel && node->parent != clib_rb_node_null)
            return node->parent;
        return clib_rb_node_null;
    }

clib_int 
compare_rb_e ( clib_type  l, clib_type r ) {

    clib_int left =  0;
    clib_int right = 0;

    if ( l ) left  = *(int*)l;
    if ( r ) right = *(int*)r;

    if ( left < right ) return -1;
    if ( left == right ) return 0;

    return 1;
}

void 
free_rb_e ( clib_type p ) {
    if ( p ) {
        free ( p );
    }
}

typedef struct test_data_tree {
    clib_int element;
    clib_int left;
    clib_int right;
    clib_int parent;
    clib_int color;
} TS;


static clib_rb_node_ptr
__find_c_rb ( clib_rb_ptr tree, clib_compare fn_c, clib_type key ) {
    clib_rb_node_ptr node = tree->root;
    clib_type current_key = clib_null;
    clib_int compare_result = 0;

    current_key = (clib_type)clib_malloc ( tree->size_of_key);
    clib_memcpy ( current_key, key, tree->size_of_key);

    compare_result = (fn_c)(current_key, node->raw_data.key);
    while ((node != rb_sentinel) && (compare_result = (fn_c)(current_key, node->raw_data.key)) != 0 ){
        if ( compare_result < 0 ) {
            node = node->left;
        } else {
            node = node->right;
        }
    } 
    clib_free ( current_key );
    return node;
}
clib_rb_node_ptr
find(clib_rb_ptr tree, clib_type key ) {
    return __find_c_rb ( tree, tree->compare_fn, key );
}

static void update_values ( clib_type v, clib_int *l, clib_int *r, clib_int *p , clib_int *e, clib_rb_ptr tree ) {
    clib_rb_node_ptr x;
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
test_each_elements(clib_int l,clib_int r, clib_int p, clib_int e,clib_type v, TS ts[], clib_int i, 
        clib_rb_ptr tree) {
    assert ( ts[i].element == e);
    if (ts[i].left != 0 ) 
        assert ( ts[i].left == l);
    else
        assert ((clib_type )0 == (clib_type )get_key(tree,get_left(tree,v)));
    if ( ts[i].right != 0 ) 
        assert (ts[i].right == r);
    else
        assert ((clib_type )0 == (clib_type )get_key(tree,get_right(tree,v)));
    if (ts[i].parent != 0 ) 
        assert (ts[i].parent == p);
    else
        assert ((clib_type )0 == (clib_type )get_key(tree,get_parent(tree,v)));
}

static void
test_all_elements(clib_rb_ptr tree, TS ts[], clib_int size) {
    clib_int i = 0;
    for ( i = 0; i < size; i++) {
        clib_type v = clib_null;
        clib_int l,r,p,e;
        v = find ( tree, &ts[i].element);
        update_values( v, &l,&r,&p,&e, tree);
        test_each_elements(l,r,p,e,v, ts, i, tree);
    }
}

static clib_rb_ptr 
create_tree(TS ts[], clib_int size) {
    clib_int i = 0;
    clib_rb_ptr tree = new_c_rb( compare_rb_e,free_rb_e, clib_null, sizeof(clib_int),0);
    for ( i = 0; i < size; i++) {
        insert_c_rb( tree, &(ts[i].element) ,clib_null);
    }
    return tree;
}


void 
test_c_rb() {
    clib_int size;
    clib_int size_after_delete;
    clib_int i = 0;
    clib_rb_ptr tree;
    clib_rb_node_ptr node;

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
    {   
        i = 13;	
        size = (sizeof(ts)/sizeof(TS));
        size_after_delete = (sizeof(ts_delete_leaf_13)/sizeof(TS));
        node = remove_c_rb( tree, &i);
        if ( node != clib_rb_node_null ) {
            clib_free ( node->raw_data.key);
            clib_free ( node);
        }
        test_all_elements(tree, ts_delete_leaf_13, size_after_delete);
    }
    {
        i = 9;	
        size_after_delete = (sizeof(ts_delete_9)/sizeof(TS));
        node = remove_c_rb( tree, &i);
        if ( node != clib_rb_node_null ) {
            clib_free ( node->raw_data.key);
            clib_free ( node);
        }
        test_all_elements(tree, ts_delete_9, size_after_delete);
    }
    {
        i = 15;	
        size_after_delete = (sizeof(ts_delete_15)/sizeof(TS));
        node = remove_c_rb( tree, &i);
        if ( node != clib_rb_node_null ) {
            clib_free ( node->raw_data.key);
            clib_free ( node);
        }
        test_all_elements(tree, ts_delete_15, size_after_delete);
    }
    {
        clib_int i = 1;
        insert_c_rb( tree, &i, clib_null);
        size_after_delete = (sizeof(ts_insert_1)/sizeof(TS));
        test_all_elements(tree, ts_insert_1, size_after_delete);
    }
    {
      delete_c_rb(tree);
    }
}*/
