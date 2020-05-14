#include "linkedlist.h"

Status clear_list( List_ptr list){
  Node_ptr p_walk = list->first;
  Node_ptr element_ptr = NULL;
  while (p_walk != NULL)
  {
    element_ptr = p_walk;
    p_walk = p_walk->next;
    free(element_ptr);
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return Success;
}

void destroy_list(List_ptr list){
  Node_ptr p_walk = list->first;
  Node_ptr eliminate_ptr = NULL;
  while (p_walk != NULL)
  {
    eliminate_ptr = p_walk;
    p_walk = p_walk->next;
    free(eliminate_ptr);
  }
  free(list);
}

void display_list(List_ptr list){
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    printf("%d\n",*(int *)p_walk->element);
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

Status add_to_start( List_ptr list, Element value) {
  return insert_at(list, value, 0);
}

Status add_to_list( List_ptr list, Element value) {
  return insert_at(list, value, list->length);
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

Status is_equal( Element value1, Element value2){
  return *( int *)value1 == *(int *)value2;
}

Status is_value_present( List_ptr list, Element value, Matcher matcher){
   Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    if((*is_equal)( p_walk->element, value)) return Success;
    p_walk = p_walk->next;
  }
  return Failure;
}

Status add_unique(List_ptr list, Element value, Matcher matcher){
  if(is_value_present(list, value, matcher)) return Failure;
  return insert_at(list,value,list->length);
}

Element remove_from_start(List_ptr list) {
  if(list->first == NULL) return NULL;
  Element pre_element = list->first->element;
  if(list->length == 1)
  {
    list->last = NULL;
    list->first = NULL;
    list->length--;
    return pre_element;
  }
  Node_ptr new_node = list->first->next;
  list->first = new_node;
  list->length--;
  return pre_element;
}

Element remove_from_end(List_ptr list){
  return remove_at(list, list->length - 1);
};
 
Element remove_at(List_ptr list, int position){
  if(list->first == NULL|| position > list->length || position < 0 ) return NULL;
  if( position == 0) return remove_from_start( list );
   
  Node_ptr pre_node = get_node(list, position);
  Node_ptr elimate_node = pre_node->next;
  if( position == list->length - 1) {
    list->last = pre_node;
    list->last->next = NULL;
  }
  else {
    pre_node->next = elimate_node->next;
  };   
  list->length--;
  return elimate_node->element;
}

Element remove_first_occurrence(List_ptr list, Element value, Matcher  matcher){
  Node_ptr p_walk = list->first;
  int pos = 0;
  while (p_walk != NULL)
  {
    if((*matcher)(p_walk->element, value)) return remove_at(list, pos);
    p_walk = p_walk->next;
    pos++;
  }
  return NULL;
}

List_ptr remove_all_occurrences(List_ptr list, Element value, Matcher matcher) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  int pos = 0;
  while ( p_walk != NULL )
  {
    Element new_element= remove_first_occurrence(list, value, matcher);
    if(new_element == NULL) break;
    insert_at(new_list, new_element, pos);
    p_walk = p_walk->next;
    pos += 1;
  }
  return new_list;
}

Element increment( Element value ){
  int *number = malloc(sizeof(Element));
  *number = *(int *)value + 1;
  return number;
}

List_ptr map( List_ptr list, Mapper mapper){
  Node_ptr p_walk = list->first;
  List_ptr new_list = create_list();
  int pos = 0;
  while ( p_walk != NULL)
  {
    Element value = (*mapper)(p_walk->element);
    insert_at( new_list, value, pos);
    p_walk = p_walk->next;
    pos++;
  }
  return new_list;
}

Status is_even( void *value) {
  return *(int *)value % 2 == 0;
}

List_ptr filter( List_ptr list, Predicate predicate){
  Node_ptr p_walk = list->first;
  List_ptr  new_list = create_list();
  while ( p_walk != NULL)
  {
    if((*predicate)(p_walk->element)) add_to_list( new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}

Element sum( Element num1, Element num2){
  int *sum = malloc(sizeof(int));
  *sum = *(int *)num1 + *(int *)num2;
  return sum;
}

Element reduce( List_ptr list,Element context, Reducer reducer ){
  Node_ptr p_walk = list->first;
  while ( p_walk != NULL)
  {
    context = (*reducer)( context, p_walk->element);
    p_walk = p_walk->next;
  }
  return context;
}

void increment_by_one( Element value){
  int *num = malloc(sizeof(Element));
  *num = *(int *)value + 1;
  memcpy(value, num, sizeof(Element));
  free(num);
}

void forEach(List_ptr list, ElementProcessor processor) {
 Node_ptr p_walk = list->first;
  while ( p_walk != NULL)
  {
    (*processor)( p_walk->element);
    p_walk = p_walk->next;
  }
}

List_ptr reverse( List_ptr list){
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_start(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}