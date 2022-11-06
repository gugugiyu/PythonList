#pragma once

#ifndef PYTHON_LIST_REPLICATION_H
#define PYTHON_LIST_REPLICATION_H

#define __SHORT__           0
#define __UNSIGNED_SHORT    1
#define __CHAR__            2
#define __UNSIGNED_CHAR__   3
#define __INT__             4
#define __UNSIGNED_INT__    5
#define __LONG__            6
#define __UNSIGNED_LONG__   7
#define __FLOAT__           8
#define __DOUBLE__          9
#define __LONG_DOUBLE__     10
#define __STRING__          11
#define __CUSTOM__          12

#define __LIST_END__        NULL

#define append(list, type) addIndex(list, type->data, type->size, -1, type->mode);
#define head(list, type) addIndex(list, type->data, type->size, 0, type->mode);
#define insert(list, type, pos) addIndex(list, type->data, type->size, pos, type->mode);

#define index(list, type) findData(list, type, 0);
#define indexOffset(list, type, offset) findData(list, type, offset);

#define len(list) list != NULL ? list->size : 0
#define clear(list) clearList(list);

#define popHead(list) delete(list, 0);
#define popLast(list) delete(list, -1);
#define popIndex(list, pos) delete(list, pos);

#define getHead(list) findIndex(list, 0);
#define getLast(list) findIndex(list, -1);
#define getIndex(list, pos) findIndex(list, pos);


typedef struct list_element{
    void*                   data;
    size_t                  size;
    struct list_element*    next;
    int                     mode;
    
}list_element;

typedef struct data{
    void*                   data;
    size_t                  size;
    int                     mode;
}data;

typedef struct list{
    struct list_element*    root;
    size_t                  size;
}list;


int                         addIndex(list **list, const void* data, const size_t size, const int pos, const int mode);
void                        makeList(list ** list, ...);
int                         removeIndex(list **list, const int pos);
data*                       parseData(const int size, void* data, const int mode);
void                        reverseList(list **list);
data*                       findIndex(list **list, const int pos);
void                        modifyIndex(list **list, data* data, const int pos);
void                        clearList(list **list);
void                        print(list **list, const int step);
int                         findData(list **list, const data* data, const int offset);
int                         delete(list** arg_list, const int pos);
static void                 freeListElement(list_element *root);
static int                  iterateFunc(list_element *iterator, const data* data, const int offset);
#endif