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

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define rb_sentinel &pTree->sentinel

static void debug_verify_properties(clib_rb_ptr);
static void debug_verify_property_1(clib_rb_ptr,clib_rb_node_ptr);
static void debug_verify_property_2(clib_rb_ptr,clib_rb_node_ptr);
static clib_int debug_node_color(clib_rb_ptr,clib_rb_node_ptr n);
static void debug_verify_property_4(clib_rb_ptr,clib_rb_node_ptr);
static void debug_verify_property_5(clib_rb_ptr,clib_rb_node_ptr);
static void debug_verify_property_5_helper(clib_rb_ptr,clib_rb_node_ptr,clib_int,clib_int*);


static void
__left_rotate(clib_rb_ptr pTree, clib_rb_node_ptr x){
    clib_rb_node_ptr y;
    y = x->right;
    x->right = y->left;
    if (y->left != rb_sentinel)
        y->left->parent = x;
    if (y != rb_sentinel)
        y->parent = x->parent;
    if (x->parent){
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else
        pTree->root = y;
    y->left = x;
    if (x != rb_sentinel)
        x->parent = y;
}
static void
__right_rotate(clib_rb_ptr pTree, clib_rb_node_ptr x) {
    clib_rb_node_ptr y = x->left;
    x->left = y->right;
    if (y->right != rb_sentinel)
        y->right->parent = x;
    if (y != rb_sentinel)
        y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else
        pTree->root = y;
    y->right = x;
    if (x != rb_sentinel)
        x->parent = y;
}

clib_rb_ptr
new_c_rb(clib_compare fn_c,clib_destroy fn_ed, clib_destroy fn_vd ){

    clib_rb_ptr pTree = (clib_rb_ptr)clib_malloc(sizeof(clib_rb));
    if ( pTree == clib_rb_null )
        return clib_rb_null;

    pTree->compare_fn           = fn_c;
    pTree->destruct_k_fn        = fn_ed;
    pTree->destruct_v_fn        = fn_vd;
    pTree->root                 = rb_sentinel;
    pTree->sentinel.left        = rb_sentinel;
    pTree->sentinel.right       = rb_sentinel;
    pTree->sentinel.parent      = clib_rb_node_null;
    pTree->sentinel.color       = clib_black;

    return pTree;
}
static void
__rb_insert_fixup( clib_rb_ptr pTree, clib_rb_node_ptr x ) {
    while (x != pTree->root && x->parent->color == clib_red) {
        if (x->parent == x->parent->parent->left) {
            clib_rb_node_ptr y = x->parent->parent->right;
            if (y->color == clib_red) {
                x->parent->color         = clib_black;
                y->color                 = clib_black;
                x->parent->parent->color = clib_red;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right){
                    x = x->parent;
                    __left_rotate (pTree, x);
                }
                x->parent->color         = clib_black;
                x->parent->parent->color = clib_red;
                __right_rotate (pTree, x->parent->parent);
            }
        } else {
            clib_rb_node_ptr y = x->parent->parent->left;
            if (y->color == clib_red) {
                x->parent->color         = clib_black;
                y->color                 = clib_black;
                x->parent->parent->color = clib_red;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    __right_rotate (pTree, x);
                }
                x->parent->color         = clib_black;
                x->parent->parent->color = clib_red;
                __left_rotate (pTree, x->parent->parent);
            }
        }
    }
    pTree->root->color = clib_black;
}
clib_rb_node_ptr   
find_c_rb (clib_rb_ptr pTree, clib_type key) {
    clib_rb_node_ptr x = pTree->root;

    while (x != rb_sentinel) {
        clib_int c = 0;
        clib_type cur_key ;
        get_raw_clib_object ( x->key, &cur_key );
        c = pTree->compare_fn (key, cur_key);
        clib_free ( cur_key );
        if (c == 0) {
            break;
        } else {
            x = c < 0 ? x->left : x->right;
        }
    }
    if ( x == rb_sentinel )
        return clib_rb_node_null;

    return x;
}

clib_error  
insert_c_rb(clib_rb_ptr pTree, clib_type k, clib_size key_size, clib_type v, clib_size value_size) {

    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_rb_node_ptr x,y,z;

    x = (clib_rb_node_ptr)clib_malloc (sizeof(clib_rb_node));
    if ( x == clib_rb_node_null ) 
        return CLIB_ERROR_MEMORY;

    x->left    = rb_sentinel;
    x->right   = rb_sentinel;
    x->color   = clib_red;

    x->key     = new_clib_object ( k, key_size );
    if ( v ) {
        x->value   = new_clib_object ( v, value_size );
    } else {
        x->value =  clib_object_null;
    }

    y = pTree->root;
    z = clib_rb_node_null;

    while (y != rb_sentinel) {
        clib_int c = 0;
        clib_type cur_key,new_key ;

        get_raw_clib_object ( y->key, &cur_key );
        get_raw_clib_object ( x->key, &new_key );

        c = (pTree->compare_fn) ( new_key , cur_key);
        clib_free ( cur_key );
        clib_free ( new_key );
        if (c == 0) {
            /* TODO : Delete node here */
            return CLIB_RBTREE_KEY_DUPLICATE;
        }
        z = y;
        if ( c < 0 )
            y = y->left;
        else
            y = y->right;
    }    
    x->parent = z;
    if (z) {
        clib_int c = 0;
        clib_type cur_key,new_key ;
        get_raw_clib_object ( z->key, &cur_key );
        get_raw_clib_object ( x->key, &new_key );

        c = pTree->compare_fn( new_key, cur_key);
        clib_free ( cur_key );
        clib_free ( new_key );
        if (c < 0) {
            z->left = x;
        } else {
            z->right = x;
        }
    }
    else
        pTree->root = x;

    __rb_insert_fixup (pTree, x);

    debug_verify_properties ( pTree);
    return rc;
}
static void
__rb_remove_fixup( clib_rb_ptr pTree, clib_rb_node_ptr x ) {
    while (x != pTree->root && x->color == clib_black) {
        if (x == x->parent->left) {
            clib_rb_node_ptr w = x->parent->right;
            if (w->color == clib_red) {
                w->color         = clib_black;
                x->parent->color = clib_red;
                __left_rotate (pTree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == clib_black && w->right->color == clib_black) {
                w->color = clib_red;
                x = x->parent;
            } else {
                if (w->right->color == clib_black)  {
                    w->left->color = clib_black;
                    w->color       = clib_red;
                    __right_rotate (pTree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = clib_black;
                w->right->color = clib_black;
                __left_rotate (pTree, x->parent);
                x = pTree->root;
            }
        } else {
            clib_rb_node_ptr w = x->parent->left;
            if (w->color == clib_red) {
                w->color = clib_black;
                x->parent->color = clib_red;
                __right_rotate (pTree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == clib_black && w->left->color == clib_black) {
                w->color = clib_red;
                x = x->parent;
            } else {
                if (w->left->color == clib_black) {
                    w->right->color = clib_black;
                    w->color = clib_red;
                    __left_rotate (pTree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = clib_black;
                w->left->color = clib_black;
                __right_rotate (pTree, x->parent);
                x = pTree->root;
            }
        }
    }
    x->color = clib_black;
}

static clib_rb_node_ptr  
__remove_c_rb(clib_rb_ptr pTree, clib_rb_node_ptr z ) {
    clib_rb_node_ptr x = clib_rb_node_null;
    clib_rb_node_ptr y = clib_rb_node_null;

    if (z->left == rb_sentinel || z->right == rb_sentinel)
        y = z;
    else {
        y = z->right;
        while (y->left != rb_sentinel)
            y = y->left;
    }
    if (y->left != rb_sentinel)
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
        pTree->root = x;
    if (y != z) {
        clib_object_ptr tmp;
        tmp    = z->key;
        z->key = y->key;
        y->key = tmp;

        tmp      = z->value;
        z->value = y->value;
        y->value = tmp;
    }
    if (y->color == clib_black)
        __rb_remove_fixup (pTree, x);

    debug_verify_properties ( pTree);
    return y;
}

clib_rb_node_ptr
remove_c_rb (clib_rb_ptr pTree, clib_type key) {
    clib_rb_node_ptr z = clib_rb_node_null;

    z = pTree->root;
    while (z != rb_sentinel) {
        clib_int c = 0;
        clib_type cur_key;
        get_raw_clib_object ( z->key, &cur_key );
        c = pTree->compare_fn (key, cur_key);
        clib_free ( cur_key );
        if ( c == 0) {
            break;
        }
        else {
            z = ( c < 0) ? z->left : z->right;
        }
    }
    if (z == rb_sentinel)
        return clib_rb_node_null;
    return __remove_c_rb(pTree, z );
}
static void
__delete_c_rb_node (clib_rb_ptr pTree, clib_rb_node_ptr x ) {

    clib_type key, value;

    if ( pTree->destruct_k_fn ) {
        get_raw_clib_object ( x->key, &key );
        pTree->destruct_k_fn ( key );
    }
    delete_clib_object( x->key );

    if ( x->value ) {
        if ( pTree->destruct_v_fn ) {
            get_raw_clib_object ( x->value, &value);
            pTree->destruct_v_fn ( value );
        }
        delete_clib_object( x->value );
    }
}

clib_error  
delete_c_rb(clib_rb_ptr pTree) {

    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_rb_node_ptr z = pTree->root;

    while (z != rb_sentinel) {
        if (z->left != rb_sentinel)
            z = z->left;
        else if (z->right != rb_sentinel)
            z = z->right;
        else {
            __delete_c_rb_node ( pTree, z );
            if (z->parent) {
                z = z->parent;
                if (z->left != rb_sentinel){
                    clib_free ( z->left );
                    z->left = rb_sentinel;
                }else if (z->right != rb_sentinel){
                    clib_free ( z->right );
                    z->right = rb_sentinel;
                }
            } else {
                clib_free ( z );
                z = rb_sentinel;
            }
        }
    }
    clib_free ( pTree );
    return rc;
}

clib_bool 
empty_c_rb(clib_rb_ptr pTree) {
    if ( pTree->root != rb_sentinel )
        return clib_true;
    return clib_false;
}
/*clib_rb_node_ptr
get_next_c_rb(clib_rb_ptr pTree, clib_rb_node_ptr *current, clib_rb_node_ptr *pre) {
    clib_rb_node_ptr prev_current;
    while((*current) != rb_sentinel) {
        if((*current)->left == rb_sentinel){
            prev_current = (*current);
            (*current) = (*current)->right;
            return prev_current->raw_data.key;			
        } else {
            (*pre) = (*current)->left;
            while((*pre)->right != rb_sentinel && (*pre)->right != (*current))
                (*pre) = (*pre)->right; 
            if((*pre)->right == rb_sentinel) {
                (*pre)->right = (*current);
                (*current) = (*current)->left;
            } else {
                (*pre)->right = rb_sentinel;
                prev_current = (*current);
                (*current) = (*current)->right;
                return prev_current->raw_data.key;				
            }
        } 
    } 
    return clib_rb_node_null;
}*/

void debug_verify_properties(clib_rb_ptr t) {
    debug_verify_property_1(t,t->root);
    debug_verify_property_2(t,t->root);
    debug_verify_property_4(t,t->root);
    debug_verify_property_5(t,t->root);
}

void debug_verify_property_1(clib_rb_ptr pTree,clib_rb_node_ptr n) {
    assert(debug_node_color(pTree,n) == clib_red || debug_node_color(pTree,n) == clib_black);
    if (n == rb_sentinel) return;
    debug_verify_property_1(pTree,n->left);
    debug_verify_property_1(pTree,n->right);
}

void debug_verify_property_2(clib_rb_ptr pTree,clib_rb_node_ptr root) {
    assert(debug_node_color(pTree,root) == clib_black);
}

clib_int debug_node_color(clib_rb_ptr pTree,clib_rb_node_ptr n) {
    return n == rb_sentinel ? clib_black : n->color;
}

void debug_verify_property_4(clib_rb_ptr pTree,clib_rb_node_ptr n) {
    if (debug_node_color(pTree,n) == clib_red) {
        assert (debug_node_color(pTree,n->left)   == clib_black);
        assert (debug_node_color(pTree,n->right)  == clib_black);
        assert (debug_node_color(pTree,n->parent) == clib_black);
    }
    if (n == rb_sentinel) return;
    debug_verify_property_4(pTree,n->left);
    debug_verify_property_4(pTree,n->right);
}

void debug_verify_property_5(clib_rb_ptr pTree,clib_rb_node_ptr root) {
    clib_int black_count_path = -1;
    debug_verify_property_5_helper(pTree,root, 0, &black_count_path);
}

void debug_verify_property_5_helper(clib_rb_ptr pTree,clib_rb_node_ptr n, clib_int black_count, clib_int* path_black_count) {
    if (debug_node_color(pTree,n) == clib_black) {
        black_count++;
    }
    if (n == rb_sentinel) {
        if (*path_black_count == -1) {
            *path_black_count = black_count;
        } else {
            assert (black_count == *path_black_count);
        }
        return;
    }
    debug_verify_property_5_helper(pTree,n->left,  black_count, path_black_count);
    debug_verify_property_5_helper(pTree,n->right, black_count, path_black_count);
}

