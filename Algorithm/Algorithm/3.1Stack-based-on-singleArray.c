//Chapter3 Stack and Queuues
//3.1
//Describe how you could use a single array to implement three stacks.



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int Element;

typedef struct SingleArray
{
	Element data;
	int stack;
}Array;
//stack contain 1,2 or 3  //empty stack == stack =0

//To implement three stacks with single array, 
//Single Arrray has two kinds of Elements

typedef struct StackType
{
	int maxSize;
	int index_Stack1;	//index mean Top of stack
	int index_Stack2;
	int index_Stack3;	
	//It will be great to use array for this time, but just for satisfaction
	//It is unavoidable to use 'switch'

	struct SingleArray* pLink;
}Stack;


Stack* CreateStack(int size)
{
	Stack* sReturn = NULL;
	sReturn = (Stack*)malloc(sizeof(Stack));
	sReturn->maxSize = size;
	sReturn->index_Stack1 = -1;
	sReturn->index_Stack2 = -1;
	sReturn->index_Stack3 = -1;

	sReturn->pLink = (Array*)malloc(sizeof(Array) * size);
	
	int i;
	for (i = 0; i < size; i++)
	{
		sReturn->pLink[i].stack = 0;
		sReturn->pLink[i].data = -1;
	}

	return sReturn;
}

// I will use Circular System to overcome a weakness of Array.

Element Pop(Stack* pStack, int which_Stack)
{
	int index = -1;
	Element dataReturn = 0;

	switch (which_Stack)
	{
	case 1:
		if (pStack->index_Stack1 == -1)			//that stack is empty
			return -1;
		
		index = pStack->index_Stack1;
		break;
	case 2:
		if (pStack->index_Stack2 == -1)
			return -1;
		
		index = pStack->index_Stack2;
		break;
	case 3:
		if (pStack->index_Stack3 == -1)
			return -1;
		
		index = pStack->index_Stack3;
		break;
	default:	//if not 1,2 or 3
		return -1;
	}

	dataReturn = pStack->pLink[index].data;
	pStack->pLink[index].data = -1;
	pStack->pLink[index].stack = 0;

	int i;
	int j;
	for (i = index; i >= 0; i--)
	{
		if (pStack->pLink[i].stack == which_Stack)
		{
			index = i;
			break;
		}

		if (i == 0)
		{
			for (j = pStack->maxSize-1; j > index; j--)
			{
				if (pStack->pLink[j].stack == which_Stack)
				{
					index = j;
					break;
				}
				
				if (j == index + 1)
					index = -1;
			}
		}
	}

	switch (which_Stack)
	{
	case 1:
		pStack->index_Stack1 = index;
		break;
	case 2:
		pStack->index_Stack2 = index;
		break;
	case 3:
		pStack->index_Stack3 = index;
		break;
	default:	//if not 1,2 or 3
		return -1;
	}


	printf("\nPop operation : %d, from Stack : %d\n", dataReturn, which_Stack);
	return dataReturn;
}

bool IsFull(Stack* pStack)
{
	int i;
	for (i = 0; i < pStack->maxSize; i++)
	{
		if (pStack->pLink[i].stack == 0)
			return false;
	}

	return true;
}
bool Push(Stack* pStack, Element dataInput, int which_Stack)
{
	if (IsFull(pStack))
		return false;
	
	int index = -1;
	int cases = 0;
	
	switch (which_Stack)
	{
	case 1:
		if (pStack->index_Stack1 == -1)
			cases = 1;
		else
			index = pStack->index_Stack1;
		break;
	case 2:
		if (pStack->index_Stack2 == -1)
			cases = 1;
		else
			index = pStack->index_Stack2;
		break;
	case 3:
		if (pStack->index_Stack3 == -1)
			cases = 1;
		else
			index = pStack->index_Stack3;
		break;
	default:	//if not 1,2 or 3
		return false;
	}

	/*
	cases == 0
		means that stack has some elements
	cases == 1
		means that stack was empty
	*/
	int i;
	if (cases == 1)
	{
		for (i = 0; i < pStack->maxSize; i++)
		{
			if (pStack->pLink[i].stack == 0)
			{
				pStack->pLink[i].stack = which_Stack;
				pStack->pLink[i].data = dataInput;

				switch (which_Stack)
				{
				case 1:
					pStack->index_Stack1 = i;
					break;
				case 2:
					pStack->index_Stack2 = i; 
					break;
				case 3:
					pStack->index_Stack3 = i;
					break;
				default:	//if not 1,2 or 3
					return false;
				}

				return true;
			}
		}
	}
	else
	{
		for (i = index; i < pStack->maxSize; i++)
		{
			if (pStack->pLink[i].stack == 0)
			{
				pStack->pLink[i].stack = which_Stack;
				pStack->pLink[i].data = dataInput;

				switch (which_Stack)
				{
				case 1:
					pStack->index_Stack1 = i;
					break;
				case 2:
					pStack->index_Stack2 = i;
					break;
				case 3:
					pStack->index_Stack3 = i;
					break;
				default:	//if not 1,2 or 3
					return false;
				}

				return true;
			}

			if (i == (pStack->maxSize) - 1)
			{
				int j;
				for (j = 0; j < index; j++)
				{
					if (pStack->pLink[j].stack == 0)
					{
						pStack->pLink[j].stack = which_Stack;
						pStack->pLink[j].data = dataInput;

						switch (which_Stack)
						{
						case 1:
							pStack->index_Stack1 = j;
							break;
						case 2:
							pStack->index_Stack2 = j;
							break;
						case 3:
							pStack->index_Stack3 = j;
							break;
						default:	//if not 1,2 or 3
							return false;
						}

						return true;
					}
				}
			}
		}
	}
}

void PrintStack(Stack* pStack)
{
	int i;
	printf("Print elements of each stack from top to bottom\n");
	printf("Stack 1 : ");
	for (i = pStack->index_Stack1; i >= 0; i--)
	{
		if (pStack->pLink[i].stack == 1)
			printf("%d ", pStack->pLink[i].data);
	}
	for (i = pStack->maxSize-1; i > pStack->index_Stack1; i--)
	{
		if (pStack->pLink[i].stack == 1)
			printf("%d ", pStack->pLink[i].data);
	}
	printf("\n");

	printf("Stack 2 : ");
	for (i = pStack->index_Stack2; i >= 0; i--)
	{
		if (pStack->pLink[i].stack == 2)
			printf("%d ", pStack->pLink[i].data);
	}
	for (i = pStack->maxSize - 1; i > pStack->index_Stack2; i--)
	{
		if (pStack->pLink[i].stack == 2)
			printf("%d ", pStack->pLink[i].data);
	}
	printf("\n");

	printf("Stack 3 : ");
	for (i = pStack->index_Stack3; i >= 0; i--)
	{
		if (pStack->pLink[i].stack == 3)
			printf("%d ", pStack->pLink[i].data);
	}
	for (i = pStack->maxSize - 1; i > pStack->index_Stack3; i--)
	{
		if (pStack->pLink[i].stack == 3)
			printf("%d ", pStack->pLink[i].data);
	}
	printf("\n");

}


//test each function 
int main()
{
	Stack* pStack = CreateStack(20);
	Push(pStack, 1, 1);
	Push(pStack, 2, 1);
	Push(pStack, 3, 2);
	Push(pStack, 4, 2);
	Push(pStack, 5, 2);
	Push(pStack, 6, 2);
	Push(pStack, 7, 1);
	Push(pStack, 8, 3);
	Push(pStack, 9, 3);
	Push(pStack, 10, 3);
	Push(pStack, 11, 3);

	PrintStack(pStack);

	Pop(pStack, 2);
	PrintStack(pStack);

	Pop(pStack, 2);
	PrintStack(pStack);

	Pop(pStack, 3);
	PrintStack(pStack);

	printf("Push operation %d, Stack : %d\n", 12, 3);
	Push(pStack, 12, 3);
	PrintStack(pStack);

}