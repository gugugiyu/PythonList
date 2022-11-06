#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Lib/PythonListReplication.h"
int main(){
    struct list **list = (struct list**)malloc(sizeof(struct list*) * 5);

    for (int i = 0; i < 5; i++)
        list[i] = NULL;

    int a = 10; //4 bytes 32x, 8 bytes 64x
    double b = 3.14;
    char *str = "This is a string";
    int bc = 20;
    makeList(&list[0], parseData(sizeof(int), &a, __INT__), parseData(sizeof(double), &b, __DOUBLE__),parseData(strlen(str) + 1, str, __STRING__), __LIST_END__);
    append(&list[0], parseData(sizeof(bc), &bc, __INT__));
    head(&list[0], parseData(strlen(str) + 1, str, __STRING__));

    makeList(&list[1], parseData(sizeof(int), &a, __INT__), parseData(sizeof(double), &b, __DOUBLE__),parseData(strlen(str) + 1, str, __STRING__), __LIST_END__);
    append(&list[1], parseData(sizeof(double), &b, __DOUBLE__));
    head(&list[1], parseData(sizeof(double), &b, __DOUBLE__));

    popLast(&list[0]);


    print(&list[0], 1);
    print(&list[1], 1);
    
    int idx = indexOffset(&list[0], parseData(strlen(str) + 1, str, __STRING__), 3);
    printf("The index of %s is %d\n", str, idx);
    return 0;
}