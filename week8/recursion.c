#include <stdio.h>
#include <stdlib.h>


struct node_t {
  int value;
  struct node_t* next;
  struct node_t* prev;
};

struct list_t {
  struct node_t* head;
  struct node_t* tail;
  int size;

};


void push_back(struct list_t *list, int value)
{

    struct node_t* new_node = malloc(sizeof(struct node_t));

    new_node->value = value;

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




//zad2.1
int num2innum1(int num1, int num2)
{
    if(num1 == 0)
        return 0;
    if(num2 == 0)
        return 1;

    if(num2 % 10 == num1 %10)
        num2 /= 10;

    num2innum1(num1/10, num2);
}


//zad2.2
void help(int *arr, int cnt, int sub_arr_found, int arr_size, int start, int len, int *max_len, int *max_start)
{
    if(cnt < arr_size)
    {
        if(arr[cnt] == arr[cnt - 1])
        {
            if(sub_arr_found == 0)
            {
                sub_arr_found = 1;
                start = cnt - 1;
            }
            len++;

        }
        
        if (arr[cnt] != arr[cnt - 1] || cnt == arr_size - 1)
        {
            if(sub_arr_found == 1 )
            {
                if(len > *max_len)
                {
                    *max_len = len;
                    *max_start = start;
                    len = 1;
                }
                sub_arr_found = 0;
            }
        }

        help(arr, cnt+1, sub_arr_found, arr_size, start, len, max_len, max_start);
    }

}


void longest_subarray(int *arr, int arr_size)
{
    int max_start = 0;
    int max_len = 1;

    help(arr, 1, 0, arr_size, 0, 1, &max_len, &max_start);

    printf("max_start:%d, max_len:%d\n", max_start, max_len);
}



void print_list_rec(struct node_t* head)
{

}

void print_mid(struct node_t* head, struct node_t* tail)
{
    if(head == NULL || tail == NULL)
    {
        return;
    }
    else if(head == tail)
    {
        printf("mid is %d\n", head->value);
    }
    else if(head->next == tail && tail->prev == head)
    {
        printf("no middle elem");
    }
    else
    {
        print_mid(head->next, tail->prev);
    }
    
}




int main()
{
    struct list_t my_list = {NULL, NULL};


    push_back(&my_list, 11);
    push_back(&my_list, 23);
    push_back(&my_list, 33);
    push_back(&my_list, 41);
    push_back(&my_list, 53);
    push_back(&my_list, 61);
    push_back(&my_list, 74);
    push_back(&my_list, 83);


    print_list(&my_list);


    int arr[] = {1,2,2,2,3,3,5,3,5,3};
    longest_subarray(arr,10);

    return 0;
}
