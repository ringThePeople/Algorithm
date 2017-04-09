//	Chapter4 Trees and Graphs
//	4.2

//Given a directed graph, design an algorithm to find out whether there is a route between two nodes.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Element;
#define MAX 214748364;

typedef struct VertexType
{
	struct VertexType* LikedRight;
	struct VertexType* Next;
	Element data;
	int degree;
	int weight;
	bool processed;
}VERTEX;

typedef struct GraphType
{
	int vertexCnt;
	struct VertexType* VertexLink;
}GRAPH;

typedef struct NodeType
{
	struct NodeType* Down;
	Element data;
}NODE;
typedef struct StackType
{
	NODE* Top;
	int Cnt;
}STACK;

typedef struct QueueType
{
	NODE* Front;
	NODE* Rear;
	int Cnt;
}QUEUE;

GRAPH* graphCreate()
{
	GRAPH* gReturn = NULL;
	gReturn = (GRAPH*)malloc(sizeof(GRAPH));
	gReturn->vertexCnt = 0;
	gReturn->VertexLink = NULL;

	return gReturn;
}

void graphInsertVertex(GRAPH* pGraph, Element data)
{
	if (pGraph->vertexCnt == 0)
	{
		pGraph->VertexLink = (VERTEX*)malloc(sizeof(VERTEX));
		pGraph->VertexLink->data = data;
		pGraph->VertexLink->degree = 0;
		pGraph->VertexLink->LikedRight = NULL;
		pGraph->VertexLink->weight = 0;
		pGraph->VertexLink->processed = false;
		pGraph->VertexLink->Next = NULL;

		pGraph->vertexCnt++;
		return;
	}

	if (pGraph->vertexCnt == 1)
	{
		pGraph->VertexLink->Next = (VERTEX*)malloc(sizeof(VERTEX));
		pGraph->VertexLink->Next->data = data;
		pGraph->VertexLink->Next->degree = 0;
		pGraph->VertexLink->Next->LikedRight = NULL;
		pGraph->VertexLink->Next->weight = 0;
		pGraph->VertexLink->Next->processed = false;
		pGraph->VertexLink->Next->Next = NULL;

		pGraph->vertexCnt++;
		return;
	}
	VERTEX* pVertex = NULL;
	pVertex = pGraph->VertexLink;

	while (pVertex->Next != NULL)
	{
		pVertex = pVertex->Next;
	}
	pVertex->Next = (VERTEX*)malloc(sizeof(VERTEX));
	pVertex->Next->data = data;
	pVertex->Next->degree = 0;
	pVertex->Next->LikedRight = NULL;
	pVertex->Next->weight = 0;
	pVertex->Next->processed = false;
	pVertex->Next->Next = NULL;

	pGraph->vertexCnt++;
	return;

}

void DestroyVertexLink(VERTEX* first)
{
	VERTEX* pVertex = NULL;
	if (first == NULL)
		return;
	else if (first->LikedRight == NULL)
		free(first);
	else
	{
		pVertex = first;
		first = first->LikedRight;
		free(pVertex);
		DestroyVertexLink(first);
	}
}

void graphDestroy(GRAPH* pGraph)
{
	VERTEX* pVertex = NULL;
	VERTEX* pTemp = NULL;
	pVertex = pGraph->VertexLink;
	while (pVertex != NULL)
	{
		DestroyVertexLink(pVertex->LikedRight);
		pTemp = pVertex;
		pVertex = pVertex->Next;
		free(pTemp);
	}
	printf("\n<graphDestroy 완료>\n");
	free(pGraph);
}

VERTEX* findVertex(VERTEX* first, Element findData)
{
	VERTEX* find = NULL;
	find = first;

	while (find != NULL)
	{
		if (find->data == findData)
			return find;
		else
			find = find->Next;
	}
}

void graphRemoveArc(GRAPH* pGraph, Element a, Element b)
{
	VERTEX* R1 = findVertex(pGraph->VertexLink, a);
	VERTEX* R2 = findVertex(pGraph->VertexLink, b);
	VERTEX* tempV = NULL;
	if (R1->LikedRight->data == b)
	{
		tempV = R1->LikedRight;
		R1->LikedRight = tempV->LikedRight;
		free(tempV);
		R1->degree--;
	}
		R2->degree--;

	VERTEX* pVertex = NULL;

	pVertex = R1->LikedRight;
	while (pVertex->LikedRight != NULL)
	{
		if (pVertex->LikedRight->data == b)
		{
			tempV = pVertex->LikedRight;
			pVertex->LikedRight = tempV->LikedRight;
			free(tempV);
			R1->degree--;
			break;
		}
		else
			pVertex = pVertex->LikedRight;
	}
}

void graphInsertArc(GRAPH* pGraph, Element a, Element b, int weight)
{
	VERTEX* aVertex = findVertex(pGraph->VertexLink, a);
	VERTEX* bVertex = findVertex(pGraph->VertexLink, b);
	aVertex->degree++;
	bVertex->degree++;

	if (aVertex->degree == 1)
	{
		aVertex->LikedRight = (VERTEX*)malloc(sizeof(VERTEX));
		aVertex = aVertex->LikedRight;
		aVertex->data = b;
		aVertex->degree = 0;
		aVertex->LikedRight = NULL;
		aVertex->Next = NULL;
		aVertex->processed = false;
		aVertex->weight = weight;
	}
	else
	{
		while (aVertex->LikedRight != NULL)
		{
			aVertex = aVertex->LikedRight;
		}
		aVertex->LikedRight = (VERTEX*)malloc(sizeof(VERTEX));
		aVertex = aVertex->LikedRight;
		aVertex->data = b;
		aVertex->degree = 0;
		aVertex->LikedRight = NULL;
		aVertex->Next = NULL;
		aVertex->processed = false;
		aVertex->weight = weight;
	}
}

void graphRemoveVertex(GRAPH* pGraph, Element removeData)
{
	VERTEX* removeVertex = NULL;
	VERTEX* tempV = NULL;
	removeVertex = pGraph->VertexLink;

	if (pGraph->vertexCnt == 0)
		return;
	if (pGraph->vertexCnt == 1)
	{
		if (pGraph->VertexLink->data == removeData)
		{
			free(pGraph->VertexLink);
			pGraph->vertexCnt--;
			pGraph->VertexLink = NULL;
			return;
		}
		else
		{
			printf("지우려는 Vertex가 없습니다.\n");
			return;
		}
	}
	else
	{
		if (removeVertex->data == removeData)
		{
			if (removeVertex->degree == 0)
			{
				pGraph->VertexLink = removeVertex->Next;
				pGraph->vertexCnt--;
				free(removeVertex);
			}
			else
			{
				printf("지우려는 Vertex가 Empty상태가 아닙니다\n");
				return;
			}
		}
		while (1)
		{

			if (removeVertex->Next->data == removeData)
			{
				if (removeVertex->Next->degree == 0)
				{
					tempV = removeVertex->Next;
					removeVertex->Next = tempV->Next;
					pGraph->vertexCnt--;
					free(tempV);
				}
				else
				{
					printf("지우려는 Vertex가 Empty상태가 아닙니다\n");
					return;
				}
			}
			else
			{
				if (removeVertex->Next == NULL)
				{
					printf("지우려는 Vertex가 없습니다.\n");
					return;
				}
				removeVertex = removeVertex->Next;
			}

		}
	}
}

STACK* createStack()
{
	STACK* sReturn = NULL;
	sReturn = (STACK*)malloc(sizeof(STACK));
	sReturn->Top = NULL;
	sReturn->Cnt = 0;

	return sReturn;
}

Element Pop(STACK* pStack)
{
	Element eReturn = pStack->Top->data;
	NODE* temp = pStack->Top;
	pStack->Top = pStack->Top->Down;
	pStack->Cnt--;
	free(temp);

	return eReturn;
}

void Push(STACK* pStack, Element data)
{
	NODE* NewNode = NULL;
	NewNode = (NODE*)malloc(sizeof(NODE));
	NewNode->data = data;
	NewNode->Down = pStack->Top;
	pStack->Top = NewNode;
	pStack->Cnt++;
	return;
}


QUEUE* createQueue()
{
	QUEUE* qReturn = NULL;
	qReturn = (QUEUE*)malloc(sizeof(QUEUE));
	qReturn->Cnt = 0;
	qReturn->Front = NULL;
	qReturn->Rear = NULL;

	return qReturn;
}

void Enqueue(QUEUE* pQueue, Element data)
{
	NODE* NewNode = NULL;
	NewNode = (NODE*)malloc(sizeof(NODE));
	NewNode->data = data;
	NewNode->Down = NULL;

	if (pQueue->Cnt == 0)
	{
		pQueue->Rear = NewNode;
		pQueue->Front = NewNode;
		pQueue->Cnt++;
		return;
	}
	pQueue->Rear->Down = NewNode;
	pQueue->Rear = NewNode;

	pQueue->Cnt++;
}

Element Dequeue(QUEUE* pQueue)
{
	NODE* tempN = NULL;
	Element Data = 0;
	tempN = pQueue->Front;
	pQueue->Front = tempN->Down;
	Data = tempN->data;

	free(tempN);

	if (pQueue->Cnt == 1)
		pQueue->Rear = NULL;

	pQueue->Cnt--;

	return Data;
}




int findVertexRight(VERTEX* first, Element findData)
{
	VERTEX* find = NULL;
	find = first;

	while (find != NULL)
	{
		if (find->data == findData)
			return find->weight;
		else
			find = find->LikedRight;
	}
	return 0;
}


bool Find_out_route(GRAPH* pGraph, Element Node1, Element Node2)		//I will use BFS(Breadth-first search)
{
	if (pGraph->vertexCnt == 0)
	{
		printf("Graph is Empty, Find_out_route Error\n");
		return false;
	}
	QUEUE* pQueue = createQueue();
	VERTEX* pVertex = NULL;
	Element Data = 0;
	Enqueue(pQueue, Node1);

	while (pQueue->Cnt != 0)
	{
		Data = Dequeue(pQueue);
		if (Data == Node2)
		{
			printf("There is route between Node %c and Node %c\n", Node1, Node2);
			return true;
		}

		pVertex = findVertex(pGraph->VertexLink, Data);
		if (pVertex->processed == false)
		{
			pVertex->processed = true;
			while (pVertex != NULL)
			{
				Enqueue(pQueue, pVertex->data);
				pVertex = pVertex->LikedRight;
			}
		}
		else
			continue;
	}
	pVertex = pGraph->VertexLink;
	while (pVertex != NULL)
	{
		pVertex->processed = false;
		pVertex = pVertex->Next;
	}
	printf("There is not route between %c and Node %c\n", Node1, Node2);
	return false;

	free(pQueue);
}


int main()
{
	GRAPH* pGraph = NULL;
	pGraph = graphCreate();

	graphInsertVertex(pGraph, 'A');
	graphInsertVertex(pGraph, 'B');
	graphInsertVertex(pGraph, 'C');
	graphInsertVertex(pGraph, 'D');
	graphInsertVertex(pGraph, 'E');
	graphInsertVertex(pGraph, 'F');

	graphInsertArc(pGraph, 'A', 'B', 523);
	graphInsertArc(pGraph, 'A', 'C', 345);
	graphInsertArc(pGraph, 'B', 'C', 200);
	graphInsertArc(pGraph, 'B', 'D', 548);
	graphInsertArc(pGraph, 'C', 'D', 360);
	graphInsertArc(pGraph, 'C', 'E', 467);
	graphInsertArc(pGraph, 'D', 'E', 245);
	graphInsertArc(pGraph, 'D', 'F', 320);
	graphInsertArc(pGraph, 'E', 'F', 555);

	Find_out_route(pGraph, 'A', 'F');
	Find_out_route(pGraph, 'E', 'B');
//     →B	 →  D	→F
// A	 ↓	 ↗ ↓	↗  
//     →C   →  E

	graphDestroy(pGraph);
}