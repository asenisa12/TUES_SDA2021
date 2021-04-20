#include <stdio.h>
#include <stdlib.h>


struct node_t
{  
    struct node_t* left; 
    struct node_t* right;
    int data;
};



struct node_t* create_node(int data)
{
    struct node_t* new_node = malloc(sizeof(struct node_t));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}


void add_leaf(struct node_t *root, int data)
{
    if(root->data == data)
    {
        return;
    }

    if(root->data > data)
    {
        if (root->left == NULL) 
        {
            root->left = create_node(data);
        }
        else
        {
            add_leaf(root->left, data);
        }
        
        
    }
    else if(root->data < data)
    {

        if (root->right == NULL) 
        {
            root->right = create_node(data);
        }
        else
        {
            add_leaf(root->right, data);
        }
    }
    
}


void free_tree(struct node_t *root)
{
    if(root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

void printLevel(struct node_t* leaf, int level)
{
    printLevel_helper(leaf, level);
    puts("");
}

void printLevel_helper(struct node_t* leaf, int level)
{
    level--;
    if(level < 0 || leaf == NULL)
    {
        return;
    }

    if(level == 0)
    {
        printf("%d", leaf->data);
    }
    else
    {
        printLevel_helper(leaf->left, level - 1);
        printLevel_helper(leaf->right, level - 1);
    }
    
}



int countPathsWithsum(struct node_t* leaf, int targetSum, int currentSum)
{
    if(leaf == NULL) return 0;

    currentSum += leaf->data;
    int paths_count = 0;
    if(currentSum == targetSum)
    {
        paths_count++;
    }
    else
    {
        paths_count += countPathsWithsum_helper(leaf->left, targetSum, currentSum);
        paths_count += countPathsWithsum_helper(leaf->right, targetSum, currentSum);
    }
    return paths_count;
}


struct node_t* lowest_common_ancestor(struct node_t* n1, struct node_t *n2, struct node_t* root)
{
    if(root == NULL)
    {
        return NULL;
    }

    int min_data = min(n1->data, n2->data);
    int max_data = max(n1->data, n2->data);

    if(root->data > min_data && root->data < max_data)
    {
        return root;
    }
    // if both x and y are smaller than root, LCA exists in left subtree
	else if (root->data > max_data)
    {
		return lowest_common_ancestor(n1, n2, root->left);
    }
	// if both x and y are greater than root, LCA exists in right subtree
	else  if (root->data < min_data)
    {
		return lowest_common_ancestor(n1, n2, root->right);
    }

}

// Task 3
struct node_t* k_smallest_element(struct node_t *root, int k) 
{ 
    struct node_t* nodes_array[100];
    const int len = 100;
    int i = 0;

    struct node_t *current = root; 
  
    while( current != NULL ) 
    { 
        nodes_array[i++] = current;
        current = current->left; 
    } 
  
 
    while( i > 0 ) 
    { 
        current = nodes_array[i--];
        if( --k == 0 ) 
        {
            break; 
        } 
  
        if( current->right ) 
        { 
            current = current->right; 
            while( current ) 
            { 
                nodes_array[i++] = current;
                current = current->left; 
            } 

        } 
    } 
    if(k != 0)
    {
        puts("Wrong parameters");
        return NULL;
    }

    /* node_t having k-th element or NULL node_t */
    return current; 
} 