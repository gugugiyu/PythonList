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

#define TOTAL_MODE 29

enum modePool{
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
    __SHORT_PTR__,
    __UNSIGNED_SHORT_PTR__,
    __CHAR_PTR__,
    __UNSIGNED_CHAR_PTR__,
    __INT_PTR__,
    __UNSIGNED_INT_PTR__,
    __LONG_PTR__,
    __UNSIGNED_LONG_PTR__,
    __LONG_LONG_INT_PTR__,
    __UNSIGNED_LONG_LONG_INTPTR__,
    __FLOAT_PTR__,
    __DOUBLE_PTR__,
    __LONG_DOUBLE_PTR__,
    __STRING_PTR__,
    __BOOLEAN_PTR__,    
    __CUSTOM__            
};


#define __MAKE_END NULL

#define MAX_SIZE_BUFFER_SHORT 257
#define MAX_SIZE_BUFFER_MEDIUM 513
#define MAX_SIZE_BUFFER_LARGE 1025

#define append(list, data) addIndex(list, data, -1)
#define head(list, data) addIndex(list, data, 0)
#define insert(list, data, pos) addIndex(list, data, pos)

#define index(list, data) findData(list, data, 0)
#define indexOffset(list, data, offset) findData(list, data, offset)

#define len(list) (*list ! = NULL ? (*list)->size: 0)
#define clear(list) clearList(list)

#define popHead(list) delete(list, 0)
#define popLast(list) delete(list, -1)
#define popIndex(list, pos) delete(list, pos)

#define getHead(list) findIndex(list, 0)
#define getLast(list) findIndex(list, -1)
#define getIndex(list, pos) findIndex(list, pos)

#define error_report(func_name, err) fprintf(stderr, "%s: %s", #func_name, err)

//_Generic selection upgraded, credit to Alex Gray from this post:
//https://stackoverflow.com/questions/9804371/syntax-and-sample-usage-of-generic-in-c11/17290414#17290414

#define dataOf(VAL) _Generic((0,VAL),                                                                                                          \
        /*This should be compatible with all the variable passing type*/                                                                       \
        _Bool *                 : parseData(sizeof(bool *), VAL, __BOOLEAN__),                                                                 \
        char *                  : parseData(strlen((char *) VAL) + 1, VAL, __STRING__),                                                        \
        unsigned char *         : parseData(strlen((char *) VAL) + 1 , VAL, __STRING__),                                                       \
        const char *            : parseData(strlen((char *) VAL) + 1,  VAL, __STRING__),                                                       \
        signed char *           : parseData(strlen((char *) VAL) + 1, VAL, __STRING__),                                                        \
        short int *             : parseData(sizeof(short *),  VAL, __SHORT__),                                                                 \
        unsigned short int *    : parseData(sizeof(unsigned short *),  VAL, __UNSIGNED_SHORT__),                                               \
        int *                   : parseData(sizeof(int *),  VAL, __INT__),                                                                     \
        unsigned int *          : parseData(sizeof(unsigned int *),  VAL, __UNSIGNED_INT__),                                                   \
        long int *              : parseData(sizeof(long *),  VAL, __LONG__),                                                                   \
        unsigned long int *     : parseData(sizeof(unsigned long *),  VAL, __UNSIGNED_LONG__),                                                 \
        long long int *         : parseData(sizeof(long long *),  VAL, __LONG_LONG_INT__),                                                     \
        unsigned long long int *: parseData(sizeof(unsigned long long *),  VAL, __UNSIGNED_LONG_LONG_INT__),                                   \
        float *                 : parseData(sizeof(float *),  VAL, __FLOAT__),                                                                 \
        double *                : parseData(sizeof(double *),  VAL, __DOUBLE__),                                                               \
        long double *           : parseData(sizeof(long double *),  VAL, __LONG_DOUBLE__),                                                     \
        /*User struct */                                                                                                                       \
        default                 : NULL)

#define dataOf_l(VAL) _Generic((0,VAL),                                                                                                        \
        char*                   : literalStringHandler,                                                                                        \
        char                    : literalCharHandler,                                                                                          \
        int                     : literalIntegerHandler,                                                                                       \
        float                   : literalFloatHandler,                                                                                         \
        double                  : literalDoubleHandler,                                                                                        \
        long double             : literalLongDoubleHandler,                                                                                    \
        long int                : literalLongIntHandler,                                                                                       \
        long long int           : literalLongLongIntHandler,                                                                                   \
        default                 : NULL)(VAL)

typedef struct l_elem{
    void*                   data;
    size_t                  size;
    int                     mode;
    struct l_elem*    next; 
}l_elem;

typedef struct l_elem_sup_struct{
    l_elem*                 l_elem;
    const char*                   struct_name;
}l_elem_sup_struct;


typedef struct data{
    void*                   data;
    size_t                  size;
    int                     mode;
}data;

typedef struct{
    struct l_elem*    root;
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

int                         addIndex(list **list, const data* data, const int pos);
void                        makeList(list ** list, ...);
int                         removeIndex(list **list, const int pos);
void                        reverseList(list **list);
data*                       findIndex(list **list, const int pos);
int                         modifyIndex(list **list, data* data, const int pos);
void                        clearList(list **list);
static void                 freeListElement(l_elem *root);
void                        print(list **list, const int step);
int                         findData(list **list, const data* data, const int offset);
int                         delete(list** _list, const int pos);
static int                  iterateFunc(l_elem *iterator, const data* data, const int offset);
#endif