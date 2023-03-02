/**
 * @file PythonListReplication.h
 * @author MagicExists (nguyen121107@gmail.com)
 * @brief https://github.com/gugugiyu/PythonList
 * @version 1.0
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PYTHON_LIST_REPLICATION_H
#define PYTHON_LIST_REPLICATION_H


#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_PRIMITIVE_MODE 16

typedef enum primitiveModePool{
    /* Listing out all mode to support*/
    __SHORT__,
    __UNSIGNED_SHORT__,
    __CHAR__,
    __UNSIGNED_CHAR__,
    __INT__,
    __UNSIGNED_INT__,
    __LONG__,
    __UNSIGNED_LONG__,
    __LONG_LONG_INT__,
    __UNSIGNED_LONG_LONG_INT__,
    __FLOAT__,
    __DOUBLE__,
    __LONG_DOUBLE__,
    __STRING__,
    __BOOLEAN__,
    __TUPLE__,
    __CUSTOM__            
} primitiveModePool;

extern const char *table[];


#define __MAKE_END NULL

#define MAX_SIZE_BUFFER_SHORT (2 << 8) + 1
#define MAX_SIZE_BUFFER_MEDIUM (2 << 9) + 1
#define MAX_SIZE_BUFFER_LARGE (2 << 10) + 1

#define append(list, data) addIndex(list, data, -1)
#define head(list, data) addIndex(list, data, 0)
#define insert(list, data, pos) addIndex(list, data, pos)

#define indexOf(list, data) findData(list, data, 0)
#define indexOf_o(list, data, offset) findData(list, data, offset)

#define len(list) (*(list) != NULL ? (*list)->size: 0)
#define clear(list) clearList(list)

#define popHead(list) deletePos(list, 0)
#define popLast(list) deletePos(list, -1)
#define popIndex(list, pos) deletePos(list, pos)

#define getHead(list) findIndex(list, 0)
#define getLast(list) findIndex(list, -1)
#define getIndex(list, pos) findIndex(list, pos)

#define sort(list, func) listSort((list->root), func)

#define error_report(func_name, err) fprintf(stderr, "%s: %s", #func_name, err)

//_Generic selection upgraded, credit to Alex Gray from this post:
//https://stackoverflow.com/questions/9804371/syntax-and-sample-usage-of-generic-in-c11/17290414#17290414

/**
 * @brief This will auto detect type of the given value, only using this macro for non-literal type
 * 
 */
#define dataOf(val) _Generic((0,val),                                                                                                          \
        /*This should be compatible with all the variable passing type*/                                                                       \
        _Bool *                 : parseData(sizeof(bool *), val, __BOOLEAN__),                                                                 \
        char *                  : parseData(strlen((char *) val) + 1, val, __STRING__),                                                        \
        unsigned char *         : parseData(strlen((char *) val) + 1 , val, __STRING__),                                                       \
        const char *            : parseData(strlen((char *) val) + 1,  val, __STRING__),                                                       \
        signed char *           : parseData(strlen((char *) val) + 1, val, __STRING__),                                                        \
        short int *             : parseData(sizeof(short *),  val, __SHORT__),                                                                 \
        unsigned short int *    : parseData(sizeof(unsigned short *),  val, __UNSIGNED_SHORT__),                                               \
        int *                   : parseData(sizeof(int *),  val, __INT__),                                                                     \
        unsigned int *          : parseData(sizeof(unsigned int *),  val, __UNSIGNED_INT__),                                                   \
        long int *              : parseData(sizeof(long *),  val, __LONG__),                                                                   \
        unsigned long int *     : parseData(sizeof(unsigned long *),  val, __UNSIGNED_LONG__),                                                 \
        long long int *         : parseData(sizeof(long long *),  val, __LONG_LONG_INT__),                                                     \
        unsigned long long int *: parseData(sizeof(unsigned long long *),  val, __UNSIGNED_LONG_LONG_INT__),                                   \
        float *                 : parseData(sizeof(float *),  val, __FLOAT__),                                                                 \
        double *                : parseData(sizeof(double *),  val, __DOUBLE__),                                                               \
        long double *           : parseData(sizeof(long double *),  val, __LONG_DOUBLE__),                                                     \
        /*Built in type of tuple in order to resolve user defined structure*/                                                                  \
        tuple *                 : parseData(sizeof(tuple *), val, __TUPLE__),                                                                  \
        /*User struct */                                                                                                                       \
        default                 : NULL)                                                                                                        

/**
 * @brief This will auto detect type of the given value, only using this macro for literal type
 * 
 */
#define dataOf_l(val) _Generic((0,val),                                                                                                        \
        char*                   : literalStringHandler,                                                                                        \
        char                    : literalCharHandler,                                                                                          \
        int                     : literalIntegerHandler,                                                                                       \
        float                   : literalFloatHandler,                                                                                         \
        double                  : literalDoubleHandler,                                                                                        \
        long double             : literalLongDoubleHandler,                                                                                    \
        long int                : literalLongIntHandler,                                                                                       \
        long long int           : literalLongLongIntHandler,                                                                                   \
        default                 : NULL)(val)

typedef struct l_elem{
    void*                   data;
    size_t                  size;
    primitiveModePool       mode;
    struct l_elem*          next; 
}l_elem;

typedef struct data{
    void*                   data;
    size_t                  size;
    primitiveModePool       mode;
}data;

typedef struct list{
    struct l_elem*          root;
    size_t                  size;
}list;


data*                       parseData(const int size, void* data, const int mode);

/* Literal handler case */
data*                       literalCharHandler(char data);
data*                       literalStringHandler(char* data);
data*                       literalFloatHandler(float data);
data*                       literalIntegerHandler(int data);
data*                       literalLongDoubleHandler(long double data);
data*                       literalLongIntHandler(long int data);
data*                       literalDoubleHandler(double data);
data*                       literalLongLongIntHandler(long long  data);

// INSERTION SECTION 

int                         addIndex(list **list, const data* data, const int pos);


// REVERSAL SECTION

void                        reverseList(list **list);


// PRINT SECTION
void                        singlePrint(primitiveModePool mode, const void* const data);
void                        print(list **list, const int step);


// DELETION SECTION

static int                  iterateFunc(l_elem *iterator, const data* data, const int offset);
int                         deletePos(list** _list, const int pos);
void                        clearList(list **list);
static void                 freeListElement(l_elem *root);


// SEARCHING SECTION

int                         findData(list **list, const data* data, const int offset);
data*                       findIndex(list **list, const int pos);


// INITILIZATION SECTION

void                        makeList(list ** list, ...);


// UTILITY SECTION

list*                       clone(const list* list, const unsigned char isRev);
int                         modifyIndex(list **list, data* data, const int pos);
size_t                      count(list** list, data* data);


// SORTING SECTION

void                        listSort(l_elem **list,  int (*cmp)(const data *, const data *));
static                      l_elem* merge(l_elem* hLeft, l_elem* hRight, int (*cmp)(const data *, const data *));
static void                 splitHalf(l_elem *root, l_elem** hLeft, l_elem** hRight);
#endif