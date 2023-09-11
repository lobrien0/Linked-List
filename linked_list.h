#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
    size_t dataSize;
    void *data;
    struct Node *next;
};

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

struct Node* list_last( struct Node *head )
{
    struct Node *current = head;
    while(current->next != NULL)
        current = current->next;
    
    return current;
}

size_t list_length( struct Node *head )
{
    size_t count = 0;
    struct Node *current = head;
    while(current != NULL) {
        current = current->next;
        count++;
    }
}

struct Node* list_init()
{
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = NULL;
    temp->dataSize = 0;
    temp->next = NULL;
    return temp;
}

void list_add( struct Node *head, void *data, size_t dataSize )
{
    if(head->data == NULL){
        head->dataSize = dataSize;
        head->data = (void*) malloc(dataSize);
        int x;
        memcpy(head->data, data, dataSize);
    }
    else
    {
        struct Node *current = head;
        struct Node *newNode = list_newNode(data, dataSize);
        while(current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

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
        if(count+1 == index && current->next != NULL);
            prev = current;
        current = current->next;
        count++;
    }
    if(current != NULL && prev != NULL)
    {
        prev->next = current->next;
        free(current->data);
        free(current);
    }
}

void list_print( struct Node *head )
{
    struct Node *current = head;
    while( current != NULL )
    {
        printf("%s\n", current->data );
        current = current->next;
    } 
}

void list_printNode( struct Node *node )
{
    if(node != NULL)
        printf("Data:\t\t%s\nDataSize:\t%d\nNext:\t\t%p\n", node->data, node->dataSize, node->next);

    else
        printf("Node NULL\n");
}

#endif