#include <stdio.h>
#include <stdlib.h>


struct leaf_t
{
    int data;
    struct leaf_t* left;
    struct leaf_t* right;
};

struct tree_t
{
    struct leaf_t *root;
};


struct leaf_t* create_node(int data)
{
    struct leaf_t* new_node = malloc(sizeof(struct leaf_t));
    
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;

}


struct leaf_t* merge(struct leaf_t* t1, struct leaf_t* t2)
{
    if(t1 == NULL)
        return t2;
    if(t2 == NULL)
        return t1;

    t1->data += t2->data;

    merge(t1->left, t2->left);
    merge(t1->right, t2->right);
    free(t2);

    return t1;
}


void print_inorder_helper(struct leaf_t* leaf, int level)
{
    if(leaf == NULL)
    {
        return;
    }

    print_inorder_helper(leaf->left,level+1);
    int i = 0;
    for (;i<level*2; i++)
        printf(" ");
    printf(" %d\n", leaf->data);

    print_inorder_helper(leaf->right, level+1);
}

void print_inorder(struct tree_t* tree)
{
    print_inorder_helper(tree->root, 0);
}




void add_leaf(struct leaf_t *leaf, int value)
{
    if(leaf->data == value)
    {
        return;
    }

    if(leaf->data > value)
    {
        if(leaf->left == NULL)
        {
            leaf->left = create_node(value);
        }
        else
        {
            add_leaf(leaf->left, value);
        }

    }

    if(leaf->data < value)
    {
        if(leaf->right == NULL)
        {
            leaf->right = create_node(value);
        }
        else
        {
            add_leaf(leaf->right, value);
        }
        
    }
}


struct leaf_t* remove_elem(struct leaf_t* t)
{
    struct leaf_t* new = NULL;
    if(t->right == NULL)
    {

        new = t->left;
    }
    else
    {

        struct leaf_t** new_min = &t->right;
        while((*new_min)->left != NULL)
        {
            new_min = &(*new_min)->left;
        }
        new = *new_min;
        *new_min = (*new_min)->right;

        new->left = t->left;
        new->right = t->right; 
    }

    free(t);
    return new;

    
}

struct leaf_t* filter(struct leaf_t* t, int (*filt)(int))
{
    if(t != NULL)
    {
        if(filt(t->data) != 1)
        {
            
            t = remove_elem(t);
            t = filter(t, filt);
            
        }
        else
        {
            t->left = filter(t->left, filt);
            t->right = filter(t->right, filt);
        }
        

    }
    return t;
}

struct leaf_t* arr_to_tree(int* arr, int start, int end)
{
    if(start > end)
        return NULL;
    
    struct leaf_t* leaf = malloc(sizeof(struct leaf_t));
    int mid = (start + end)/2;
    leaf->data = arr[mid];
    leaf->left = arr_to_tree(arr, start, mid - 1);
    leaf->right = arr_to_tree(arr, mid + 1, end);
}

int is_odd(int num)
{
    return num % 2 > 0;
}


int is_even(int num)
{
    return num % 2 == 0;
}

int main()
{
    struct tree_t tree;
    tree.root = create_node(5);
    tree.root->left = create_node(3);
    tree.root->right = create_node(6);
    

    
    add_leaf(tree.root,7);
    add_leaf(tree.root,2);
    add_leaf(tree.root,4);

    tree.root = remove_elem(tree.root);

    puts("");
    print_inorder(&tree);
    tree.root = filter(tree.root, is_even);
    puts("\n");

    print_inorder(&tree);
    puts("");
    struct tree_t tree2;
    tree2.root = create_node(5);
    tree2.root->left = create_node(3);
    tree2.root->right = create_node(6);
    
    add_leaf(tree2.root,2);
    

    print_inorder(&tree);
    struct tree_t tree3;
    tree3.root = merge(tree.root, tree2.root);
    print_inorder(&tree3);
    puts("");
    print_inorder(&tree3);

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    struct tree_t arr_tree;
    arr_tree.root = arr_to_tree(arr, 0, 9);
    puts("");
    print_inorder(&arr_tree);




    return 0;
}