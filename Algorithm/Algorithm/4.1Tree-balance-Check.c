//Chapter4 Trees and Graphs
//4.1
//Implement a function to check if a tree is balanced. For the purposes of this question,
//a balanced tree is defined to be a tree such that no two leaf nodes differ in distance
//from the root by more than one.

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "binary_tree.h"


TreeNode* CreateTree(TreeNode* bt1, Element item, TreeNode* bt2)
{
	TreeNode* tReturn = NULL;
	tReturn = (TreeNode*)malloc(sizeof(TreeNode));
	tReturn->LeftTree = bt1;
	tReturn->RightTree = bt2;
	tReturn->data = item;

	return tReturn;
}


bool IsEmpty(TreeNode* bt)
{
	if (bt == NULL)
	{
		return true;
	}
	else
		return false;
}


Element TreeData(TreeNode* bt)
{
	if (!IsEmpty(bt))
	{
		return bt->data;
	}
	else
	{
		printf("ERROR");
		return 0;
	}
}


TreeNode* LeftTree(TreeNode* bt)
{
	if (!IsEmpty(bt))
	{
		return bt->LeftTree;
	}
	else
	{
		printf("ERROR");
		return NULL;
	}
}


TreeNode* RightTree(TreeNode* bt)
{
	if (!IsEmpty(bt))
	{
		return bt->RightTree;
	}
	else
	{
		printf("ERROR");
		return NULL;
	}
}


void DestroyTree(TreeNode* bt)
{
	if (IsEmpty(bt))
		return;

	DestroyTree(bt->LeftTree);
	DestroyTree(bt->RightTree);

	free(bt);
}


void traversal_preorder(TreeNode* root)
{
	if (IsEmpty(root))
		return;

	printf("%c", root->data);
	traversal_preorder((root->LeftTree));
	traversal_preorder((root->RightTree));

}


void traversal_inorder(TreeNode* root)
{
	if (IsEmpty(root))
		return;

	traversal_inorder((root->LeftTree));
	printf("%c", root->data);
	traversal_inorder((root->RightTree));
}


void traversal_postorder(TreeNode* root)
{
	if (IsEmpty(root))
		return;

	traversal_postorder((root->LeftTree));
	traversal_postorder((root->RightTree));
	printf("%c", root->data);

}


int absoluteValue(int integer)
{
	if (integer >= 0)
		return integer;
	else
		return (integer*(-1));
}


int biggerOne(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	else
		num2;
}
int balancedCheck(TreeNode* pTree)
{
	if (pTree == NULL)
		return -1;
	int left_depth = balancedCheck(pTree->LeftTree) + 1;
	int right_depth = balancedCheck(pTree->RightTree) + 1;

	if (left_depth < 0 || right_depth < 0)
		return -1000;
	
	if (absoluteValue(left_depth - right_depth) > 1)
		return -1000;
	else
		return biggerOne(left_depth, right_depth);
}


bool isTreeBalanced(TreeNode* pTree)
{
	if (balancedCheck(pTree) < 0)
	{
		printf("This Tree is not balanced\n");
		return false;
	}
	else
	{
		printf("This Tree is balanced\n");
		return true;
	}
}


int main()
{
	TreeNode* pNode1 = CreateTree(NULL, 'D', NULL);
	pNode1 = CreateTree(pNode1, 'B', NULL);
	TreeNode* pNode2 = CreateTree(NULL, 'G', NULL);
	pNode2 = CreateTree(pNode2, 'E', NULL);
	TreeNode* pNode3 = CreateTree(NULL, 'F', NULL);
	pNode2 = CreateTree(pNode2, 'C', pNode3);
	pNode1 = CreateTree(pNode1, 'A', pNode2);
	//		A
	//	  B    C
	//	D     E   F
	//		G			//balanced case

	isTreeBalanced(pNode1);

	free(pNode1->RightTree->RightTree);
	pNode1->RightTree->RightTree = NULL;
	//		A
	//	  B    C
	//	D     E   
	//		G			// not balanced case

	isTreeBalanced(pNode1);

	return 0;
}