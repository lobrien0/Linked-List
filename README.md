# Linked Lists

The following header file is a easy to include version of linked lists made for C.  
The header provides many functions and structures that give the user a wide range of control over how they store their data

## How to use

Please see `example.c` for a working test-case that shows a lot of the functionality of this linked list program.

## Supported Data Types

### Void Pointers

The primary data type that stores all the data is a void pointer.  

This allows the programmer freedom to store just about anything. Even other data structures given enough know-how.  
By default all the default functions cater to this type. For example:  
```C
int list_add( struct List *ptr, void* data, size_t dataSize );
```
```C
int list_set( struct List *ptr, size_t index, void* data, size_t dataSize);
```


But don't be discouraged if you aren't sure how to do that, there are plenty of functions to make storing a variety of stuff easily.

### String

Storing a large list of Strings is very easy with the helper functions.  
See the code below for an example:

```C
struct List *myList = list_init();

list_addStr(myList, "Hello World!");

// Gets the first Node in the list and prints it out as a string
printf("%s\n", list_getStr(list_index(myList, 0));
```

### Primitives

All the primary data types in C have a way to be stored with their own functions.

```C
struct List *myList = list_init();

list_addInt(myList, 5280);
list_addInt(myList, 31415);

// Prints the whole list as Integers
list_printInt(myList);
```

## Future Plans

### Optimization

Eventually I plan on adding further optimization to the linked list.  
This will likely be a little ways out since there is quite a bit of code refactoring that would need to go into it.

For now the linked list is fully functional. Just not the best option for large data-sets.

## Questions, Comments, Concerns?

If you would like to reach out to me about this program, or any others of mine, please reach out via email at:  

[lobrien@uccs.edu]()