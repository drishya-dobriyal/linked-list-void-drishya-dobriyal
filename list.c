#include "linkedlist.h"

void display_list(List_ptr list){
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    printf("%f\n",*(double *)p_walk->element);
    p_walk = p_walk->next;
  }
}

Node_ptr create_node(Element element){
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = malloc(sizeof(Element));
  memcpy( new_node->element, element, sizeof(Element));
  new_node->next = NULL;
  return new_node;
}

List_ptr create_list(void){
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_start( List_ptr list, int value) {
  return insert_at(list, value, 0);
}

Status insert_initial_node(List_ptr list, Node_ptr node){
  list->last = node;
  list->first = node;
  list->length++;
  return Success;
}

Status insert_at_start(List_ptr list,Node_ptr new_node) {
  Node_ptr pre_pos = list->first;
  list->first = new_node;
  new_node->next = pre_pos;
  list->length++;
  return Success;
}

Node_ptr get_node( List_ptr list, int position){
  Node_ptr p_walk = list->first;
  int currPosition = 1;
  while ( currPosition != position)
  {
    p_walk = p_walk->next;
    currPosition++;
  }
  return p_walk;
}

Status insert_at(List_ptr list, Element element, int position){
  if( position > list->length || position < 0) return Failure;
  Node_ptr new_node = create_node(element);
  if(list->first == NULL) return insert_initial_node( list, new_node);
  if( position == 0) return insert_at_start(list, new_node);

  Node_ptr p_walk = get_node(list, position);
  Node_ptr pre_pos = p_walk->next;
  p_walk->next =  new_node;
  if( position == list->length) list->last = new_node;
  else new_node->next = pre_pos;   
  list->length++;
  return Success;
}