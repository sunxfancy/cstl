#include "c_lib.h"

clib_slist_ptr 
new_c_slist(clib_destroy fn_d, clib_compare fn_c){
    clib_slist_ptr ll  = (clib_slist_ptr)clib_malloc(sizeof(clib_slist));
    ll->head           = clib_slist_node_null;
    ll->destruct_fn    = fn_d;
    ll->compare_key_fn = fn_c;
    ll->size           = 0;
    return ll;
}
void           
delete_c_slist( clib_slist_ptr ll){
    clib_slist_node_ptr current = ll->head;
    clib_slist_node_ptr temp    = clib_slist_node_null;

    while ( current != clib_slist_node_null ) {
	temp    = current;
        current = current->next;

        (ll->destruct_fn)(temp->elem);
	clib_free ( temp );
    }
    clib_free ( ll );
}

void           
push_back_c_slist( clib_slist_ptr ll, clib_type v){
    clib_slist_node_ptr current  = clib_slist_node_null;
    clib_slist_node_ptr new_node = clib_slist_node_null;

    new_node       = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));
    new_node->elem = v;
    new_node->next = clib_slist_node_null;

    if ( ll->head == clib_slist_node_null ) {
        ll->head = new_node;
        ll->size++;
        return;
    }
    current = ll->head;
    while ( current->next != clib_slist_node_null )
        current  = current->next;    
    current->next = new_node;
    ll->size++;
}
void           
remove_c_slist( clib_slist_ptr ll, int pos) {
    int i = 0;
    clib_slist_node_ptr current = ll->head;
    clib_slist_node_ptr temp    = clib_slist_node_null;

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
insert_c_slist( clib_slist_ptr ll, clib_type v, int pos) {
    int i = 0;
    clib_slist_node_ptr current  = ll->head;
    clib_slist_node_ptr new_node = clib_slist_node_null;
   
    if ( pos == 1 ) {
        new_node       = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));
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
    new_node       = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));
    new_node->elem = v;
    new_node->next = current->next;
    current->next  = new_node;
    ll->size++;
}
void           
for_each_c_slist (clib_slist_ptr ll, void (*fn)(void*)) {
    clib_slist_node_ptr current  = ll->head;
    while ( current != clib_slist_node_null ) {
        (fn)(current->elem);
        current = current->next;
    }    
}
clib_type      
find_c_slist (clib_slist_ptr ll, clib_type v) {
    clib_slist_node_ptr current  = ll->head;
    while ( current != clib_slist_node_null && (ll->compare_key_fn)(v,current->elem) == 0) {
            current = current->next;
    }
    if ( current )
        return current->elem;
    return clib_null;
}
