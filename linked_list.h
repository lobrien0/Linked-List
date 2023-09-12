/*
#   Author Info:
#       Name: Luke O'Brien
#       Last Updated: 11 Sep 2023
#
#   Program Description:
#       This header-file offers a easy way to create and manage
#       singly linked lists. Stores raw data, no types (can be cast)
#       (I plan on adding doubly linked lists soon)
#
#       Everything here is a passion project to hopefully make
#       things just a little easier.
#       Suggestions are always welcome
#       lobrien@uccs.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*  General Node for storing data
        '*data' is used to store a pointer to allocated space for data
        'dataSize' stores the size of '*data'
        '*next' stores the location of the next 'Node'
*/
struct Node {
    size_t dataSize;
    void *data;
    struct Node *next;
};

/*  New Node
        On call, allocated space and creates a new 'Node' structure.
        Then returning the pointer of the new 'Node'

        Each new node is filled with the passed '*data' and 'dataSize'
*/
struct Node* list_newNode(void *data, size_t dataSize)
{
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->dataSize = dataSize;
    temp->next = NULL;
    temp->data = (void*) malloc(dataSize);
    
    int x;
    memcpy(temp->data, data, dataSize);

    return temp;
}

/*  Last
        On call, the function will attempt to search the provided list
        for the very last allocated Node
*/
struct Node* list_last( struct Node *head )
{
    struct Node *current = head;
    while(current->next != NULL)
        current = current->next;
    
    return current;
}

/*  Length
        On call, function will attempt to count the number of nodes
        in the list, returning the total count.
*/
size_t list_length( struct Node *head )
{
    size_t count = 0;
    struct Node *current = head;
    while(current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

/*  Init
        Will create the "head" of an empty list, returning the pointer.
*/
struct Node* list_init()
{
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = NULL;
    temp->dataSize = 0;
    temp->next = NULL;
    return temp;
}

/*  Add
        Creates a new Node and adds the address to the list
*/
void list_add( struct Node *head, void *data, size_t dataSize )
{
    // If the list is empty, the first node is already created.
    // So we just fill it with data.
    if(head->data == NULL){
        head->dataSize = dataSize;
        head->data = (void*) malloc(dataSize);
        int x;
        memcpy(head->data, data, dataSize);
    }
    // If list isn't empty, creates a new node and links the pointer
    else
    {
        struct Node *current = head;
        struct Node *newNode = list_newNode(data, dataSize);
        while(current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

/*  Index
        On call, the function will attempt to reach the index provided.

        If the index is reached, the Node pointer will be returned.
        Otherwise NULL will be returned.
*/
struct Node* list_index( struct Node *head, size_t index)
{
    size_t count = 0;
    struct Node* current = head;
    
    while(current != NULL && count != index) {
        current = current->next;
        count++;
    }

    if(current != NULL)
        return current;
    return NULL;
}

/*  Remove First
        Deletes the first Node in the list.

        ***IMPORTANT
        Because the list is passed to the functions, changing
        the head would require a double pointer, or another struct.
        To simplify the matter, instead of deleting the data from the first
        Node, the data from the second node is copied over to the first, then
        the second node is deleted.

        Returns 0 if unsuccessful and 1 if successful
*/
int list_removeFirst( struct Node *head )
{
    if( head == NULL )
        return 0;
    
    if( head->next == NULL )
    {
        head->data = NULL;
        head->dataSize = 0;
        head->next = NULL;
        return 1;
    }
    
    struct Node *current = head->next;
    free(head->data);
    head->data = (void*) malloc(current->dataSize);
    memcpy(head->data, current->data, current->dataSize);
    head->dataSize = current->dataSize;
    head->next = current->next;

    free(current->data);
    free(current);
    return 1;
}

/*  Remove Last
        Deletes the last Node in the list.

        If the head is the first, and last node, the function will simply
        clear out the data from the node instead of deleting the whole node.

        Returns 0 if unsuccessful and 1 if successful
*/
int list_removeLast( struct Node *head )
{
    struct Node* current = head;
    if(current == NULL)
        return 0;

    if(current->next == NULL)
    {
        free(head->data);
        head->data = NULL;
        head->dataSize = 0;
        head->next = NULL;
        return 1;
    }

    while(current->next->next != NULL)
        current = current->next;

    struct Node* temp = current->next;
    current->next = NULL;
    free(temp->data);
    free(temp);
    return 1;
}

/*  Remove
        Deletes Node by passed index value.

        Returns 0 if unsuccessful and 1 if successful
*/
int list_remove( struct Node* head, size_t index)
{
    if(head == NULL)
        return 0;
    if(index == 0) {
        if(list_removeFirst(head))
            return 1;
        return 0;
    }
    
    struct Node *current = head;
    struct Node *prev;
    size_t count = 0;
    while(current != NULL && index != count)
    {
        if(count+1 == index && current->next != NULL)
            prev = current;
        current = current->next;
        count++;
    }
    if(current != NULL && prev != NULL)
    {
        prev->next = current->next;
        free(current->data);
        free(current);
        return 1;
    }
    return 0;
}

/*  Print
        Attempts to figure the type of the stored data in each node
        and print it out.
        otherwise the print fails.
*/
void list_print( struct Node *head )
{
    struct Node *current = head;
    while( current != NULL )
    {
        if( ((char*)current->data)[current->dataSize-1] == '\0')
            printf("%s\n", current->data );
        else if( current->dataSize == sizeof(int) )
            printf("INT: %d\n", *((int*)current->data) );
        else if( current->dataSize == sizeof(double) )
            printf("DOUBLE: %ld\n", *((double*)current->data) );
        else {
            int x;
            printf("0x");
            for(x=0; x<current->dataSize; x++)
                printf("%X ", ((char*)current->data)[x]);
            printf("\n");
        }
        current = current->next; 
    } 
}

/* Print Node
        Prints out the data inside a single node

        Data:       *string*
        DataSize:   *size_t*
        Next:       *pointer*
*/
void list_printNode( struct Node *node )
{
    if(node != NULL)
        printf("Data:\t\t%s\nDataSize:\t%d\nNext:\t\t%p\n", node->data, node->dataSize, node->next);

    else
        printf("Node NULL\n");
}

#endif
