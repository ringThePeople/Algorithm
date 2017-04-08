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
