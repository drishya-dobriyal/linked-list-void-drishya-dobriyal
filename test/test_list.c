#include <assert.h>
#include <stdio.h>
#include "../linkedlist.h"

void test_add_to_list( void ){
  printf("Testing add_to_list \n");
  List_ptr list = create_list();
  int *number = malloc(sizeof(Element));
  printf("Should add number to list when list is empty\n");
  *number = 1;
  assert(add_to_list(list , number));
  assert(list->length == 1);
  assert(*(int *)list->first->element== 1);
  assert(*(int *)list->last->element== 1);

  printf("Should add the number when list is not empty\n");
  *number = 2;
  add_to_list(list, number);
  *number = 3;
  add_to_list(list, number);
  *number = 4;
  assert(add_to_list(list, number));
  assert(list->length == 4);
  assert(*(int *)list->last->element == 4);

  printf("Test for add_to_list completed\n\n");
}

void test_add_to_start( void ){
  printf("Testing add_to_start \n");
  List_ptr list = create_list();
  int *number = malloc(sizeof(Element));
  printf("Should add number to start when list is empty\n");
  *number = 1;
  assert(add_to_start(list , number));
  assert(list->length == 1);
  assert(*(int *)list->first->element == 1);
  assert(*(int *)list->last->element == 1);

  printf("Should add the number when list is not empty\n");
  *number = 2;
  add_to_start(list, number);
  *number = 3;
  add_to_start(list, number);
  *number = 4;
  assert(add_to_start(list, number));
  assert(*(int *)list->first->element == 4);
  assert(list->length == 4);

  printf("Test for add_to_list completed\n\n");
}

void test_insert_at( void ){
  printf("Testing insert_at \n");
  List_ptr list = create_list();
  int *number = malloc(sizeof(Element));
  printf("Should insert at zero position of list when list  is empty\n");
  *number = 1;
  assert(insert_at(list, number , 0));
  assert(list->length == 1);
  assert(*(int *)list->first->element == 1);
  assert(*(int *)list->last->element== 1);

  printf("Should insert at middle of the list \n");
  *number = 2;
  add_to_list(list, number);
  *number = 3;
  add_to_list(list, number);
  *number = 4;
  assert(insert_at(list, number, 1)); 
  assert(list->length == 4);
  assert(*(int *)list->first->next->element== 4);

  printf("Should insert at last of the list \n");
  *number = 5;
  assert(insert_at(list, number , 4));
  assert(list->length == 5);
  assert(*(int *)list->last->element == 5);
   
  printf("Should not insert at invalid position\n");
  *number = 5;
  assert(!insert_at(list, number , 10));
  assert(list->length == 5);

  printf("Test for insert_at completed\n\n");
}

void test_add_unique( void ){
  printf("Testing add_unique \n");
  List_ptr list = create_list();
  Matcher matcher = &is_equal;
  int *number = malloc(sizeof(Element));
  *number = 1;
  add_unique(list, number, matcher);
  *number = 2;
  add_unique(list, number, matcher);
  *number = 3;
  add_unique(list, number, matcher);

  printf("Should add num at last if num is not present\n");
  *number = 4;
  assert(add_unique(list, number , matcher));
  assert(list->length == 4);
  assert(*(int *)list->last->element == 4);

  printf("Should not add num at last if num is not present\n");
  *number = 1;
  assert(!add_unique(list, number, matcher));
  assert(list->length == 4);
  assert(*(int *)list->last->element == 4);
  printf("Test for add_unique completed\n\n");
}

int main(void){
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_add_unique();
  return  0;
}