#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./lib/PythonListReplication.h"

int main(){
  list* my_list[5] = {NULL, NULL, NULL, NULL};

  for (int i = 0; i < 5; i++){
    makeList(&my_list[i], dataOf("Something"), dataOf_l('e'), dataOf_l(1), dataOf_l(3.14F), __MAKE_END);
  } 

  reverseList(&my_list[0]);
  for (int i = 0; i < 5; i++)
    print(&my_list[i], 1);
  
  printf("%d\n", index(&my_list[0], dataOf_l("Something")));
  pause();


  return 0;
}