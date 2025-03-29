#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct edge
{
    int dest;
    int weight;
} Edge;

typedef struct adjlist
{
    int deg;
    Edge *arr;
} AdjList;

typedef struct vertex
{
    int key;
    int parent;
    int idx;
} Node;

typedef struct graph
{
    int numVertices;
    Node *vertices;
    AdjList *adjList;
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

void heapDecreaseKey(Node *arr, int i, int newKey, int heapSize, int idx)
{
    if (idx < 0)
    {
        printf("Underflow\n");
        return;
    }

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

void printQueue(Node *queue, int idx)
{
    int i;
    for (i = 0; i < idx; i++)
    {
        printf("(%d | %d) ", queue[i].idx, queue[i].key);
    }
    printf("\n");
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
    graph->adjList = (AdjList *)malloc(numVertices * sizeof(AdjList));
    graph->vertices = (Node *)malloc(numVertices * sizeof(Node));

    if (!graph->adjList || !graph->vertices)
    {
        printf("Memory allocation failed for graph components\n");
        exit(1);
    }

    int i;
    for (i = 0; i < numVertices; i++)
    {
        graph->adjList[i].arr = (Edge *)malloc(numVertices * sizeof(Edge));
    }

    // Graph initialization
    for (i = 0; i < numVertices; i++)
    {
        graph->vertices[i].key = 9999;
        graph->vertices[i].parent = -1;
        graph->vertices[i].idx = i;
        graph->adjList[i].deg = 0;
    }

    return graph;
}

void readGraphFromFile(Graph *graph, char *fileName)
{
    FILE *file = fopen(fileName, "r");
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

        graph->adjList[vertex].deg = degree;
        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);

            if (neighbor < 0 || neighbor >= graph->numVertices)
            {
                printf("Invalid neighbor index: %d\n", neighbor);
                continue;
            }

            graph->adjList[vertex].arr[i].dest = neighbor;
            graph->adjList[vertex].arr[i].weight = weight;
        }
    }

    fclose(file);
}

void relax(Graph *graph, int u, int v, Node *queue, int idx)
{
    int wt, i, j = 0;
    for (i = 0; i < graph->adjList[u].deg; i++)
    {
        if (graph->adjList[u].arr[i].dest == v)
            wt = graph->adjList[u].arr[i].weight;
    }

    for (i = 0; i < graph->numVertices; i++)
    {
        if (v == queue[i].idx)
            j = i;
    }

    if (graph->vertices[v].key > graph->vertices[u].key + wt)
    {
        graph->vertices[v].key = graph->vertices[u].key + wt;
        graph->vertices[v].parent = u;
        heapDecreaseKey(queue, j, graph->vertices[u].key + wt, graph->numVertices, idx);
    }
}

void dijkstra(Graph *graph, Node *queue, int *idx, int s)
{
    graph->vertices[s].key = 0;
    int i, j, v;
    Node u;
    for (i = 0; i < graph->numVertices; i++)
    {
        enqueue(queue, graph->numVertices, idx, graph->vertices[i]);
    }

    printf("Initally the queue:\n");
    printQueue(queue, (*idx));

    while ((*idx) != -1) // Empty
    {
        u = dequeue(queue, graph->numVertices, idx);
        for (j = 0; j < graph->adjList[u.idx].deg; j++)
        {
            v = graph->adjList[u.idx].arr[j].dest;
            relax(graph, u.idx, v, queue, (*idx));
            printQueue(queue, (*idx));
        }
    }
}

void printGraph(Graph *graph)
{
    int v, j, wt, p, key, dest;
    printf("Vertex\t\t(Destination | Weight | Key | Parent)\n");
    for (v = 0; v < graph->numVertices; v++)
    {
        printf("%d:\t", v);
        for (j = 0; j < graph->adjList[v].deg; j++)
        {
            dest = graph->adjList[v].arr[j].dest;
            wt = graph->adjList[v].arr[j].weight;
            key = graph->vertices[v].key;
            p = graph->vertices[v].parent;

            printf("(%d | %d | %d | %d)\t", dest, wt, key, p);
        }
        printf("\n");
    }
    printf("\n");
}

void printDistance(Graph *graph)
{
    int v;
    printf("Vertex\tDistance\n");
    for (v = 0; v < graph->numVertices; v++)
    {
        printf("%d\t\t%d\n", v, graph->vertices[v].key);
    }
    printf("\n");
}

int printPath(Graph *graph, int src, int dest)
{
    if (src == dest)
    {
        printf("%d ", dest);
        return 0;
    }

    if (graph->vertices[dest].parent == -1)
    {
        printf("No path exists.\n");
        return -1;
    }

    int parent = graph->vertices[dest].parent;
    int weight = 0, i;

    for (i = 0; i < graph->adjList[parent].deg; i++)
    {
        if (graph->adjList[parent].arr[i].dest == dest)
        {
            weight = graph->adjList[parent].arr[i].weight;
            break;
        }
    }

    int totalCost = printPath(graph, src, parent);
    if (totalCost == -1)
        return -1;

    printf("-> %d ", dest);
    return totalCost + weight;
}

int main()
{
    int n, i = -1, s;
    char *file = (char *)malloc(MAX * sizeof(char));

    printf("Enter Input File Name\n");
    scanf("%s", file);
    printf("Enter no. of vertices\n");
    scanf("%d", &n);
    Graph *graph = createGraph(n);
    readGraphFromFile(graph, file);
    Node *queue = (Node *)malloc(n * sizeof(Node));

    printf("\nThe Graph\n");
    printGraph(graph);

    printf("Enter source index\n");
    scanf("%d", &s);
    dijkstra(graph, queue, &i, s);
    printf("\nAfter Dijkstra -> Distance from Src. vertex %d:\n", s);
    printDistance(graph);

    int src, dest;
    printf("Enter source & destination\n");
    scanf("%d%d", &src, &dest);
    int cost = printPath(graph, src, dest);
    printf(" : Path Cost = %d\n", cost);

    free(queue);
    free(file);
    free(graph);
    return 0;
}