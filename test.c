#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Lib/PythonListReplication.h"

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

    printf("The size of the list is = %d\n", len(my_list));

    print(&my_list, 1);

    printf("%d\n", indexOffset(&my_list, parseData(strlen("This is a string") + 1, "This is a string", __STRING__), 999));
    printf("%d\n", indexOffset(&my_list, NULL, 0));

    
    return 0;
}