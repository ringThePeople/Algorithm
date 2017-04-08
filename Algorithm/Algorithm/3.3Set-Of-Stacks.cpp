//	Chapter3 Stack and Queues
//	3.3

//	Imagine a(literal) stack of plates.If the stack gets too high, it might topple.Therefore,
//	in real life, we would likely start a new stack when the previous stack exceeds
//	some threshold.Implement a data structure SetOfStacks that mimics this.SetOf -
//	Stacks should be composed of several stacks, and should create a new stack once
//	the previous one exceeds capacity.SetOfStacks.push() and SetOfStacks.pop() should
//	behave identically to a single stack(that is, pop() should return the same values as it
//	would if there were just a single stack).
//	FOLLOW UP
//	Implement a function popAt(int index) which performs a pop operation on a specific
//	sub - stack.



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct NodeType
{
	struct NodeType* pNode;
	Element data;
}Node;

class Stack
{
private:
	struct NodeType* Top;
	int cnt;
public:
	Element Pop();
	bool Push(Element data, int threshold);
	bool isStackFull(int threshold);
	bool isStackEmpty();
};

class SetOfStack
{
private:
	int CntOfSet;
	int threshold;
	Stack** pSet;
public:
	void SetInfo(int threshold);
	Element Pop();
	bool Push(Element data);
};


void SetOfStack::SetInfo(int thresholdInput)
{
	CntOfSet = 0;
	threshold = thresholdInput;
	pSet = NULL;
}


Element SetOfStack::Pop()
{
	if (CntOfSet == 0)
	{
		printf("SetOfStack is Empty, Error SetOfStack.Pop\n");
		return -1;
	}

	Element popData = pSet[CntOfSet - 1]->Pop();
	if (pSet[CntOfSet - 1]->isStackEmpty())
	{
		if (CntOfSet == 1)
		{
			free(*pSet);
			pSet = NULL;
		}
		else
		{
			Stack** newStack = NULL;
			Stack** ppStack = NULL;
			newStack = (Stack**)malloc(sizeof(Stack*)*(CntOfSet - 1));
			for (int i = 0; i < CntOfSet - 1; i++)
				newStack[i] = pSet[i];

			free(pSet[CntOfSet - 1]);
			ppStack = pSet;
			pSet = newStack;
			free(ppStack);
		}
		CntOfSet--;
	}
	return popData;
}


Element Stack::Pop()
{
	if (isStackEmpty())
	{
		printf("Stack is Empty, Error Stack Pop()\n");
		return -1;
	}
	else
	{
		Node* pNode = NULL;
		Element popData;
		popData = Top->data;
		pNode = Top;

		Top = pNode->pNode;
		free(pNode);
		cnt--;
		return popData;
	}
}


bool Stack::Push(Element data, int threshold)
{
	if (isStackFull(threshold))
	{
		printf("Stack is Full, Error Stack Push()\n");
		return false;
	}
	else
	{
		Node* newNode = NULL;
		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = data;
		newNode->pNode = Top;

		Top = newNode;
		cnt++;

		return true;
	}
}


bool Stack::isStackFull(int threshold)
{
	if (cnt < threshold)
		return false;
	else
		return true;
}


bool Stack::isStackEmpty()
{
	if (cnt == 0)
		return true;
	else
		return false;
}
int main()
{



}