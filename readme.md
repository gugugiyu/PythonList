
# PythonList

PythonList is a concise library that written in pure C language in order to replicate literally the list data structure in the
Python programming language. This library targeting those who are familiar with Python syntax
and want to experience the same type of data structure in Python while coding C.



## Acknowledgements

    Since the syntax of the replicated list aren't perfectly identical to the Python language,
    there isn't any prerequisites to use the library. However, it's encouraged to have the basic
    knowledge of general C concepts inorder to expand this library:

 - [What are pointer](https://www.javatpoint.com/c-pointers#:~:text=The%20pointer%20in%20C%20language,a%20pointer%20is%202%20byte.)
 - [Python List Data Structure](https://docs.python.org/3/tutorial/datastructures.html)
```
    Syntax of the library will be clarified in the API Reference
```
- [Go to API Reference](#API-Reference)    
    

## Authors

- [@gugugiyu](https://www.github.com/gugugiyu)


## Features

- Replication of Python List in C with integrated function featuring:
```
- Initilization
- Insertion
- Deletion
- Integrated print function
- Reversal
```


## Structure defined

### List

This is the main list used for storing. Defined this list in the following syntax:

**list \*my_list_name = NULL;**

***Note: the upper list must be initialized to be NULL***

```javascript
typedef struct list{
    struct list_element*    root;
    size_t                  size;
}list;
```

### Data

The specific data type used for storing values. Defined either through parseData function or manually:


#### Manually example:


**data \*my_data_name = (data\*)malloc(sizeof(data));** //Allocating memory with malloc

**my_data_name->data = pointer_to_data;** //Set the data

**my_data_name->size = size_in_bytes;** //Set the size

**my_data_name->mode = defined macros;** //Set the mode (datatype) of this data


#### Using parseData() function example:

**data \*my_data_name = (data\*)malloc(sizeof(data));** 

**data = parseData(size_int_bytes, pointer_to_data, defined_macros);** //Built in parse function



```javascript
typedef struct data{
    void*                   data;
    size_t                  size;
    int                 mode : 5;
}data;
```

### list_element

The replication of nodes inside this list, it's not encouraged to declare this out as an variable or pointer, as the usages are internal

```
typedef struct list_element{
    void*                   data;
    size_t                  size;
    int                 mode : 5;
    struct list_element*    next;    
}list_element;
```


## Defined macro

### Initialize a list

```
void makeList(list ** list, ...);
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `...`     | `undefined`|The variadic parameters   |

***Note: The `...` parameter must be ended with macro '__ LIST_END__'***

The makeList() function will initialize the list with multiple input

### Adding an element
***All defined macro will invoke the static function 'addIndex'***

```
MACRO: append(list, type)
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `type`     | `data*` | **Required**. The given data structure (must be initialized) |

This macro will add a new `list_element` node to the end of the list


```
MACRO: head(list, type)
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `type`     | `data*` | **Required**. The given data structure (must be initialized) |

This macro will add a new `list_element` node to the start of the list


```
MACRO: insert(list, type)
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `type`     | `data*` | **Required**. The given data structure (must be initialized) |

This macro will add a new `list_element` node to a given index of the list

### Searching with Data
***All defined macro will invoke the static function 'findData'***

```
MACRO: index(list, type)
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `type`     | `data*` | **Required**. The given data structure (must be initialized) |

This macro will return the index of the given data, if error, the macro will return 1

```
MACRO: indexOffset(list, type, offset)
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `list`    | `list**` | **Required**. The given list to be initialize |
| `type`     | `data*` | **Required**. The given data structure (must be initialized) |
| `offset`  | `int`    | **Required**. The given offset to be searched|

This macro will return the index of the given data from range of `[offset...n]`




