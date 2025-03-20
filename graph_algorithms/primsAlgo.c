#include <stdio.h>
#include <stdlib.h>

typedef struct vertex
{
    int key;
    int parent;
    int idx;
} Node;

typedef struct adjArr
{
    int degree;
    Node *vertex;
} AdjArr;

typedef struct graph
{
    int numVertices;
    Node *vertices;
    AdjArr *adjList;
    int **weights;
} Graph;

void minHeapify(Node *arr, int i, int size)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int min;
    Node t;

    if (l < size && arr[l].key < arr[i].key)
        min = l;
    else
        min = i;

    if (r < size && arr[r].key < arr[min].key)
        min = r;

    if (min != i)
    {
        t = arr[i];
        arr[i] = arr[min];
        arr[min] = t;
        minHeapify(arr, min, size);
    }
}

void enqueue(Node *arr, int size, int *i, Node x)
{
    (*i)++;
    if ((*i) >= size)
    {
        printf("Overflow\n");
        (*i)--;
        return;
    }

    arr[*i] = x;
    int child = *i;
    int parent = (child - 1) / 2;
    Node temp;

    while (child > 0 && arr[parent].key > arr[child].key)
    {
        temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

Node dequeue(Node *arr, int size, int *i)
{
    if ((*i) < 0)
    {
        printf("Underflow\n");
        Node emptyNode = {9999, -1, -1};
        return emptyNode;
    }
    Node min = arr[0];
    arr[0] = arr[(*i)];
    (*i)--;
    minHeapify(arr, 0, (*i) + 1);

    printf("Dequeued %d with key = %d\n", min.idx, min.key);
    return min;
}

void heapDecreaseKey(Node *arr, int i, int newKey, int heapSize)
{
    if (i < 0 || i > heapSize - 1)
    {
        printf("Invalid Index\n");
        return;
    }

    if (newKey > arr[i].key)
    {
        printf("New key is larger than the current key! Invalid operation.\n");
        return;
    }

    arr[i].key = newKey;

    int child = i;
    int parent = (child - 1) / 2;
    Node temp;
    while (child > 0 && arr[parent].key > arr[child].key)
    {
        temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

int isInQueue(Node *arr, int size, int idx)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i].idx == idx)
            return 1;
    }

    return 0;
}

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory allocation failed for graph\n");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->adjList = (AdjArr *)malloc(numVertices * sizeof(AdjArr));
    graph->vertices = (Node *)malloc(numVertices * sizeof(Node));
    graph->weights = (int **)malloc(numVertices * sizeof(int *));

    if (!graph->adjList || !graph->vertices || !graph->weights)
    {
        printf("Memory allocation failed for graph components\n");
        exit(1);
    }

    for (int i = 0; i < numVertices; i++)
    {
        graph->weights[i] = (int *)malloc(numVertices * sizeof(int));
        if (!graph->weights[i])
        {
            printf("Memory allocation failed for weights\n");
            exit(1);
        }
    }

    // Graph initialization
    for (int i = 0; i < numVertices; i++)
    {
        graph->vertices[i].key = 9999;
        graph->vertices[i].parent = -1;
        graph->vertices[i].idx = i;
        graph->adjList[i].degree = 0;
        graph->adjList[i].vertex = (Node *)malloc(numVertices * sizeof(Node));
        if (!graph->adjList[i].vertex)
        {
            printf("Memory allocation failed for adjacency list\n");
            exit(1);
        }

        for (int j = 0; j < numVertices; j++)
        {
            graph->weights[i][j] = 0;
            graph->adjList[i].vertex[j].key = 9999;
            graph->adjList[i].vertex[j].parent = -1;
        }
    }

    return graph;
}

void readGraphFromFile(Graph *graph)
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        printf("Error opening input file!\n");
        exit(1);
    }

    int vertex, degree, i, neighbor, weight;
    while (fscanf(file, "%d %d", &vertex, &degree) != EOF)
    {
        if (vertex < 0 || vertex >= graph->numVertices)
        {
            printf("Invalid vertex index: %d\n", vertex);
            continue;
        }

        graph->adjList[vertex].degree = degree;
        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);

            if (neighbor < 0 || neighbor >= graph->numVertices)
            {
                printf("Invalid neighbor index: %d\n", neighbor);
                continue;
            }

            graph->weights[vertex][neighbor] = weight;
        }
    }

    fclose(file);
}

void prims(Graph *graph, int s, Node *queue, int *idx)
{
    graph->vertices[s].key = 0;
    int i, j;
    Node u, v;
    for (i = 0; i < graph->numVertices; i++)
    {
        enqueue(queue, graph->numVertices, idx, graph->vertices[i]);
    }

    while ((*idx) != -1) // Empty
    {
        u = dequeue(queue, graph->numVertices, idx);
        for (i = 0; i < graph->numVertices; i++)
        {
            if (graph->weights[u.idx][i] != 0)
            {
                if (isInQueue(queue, graph->numVertices, i) && graph->weights[u.idx][i] < graph->vertices[i].key)
                {
                    graph->vertices[i].parent = u.idx;
                    graph->adjList[u.idx].vertex[i].parent = u.idx;
                    graph->vertices[i].key = graph->weights[u.idx][i];
                    graph->adjList[u.idx].vertex[i].key = graph->weights[u.idx][i];
                    heapDecreaseKey(queue, i, graph->weights[u.idx][i], graph->numVertices);
                }
            }
        }
    }
}

void printGraph(Graph *graph)
{
    int v, j, w, p;
    for (v = 0; v < graph->numVertices; v++)
    {
        printf("%d: ", v);
        for (j = 0; j < graph->numVertices; j++)
        {
            w = graph->adjList[v].vertex[j].key;
            p = graph->adjList[v].vertex[j].parent;
            if (graph->weights[v][j] != 0)
            {
                printf("%d/%d/%d ", j, p, w);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printMST(Graph *graph)
{
    int v;
    printf("Vertex\t   Predecessor\t\tKey\n");
    for(v=0; v<graph->numVertices; v++)
    {
        printf("%d\t\t%d\t\t%d\n", graph->vertices[v].idx, graph->vertices[v].parent, graph->vertices[v].key);
    }
    printf("\n");
}

int main()
{
    int n, i = -1, s;
    printf("Enter no. of vertices\n");
    scanf("%d", &n);
    Graph *graph = createGraph(n);
    readGraphFromFile(graph);
    Node *queue = (Node *)malloc(n * sizeof(Node));

    printf("\nThe Graph\n");
    printGraph(graph);

    printf("Enter source index\n");
    scanf("%d", &s);
    prims(graph, s, queue, &i);
    printf("After Prims -> MST\n");
    printMST(graph);
    return 0;
}
