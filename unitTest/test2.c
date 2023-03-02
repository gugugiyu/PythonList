#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\lib\PythonListReplication.h"

int main(){
    list* my_list = NULL;

    
    printf("The size of the list is: %d\n", len(&my_list));

    for (int i = 0; i < 10; i++)
        printf("%d\n", indexOf_o(&my_list, NULL, 0));

    for (int j = 0; j < 5; j++)
        popHead(&my_list);

    print(&my_list, 0);
    return 0;
}