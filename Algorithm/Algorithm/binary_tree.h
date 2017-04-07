#pragma once
#include <stdbool.h>

typedef char Element;

typedef struct _TreeNode
{
	Element data;
	struct _TreeNode* LeftTree;
	struct _TreeNode* RightTree;
}TreeNode;

TreeNode* CreateTree(TreeNode* bt1, Element item, TreeNode* bt2);
bool IsEmpty(TreeNode* bt);
Element TreeData(TreeNode* bt);
TreeNode* LeftTree(TreeNode* bt);
TreeNode* RightTree(TreeNode* bt);
void DestroyTree(TreeNode* bt);
void traversal_preorder(TreeNode* root);
void traversal_inorder(TreeNode* root);
void traversal_postorder(TreeNode* root);