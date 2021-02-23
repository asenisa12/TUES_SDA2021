#include <stdio.h>
#include <stdlib.h>


struct node_t {
  int value;
  struct node_t* next;
  struct node_t* prev;
  struct node_t* skip;
};

struct list_t {
  struct node_t* head;
  struct node_t* tail;
  int size;
  int skip_size;

};


void push_back(struct list_t *list, int value)
{

    struct node_t* new_node = malloc(sizeof(struct node_t));

    new_node->value = value;
    new_node->next = NULL;
    new_node->skip = NULL;

    if(!list->head)
    {
        list->head = new_node;
        new_node->prev = NULL;
    }
    else
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }
    
    list->tail = new_node;
    list->size++;
    int i;
    struct node_t* current = new_node;
    for(i = 0; i < list->skip_size && current != NULL; i++)
    {
      current = current->next;
    }
    if(current!=NULL)
      current->skip = new_node;
    
}


int search(int value, struct list_t* list)
{
  struct node_t *current = list->head;
  while(current != NULL)
  {
    if(current->value == value)
      return 1;

    struct node_t *skip = current->skip;
    
    if(skip == NULL || skip->value > value)
    {

      while(current != skip)
      {
        if(current->value == value)
          return 1;

        current = current->next;
      }

    }

    current = skip;
  }
}

struct node_t* get_min(struct node_t* current)
{
  struct node_t* min_node = current;
  while(current != NULL){
    if(current->value < min_node->value)
    {
      min_node = current;
    }
    current = current->next;
  }

  return min_node;
  

}

void swap_int2(int num1, int num2)
{
  int tmp = num1;
  num1 = num2;
  num2 = tmp;
}

void swap_int(int* num1, int* num2)
{
  int tmp = *num1;
  *num1 = *num2;
  *num2 = tmp;
  //int **arr2D = malloc(sizof(int*)*N)
  //for
    //arr2D[i] = malloc(sizof(int)*M)
}

void swap_links(struct node_t** node1, struct node_t** node2)
{
  struct node_t* tmp = *node1;
  *node1 = *node2;
  *node2 = tmp;
}

void sort_list(struct list_t* list)
{

  struct node_t* current = list->head;
  while(current->next != NULL)
  {
    struct node_t *min_node = get_min(current);
    if(min_node->value == current->value)
    {
      current = current->next;
      continue;
    }

    if(current->next == min_node)
    {
      current->next = min_node->next;
      min_node->next = current;
      min_node->prev = current->prev;
      current->prev = min_node;
    }
    else
    {
      swap_links(&min_node->next, &current->next);
      swap_links(&min_node->prev, &current->prev);
      
    }
    swap_links(&min_node->skip, &current->skip);
    if(list->tail == min_node)
    {
      list->tail = current;
    }
    else
    {
      current->next->prev = current;
    }
    current->prev->next = current;

    if(list->head == current)
    {
      list->head = min_node;
    }
    else
    {
      min_node->prev->next = min_node;
    }
    min_node->next->prev = min_node;

    current = min_node->next;    

  }
  

}

void print_list(struct list_t* list) {
  struct node_t* curr = list->head;
  int counter = 1;
  //("size == %d\n", list->size);

  while(curr != NULL) {
    printf("[%d] %d\n", counter++, curr->value);
    curr = curr->next;
  }
}


void print_list_rev(struct list_t* list) {
  struct node_t* curr = list->tail;
  int counter = 1;
  //("size == %d\n", list->size);

  while(curr != NULL) {
    printf("[%d] %d\n", counter++, curr->value);
    curr = curr->prev;
  }
}




int main()
{
    struct list_t my_list = {NULL, NULL};
    my_list.skip_size = 3;


    push_back(&my_list, 44);
    push_back(&my_list, 23);
    push_back(&my_list, 33);
    push_back(&my_list, 41);
    push_back(&my_list, 23);
    push_back(&my_list, 41);
    push_back(&my_list, 44);
    push_back(&my_list, 13);
    push_back(&my_list, 11);
    struct node_t* min = get_min(my_list.head);
    printf("min: %d\n", min->value);
    sort_list(&my_list);
    print_list(&my_list);
    puts("");
    print_list_rev(&my_list);
    puts("");
    printf("search %d result: %d\n", 441, search(441, &my_list));
    puts("");
    printf("search %d result: %d\n", 33, search(33, &my_list));

    return 0;
}
