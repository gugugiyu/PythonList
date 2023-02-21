/**
 * @file PythonListReplication.c
 * @author MagicExists (nguyen121107@gmail.com)
 * @brief https://github.com/gugugiyu/PythonList
 * @version 1.0
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include ".\PythonListReplication.h"



const char *table[] = {
    "Data parameter is null!",
    "Invalid mode, value either negative or exceeded 12!",
    "Invalid offset, offset value larger than the size of list!",
    "List is clear, try to add more elements!",
    "Failed to allocate memory!",
    "Invalid step, step musn't be 0!",
    "Warning: The list has no element, most function don't work on a clear list!"
};

data* literalIntegerHandler(int data){
    int* dataRet = malloc(sizeof(int));
    *dataRet = data;
    return parseData(sizeof(int), dataRet, __INT__);
}

data* literalStringHandler(char* data){
    return parseData(strlen(data) + 1, data, __STRING__);
}

data* literalCharHandler(char data){
    char* dataRet = malloc(1);
    *dataRet = data;
    return parseData(1, dataRet, __CHAR__);
}

data* literalFloatHandler(float data){
    float* dataRet = malloc(sizeof(float));
    *dataRet = data;
    return parseData(sizeof(float), dataRet, __FLOAT__);
}

data* literalDoubleHandler(double data){
    double* dataRet = malloc(sizeof(double));
    *dataRet = data;
    return parseData(sizeof(double), dataRet, __DOUBLE__);
}

data* literalLongIntHandler(long data){
    long* dataRet = malloc(sizeof(long));
    *dataRet = data;
    return parseData(sizeof(long), dataRet, __CHAR__);
}

data* literalLongDoubleHandler(long double data){
    long double * dataRet = malloc(sizeof(long double));
    *dataRet = data;
    return parseData(sizeof(long double), dataRet, __CHAR__);
}

data* literalLongLongIntHandler(long long data){
    long long * dataRet = malloc(sizeof(long long));
    *dataRet = data;
    return parseData(sizeof(long long), dataRet, __CHAR__);
}

/**
 * @brief This function will modify the content of the list at a given index
 * 
 * @param arg_list The pointer to the given list
 * @param data The given data structure which was parsed
 * @param pos The index of the node to be modifed
 * 
 * @return On success, the function will return 0, else 1 is returned if error. Note that if the position exceeded the list's size, append action will be perform instead, this counts as a success.
 */

void reverseList(list **arg_list){

    struct l_elem* prev = NULL;
    struct l_elem* current = (*arg_list)->root;
    struct l_elem* next = NULL;
    
    while (current != NULL) {
        next = current->next;

        current->next = prev;
 
        prev = current;
        current = next;
    }
    (*arg_list)->root = prev;
}

/**
 * @brief This function will modify the data at a given position
 * 
 * @param arg_list The given list to be modified
 * @param data The data that will replace the currnet one
 * @param pos The position to replace, put negative value for end of the list
 * @return int return 0 upon success, else 1 is return 
 */
int modifyIndex(list **arg_list, data* data, const int pos){
    if (data == NULL){
        error_report(modifyIndex, table[0]);
        goto fail;
    }else if (pos >= (*arg_list)->size){
        append(arg_list, data);
        goto fail;
    }else if (*arg_list == NULL){
        error_report(modifyIndex, table[0]);
        goto fail;
    }else{
        l_elem* iterator = (*arg_list)->root;

        if (pos < 0){
            while (iterator->next != NULL)
                iterator = iterator->next;
        }else{
            int counter = 0;

            while (counter < pos && iterator->next != NULL){
                iterator = iterator->next;
                counter++;
            }
        }
        //Modify the data structure
        iterator->data = realloc(iterator->data, data->size);

        if (iterator == NULL){
            error_report(modifyIndex, table[4]);
            goto fail;
        }
        memcpy(iterator->data, data->data, data->size);

        iterator->size = data->size;
        iterator->mode = data->mode;

    }  
    return EXIT_SUCCESS;
    fail:
    return EXIT_FAILURE;

}
/**
 * @brief This function is a complement for the clearList function, clear the root in detail
 * 
 * @param root The root passed by the clearList function
 */
void freeListElement(l_elem *root){
    l_elem *iterator;
    
    while (root != NULL){
        iterator = root;
        root = root->next;

        free(iterator->data);
        free(iterator);
    }
    root = NULL;
}
/**
 * @brief This function will find the index of a given data structure which is inputted through arguments
 * 
 * @param arg_list The pointer to the list of checking
 * @param data The given data
 * @param offset The offset of checking process, the iterator will skipped to the unoffset part
 * @return int On success, the function will return the index of the given data, else 1 is return if error
 */
int findData(list ** arg_list, const data* data, const int offset){
    if (data == NULL){
        error_report(findData, table[0]);
        goto fail;
    }
    
    if (data->mode < 0 || data->mode > TOTAL_MODE){
        error_report(findData, table[0]);
        goto fail;
    }

    if (offset < 0 || offset >= (*arg_list)->size){
        error_report(findData, table[0]);
        goto fail;
    }

    l_elem *iterator = (*arg_list)->root;

    int offsetCount = 0;
    while (iterator != NULL && offsetCount < offset){
        iterator = iterator->next;
        offsetCount++;
    }

    if (!iterator)
        goto fail;

    return iterateFunc(iterator, data, offset);
    fail:
    return EXIT_FAILURE;
}

static int iterateFunc(l_elem *iterator, const data* data, const int offset){
    int counter = offset;
    while (iterator != NULL){
        if (iterator->mode == data->mode){
            if (data->mode == __CUSTOM__)
                continue;

            if (data->mode == __STRING__){
                if (!strcmp((char*)data->data, (char*)iterator->data))
                    return counter;
            }else{
                int ret = memcmp(data->data, iterator->data, iterator->size);

                if (!ret)
                    return counter;
            }
        }
        counter++;
        iterator = iterator->next;
    }
    return -1;
}


/**
 * @brief This function will return the data structure based on the given index
 * 
 * @param arg_list The pointer to the list of checking
 * @param pos The position of index
 * @return data* On sucess, the pointer to this data structure will be returned, else NULL will be returned
 */
data* findIndex(list** arg_list, const int pos){
    if (*arg_list == NULL){
        error_report(findIndex, table[3]);
        goto fail;
    }else if(pos > (*arg_list)->size){
        error_report(findIndex, table[2]);
        goto fail;
    }else{
        l_elem* iterator = (*arg_list)->root;

        if (iterator->next == NULL){
            return parseData(iterator->size, iterator->data, iterator->mode);
        }else{
            if (pos < 0){
                while (iterator->next != NULL)
                    iterator = iterator->next;
            }else{
                int counter = 0;

                while (counter != pos && iterator->next != NULL){
                    iterator = iterator->next;
                    counter++;
                }
            }
        }
        return parseData(iterator->size, iterator->data, iterator->mode);
    }
    fail:
    return NULL;

}

/**
 * @brief This function will parse the given content into the data structure
 * 
 * @param size The total size of the content (must be converted in bytes)
 * @param content The void pointer to the given content
 * @param mode The data type (should be setted with defined macro) of the content
 * @return data* On sucess, the pointer to this data structure will be returned, else NULL will be returned
 */
data* parseData(const int size, void* content, const int mode){
    if (mode < 0 || mode > TOTAL_MODE){
        error_report(parseData, table[1]);
        goto fail;
    }

    if (content == NULL){
        error_report(parseData, table[0]);
        goto fail;
    }

    data* ret = (data*)malloc(sizeof(data));
    
    ret->size = size;
    ret->data = malloc(sizeof(size));

    if(ret->data)
        memcpy(ret->data, content, size);
    else{
        error_report(4, "parseData");
        goto fail;
    }
    
    ret->mode = mode;

    return ret;

    fail:
    return NULL;
}

/**
 * @brief This function will add multiple data structure into the list (it is encouraged to used with simultanenous insertion, like initialization)
 * 
 * @param arg_list The pointer to the list of checking
 * @param ... Data structures, must be ended with macro "__LIST_END__"
 */
void makeList(list** arg_list, ...){
    va_list list_va;

    va_start(list_va, arg_list);

    while (1){
        data* ret = va_arg(list_va, data*);

        if (ret == __MAKE_END)
            break;

        addIndex(arg_list, ret, -1);
    }

    va_end(list_va);   
}

/**
 * @brief This function will free the whole list
 * 
 * @param arg_list The pointer to the list to be freed
 */
void clearList(list **arg_list){
    freeListElement((*arg_list)->root);
    free(*arg_list);
    *arg_list = NULL;
}

/**
 * @brief This function will delete a l_elem structure at a given index
 * 
 * @param arg_list The pointer to the list to be deleted
 * @param pos The given index to the l_elem structure to be deleted. Negative values are treated as end of list;
 * @return int On success, the function returns 0, else 1 will be returned
 */

int delete(list** arg_list, const int pos){
    if (*arg_list == NULL){
        error_report(0, "delete");
        goto fail;
    }else{
        l_elem* iterator = (*arg_list)->root;

        if (iterator->next == NULL){
                //FREE THE LIST;
                clearList(arg_list);
        }else{
            if (pos < 0){
                while (iterator->next->next != NULL)
                    iterator = iterator->next;

                free(iterator->next->data);
                free(iterator->next);
                iterator->next = NULL;

            }else if(pos == 0){
                l_elem *buffer = (*arg_list)->root;
                (*arg_list)->root    = (*arg_list)->root->next;

                free(buffer);
            }else{
                int counter = 0;

                while (counter != pos-1 && iterator->next->next != NULL){
                    iterator = iterator->next;
                    counter++;
                }

                l_elem *buffer =  iterator->next->next;
                free(iterator->next->data);
                free(iterator->next);

                iterator->next = NULL;
                iterator->next = buffer;

            }
            (*arg_list)->size--;
        }
    }
    return EXIT_SUCCESS;
    fail:
    return EXIT_FAILURE;

}

/**
 * @brief This function will add a new node based on the given index, and initialize the list if it's NULL
 * 
 * @param arg_list The pointer to the list to be inserted
 * @param value The pointer to the value
 * @param size The size of the value
 * @param pos The position to be added, input negative value to add at the end
 * @param data->mode The defined macro of data->mode
 * @return int On success, 0 will be returned, else 1 will be returned if error
 */
int addIndex(list** arg_list, const data* data, const int pos){
    if (data->mode < 0 || data->mode > TOTAL_MODE){
        printf("what ? %d\n", data->mode);
        error_report(addIndex, table[1]);
        goto fail;
    }

    if (data->data == NULL){
        error_report(addIndex, table[0]);
        goto fail;
    }

    if ((*arg_list) == NULL){
        //Initialize the list
        *arg_list         = (list*)malloc(sizeof(list));
        (*arg_list)->root = (l_elem*)malloc(sizeof(l_elem));

        (*arg_list)->root->data = malloc(data->size);

        if ((*arg_list)->root->data)
            memcpy((*arg_list)->root->data, data->data, data->size);
        else{
            error_report(4, "addIndex");
            goto fail;
        }
        (*arg_list)->root->size = data->size;
        (*arg_list)->root->next = NULL;
        (*arg_list)->root->mode = data->mode;
        (*arg_list)->size = 1;
    }else{

        l_elem* new_l_elem = (l_elem*)malloc(sizeof(l_elem));
        new_l_elem->data = malloc(data->size);
        new_l_elem->size = data->size;
        new_l_elem->mode = data->mode;

        if (new_l_elem->data)
            memcpy(new_l_elem->data, data->data, data->size);
        else{
            error_report(addIndex, table[4]);
            goto fail;
        }

        if (pos == 0){
            new_l_elem->next = (*arg_list)->root;
            (*arg_list)->root = new_l_elem;
        }else if (pos < 0){
            l_elem *iterator = (*arg_list)->root;
            while(iterator->next != NULL)
                iterator = iterator->next;

            iterator->next = new_l_elem;
            new_l_elem->next = NULL;
        }else{
            int counter = 0;
            l_elem *iterator = (*arg_list)->root;
            l_elem *buffer;

            while (counter != pos && iterator->next != NULL){
                iterator = iterator->next;
                counter++;
            }
            
            buffer = iterator->next;
            iterator->next = new_l_elem;
            new_l_elem->next = buffer;
        }
        (*arg_list)->size++;
    }
    return EXIT_SUCCESS;
    fail:
    return EXIT_FAILURE;
}

/**
 * @brief This built-in print function will print out the list, bypass error and custom input type
 * 
 * @param arg_list The pointer to the list to be printed
 * @param step The iteration cycles 
 */
void print(list **arg_list, const int step){
    if(*arg_list == NULL){
        error_report(print, table[6]);
        printf("[]");
        return;
    }

    if (!step){
        error_report(print, table[5]);
        return;
    }
    
    l_elem *iterator = (*arg_list)->root;
    printf("[");
    while (iterator != NULL){
        switch(iterator->mode){
            case __SHORT__:
                printf("%i", *((short*)iterator->data));
                break;
            case __UNSIGNED_SHORT__:
                printf("%i", *((unsigned short*)iterator->data));
                break;
            case __CHAR__:
                printf("%c", *((char*)iterator->data));
                break;
            case __UNSIGNED_CHAR__:
                printf("%c", *((unsigned char*)iterator->data));
                break;
            case __INT__:
                printf("%d", *((int*)iterator->data));
                break;
            case __UNSIGNED_INT__:
                printf("%lu", *((unsigned int*)iterator->data));
                break;
            case __LONG__:
                printf("%li", *((long*)iterator->data));
                break;
            case __UNSIGNED_LONG__:
                printf("%lu", *((unsigned long*)iterator->data));
                break;
            case __FLOAT__:
                printf("%g", *((float*)iterator->data));
                break;
            case __DOUBLE__:
                printf("%g", *((double*)iterator->data));
                break;
            case __LONG_DOUBLE__:
                printf("%Lf", *((long double*)iterator->data));
                break;
            case __STRING__:
                printf("%s", ((char*)iterator->data));
                break;
            case __BOOLEAN__:
                printf("%s", *((bool *)iterator->data) == true ? "true" : "false");
                break;
            case __CUSTOM__:
                printf("CUSTOM");
                break;
            default:
                printf("ERROR");
        }

        for (int i = 0; i < step; i++){
            if (iterator->next == NULL){
                printf("]\n");
                return;
            }

            iterator = iterator->next;
        }

        if (iterator != NULL)
            printf(", ");
    }
    printf("]\n");
}