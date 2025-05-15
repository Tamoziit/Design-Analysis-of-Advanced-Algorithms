#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct edge
{
    int dest;
    int weight;
} Edge;

typedef struct adjList
{
    int deg;
    Edge *arr;
} AdjList;

typedef struct graph
{
    int numVertices;
    AdjList *adjList;
} Graph;

typedef struct UFNode
{
    int ele;
    struct UFNode *set;
    int rank;
    struct UFNode *next;
} UFNode;

typedef struct edgeRecord
{
    int src;
    int dest;
    int weight;
} EdgeRecord;

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory alloc. error\n");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->adjList = (AdjList *)malloc(numVertices * sizeof(AdjList));
    if (!graph->adjList)
    {
        printf("Memory alloc. error\n");
        exit(1);
    }

    int i;
    for (i = 0; i < numVertices; i++)
    {
        graph->adjList[i].deg = 0;
        graph->adjList[i].arr = (Edge *)malloc(numVertices * sizeof(Edge));
    }

    return graph;
}

void readFile(Graph *graph)
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        printf("Error in reading file\n");
        exit(1);
    }

    int i, vertex, degree, neighbor, weight;
    while (fscanf(file, "%d %d", &vertex, &degree) != EOF)
    {
        if (vertex < 0 || vertex >= graph->numVertices)
        {
            printf("Invalid src idx\n");
            continue;
        }

        graph->adjList[vertex].deg = degree;
        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);
            if (neighbor < 0 || neighbor > graph->numVertices)
            {
                printf("Invalid dest idx\n");
                continue;
            }

            graph->adjList[vertex].arr[i].dest = neighbor;
            graph->adjList[vertex].arr[i].weight = weight;
        }
    }

    fclose(file);
}

void printGraph(Graph *graph)
{
    int i, j, dest, wt;

    printf("Vertex\t(Dest | Weight)\n");
    for (i = 0; i < graph->numVertices; i++)
    {
        printf("%d\t", i);
        for (j = 0; j < graph->adjList[i].deg; j++)
        {
            dest = graph->adjList[i].arr[j].dest;
            wt = graph->adjList[i].arr[j].weight;
            printf("(%d | %d)\t", dest, wt);
        }
        printf("\n");
    }
    printf("\n");
}

/*UNION-FIND*/
UFNode *makeset(int x)
{
    UFNode *node = (UFNode *)malloc(sizeof(UFNode));
    node->ele = x;
    node->next = node;
    node->set = node;
    node->rank = 0;

    return node;
}

UFNode *findset(UFNode *x)
{
    if (x->set != x)
    {
        x->set = findset(x->set);
    }

    return x->set;
}

void unionSets(UFNode *x, UFNode *y)
{
    UFNode *s1 = findset(x), *s2 = findset(y);
    if (s1 == s2)
        return;

    if (s1->rank < s2->rank)
    {
        s1->set = s2;
    }
    else if (s1->rank > s2->rank)
    {
        s2->set = s1;
    }
    else
    {
        s1->set = s2;
        s2->rank++;
    }
}

/*Sorting*/
void swap(EdgeRecord *a, EdgeRecord *b)
{
    EdgeRecord temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EdgeRecord *arr, int low, int high)
{
    EdgeRecord pivot = arr[high];
    int i = low - 1, j;
    for (j = low; j <= high; j++)
    {
        if (arr[j].weight < pivot.weight)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(EdgeRecord *arr, int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

/*Kruskal*/
EdgeRecord *kruskalMST(Graph *graph, int *totalWeight, int *mstSize)
{
    int n = graph->numVertices, i, j;
    int edgeCount = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < graph->adjList[i].deg; j++)
        {
            if (i < graph->adjList[i].arr[j].dest)
                edgeCount++;
        }
    }

    EdgeRecord *edges = (EdgeRecord *)malloc(edgeCount * sizeof(EdgeRecord));
    int dest, k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < graph->adjList[i].deg; j++)
        {
            dest = graph->adjList[i].arr[j].dest;
            if (i < dest)
            {
                edges[k].src = i;
                edges[k].dest = dest;
                edges[k].weight = graph->adjList[i].arr[j].weight;
                k++;
            }
        }
    }

    quicksort(edges, 0, edgeCount - 1);
    EdgeRecord *result = (EdgeRecord *)malloc((n - 1) * sizeof(EdgeRecord));
    UFNode **ufSets = (UFNode **)malloc(n * sizeof(UFNode *));
    for (i = 0; i < n; i++)
    {
        ufSets[i] = makeset(i);
    }

    int e = 0, idx = 0;
    while (e < n - 1 && idx < edgeCount)
    {
        EdgeRecord curr = edges[idx++];
        printf("Trying to Union %d -- %d, weight = %d\n", curr.src, curr.dest, curr.weight);

        if (findset(ufSets[curr.src]) != findset(ufSets[curr.dest]))
        {
            result[e++] = curr;
            *totalWeight += curr.weight;
            unionSets(ufSets[curr.src], ufSets[curr.dest]);
        }
    }

    *mstSize = e;
    free(edges);
    free(ufSets);
    return result;
}

int main()
{
    Graph *graph = NULL;
    int numVertices, i = -1;

    printf("Enter no. of vertices\n");
    scanf("%d", &numVertices);
    graph = createGraph(numVertices);
    readFile(graph);
    printGraph(graph);

    int mstSize = 0, totalWeight = 0;
    printf("Running the Kruskal Algorithm\n");
    EdgeRecord *mst = kruskalMST(graph, &totalWeight, &mstSize);

    printf("\nEdges in the MST:\n");
    for (i = 0; i < mstSize; i++)
    {
        printf("%d -- %d  weight: %d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
    printf("Total weight of MST: %d\n", totalWeight);

    free(mst);
    for (i = 0; i < graph->numVertices; i++)
    {
        free(graph->adjList[i].arr);
    }
    free(graph->adjList);
    free(graph);

    return 0;
}