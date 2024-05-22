#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;


    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;


    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");


    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

int Connected (Graph g)
{
    Stack stack;
    stack.head = NULL;
    stack.size = 0;
    int i, j, unvisitedIndicator, currentVertex;
    
    g.visited[0] = 1;
    push(&stack, 1);
    // DFS Traversal
    while (!isEmptyStack(stack))
    {
        currentVertex = peek(stack);
        unvisitedIndicator = 0;
        for (i = 0; i < g.V; i++)
        {
            if (g.matrix[currentVertex-1][i] == 1 && g.visited[i] != 1)
            {
                g.visited[i] = 1;
                push(&stack, i+1);
                unvisitedIndicator = 1;
                break;
            }
        }
        if (unvisitedIndicator == 0)
        {
            pop(&stack);
        }
    }
    for (i = 0; i < g.V; i++)
    {
        if (g.visited[i] != 1)
        {
            return -1;
        }
    }
    removeAllItemsFromStack(&stack); // Clear stack for next DFS

    // Reverse the damn graph
    Graph reversedGraph;
    reversedGraph.E = g.E;
    reversedGraph.V = g.V;
    reversedGraph.matrix = (int **)malloc(reversedGraph.V*sizeof(int *));
    for(i=0;i<g.V;i++){
        reversedGraph.matrix[i] = (int *)malloc(reversedGraph.V*sizeof(int));
    }
    for(i=0;i<reversedGraph.V;i++){
        reversedGraph.visited[i] = 0;
    }
    for (i = 0; i < reversedGraph.V; i++)
    {
        for (j = 0; j < reversedGraph.V; j++)
        {
            reversedGraph.matrix[i][j] = g.matrix[j][i];
        }
    }
    // DFS on reversedGraph
    reversedGraph.visited[0] = 1;
    push(&stack, 1);
    while (!isEmptyStack(stack))
    {
        unvisitedIndicator = 0;
        currentVertex = peek(stack);
        for (i = 0; i < reversedGraph.V; i++)
        {
            if (reversedGraph.matrix[currentVertex-1][i] == 1 && reversedGraph.visited[i] != 1)
            {
                reversedGraph.visited[i] = 1;
                push(&stack, i+1);
                unvisitedIndicator = 1;
                break;
            }
        }
        if (unvisitedIndicator == 0)
        {
            pop(&stack);
        }
    }

    for (i = 0; i < reversedGraph.V; i++)
    {
        if (reversedGraph.visited[i] != 1)
        {
            return -1; // Not strongly connected
        }
    }
    return 1; // Strongly connected
}


void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}