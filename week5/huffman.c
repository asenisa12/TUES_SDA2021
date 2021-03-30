#include <stdio.h>
#include <stdlib.h>



struct tree_node_t
{
    char letter;
    int frequency;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

struct queue_node_t
{
    struct tree_node_t* node;
    struct queue_node_t *next;
};

struct queue_t
{
    struct queue_node_t *head;
    struct queue_node_t *tail;
    int size;
};


struct tree_node_t* q_pop(struct queue_t* queue)
{
    struct tree_node_t* node = NULL;
    
    if(queue->head != NULL)
    {
        node = queue->head->node;
        struct queue_node_t* next = queue->head->next;
        free(queue->head);
        queue->head = next;
        if(queue->head == NULL)
        {
            queue->tail = NULL;
        }
        queue->size--;
    }

    return node;
}

void q_push(struct queue_t* queue, struct tree_node_t* t_node)
{

    struct queue_node_t *new_q_node = malloc(sizeof(struct queue_node_t));
    new_q_node->next = NULL;
    new_q_node->node = t_node;
    
    queue->size++;
    if(queue->tail == NULL)
    {
        queue->tail = queue->head = new_q_node;
        return;
    }
    queue->tail->next = new_q_node;
    queue->tail = queue->tail->next;
}

struct tree_node_t* create_tree_node(char letter, int frequency)
{
    struct tree_node_t* node = malloc(sizeof(struct tree_node_t));
    
    node->left = node->right = NULL;
    node->letter = letter;
    node->frequency = frequency;

    return node;
}


void print_tree(struct tree_node_t *root, int level)
{
    if(root == NULL)
    {
        return;
    }

    print_tree(root->left, level + 1);


    int i = 0;
    for(; i<level*2; i++)
        printf(" ");
    printf("%c %d\n", root->letter, root->frequency);

    print_tree(root->right, level + 1);

}


struct tree_node_t* create_huffman_tree(struct queue_t* q1, struct queue_t* q2)
{
    struct tree_node_t *root;
    struct queue_t *q_cur = NULL, *q_other;
    do
    {
        if(q1->size > 0)
        {
            q_cur = q1;
            q_other = q2;
        }
        else
        {
            q_cur = q2;
            q_other = q1;
        }

        if(q_cur->size == 1)
        {
            root = q_pop(q_cur);
        }

        while(q_cur->size > 0){
            struct tree_node_t *t_node =  create_tree_node('\0', 0);

            t_node->left = q_pop(q_cur);
            t_node->right = q_pop(q_cur);

            t_node->frequency = t_node->left->frequency;
            if(t_node->right != NULL)
                t_node->frequency += t_node->right->frequency;
            q_push(q_other, t_node);
        }
        
    }while(q_other->size > 0);
    
    return root;
}


void print_codes(struct tree_node_t *root, short bits[], int bits_count)
{

    if(root->left != NULL)
    {
        bits[bits_count] = 0;
        print_codes(root->left, bits, bits_count+1);
    }
    if(root->right != NULL)
    {
        bits[bits_count] = 1;
        print_codes(root->right, bits, bits_count+1);
    }

    if(root->left == NULL && root->right == NULL)
    {
        printf("letter:%c frequency:%d code:", root->letter, root->frequency);
        for(size_t i = 0; i < bits_count; i++)
        {
            printf("%d", bits[i]);
        }
        printf("\n");
    }

}


int main()
{
    struct queue_t q1 = {NULL, NULL, 0};
    struct queue_t q2 = {NULL, NULL, 0};

    int freq[] = {2,4,6,7,8,10, 11};
    char letters[] = {'v','g','d','a','c','o', 'b'};

    for(size_t i = 0; i < 7; i++)
    {
        q_push(&q1, create_tree_node(letters[i],freq[i]));
    }
    
    
    struct tree_node_t *root = create_huffman_tree(&q1, &q2);
    print_tree(root,0);
    short bits[100];
    print_codes(root, bits, 0);
    while(q1.head != NULL){
        struct tree_node_t *tn = q_pop(&q1);

        printf("-%c\n", tn->letter);
        printf("s:%d\n", q1.size);
        free(tn);
    }
    

}