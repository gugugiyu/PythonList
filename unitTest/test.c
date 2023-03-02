#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../lib/PythonListReplication.h"
#include "../lib/PythonTupleReplication.h"

int cmpfunc(const data* a, const data* b){
  float fa = *(const float*) a->data;
  float fb = *(const float*) b->data;
  return (fa > fb) - (fa < fb);
}


int main(){
  list* my_list = NULL;
  tuple* my_tuple = NULL;

  makeList(&my_list, dataOf_l(3.24F), dataOf_l(2.F), dataOf_l(2.45F), dataOf_l(2.45F), dataOf_l("b"), dataOf_l(-13.3F), dataOf_l(2.45F),__MAKE_END);

  makeTuple(&my_tuple, 3, dataOf("Tuple data type!"), dataOf_l(1), dataOf_l(2.32));

  append(&my_list, dataOf_l("Added"));

  append(&my_list, dataOf(my_tuple));

  int at = indexTuple(&my_tuple, dataOf_l(2.32));

  printf("Found at: %d\n", at);

  //popLast(&my_list);

  sort(&my_list, cmpfunc);

  append(&my_list, dataOf_l(2.45));

  int total = count(&my_list, dataOf_l(2.45F));

  print(&my_list, 1);

  printf("Replacing the tuple with its index of 2.32!\n");

  modifyIndex(&my_list, dataOf(&at), 1);

  print(&my_list, 1);

  return 0;
}