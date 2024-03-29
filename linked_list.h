/*
#   Author Info:
#       Name: Luke O'Brien
#       Last Updated: 12 Sep 2023
#
#   Program Description:
#       This header-file offers a easy way to create and manage
#       doubly linked lists. Stores raw data, but can be casted.
#
#       Everything here is a passion project to hopefully make
#       things just a little easier for me, and hopefully you.
#       Suggestions are always welcome
#       lobrien@uccs.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*  Node structure
        Used for storing data dynamicly. 
        '*data' is used to store a pointer to allocated space for data
        'dataSize' stores the size of '*data'
        '*next' stores the location of the next 'Node'
        '*prev' stores the location of the previous "Node"
*/
struct Node {
    size_t dataSize;
    void *data;
    struct Node *next;
    struct Node *prev;
};

/*  List structure
        Used to store Node data in a way easy to use.
        'length' - used to store the length of list.
        '*head' - used to the store the first node of a linked list.
        '*tail' - used to the store the last node of a linked list.
*/
struct List {
    size_t length;
    struct Node *head;
    struct Node *tail;
};

/*################################################
#
#           List Creation Functions
#
################################################*/

/*  New Node
        Creates and allocates space for a temporary Node structure
        settings all the data to zero or Null.
        Returns the Node to be added to a list
*/
struct Node* list_newNode(void *data, size_t dataSize)
{
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->dataSize = dataSize;
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = (void*) malloc(dataSize);
    
    memcpy(temp->data, data, dataSize);

    return temp;
}

/*  Init
        Allocates space for a List structure, setting everything to null
        or zero
*/
struct List* list_init()
{
    struct List *temp = (struct List*) malloc(sizeof(struct List));
    temp->length = 0;
    temp->head = NULL;
    temp->tail = NULL;

    return temp;
}

/*  Add
        Creates a new Node and adds the address to the list
*/
int list_add( struct List *list, void *data, size_t dataSize )
{
    // If list is empty.
    if(list->head == NULL) {
        list->head = list_newNode(data, dataSize);
        list->tail = list->head;
        list->length++;
    }

    // if list is not empty
    else
    {
        list->tail->next = list_newNode(data, dataSize);
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->length++;
    }
    
    // If nothing is set, return failed (0)
    if( !(list->head && list->tail) )
        return 1;
    return 0;
}

/*################################################
#
#           List Seek Functions
#
################################################*/

/*  Index
        will return the node of passed index.

        Will attempt to optimize search time based on the distance
        to head or tail.
*/
struct Node* list_index( struct List *list, size_t index )
{
    size_t count = 0;
    if(list->head == NULL || index > list->length)
        return NULL;
    
    // If the node is in the first part of the list, start at head
    if( index <= (int)(list->length/2) ) 
    {
        struct Node* current = list->head;
        while( current != NULL && index != count ) {
            current = current->next;
            count++;
        }
        return current;
    }

    // If the node is in the second part of the list, start at tail.
    else
    {
        struct Node* current = list->tail;
        size_t reverseIndex = list->length - index;
        while( current != NULL && count != reverseIndex ) {
            current = current->prev;
            count++;
        }
        return current;
    }
}

/*  Search
        Given a list, this will search the data in every node,
        returning the index if found
*/
size_t list_search( struct List *list, void* data, size_t dataSize )
{
    struct Node *current = list->head;
    size_t lowest; size_t count = 0;
    while(current != NULL) {
        if(dataSize == current->dataSize)
            if(!memcmp(current->data, data, dataSize))
                return count;
        current = current->next;
        count++;
    }
    return count;
}

/*################################################
#
#           List Removal Functions
#
################################################*/

/*  Remove First
        Deletes the first Node in the list.

        Head is set to the node next to it (if not NULL)
*/
int list_removeFirst( struct List *list )
{
    // If list is empty.
    if(list->head == NULL)
        return 0;

    // if list is only 1 node.
    if(list->head->next == NULL)
    {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return 1;
    }
    // if list is more than 2 nodes.
    else
    {
        struct Node *temp = list->head;
        list->head = list->head->next;
        list->length--;

        free(temp->data);
        free(temp);
        return 1;
    }
}

/*  Remove Last
        Deletes the last Node in the list.

        tail is set to the node previous to it (if not NULL)
*/
int list_removeLast( struct List *list )
{
    // if list is empty.
    if(list->head == NULL)
        return 0;

    // if list only has 1 node.
    if(list->head->next == NULL)
        return list_removeFirst(list);
        
    // if list has more than two nodes
    else
    {
        struct Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->length--;

        free(temp->data);
        free(temp);
        return 1;
    }
}

/*  Remove
        Deletes Node by passed index value.

        find node by reference index, then removes it
        If first or last node is picked, respective function is called.
*/
int list_remove( struct List *list, size_t index)
{
    struct Node *current = list_index(list, index);
    if(current == NULL)
        return 0;
    
    // gets the nodes before and after current node
    struct Node *prev = current->prev;
    struct Node *next = current->next;

    // links the previous and next node together, skipping current node.
    if(prev != NULL && next != NULL) {
        prev->next = next;
        next->prev = prev;
        list->length--;

        free(current->data);
        free(current);
        return 1;
    }
    // If node is at beginning of list.
    else if(prev == NULL)
        return list_removeFirst(list);
    // If node is at end of list.
    else
        return list_removeLast(list);
}

/*  Close
        Deallocates all the nodes in the list before
        deallocating the space used by the list itself.
*/
int list_close( struct List *list )
{
    while(list_removeLast(list));
    free(list);
}

/*################################################
#
#           List Modifier Functions
#
################################################*/

/*  Set
        Sets an existing node of 'x' index to the new data and datasize provided

        This function accomplishes this by reallocating the amount of memory
        needed. Using realloc instead of malloc to possibly be more efficient.
*/
int list_set( struct List *list, size_t index, void* data, size_t dataSize)
{
    // Gets the Node by index
    struct Node *current = list_index(list, index);
    if(current == NULL)
        return 0;
    
    // Reallocates the memory size and sets data inside node
    current->data = (void*) realloc(current->data, dataSize);
    memcpy(current->data, data, dataSize);
    current->dataSize = dataSize;

    if(current->data == NULL)
        return 0;
    return 1;
}

/*################################################
#
#           List Debugging Functions
#
################################################*/

/* Print Node
        Prints out the data inside a single node

        Node:       *pointer*
        DataSize:   *size_t*
        Next:       *pointer*
        Prev:       *pointer*
        Data:       *Raw-Hex*
*/
void list_printDetails( struct Node *node )
{
    if(node != NULL) {
        printf("Node:\t\t%p\nDataSize:\t%ld\nNext:\t\t%p\nPrev:\t\t%p\nData:\t\t0x", node, node->dataSize, node->next, node->prev);
        int x;
        for(x=0; x<node->dataSize; x++)
            printf("%X ", ((char*)node->data)[x] );
        printf("\n");
    }

    else
        printf("Node NULL\n");
}

size_t list_length( struct List *list ) {
    return list->length;
}

/*################################################
#
#             Multi-Use Functions
#
################################################*/

/*  Pop First
        Deletes the first Node in the list given,
        then returns the data what was in the deleted node.
        (It doesn't dealloc the data - ptr that was in node)
*/
void* list_popFirst( struct List *list )
{
    void* dataPtr;

    // If list is empty.
    if(list->head == NULL)
        return NULL;

    // if list is only 1 node.
    if(list->head->next == NULL)
    {
        dataPtr = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return dataPtr;
    }
    // if list is more than 2 nodes.
    else
    {
        struct Node *temp = list->head;
        list->head = list->head->next;
        list->length--;

        dataPtr = temp->data;
        free(temp);
        return dataPtr;
    }
}

/*  Pop Last
        Deletes the last Node in the list given,
        then returns the data what was in the deleted node.
        (It doesn't dealloc the data - ptr that was in node)
*/
void* list_popLast( struct List *list )
{
    void* dataPtr;

    // if list is empty.
    if(list->head == NULL)
        return NULL;

    // if list only has 1 node.
    if(list->head->next == NULL)
        return list_popFirst(list);
        
    // if list has more than two nodes
    else
    {
        struct Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->length--;

        dataPtr = temp->data;
        free(temp);
        return dataPtr;
    }
}

/*  Pop 
        Deletes the node in the list at the index given,
        then returns the data what was in the deleted node.
        (It doesn't dealloc the data - ptr that was in node)
*/
void* list_pop( struct List *list, size_t index )
{
    struct Node *current = list_index(list, index);
    void* dataPtr;

    if(current == NULL)
        return NULL;
    
    // gets the nodes before and after current node
    struct Node *prev = current->prev;
    struct Node *next = current->next;

    // links the previous and next node together, skipping current node.
    if(prev != NULL && next != NULL) {
        prev->next = next;
        next->prev = prev;
        list->length--;

        dataPtr = current->data;
        free(current);
        return dataPtr;
    }
    // If node is at beginning of list.
    else if(prev == NULL)
        return list_popFirst(list);
    // If node is at end of list.
    else
        return list_popLast(list);
}

/*################################################
#
#           Node Specific Functions
#
################################################*/

/*  NODE - Set
        Sets the data of the node to a what ever the user
        has passed. Additionally set the dataSize
*/
int node_set( struct Node *node, void *data, size_t dataSize )
{
    if(node == NULL)
        return 0;
    node->data = (void*) realloc(node->data, dataSize);
    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;

    if(node->data == NULL)
        return 0;
    return 1;
}

/*  NODE - Remove
        Deletes a specific node in a list.
*/
int node_remove( struct List *list, struct Node *node )
{
    if(node == NULL)
        return 0;

    struct Node *prev = node->prev;
    struct Node *next = node->next;
    free(node->data);
    free(node);
    list->length--;

    if(prev != NULL && next != NULL) {
        prev->next = next;
        next->prev = prev;
    }
    else if(prev == NULL && next == NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    else if(prev == NULL) {
        list->head = next;
        next->prev = NULL;
    }
    else {
        list->tail = prev;
        prev->next = NULL;
    }
    return 1;
}

/*################################################
#
#           Typing/Casting Functions
#
################################################*/

/*  Print{*TYPE*}
        An array of functions that print out the entire list
        depending on the type printed
*/
void list_printStr( struct List *list ) {
    struct Node *current = list->head;
    while( current != NULL ) {
        printf("%s\n", (char*) current->data);
        current = current->next; 
    } 
}
void list_printInt( struct List *list ) {
    struct Node *current = list->head;
    while( current != NULL ) {
        printf("%d\n", (int) *((int*)current->data));
        current = current->next; 
    } 
}
void list_printLong( struct List *list ) {
    struct Node *current = list->head;
    while( current != NULL ) {
        printf("%ld\n", (long) *((long*)current->data));
        current = current->next; 
    } 
}
void list_printFloat( struct List *list ) {
    struct Node *current = list->head;
    while( current != NULL ) {
        printf("%f\n", (float) *((float*)current->data));
        current = current->next; 
    } 
}
void list_printDouble( struct List *list ) {
    struct Node *current = list->head;
    while( current != NULL ) {
        printf("%lf\n", (double) *((double*)current->data));
        current = current->next; 
    } 
}

/*  Add{*type*} - wrapper functions
        A array of functions to easily add different
        primitive types to the void pointer
*/
int list_addInt( struct List *list, int data ) {
    return list_add(list, &data, sizeof(int));
}
int list_addLong( struct List *list, long data ) {
    return list_add(list, &data, sizeof(long));
}
int list_addFloat( struct List *list, float data ) {
    return list_add(list, &data, sizeof(float));
}
int list_addDouble( struct List *list, double data ) {
    return list_add(list, &data, sizeof(double));
}
int list_addStr( struct List *list, char* data ) {
    return list_add(list, data, strlen(data)+1);
}

/*  Set{*type*} - wrapper functions
        Lets you set new data in a node of a specific type
*/
int list_setInt( struct List *list, size_t index, int data ) {
    return list_set(list, index, &data, sizeof(int));
}
int list_setLong( struct List *list, size_t index, long data ) {
    return list_set(list, index, &data, sizeof(long));
}
int list_setFloat( struct List *list, size_t index, float data ) {
    return list_set(list, index, &data, sizeof(float));
}
int list_setDouble( struct List *list, size_t index, double data ) {
    return list_set(list, index, &data, sizeof(double));
}
int list_setStr( struct List *list, size_t index, char* data ) {
    return list_set(list, index, data, strlen(data));
}

/*  NODE - Set{*type*} - wrapper functions
        sets the data stored to what the user passes, 
        specific to the data-type called.
*/

int node_setInt( struct Node *node, int data ) {
    return node_set(node, &data, sizeof(int));
}
int node_setLong( struct Node *node, long data ) {
    return node_set(node, &data, sizeof(long));
}
int node_setFloat( struct Node *node, float data ) {
    return node_set(node, &data, sizeof(float));
}
int node_setDouble( struct Node *node, double data ) {
    return node_set(node, &data, sizeof(double));
}
int node_setStr( struct Node *node, char* data ) {
    return node_set(node, data, strlen(data));
}

/*  NODE - Get{*type*}
        In a Node, returns the value stored
        in 'data', specified by type
*/
int node_getInt( struct Node *node ) {
    return (int) *((int*) node->data);
}
long node_getLong( struct Node *node ) {
    return (long) *((long*) node->data);
}
float node_getFloat( struct Node *node ) {
    return (float) *((float*) node->data);
}
double node_getDouble( struct Node *node ) {
    return (double) *((double*) node->data);
}
char* node_getString( struct Node *node ) {
    return (char*) node->data;
}

/*  Get{*type*}
        Returns the Type specified stored in the index provided
*/
int list_getInt( struct Node *node ) {
    if(node != NULL)
        return (int) *((int*)node->data);
    perror("Error - Node Empty:");
    return 0;
}
long list_getLong( struct Node *node ) {
    if(node != NULL)
        return (long) *((long*)node->data);
    perror("Error - Node Empty:");
    return 0;
}
float list_getFloat( struct Node *node ) {
    if(node != NULL)
        return (float) *((float*)node->data);
    perror("Error - Node Empty:");
    return 0;
}
double list_getDouble( struct Node *node ) {
    if(node != NULL)
        return (double) *((double*)node->data);
    perror("Error - Node Empty:");
    return 0;
}
char* list_getStr( struct Node *node ) {
    if(node != NULL) {
        if(node->data == NULL) {
            perror("Error - Data NULL");
            return NULL;
        }
        else
            return (char*) node->data;
    }
    perror("Error - Node Empty:");
    return NULL;
}

#endif