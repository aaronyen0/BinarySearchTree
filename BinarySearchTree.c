#include "stdafx.h"
#include <stdlib.h>
#include "BinarySearchTree.h"


struct TreeNode* BST_NewNode(int value)
{
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct TreeNode* BST_FindMax(struct TreeNode* node)
{
    if(node == NULL) 
	{
		//printf("Root Is NULL\n");
        return NULL;
    }

    if(node->right)
	{
		BST_FindMax(node->right);
	}
	else
	{
		return node;
	}
}

void BST_InsertValue(struct TreeNode **node, int value)
{
	if(*node == NULL)
	{
		//printf("Node Is NULL\n");
		*node = BST_NewNode(value);
	}
	else if(value < (*node)->value)
	{
		BST_InsertValue(&(*(node))->left, value);
	}
	else if(value > (*node)->value)
	{
		BST_InsertValue(&(*(node))->right, value);
	}   
}

struct TreeNode* BST_DeleteValue(struct TreeNode *node, int value)
{
    struct TreeNode *temp;
    if(node == NULL) 
	{
        //printf("Value Not Found\n");
    }
    else if(value < node->value) {
        node->left = BST_DeleteValue(node->left, value);
    }
            
    else if(value > node->value) {
        node->right = BST_DeleteValue(node->right, value);
    }
    else // data == node->data
    {
        if(node->right && node->left)
        {
            temp = BST_FindMax(node->left);
            node->value = temp->value;
            node->left = BST_DeleteValue(node->left, temp->value);
        }
        else//only 1 or 0 children
        {
            temp = node;
            if(node->left == NULL)
			{
                node = node->right;
			}
            else if(node->right == NULL)
			{
                node = node->left;
			}
			//printf("Value = %d\n", temp->value);
            free(temp);
        }
    }
    return node;
}


void PrintTree(struct TreeNode* node, int level){
	for(int i = 0; i < level; ++i){
		printf("%s", "|  ");
	}

	if(node == NULL){
		printf("%s", "+- ");
		printf("<nil>\n");
		return;
	}else{
		printf("%s", "+- ");
		printf("<Lv%d, %d>\n", level, node->value);
		PrintTree(node->left, level + 1);
		PrintTree(node->right, level + 1);
		return;
	}
}
