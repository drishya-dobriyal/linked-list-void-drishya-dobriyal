#include "linkedlist.h"

int main()
{
  List_ptr list = create_list();
  double *number = malloc(sizeof(Element));
  *number = 1.33;
  insert_at( list, number, 0);
  *number = 2.33;
  insert_at( list, number, 1);
  *number = 3.33;
  insert_at( list, number, 2);
  *number = 4.33;
  insert_at( list, number, 3);
  *number = 5.33;
  insert_at( list, number, 1);
  display_list(list);
  return 0;
}
