#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void 
delete_e ( void *ptr ) 
{  
    if ( ptr ) free ( ptr );
}
static void 
delete_v ( void *ptr ) 
{  
    if ( ptr ) free ( ptr ); 
}
static int 
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
static void
insert_edges_into_graph ( CLIB_GRAPH_PTR g ){
}
void
test_c_graph() {
    CLIB_GRAPH_PTR graph = new_c_graph( delete_e, delete_v, compare_e, CLIB_GRAPH_UNDIRECTED);
    insert_edges_into_graph ( graph );
}