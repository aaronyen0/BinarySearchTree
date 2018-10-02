#pragma once

struct TreeNode{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* BST_NewNode(int value);
struct TreeNode* BST_FindMax(struct TreeNode* node);
void   BST_InsertValue(struct TreeNode **node, int value);
struct TreeNode* BST_DeleteValue(struct TreeNode *node, int value);

void PrintTree(struct TreeNode* node, int level);
