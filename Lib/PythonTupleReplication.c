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

#include "./PythonTupleReplication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

int makeTuple(tuple** tuple_arg, size_t size, ...){
    if (*tuple_arg != NULL){
        error_report(makeTuple, table[0]);
        goto fail;
    }

    //Initialize process
    *tuple_arg = (tuple*)malloc(sizeof(tuple));

    if (!tuple_arg){
        error_report(makeTuple, table[4]);
        goto fail;
    }

    (*tuple_arg)->dataPool = (void*)malloc(sizeof(data*) * size);

    if (!(*tuple_arg)->dataPool){
        error_report(makeTuple, table[4]);
        goto fail;
    }

    (*tuple_arg)->size    += size; 

    if (!(*tuple_arg)->size){
        error_report(makeTuple, table[4]);
        goto fail;
    }

    va_list arg_value;
    va_start(arg_value, size);

    for (size_t i = 0; i < size; i++)
        (*tuple_arg)->dataPool[i] = va_arg(arg_value, data*);

    va_end(arg_value);

    return EXIT_SUCCESS;
    fail:
    return EXIT_FAILURE;
}

size_t indexTuple(tuple** tuple, data* data){
    if (*tuple == NULL || data == NULL){
        error_report(indexTuple, table[0]);
        goto fail;
    }

    for (size_t i = 0; i < (*tuple)->size; i++){
        //Iterate through a list 
        if ((*tuple)->dataPool[i]->mode == data->mode){
            if (data->mode == __CUSTOM__)
                continue;

            if (data->mode == __STRING__){
                if (!strcmp((char*)data->data, (char*)(*tuple)->dataPool[i]->data))
                    return i;
            }else{
                int ret = memcmp(data->data, (*tuple)->dataPool[i]->data, (*tuple)->dataPool[i]->size - 1);
                
                if (!ret){
                    return i;
                }
            }
        }
    }

    fail:
    return -EXIT_FAILURE;
}

size_t countTuple(tuple** tuple, data* data){
    if (*tuple == NULL || data == NULL){
        error_report(indexTuple, table[0]);
        goto fail;
    }

    size_t counter = 0;
    for (size_t i = 0; i < (*tuple)->size; i++){
        //Iterate through a list 
        if ((*tuple)->dataPool[i]->mode == data->mode){
            if (data->mode == __CUSTOM__)
                continue;

            if (data->mode == __STRING__){
                if (!strcmp((char*)data->data, (char*)(*tuple)->dataPool[i]->data))
                    counter++;
            }else{
                int ret = memcmp(data->data, (*tuple)->dataPool[i]->data, (*tuple)->dataPool[i]->size - 1);
                
                if (!ret){
                    counter++;
                }
            }
        }
    }



    return counter;
    fail:
    return EXIT_FAILURE;
}


