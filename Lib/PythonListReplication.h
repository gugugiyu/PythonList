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
#include <string.h>

#define TOTAL_MODE 29
enum modePool{
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

#define append(list, type) addIndex(list, type, -1)
#define head(list, type) addIndex(list, type, 0)
#define insert(list, type, pos) addIndex(list, type, pos)

#define index(list, type) findData(list, type, 0)
#define indexOffset(list, type, offset) findData(list, type, offset)

#define len(list) (*list ! = NULL ? (*list)->size: 0)
#define clear(list) clearList(list)

#define popHead(list) delete(list, 0)
#define popLast(list) delete(list, -1)
#define popIndex(list, pos) delete(list, pos)

#define getHead(list) findIndex(list, 0)
#define getLast(list) findIndex(list, -1)
#define getIndex(list, pos) findIndex(list, pos)

#define error_report(func_name, err) fprintf(stderr, #func_name #err)

//_Generic selection upgraded, credit to Alex Gray from this post:
//https://stackoverflow.com/questions/9804371/syntax-and-sample-usage-of-generic-in-c11/17290414#17290414

#define dataOf(x) _Generic((0,x),                                                                                                          \
        /*Case where value are not literal*/                                                                                               \
        _Bool                   : parseData(sizeof(bool), x, __BOOLEAN__),                                                                 \
        unsigned char           : parseData(sizeof(unsigned char), x, __UNSIGNED_CHAR__),                                                  \
        char                    : parseData(1,  x, __CHAR__),                                                                              \
        signed char             : parseData(sizeof(signed char), x, __CHAR__),                                                             \
        short int               : parseData(sizeof(short),  x, __SHORT__),                                                                 \
        unsigned short int      : parseData(sizeof(unsigned short),  x, __UNSIGNED_SHORT__),                                               \
        int                     : parseData(sizeof(int),  x, __INT__),                                                                     \
        unsigned int            : parseData(sizeof(unsigned int),  x, __UNSIGNED_INT__),                                                   \
        long int                : parseData(sizeof(long),  x, __LONG__),                                                                   \
        unsigned long int       : parseData(sizeof(unsigned long),  x, __UNSIGNED_LONG__),                                                 \
        long long int           : parseData(sizeof(long long),  x, __LONG_LONG_INT__),                                                     \
        unsigned long long int  : parseData(sizeof(unsigned long long),  x, __UNSIGNED_LONG_LONG_INT__),                                   \
        float                   : parseData(sizeof(float),  x, __FLOAT__),                                                                 \
        double                  : parseData(sizeof(double),  x, __DOUBLE__),                                                               \
        long double             : parseData(sizeof(long double),  x, __LONG_DOUBLE__),                                                     \
        /*Pointer case*/                                                                                                                   \
        _Bool *                 : parseData(sizeof(bool *), x, __BOOLEAN__),                                                               \
        char *                  : parseData(strlen((char *) x) + 1, (x), __STRING__),                                                      \
        unsigned char *         : parseData(strlen((char *) x) + 1 , x, __UNSIGNED_CHAR__),                                                \
        const char *            : parseData(strlen((char *) x) + 1,  x, __STRING__),                                                       \
        signed char *           : parseData(strlen((char *) x) + 1, x, __STRING__),                                                        \
        short int *             : parseData(sizeof(short *),  x, __SHORT__),                                                               \
        unsigned short int *    : parseData(sizeof(unsigned short *),  x, __UNSIGNED_SHORT__),                                             \
        int *                   : parseData(sizeof(int *),  x, __INT__),                                                                   \
        unsigned int *          : parseData(sizeof(unsigned int *),  x, __UNSIGNED_INT__),                                                 \
        long int *              : parseData(sizeof(long *),  x, __LONG__),                                                                 \
        unsigned long int *     : parseData(sizeof(unsigned long *),  x, __UNSIGNED_LONG__),                                               \
        long long int *         : parseData(sizeof(long long *),  x, __LONG_LONG_INT__),                                                   \
        unsigned long long int *: parseData(sizeof(unsigned long long *),  x, __UNSIGNED_LONG_LONG_INT__),                                 \
        float *                 : parseData(sizeof(float *),  x, __FLOAT__),                                                               \
        double *                : parseData(sizeof(double *),  x, __DOUBLE__),                                                             \
        long double *           : parseData(sizeof(long double *),  x, __LONG_DOUBLE__),                                                   \
        /*User struct */                                                                                                                   \
        default                 : "other")

typedef struct list_element{
    void*                   data;
    size_t                  size;
    int                     mode;
    struct list_element*    next; 
    typedef void (*print_func)(void*);   
}__attribute__((packed, aligned(1))) list_element;

typedef struct data{
    void*                   data;
    size_t                  size;
    int                     mode;
}__attribute__((packed, aligned(1))) data;

typedef struct{
    struct list_element*    root;
    size_t                  size;
}list;


data*                       parseData(const int size, void* data, const int mode);
int                         addIndex(list **list, const data* data, const int pos);
void                        makeList(list ** list, ...);
int                         removeIndex(list **list, const int pos);
void                        reverseList(list **list);
data*                       findIndex(list **list, const int pos);
int                         modifyIndex(list **list, data* data, const int pos);
void                        clearList(list **list);
static void                 freeListElement(list_element *root);
void                        print(list **list, const int step);
int                         findData(list **list, const data* data, const int offset);
int                         delete(list** arg_list, const int pos);
static int                  iterateFunc(list_element *iterator, const data* data, const int offset);
#endif