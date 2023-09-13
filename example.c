#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"

int main()
{
    struct List *myList = list_init();
    struct List *myList2 = list_init();
    struct List *myList3 = list_init();

    printf("----- ----- -----\n");
    // You can store strings quite easily
    char myString[] = "Example Five";

    list_add(myList, "Example Zero", 13);
    list_add(myList, "Example One", 12);
    list_add(myList, "Example Two", 12);
    list_add(myList, "Example Three", 14);
    list_add(myList, "Example Four", 13);
    list_add(myList, myString, strlen(myString));

    // Dedicated print and get function for all primary data types.
    list_printStr(myList);
    char* strPtr = list_getStr(list_index(myList, 2));
    printf("---\n%s\n", strPtr);

    printf("----- ----- -----\n");
    // Easily print out all details of a node for debugging.
    list_printDetails(list_index(myList, 5));

    printf("----- ----- -----\n");
    // Easily store integers in the lists too.
    int x;
    for(x=0; x<11; x++)
        list_add(myList2, &x, sizeof(int));
    
    list_printInt(myList2);

    // Many functions to remove nodes
    printf("--- --- ---\n");
    list_removeFirst(myList2);
    list_removeLast(myList2);
    list_remove(myList2, 1);

    list_printInt(myList2);

    printf("----- ----- -----\n");
    // Even easily store floats.
    float y;
    for(y=0; y<1; y=y+0.1)
        list_add(myList3, &y, sizeof(float));
    
    list_printFloat(myList3);

    printf("----- Error in Code -----\n");
    // Functions to close and deallocate the entire list
    list_close(myList3);
    
    // This line causes a segmentation fault because the list no longer exists
    // We had deallocated all the nodes and the list itself.
    list_printFloat(myList3);

    printf("----- ----- -----\n");


}
