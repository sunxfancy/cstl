#include "c_datastructure.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define RB_SENTINEL &pTree->sentinel

static void
__left_rotate(CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR x){
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
        pTree->root = y;
    y->left = x;
    if (x != RB_SENTINEL)
        x->parent = y;
}
static void
__right_rotate(CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR x) {
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
        pTree->root = y;
    y->right = x;
    if (x != RB_SENTINEL)
        x->parent = y;
}

CLIB_RB_PTR
new_c_rb(CLIB_DESTROY fn_ed, CLIB_DESTROY fn_vd, CLIB_COMPARE fn_c, CLIB_SIZE key_size, CLIB_SIZE value_size ){

    CLIB_RB_PTR pTree = (CLIB_RB_PTR)clib_malloc(sizeof(CLIB_RB));
    if ( pTree == CLIB_RB_NULL )
        return CLIB_RB_NULL;

    pTree->compare_fn = fn_c;
    pTree->destruct_k_fn  = fn_ed;
    pTree->destruct_v_fn  = fn_vd;
    pTree->size_of_key = key_size;
    pTree->size_of_value = value_size;

    pTree->root  = RB_SENTINEL;
    pTree->sentinel.left = RB_SENTINEL;
    pTree->sentinel.right= RB_SENTINEL;

    pTree->sentinel.parent = CLIB_RB_NODE_NULL;

    pTree->sentinel.color = CLIB_BLACK;

    pTree->sentinel.data.key = CLIB_NULL;
    pTree->sentinel.data.value  = CLIB_NULL;

    return pTree;
}
static void
__rb_insert_fixup( CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR x ) {
    while (x != pTree->root && x->parent->color == CLIB_RED) {
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
                    __left_rotate (pTree, x);
                }
                x->parent->color         = CLIB_BLACK;
                x->parent->parent->color = CLIB_RED;
                __right_rotate (pTree, x->parent->parent);
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
                    __right_rotate (pTree, x);
                }
                x->parent->color         = CLIB_BLACK;
                x->parent->parent->color = CLIB_RED;
                __left_rotate (pTree, x->parent->parent);
            }
        }
    }
    pTree->root->color = CLIB_BLACK;
}
static CLIB_TYPE
__find_c_rb ( CLIB_RB_PTR pTree, CLIB_TYPE k ) {
    CLIB_RB_NODE_PTR x = pTree->root;
    int compare_result;

    while (x != RB_SENTINEL) {
        CLIB_TYPE current_key = CLIB_NULL;
        current_key = (CLIB_TYPE)clib_malloc ( pTree->size_of_key);
        clib_memcpy ( current_key, k, pTree->size_of_key);

        compare_result = pTree->compare_fn (current_key, x->data.key);
        if (compare_result == 0) {
            if ( pTree->type == CLIB_MAP_TYPE ) {
                clib_free ( current_key );
                return x->data.value;
            }
            clib_free ( current_key );
            return x->data.key;
        } else {
            x = compare_result < 0 ? x->left : x->right;
        }
        clib_free ( current_key );
    }
    return CLIB_NULL;
}

CLIB_ERROR  
insert_c_rb(CLIB_RB_PTR pTree, CLIB_TYPE k , CLIB_TYPE v) {

    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    CLIB_RB_NODE_PTR x,y,z;

    x = (CLIB_RB_NODE_PTR)clib_malloc (sizeof(CLIB_RB_NODE));
    if ( x == CLIB_RB_NODE_NULL ) 
        return CLIB_ERROR_MEMORY;

    x->left    = RB_SENTINEL;
    x->right   = RB_SENTINEL;
    x->color   = CLIB_RED;

    x->data.key     = (CLIB_TYPE)clib_malloc ( pTree->size_of_key);
    clib_memcpy ( x->data.key, k, pTree->size_of_key);
    if ( v ) {
        x->data.value = (CLIB_TYPE)clib_malloc ( pTree->size_of_value);
        clib_memcpy ( x->data.value, k, pTree->size_of_value);
    } else {
        x->data.value =  CLIB_NULL;
    }

    y = pTree->root;
    z = CLIB_RB_NODE_NULL;
    while (y != RB_SENTINEL)
    {
        int c = 0;
        CLIB_TYPE current_key = CLIB_NULL;
        current_key = (CLIB_TYPE)clib_malloc ( pTree->size_of_key);
        clib_memcpy ( current_key, y->data.key, pTree->size_of_key);

        c = (pTree->compare_fn) ( x->data.key, current_key);
        if (c == 0) {
            clib_free ( current_key );
            clib_free ( x->data.key);
            if (  x->data.value )
                clib_free ( x->data.value);
            clib_free ( x );
            return CLIB_RBTREE_KEY_DUPLICATE;
        }
        z = y;
        if ( c < 0 )
            y = y->left;
        else
            y = y->right;

        clib_free ( current_key );
    }    
    x->parent = z;
    /* To handle the case when set theory operation are called
     * Since we are dealing with the void* everywhere 
     * we cannot make the copy of those elements
     * instead of reference is incresed during this time
     */
    /*if ( reference ) {
      x->reference++;
      } else
      x->reference = 0;
     */
    if (z) {
        CLIB_TYPE current_key = CLIB_NULL;
        current_key = (CLIB_TYPE)clib_malloc ( pTree->size_of_key);
        clib_memcpy ( current_key, z->data.key, pTree->size_of_key);

        if (pTree->compare_fn(x->data.key, current_key) < 0)
            z->left = x;
        else
            z->right = x;

        clib_free ( current_key );
    }
    else
        pTree->root = x;

    __rb_insert_fixup (pTree, x);

    return rc;
}
static void
__rb_remove_fixup( CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR x ) {
    while (x != pTree->root && x->color == CLIB_BLACK) {
        if (x == x->parent->left) {
            CLIB_RB_NODE_PTR w = x->parent->right;
            if (w->color == CLIB_RED) {
                w->color         = CLIB_BLACK;
                x->parent->color = CLIB_RED;
                __left_rotate (pTree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == CLIB_BLACK && w->right->color == CLIB_BLACK) {
                w->color = CLIB_RED;
                x = x->parent;
            } else {
                if (w->right->color == CLIB_BLACK)  {
                    w->left->color = CLIB_BLACK;
                    w->color       = CLIB_RED;
                    __right_rotate (pTree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = CLIB_BLACK;
                w->right->color = CLIB_BLACK;
                __left_rotate (pTree, x->parent);
                x = pTree->root;
            }
        } else {
            CLIB_RB_NODE_PTR w = x->parent->left;
            if (w->color == CLIB_RED) {
                w->color = CLIB_BLACK;
                x->parent->color = CLIB_RED;
                __right_rotate (pTree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == CLIB_BLACK && w->left->color == CLIB_BLACK) {
                w->color = CLIB_RED;
                x = x->parent;
            } else {
                if (w->left->color == CLIB_BLACK) {
                    w->right->color = CLIB_BLACK;
                    w->color = CLIB_RED;
                    __left_rotate (pTree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = CLIB_BLACK;
                w->left->color = CLIB_BLACK;
                __right_rotate (pTree, x->parent);
                x = pTree->root;
            }
        }
    }
    x->color = CLIB_BLACK;
}
static CLIB_RB_NODE_PTR  
__remove_c_rb(CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR z ) {
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
        pTree->root = x;
    if (y != z) {
        tmp           = z->data.key;
        z->data.key   = y->data.key;
        y->data.key   = tmp;

        tmp             = z->data.value;
        z->data.value = y->data.value;
        y->data.value = tmp;
    }
    if (y->color == CLIB_BLACK)
        __rb_remove_fixup (pTree, x);

    /*    if ( y->reference ) {
          y->reference--;
          return CLIB_RB_NODE_NULL;
          }*/
    return y;
}
CLIB_RB_NODE_PTR
remove_c_rb ( CLIB_RB_PTR pTree, CLIB_TYPE key ) {
    CLIB_RB_NODE_PTR z;
    z = pTree->root;
    while (z != RB_SENTINEL) {
        CLIB_TYPE current_key = CLIB_NULL;
        current_key = (CLIB_TYPE)clib_malloc ( pTree->size_of_key);
        clib_memcpy ( current_key, key, pTree->size_of_key);

        if (pTree->compare_fn (current_key, z->data.key) == 0) {
            clib_free ( current_key);
            break;
        }
        else {
            z = (pTree->compare_fn (current_key, z->data.key) < 0) ?
                z->left : z->right;
        }
        clib_free ( current_key);
    }
    if (z == RB_SENTINEL)
        return CLIB_RB_NODE_NULL;
    return ( __remove_c_rb(pTree, z ));

}

void  
delete_c_rb(CLIB_RB_PTR pTree) {
    CLIB_RB_NODE_PTR z = pTree->root;
    while (z != RB_SENTINEL) {
        if (z->left != RB_SENTINEL)
            z = z->left;
        else if (z->right != RB_SENTINEL)
            z = z->right;
        else {
            /*if ( z->reference == 0 ) {
              if (pTree->destroy_key_fn)
              pTree->destroy_key_fn (z->data.key);
              if ( pTree->_type == CLIB_MAP_TYPE ) 
              (pTree->destroy_val_fn)( z->data.value);
              } else {
              z->reference--;
              }*/
            if (z->parent) {
                z = z->parent;
                if (z->left != RB_SENTINEL){
                    clib_free ( z->left->data.key );
                    if ( z->left->data.value ) {
                        clib_free ( z->left->data.value);
                    }
                    clib_free (z->left);
                    z->left = RB_SENTINEL;
                }else if (z->right != RB_SENTINEL){
                    clib_free ( z->right->data.key );
                    if ( z->right->data.value ) {
                        clib_free ( z->right->data.value);
                    }
                    clib_free (z->right);
                    z->right = RB_SENTINEL;
                }
            } else {
                clib_free ( z->data.key );
                if ( z->data.value ) {
                    clib_free ( z->data.value);
                }
                clib_free (z);
                z =	RB_SENTINEL;
            }
        }
    }
    clib_free ( pTree );
}

CLIB_TYPE
find_c_rb(CLIB_RB_PTR pTree, CLIB_TYPE key ) {
    return __find_c_rb ( pTree, key );
}

CLIB_BOOL 
    empty_c_rb(CLIB_RB_PTR pTree) {
        if ( pTree->root != RB_SENTINEL )
            return CLIB_TRUE;
        return CLIB_FALSE;
    }
CLIB_RB_NODE_PTR
get_next_c_rb(CLIB_RB_PTR pTree, CLIB_RB_NODE_PTR *current, CLIB_RB_NODE_PTR *pre) {
    CLIB_RB_NODE_PTR prev_current;
    while((*current) != RB_SENTINEL) {
        if((*current)->left == RB_SENTINEL){
            prev_current = (*current);
            (*current) = (*current)->right;
            return prev_current->data.key;			
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
                return prev_current->data.key;				
            }
        } 
    } 
    return CLIB_RB_NODE_NULL;
}

