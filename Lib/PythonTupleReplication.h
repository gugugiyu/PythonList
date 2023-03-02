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
#ifndef PYTHON_TUPLE_REPLICATION_H
#define PYTHON_TUPLE_REPLICATION_H

#include "./PythonListReplication.h"

typedef struct tuple{
    const data**    dataPool;
    size_t          size;
}tuple;

int                            makeTuple(tuple** tuple, size_t size, ...);
size_t                         indexTuple(tuple** tuple, data* data);
size_t                         countTuple(tuple** tuple, data* data);
static bool                    haveMore(data* data);

#endif