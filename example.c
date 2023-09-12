#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

int main()
{
    struct Node *myList = list_init();
    struct Node *listTwo = list_init();
    // --- --- --- --- ---
    list_add(myList, "Example Zero\0", 14);
    list_add(myList, "Example One\0", 13);
    list_add(myList, "Example Two\0", 13);
    list_add(myList, "Example Three\0", 15);
    list_add(myList, "Example Four\0", 14);

    printf("----- List Printout -----\n");
    list_print(myList);
    list_remove(myList, 2);

    printf("----- Node, Index 1 -----\n");
    list_printNode(list_index(myList, 1));

    printf("----- List Printout -----\n");
    list_print(myList);

    printf("----- -----\n");
    printf("myList Count: %d\n", list_length(myList));

    printf("----- -----\n");
    printf("listTwo Count: %d\n", list_length(listTwo));
}