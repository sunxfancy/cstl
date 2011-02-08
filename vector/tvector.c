#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

typedef struct _test_data_vector {
    char *api;
    char **input;
    char **output;
}vector_test_data;

vector_test_data data[] = {
    {
	"vector_push_back",
	(char*[]){"1","2","3","4","5","6","7","8","9","10",""},
	(char*[]){"1","2","3","4","5","6","7","8","9","10",""}
    },
    {
	"vector_push_back",
	(char*[]){"10","20","30","40","50","60","70","80","90","100",""},
	(char*[]){"10","20","30","40","50","60","70","80","90","100",""}
    },
    {
	"vector_push_back",
	(char*[]){"100","200","300","400","500","600",
	                                         "700","800","900","1000",""},
	(char*[]){"100","200","300","400","500","600",
	                                        "700","800","900","1000",""}
    }
};
void 
free_elem ( void *e ) {
    if ( (char*)e ) free ( (char*)e ) ;
}
void
perform_vector_push_back_test(int index){
    printf ( "Test case - vector_push_back " );
    vector *p = vector_new ( 5, free_elem );
    if ( !p ) { 
	printf ( "FAIL\n" ); 
	return;
    }
    int i = 0;
    while ( data[index].input[i] != "" ) {
        vector_push_back( p,strdup ( data[index].input[i++]));
    }
    i = 0;
    while ( data[index].output[i] != "" ) {
	char *v = ( char *) vector_element_at ( p , i );
	if ( 0 != strcmp ( v, data[index].output[i++] )) {
	    printf ( "FAIL\n" );
	    abort();
	}
    }
    printf ( "PASS\n");
}
int main() {
    int i = 0;
    int num_tc = sizeof (data) / (sizeof(data[0]));
    for ( i = 0; i < num_tc ; i++) {
	if ( 0 == strcmp ( data[i].api, "vector_push_back" )) {
	    perform_vector_push_back_test(i);
	}
    }
    return 0;
}
