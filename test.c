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
    char character = 'b';
    char *C = "Hello Word!";
    char arr[12] = "oaj";
    double c = 6.7, c1, c2;
    struct new_data test;
    test.a = 10;
    test.d = 3.14;
    test.c = "test string";


    makeList(&my_list, dataOf(&b), dataOf(arr), dataOf(&c), __MAKE_END);

    print(&my_list, 1);
    return 0;
}