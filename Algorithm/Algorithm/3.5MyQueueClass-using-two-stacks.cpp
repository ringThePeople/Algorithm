//Chapter3 Stack and Queuues
//3.5
//Implement a MyQueue class which implements a queue using two stacks.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct NodeType
{
	Element data;
	struct NodeType* pNode;
}Node;

class Stack
{
private:
	int cnt;
	struct NodeType* Top;
public:
	void SetInfo();
	void Push(Element dataInput);
	Element Pop();
	bool IsEmpty();
};

class MyQueue
{
private:
	int cnt;
	Stack* Stack1;
	Stack* Stack2;
public:
	void SetInfo();
	void Enqueue(Element dataInput);
	Element Dequeue();
};

void Stack::SetInfo()
{
	cnt = 0;
	Top = NULL;
}

void Stack::Push(Element dataInput)
{
	Node* newNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->data = dataInput;
	newNode->pNode = Top;

	Top = newNode;
	cnt++;
}

bool Stack::IsEmpty()
{
	if (cnt == 0)
		return true;
	else
		return false;
}
Element Stack::Pop()
{
	if (IsEmpty())
		return -1;
	else
	{
		Element dataReturn = 0;
		Node* pNode = NULL;

		dataReturn = Top->data;
		pNode = Top;
		Top = pNode->pNode;

		free(pNode);
		cnt--;

		return dataReturn;
	}
}

void MyQueue::SetInfo()
{
	cnt = 0;
	Stack1 = (Stack*)malloc(sizeof(Stack));
	Stack2 = (Stack*)malloc(sizeof(Stack));

	Stack1->SetInfo();
	Stack2->SetInfo();
}

void MyQueue::Enqueue(Element dataInput)
{
	Stack2->Push(dataInput);
	cnt++;
}

Element MyQueue::Dequeue()
{
	if (cnt == 0)
	{
		printf("Dequeue function Error _ This Queue was Empty\n");
		return -1;
	}

	int dataReturn = 0;
	if (Stack1->IsEmpty())
	{
		while (!(Stack2->IsEmpty()))
		{
			Stack1->Push(Stack2->Pop());
		}
	}

	dataReturn = Stack1->Pop();

	cnt--;
	return dataReturn;
}

int main()
{
	MyQueue mQueue1;
	mQueue1.SetInfo();
	mQueue1.Enqueue(1);
	mQueue1.Enqueue(2);
	mQueue1.Enqueue(3);
	mQueue1.Enqueue(4);
	mQueue1.Enqueue(5);

	int cnt = 1;
	printf("[%d] data :  %d\n", cnt++, mQueue1.Dequeue());
	printf("[%d] data :  %d\n", cnt++, mQueue1.Dequeue());

	mQueue1.Enqueue(6);
	mQueue1.Enqueue(7);

	printf("[%d] data :  %d\n", cnt++, mQueue1.Dequeue());
	printf("[%d] data :  %d\n", cnt++, mQueue1.Dequeue());


	return 0;
}