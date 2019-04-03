#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} LIST;


LIST *append( LIST *, int );
LIST *sort( LIST * );
void print_list( LIST * );

int main(void)
{
    LIST *try;
    int i;

    // This is just testing code
    try = NULL;
    try = append( try, 5 );
    try = append( try, 2 );
    try = append( try, 9 );
    try = append( try, 8 );
    try = append( try, 1 );
    try = append( try, 7 );

    printf("Original list:\n");
    print_list( try );
    try = sort( try );
    printf("Sorted list:\n");
    print_list( try );
    return 0;
}

void print_list( LIST *t )
{
    while( t != NULL ) {
        printf( "%d\n", t->data );
        t = t->next;
    }
}

LIST *append( LIST *start, int newdata )
{
    LIST *new, *end, *ret;

    if( (new = (LIST *)malloc(sizeof(LIST))) == NULL) {
        fprintf( stderr, "Memory Allocation error.\n" );
        // In Windows, replace following with a return statement.
        exit(1);
    }
    if( start == NULL )
        ret = new;
    else {
        ret = start;
        end = start;
        while( end->next != NULL ) end = end->next;
        end->next = new;
    }
    new->data = newdata;
    new->next = NULL;
    return ret ;
}

LIST *sort( LIST *start )
{
	if( start == NULL || !start->next ) return start;
	LIST *merge = NULL, *right = start, *left = start;
	for(;right->next != NULL && right->next->next != NULL; \
            left=left->next,right=right->next->next);    
	right = left->next;
    left->next = NULL;
    left = start;
    left = sort(left);
    right = sort(right);
    while(left != NULL || right != NULL){
        if(right == NULL || left != NULL && left->data >= right->data ){
            if (merge == NULL){ 
                start = merge = left ;
            }else{
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        }else {
            if(merge == NULL){ 
                start = merge = right;
            }else{
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
	return start;
}
