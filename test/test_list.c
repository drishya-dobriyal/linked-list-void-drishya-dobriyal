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
  assert(list->first->element== number);
  assert(list->last->element== number);

  printf("Should add the number when list is not empty\n");
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  assert(add_to_list(list, number2));
  assert(list->length == 2);
  assert(list->last->element == number2);
  destroy_list(list);
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
  assert(list->first->element == number);
  assert(list->last->element == number);

  printf("Should add the number when list is not empty\n");
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_start(list, number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_start(list, number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  assert(add_to_start(list, number4));
  assert(list->first->element == number4);
  assert(list->length == 4);
  destroy_list(list);
  printf("Test for add_to_start completed\n\n");
}

void test_insert_at( void ){
  printf("Testing insert_at\n");
  List_ptr list = create_list();
  int *number = malloc(sizeof(Element));
  printf("Should insert at zero position of list when list  is empty\n");
  *number = 1;
  assert(insert_at(list, number , 0));
  assert(list->length == 1);
  assert(list->first->element == number);
  assert(list->last->element== number);

  printf("Should insert at middle of the list \n");
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list, number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list, number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  assert(insert_at(list, number4, 1)); 
  assert(list->length == 4);
  assert(list->first->next->element== number4);
  
  printf("Should not insert at invalid position\n");
  int *number5 = malloc(sizeof(Element));
  *number5 = 5;
  assert(!insert_at(list, number5 , 10));
  assert(list->length == 4);
  destroy_list(list);
  printf("Test for insert_at completed\n\n");
}

void test_add_unique( void ){
  printf("Testing add_unique \n");
  List_ptr list = create_list();
  Matcher matcher = &is_equal;
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_unique(list, number1, matcher);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_unique(list, number2, matcher);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_unique(list, number3, matcher);

  printf("Should add num at last if num is not present\n");
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  assert(add_unique(list, number4 , matcher));
  assert(list->length == 4);
  assert(list->last->element == number4);

  printf("Should not add num at last if num is not present\n");
  int *number = malloc(sizeof(Element));
  *number = 1;
  assert(!add_unique(list, number, matcher));
  assert(list->length == 4);
  assert(list->last->element == number4);
  destroy_list(list);
  printf("Test for add_unique completed\n\n");
}

void test_remove_at(void) {
  printf("Testing remove_at\n");
  List_ptr list = create_list();
  printf("should fail if the list is empty\n");
  assert(!remove_at(list,1));
  assert(list->first == NULL);
  assert(list->last == NULL);
  assert(list->length == 0);

  int *number1 = malloc(sizeof(Element));
  add_to_list(list, number1);
  int *number2 = malloc(sizeof(Element));
  add_to_list(list, number2);
  int *number3 = malloc(sizeof(Element));
  add_to_list(list, number3);
  int *number4 = malloc(sizeof(Element));
  add_to_list(list, number4);

  printf("should remove the num in starting of list of list\n");
  assert(remove_at(list, 0) == number1);
  assert(list->length == 3);
  assert(list->first->element == number2);

  printf("should remove the num at last of list of list\n");
  assert(remove_at(list,2) == number4);
  assert(list->length == 2);
  assert(list->last->element == number3);

  int *number5 = malloc(sizeof(Element));
  add_to_list(list, number5);
  printf("should remove the num in middle of list\n");
  assert( remove_at(list,1) == number3);
  assert(list->length == 2);
  assert(list->first->next->element == number5);
 
  printf("should fail if invalid position is given\n");
  assert(!remove_at(list,5));
  assert(list->length == 2);
  destroy_list(list);
  printf("Test for remove_at completed\n\n");
};

void test_remove_from_start(void) {
  printf("Testing remove_from_start\n");
  List_ptr list = create_list();
  
  printf("should return if the list is empty\n");
  assert(!remove_from_start(list));
  assert(list->length == 0);

  printf("should remove first num from the list\n");
  int *number = malloc(sizeof(Element));
  add_to_list(list, number);
  assert(remove_from_start(list) == number);
  assert(list->length == 0);
  assert(list->first == NULL);
  assert(list->last == NULL);

  printf("should remove first num from the list when more than one is present\n");
  int *number1 = malloc(sizeof(Element));
  add_to_list(list, number1);
  int *number2 = malloc(sizeof(Element));
  add_to_list(list, number2);
  assert(remove_from_start(list) == number1);
  assert(list->length == 1);
  assert(list->last->element== number2);
  assert(list->first->element == number2);
  
  printf("Test for remove_from_start completed\n\n");
};

void test_remove_from_end(void) {
  printf("Testing remove_from_end\n");
  List_ptr list = create_list();

  printf("should fail if the list is empty\n");
  assert(!remove_from_end(list));
  assert(list->length == 0);

  printf("should remove num from last in the single list\n");
  int *number = malloc(sizeof(Element));
  add_to_list(list, number);
  Element result = remove_from_end(list);
  assert( result == number);
  assert(list->length == 0);
  assert(list->first == NULL);
  assert(list->last == NULL);

  printf("should remove num from last in the list\n");
  int *number1 = malloc(sizeof(Element));
  add_to_list(list, number1);
  int *number2 = malloc(sizeof(Element));
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  add_to_list(list,number3);
  result = remove_from_end(list);
  assert(result == number3);
  assert(list->length == 2);
  assert( list->first->element == number1);
  assert( list->last->element == number2);
  printf("Test for remove_from_end completed\n\n");
};

void test_remove_first_occurrence(void) {
  printf("Testing remove_first_occurrence\n");
  List_ptr list = create_list();
  Matcher matcher = &is_equal;
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  printf("should fail if the list is empty\n");
  assert(!remove_first_occurrence(list, number1, matcher));
  assert(list->length== 0);

  printf("should remove first occurrence in single list\n");
  add_to_list(list, number1);
  assert(remove_first_occurrence(list,number1, matcher) == number1);
  assert(list->first == NULL);
  assert(list->last == NULL);
  assert(list->length == 0);

  printf("should fail if num is not present in the list\n");
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  assert(!remove_first_occurrence(list,number3,matcher));
  assert(list->length == 2);

  printf("should remove the first occurrence of the num from the list\n"); 
  int *number4 = malloc(sizeof(Element));
  *number4 = 2;
  assert( remove_first_occurrence(list,number4, matcher) == number2);
  assert(list->length == 1);
  assert(list->first->element == number1);
  assert(list->last->element == number1);
  printf("Test for remove_first_occurrences completed\n\n");
};

void test_remove_all_occurrence(void){
  printf("Testing remove_all_occurrence\n");
  List_ptr list = create_list();
  Matcher matcher = &is_equal;
  printf("should give empty list if the list is empty\n");
  int *number = malloc(sizeof(int));
  *number = 1;
  List_ptr new_list = remove_all_occurrences(list,number, matcher);
  assert(new_list->first == NULL);
  assert(new_list->last == NULL);
  
  printf("should give empty list if the number  is not present\n");
  int *number1 = malloc(sizeof(int));
  *number1 = 1;
  add_to_list(list, number1);
  int *number2 = malloc(sizeof(int));
  *number2 = 2;
  add_to_list(list, number2);
  int *number3 = malloc(sizeof(int));
  *number3 = 4;
  new_list = remove_all_occurrences(list,number3, matcher);
  assert(new_list->length == 0);
  assert(new_list->first == NULL);
  assert(new_list->last == NULL);

  printf("should give list of the number if number is present\n");
  int *number4 = malloc(sizeof(int));
  *number4 = 1;
  add_to_list(list, number4);
  *number = 1;
  new_list = remove_all_occurrences(list, number, matcher);
  assert(new_list->length == 2);
  assert(new_list->first->element == number1);
  assert(new_list->first->next->element == number4);
  assert(new_list->last->element == number4);
  
  printf("Test for remove_all_occurrence done \n\n");
}

void test_map() {
  printf("Testing map\n");
  List_ptr list = create_list();
  Mapper mapper = &increment;
  printf("should increment the value\n");
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list,number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  add_to_list(list,number4);
  List_ptr new_list = map(list, mapper);
  assert(new_list->length == 4);
  assert(*(int *)new_list->first->element == 2);
  assert(*(int *)new_list->first->next->element == 3);
  assert(*(int *)new_list->last->element == 5);
  printf("Test passed\n\n");
}

void test_filter( void ){
  printf("Testing filter\n");
  List_ptr list = create_list();
  Predicate predicate = &is_even;
  printf("should give even number list\n");
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list,number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  add_to_list(list,number4);
  List_ptr new_list = filter(list, predicate);
  assert(new_list->length == 2);
  assert(*(int *)new_list->first->element == 2);
  assert(*(int *)new_list->last->element == 4);
  printf("Test passed\n\n");
}

void test_reduce( void ){
  printf("Testing reduce\n");
  List_ptr list = create_list();
  Reducer reducer = &sum;
  printf("should give sum of number\n");
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list,number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  add_to_list(list,number4);
  int *init = malloc(sizeof(Element));
  *init = 0;
  Element total = reduce(list,init, reducer);
  assert(*(int *)total == 10);
  printf("Test passed\n\n");
}

void test_for_each(void){
  printf("Testing forEach\n");
  List_ptr list = create_list();
  ElementProcessor processor = &increment_by_one;
  printf("should increment given list\n");
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list,number3);
  int *number4 = malloc(sizeof(Element));
  *number4 = 4;
  add_to_list(list,number4);
  forEach( list ,processor);
  assert(list->first->element == number1);
  assert(list->last->element == number4);
  assert(*(int *)list->first->element == 2);
  assert(*(int *)list->first->next->element == 3);
  assert(*(int *)list->last->element == 5);
  printf("Test passed\n\n");
}

void test_reverse( void ){
  printf("Test reverse\n");
  List_ptr list = create_list();
  int *number1 = malloc(sizeof(Element));
  *number1 = 1;
  add_to_list(list,number1);
  int *number2 = malloc(sizeof(Element));
  *number2 = 2;
  add_to_list(list,number2);
  int *number3 = malloc(sizeof(Element));
  *number3 = 3;
  add_to_list(list,number3);
  List_ptr new_list = reverse(list);
  assert(*( int *)new_list->first->element == 3);
  assert(*( int *)new_list->first->next->element == 2);
  assert(*( int *)new_list->last->element == 1);
  printf("Test completed\n\n");
}

int main(void){
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_add_unique();
  test_remove_at();
  test_remove_from_start();
  test_remove_from_end();
  test_remove_first_occurrence();
  test_remove_all_occurrence();
  test_map();
  test_filter();
  test_reduce();
  test_for_each();
  test_reverse();
  return  0;
}