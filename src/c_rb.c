#include "c_lib.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


#define rb_sentinel &pTree->sentinel

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

    pTree->compare_fn = fn_c;
    pTree->destruct_k_fn  = fn_ed;
    pTree->destruct_v_fn  = fn_vd;

    pTree->root  = rb_sentinel;
    pTree->sentinel.left = rb_sentinel;
    pTree->sentinel.right= rb_sentinel;

    pTree->sentinel.parent = clib_rb_node_null;

    pTree->sentinel.color = clib_black;

    pTree->sentinel.data.key = clib_null;
    pTree->sentinel.data.value  = clib_null;

    return pTree;
}
static void
__rb_insert_fixup( clib_rb_ptr pTree, clib_rb_node_ptr x ) {
    while (x != pTree->root && x->parent->color == clib_red) {
        /* Remember newly insertly clib_rb_node_ptr always has color clib_red
         * If we are here means, color of PARENT of the newly inserted
         * clib_rb_node_ptr is also clib_red and we have clib_red->clib_red voialtion
         */
        if (x->parent == x->parent->parent->left) {
            /* Identify the orientation of the newly inserted
             * clib_rb_node_ptr, whether the clib_rb_node_ptr is inserted into left or right
             */
            clib_rb_node_ptr y = x->parent->parent->right; /*Get the uncle */
            if (y->color == clib_red) {
                /* Case : Uncle is clib_red */
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
            /* right orientation */
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
        int compare_result;
        compare_result = pTree->compare_fn (key, x->data.key);
        if (compare_result == 0) {
            break;
        } else {
            x = compare_result < 0 ? x->left : x->right;
        }
    }
    if ( x == rb_sentinel )
        return clib_rb_node_null;

    return x;
}

clib_error  
insert_c_rb(clib_rb_ptr pTree, clib_type k , clib_type v, clib_size key_size, clib_size value_size) {

    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_rb_node_ptr x,y,z;

    x = (clib_rb_node_ptr)clib_malloc (sizeof(clib_rb_node));
    if ( x == clib_rb_node_null ) 
        return CLIB_ERROR_MEMORY;

    x->left    = rb_sentinel;
    x->right   = rb_sentinel;
    x->color   = clib_red;

    /* Allocate and copy Key */
    x->data.key     = (clib_type)clib_malloc (key_size);
    /* copy bytes equal to size of key from passed k parameter
     * to RB tree key */
    clib_memcpy ((char*)x->data.key, k, key_size);
    if ( v ) {
        /* Allocate and copy value */
        x->data.value = (clib_type)clib_malloc (value_size);
        /* copy bytes equal to size of value from passed v parameter
         * to RB tree value */
        clib_memcpy ((char*)x->data.value, v, value_size);
    } else {
        /* assign null otherwise */
        x->data.value =  clib_null;
    }

    x->key_size   = key_size;
    x->value_size = value_size;

    y = pTree->root;
    z = clib_rb_node_null;

    while (y != rb_sentinel) {
        int c = 0;
        c = (pTree->compare_fn) ( x->data.key, y->data.key);
        if (c == 0) {
            clib_free ( x->data.key);
            if ( x->data.value) {
                clib_free ( x->data.value);
            }
            clib_free ( x );
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
        if (pTree->compare_fn( x->data.key, z->data.key) < 0) {
            z->left = x;
        } else {
            z->right = x;
        }
    }
    else
        pTree->root = x;

    __rb_insert_fixup (pTree, x);
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
    clib_type  tmp = clib_null;

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
        tmp  = z->data.key;
        z->data.key   = y->data.key;
        y->data.key   = tmp;

        tmp  = z->data.value;
        z->data.value = y->data.value;
        y->data.value = tmp;
    }
    if (y->color == clib_black)
        __rb_remove_fixup (pTree, x);

    return y;
}

clib_rb_node_ptr
remove_c_rb (clib_rb_ptr pTree, clib_type key) {
    clib_rb_node_ptr z = clib_rb_node_null;

    z = pTree->root;
    while (z != rb_sentinel) {
        if (pTree->compare_fn (key, z->data.key) == 0) {
            break;
        }
        else {
            z = (pTree->compare_fn (key, z->data.key) < 0) ? z->left : z->right;
        }
    }
    if (z == rb_sentinel)
        return clib_rb_node_null;

    return __remove_c_rb(pTree, z );
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
            if (z->parent) {
                z = z->parent;
                if (z->left != rb_sentinel){
                    clib_free ( z->left->data.key );
                    if ( z->left->data.value ) {
                        clib_free ( z->left->data.value);
                    }
                    clib_free (z->left);
                    z->left = rb_sentinel;
                }else if (z->right != rb_sentinel){
                    clib_free ( z->right->data.key );
                    if ( z->right->data.value ) {
                        clib_free ( z->right->data.value);
                    }
                    clib_free (z->right);
                    z->right = rb_sentinel;
                }
            } else {
                clib_free ( z->data.key );
                if ( z->data.value ) {
                    clib_free ( z->data.value);
                }
                clib_free (z);
                z =	rb_sentinel;
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
clib_rb_node_ptr
get_next_c_rb(clib_rb_ptr pTree, clib_rb_node_ptr *current, clib_rb_node_ptr *pre) {
    clib_rb_node_ptr prev_current;
    while((*current) != rb_sentinel) {
        if((*current)->left == rb_sentinel){
            prev_current = (*current);
            (*current) = (*current)->right;
            return prev_current->data.key;			
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
                return prev_current->data.key;				
            }
        } 
    } 
    return clib_rb_node_null;
}

