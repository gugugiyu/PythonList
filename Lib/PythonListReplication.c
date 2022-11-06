#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "./PythonListReplication.h"


list_element* findIndex(list** arg_list, const int pos){
    if (*arg_list == NULL){
        printf("List is clear, try to add more elements (getIndex)\n");
        goto fail;
    }else{
        list_element* iterator = (*arg_list)->root;

        if (iterator->next == NULL){
            return iterator;
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
        return iterator;
    }
    fail:
    return NULL;

}

data* parseData(const int size, void* content, const int mode){
    data* ret = (data*)malloc(sizeof(data));
    
    ret->size = size;
    ret->data = malloc(sizeof(size));

    if(ret->data)
        memcpy(ret->data, content, size);
    else{
        printf("Failed to allocate memory! (Initialize process)\n");
        goto fail;
    }
    
    ret->mode = mode;

    return ret;

    fail:
    return NULL;
}

int makeList(list** arg_list, ...){
    va_list list_va;

    va_start(list_va, arg_list);

    while (1){
        data* ret = va_arg(list_va, data*);

        if (ret == __LIST_END__)
            break;

        addIndex(arg_list, ret->data, ret->size, -1, ret->mode);
    }

    va_end(list_va);   
}

void clearList(list **arg_list){
    freeListElement((*arg_list)->root);
    free(*arg_list);
    *arg_list = NULL;
}

void freeListElement(list_element *root){
    list_element *iterator;
    
    while (root != NULL){
        iterator = root;
        root = root->next;

        free(iterator->data);
        free(iterator);
    }

    root = NULL;
}

int delete(list** arg_list, const int pos){
    
    if (*arg_list == NULL){
        printf("List is clear, try to add elements! (delete)\n");
        goto fail;
    }else{
        list_element* iterator = (*arg_list)->root;

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
                list_element *buffer = (*arg_list)->root;
                (*arg_list)->root        = (*arg_list)->root->next;

                free(buffer);
            }else{
                int counter = 0;

                while (counter != pos-1 && iterator->next->next != NULL){
                    iterator = iterator->next;
                    counter++;
                }

                list_element *buffer =  iterator->next->next;
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

int addIndex(list** arg_list, const void* value, const size_t size, const int pos, const int data_type){
    if (data_type < 0 || data_type > 12){
        printf("Invalid data type, try to use defined macro instead!\n");
        goto fail;
    }
    if ((*arg_list)== NULL){
        //Initialize the list
        *arg_list         = (list*)malloc(sizeof(list));
        (*arg_list)->root = (list_element*)malloc(sizeof(list_element));

        (*arg_list)->root->data = malloc(size);

        if ((*arg_list)->root->data)
            memcpy((*arg_list)->root->data, value, size);
        else{
            printf("Failed to allocate memory! (Initialize process)\n");
            goto fail;
        }
        (*arg_list)->root->size = size;
        (*arg_list)->root->next = NULL;
        (*arg_list)->root->mode = data_type;
        (*arg_list)->size = 1;
    }else{

        list_element* new_list_element = (list_element*)malloc(sizeof(list_element));
        new_list_element->data = malloc(size);
        new_list_element->size = size;
        new_list_element->mode = data_type;

        if (new_list_element->data)
            memcpy(new_list_element->data, value, size);
        else{
            printf("Failed to allocate memory (insertion process)!\n");
            goto fail;
        }

        if (pos == 0){
            new_list_element->next = (*arg_list)->root;
            (*arg_list)->root = new_list_element;
        }else if (pos < 0){
            list_element *iterator = (*arg_list)->root;
            while(iterator->next != NULL)
                iterator = iterator->next;

              
            iterator->next = new_list_element;
            new_list_element->next = NULL;
        }else{
            int counter = 0;
            list_element *iterator = (*arg_list)->root;
            list_element *buffer;

            while (counter != pos && iterator->next != NULL){
                iterator = iterator->next;
                counter++;
            }
            
            buffer = iterator->next;
            iterator->next = new_list_element;
            new_list_element->next = buffer;
        }
        (*arg_list)->size++;
    }
    return EXIT_SUCCESS;
    fail:
    return EXIT_FAILURE;
}

void print(list **arg_list, const int step){
    if(*arg_list == NULL){
        printf("[]\n");
        return;
    }

    if (!step){
        printf("Invalid step, step musn't be 0");
        return;
    }
    
    list_element *iterator = (*arg_list)->root;
    printf("[");
    while (iterator != NULL){
        switch(iterator->mode){
            case __SHORT__:
                printf("%i", *((short*)iterator->data));
                break;
            case __UNSIGNED_SHORT:
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
                printf("%f", *((float*)iterator->data));
                break;
            case __DOUBLE__:
                printf("%lf", *((double*)iterator->data));
                break;
            case __LONG_DOUBLE__:
                printf("%Lf", *((long double*)iterator->data));
                break;
            case __STRING__:
                printf("%s", ((char*)iterator->data));
                break;
            case __CUSTOM__:
                printf("CUSTOM ");
                break;
            default:
                printf("ERROR ");
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