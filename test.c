#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./lib/PythonListReplication.h"

int cmpfunc(const data* a, const data* b){
  float fa = *(const float*) a->data;
  float fb = *(const float*) b->data;
  return (fa > fb) - (fa < fb);
}

int main(){
  list* my_list = NULL;

  makeList(&my_list, dataOf_l(1.F), dataOf_l(8.F), dataOf_l(3.F), dataOf_l(2.6F), dataOf_l(2.4F), __MAKE_END);

  sort(&my_list, cmpfunc);

  print(&my_list, 1);

  list* copy_list = clone(my_list, 0);

  clearList(&my_list);

  print(&copy_list, 1);

  pause();


  return 0;
}