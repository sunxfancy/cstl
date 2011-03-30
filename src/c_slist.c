#include "c_datastructure.h"
CLIB_SLIST_PTR 
new_c_slist(CLIB_DESTROY fn_d, CLIB_COMPARE fn_c){
    CLIB_SLIST_PTR ll  = (CLIB_SLIST_PTR)clib_malloc(sizeof(CLIB_SLIST));
    ll->head           = CLIB_SLIST_NODE_NULL;
    ll->destruct_fn    = fn_d;
    ll->compare_key_fn = fn_c;
    ll->size           = 0;
    return ll;
}
void           
delete_c_slist( CLIB_SLIST_PTR ll){
    CLIB_SLIST_NODE_PTR current = ll->head;
    CLIB_SLIST_NODE_PTR temp    = CLIB_SLIST_NODE_NULL;

    while ( current != CLIB_SLIST_NODE_NULL ) {
	temp    = current;
        current = current->next;

        (ll->destruct_fn)(temp->elem);
	clib_free ( temp );
    }
    clib_free ( ll );
}

void           
push_back_c_slist( CLIB_SLIST_PTR ll, CLIB_TYPE v){
    CLIB_SLIST_NODE_PTR current  = CLIB_SLIST_NODE_NULL;
    CLIB_SLIST_NODE_PTR new_node = CLIB_SLIST_NODE_NULL;

    new_node       = (CLIB_SLIST_NODE_PTR)clib_malloc(sizeof(CLIB_SLIST_NODE));
    new_node->elem = v;
    new_node->next = CLIB_SLIST_NODE_NULL;

    if ( ll->head == CLIB_SLIST_NODE_NULL ) {
        ll->head = new_node;
        ll->size++;
        return;
    }
    current = ll->head;
    while ( current->next != CLIB_SLIST_NODE_NULL )
        current  = current->next;    
    current->next = new_node;
    ll->size++;
}
void           
remove_c_slist( CLIB_SLIST_PTR ll, int pos) {
    int i = 0;
    CLIB_SLIST_NODE_PTR current = ll->head;
    CLIB_SLIST_NODE_PTR temp    = CLIB_SLIST_NODE_NULL;

    if ( pos > ll->size ) return;

    if ( pos == 1 ) {
        ll->head = current->next;
        (ll->destruct_fn)(current->elem);
        clib_free ( current);
        ll->size--;
        return;
    }

    for ( i = 1; i < pos - 1; i++)
        current = current->next;

    temp          = current->next;
    current->next = current->next->next;
    (ll->destruct_fn)(temp->elem);
    clib_free (temp);
    ll->size--;
}
void           
insert_c_slist( CLIB_SLIST_PTR ll, CLIB_TYPE v, int pos) {
    int i = 0;
    CLIB_SLIST_NODE_PTR current  = ll->head;
    CLIB_SLIST_NODE_PTR new_node = CLIB_SLIST_NODE_NULL;
   
    if ( pos == 1 ) {
        new_node       = (CLIB_SLIST_NODE_PTR)clib_malloc(sizeof(CLIB_SLIST_NODE));
        new_node->elem = v;
        new_node->next = ll->head;
        ll->head       = new_node;
        ll->size++;
        return;
    }

    if ( pos >= ll->size + 1 ) {
        push_back_c_slist ( ll, v );
        return;
    }

    for ( i = 1; i < pos - 1; i++) {
        current = current->next;
    }
    new_node       = (CLIB_SLIST_NODE_PTR)clib_malloc(sizeof(CLIB_SLIST_NODE));
    new_node->elem = v;
    new_node->next = current->next;
    current->next  = new_node;
    ll->size++;
}
void           
for_each_c_slist (CLIB_SLIST_PTR ll, void (*fn)(void*)) {
    CLIB_SLIST_NODE_PTR current  = ll->head;
    while ( current != CLIB_SLIST_NODE_NULL ) {
        (fn)(current->elem);
        current = current->next;
    }    
}
CLIB_TYPE      
find_c_slist (CLIB_SLIST_PTR ll, CLIB_TYPE v) {
    CLIB_SLIST_NODE_PTR current  = ll->head;
    while ( current != CLIB_SLIST_NODE_NULL && (ll->compare_key_fn)(v,current->elem) == 0) {
            current = current->next;
    }
    if ( current )
        return current->elem;
    return CLIB_NULL;
}
