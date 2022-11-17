#define FILE_LOG_NAME 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./lib/PythonListReplication.h"

struct new_data{
    int a;
    float d;
    char *c;
};

int main(){
    list* my_list = NULL;

    int a = 10;
    char *str = "This is a string";
    float b = 3.45;
    double c = 6.7, c1, c2;
    struct new_data test;
    test.a = 10;
    test.d = 3.14;
    test.c = "test string";

    makeList(&my_list, parseData(sizeof(int), &a, __INT__), parseData(sizeof(double), &c, __DOUBLE__), parseData(strlen(str) + 1, str, __STRING__), __LIST_END__);
    append(&my_list, parseData(strlen(str) + 1, str, __STRING__));
    append(&my_list, parseData(sizeof(struct new_data), &test, __CUSTOM__));

    printf("Before modified list: \n");
    print(&my_list, 1);

    list_element *i = my_list->root;

    printf("Current length = %d\n", len(&my_list));

    for (int i = 0; i < len(&my_list); i++)
        modifyIndex(&my_list, parseData(sizeof(int), &a, __INT__), i);
    
    printf("After modifed list: \n");
    print(&my_list, 1);

    printf("%d", indexOffset(&my_list, parseData(999, NULL, __INT__), 999));
    
    return 0;
}