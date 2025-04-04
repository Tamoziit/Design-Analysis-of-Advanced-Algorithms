/*
    Kruskal using UNION-FIND Path Compressed approach
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

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

typedef struct graph
{
    int numVertices;
    AdjList *adjList;
} Graph;

typedef struct UFNode
{
    int element;
    struct UFNode *set;
    int rank;
    struct UFNode *next;
} UFNode;

typedef struct EdgeRecord
{
    int src;
    int dest;
    int weight;
} EdgeRecord;

Graph *createGraph(int numVertices)
{
    Graph *graph = malloc(sizeof(Graph));
    if (!graph)
    {
        printf("memory allocation error");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->adjList = malloc(numVertices * sizeof(AdjList));
    if (!graph->adjList)
    {
        printf("Component allocation error");
        exit(1);
    }

    for (int i = 0; i < numVertices; i++)
    {
        graph->adjList[i].deg = 0;
        graph->adjList[i].arr = malloc(numVertices * sizeof(Edge));
        if (!graph->adjList[i].arr)
        {
            printf("AdjList allocation error");
            exit(1);
        }
    }

    return graph;
}

void readGraphFromFile(Graph *graph, char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        printf("Error in opening file");
        exit(1);
    }

    int vertex, degree, i, neighbor, weight;
    while (fscanf(file, "%d %d", &vertex, &degree) != EOF)
    {
        if (vertex < 0 || vertex >= graph->numVertices)
            continue;
        graph->adjList[vertex].deg = degree;
        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);
            if (neighbor < 0 || neighbor >= graph->numVertices)
                continue;
            graph->adjList[vertex].arr[i].dest = neighbor;
            graph->adjList[vertex].arr[i].weight = weight;
        }
    }

    fclose(file);
}

/* UNION-FIND */
UFNode *makeSet(int x)
{
    UFNode *node = malloc(sizeof(UFNode));

    if (!node)
    {
        printf("UF allocation error");
        exit(1);
    }

    node->element = x;
    node->next = node;
    node->set = node; // set representative
    node->rank = 0;
    return node;
}

UFNode *findSet(UFNode *x)
{
    if (x->set != x)
        x->set = findSet(x->set);

    return x->set;
}

void unionSets(UFNode *x, UFNode *y)
{
    UFNode *s1 = findSet(x), *s2 = findSet(y);
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
        s1->rank++;
    }
}

/* Kruskal */
void swap(EdgeRecord *a, EdgeRecord *b)
{
    EdgeRecord temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(EdgeRecord arr[], int low, int high)
{
    int pivot = arr[high].weight;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j].weight <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quicksort
void quicksort(EdgeRecord arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

EdgeRecord *kruskalMST(Graph *graph, int *mstSize, int *totalWeight)
{
    int n = graph->numVertices, i, j, edgeCount = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < graph->adjList[i].deg; j++)
        {
            // avoiding edge repetition in undirected G(V, E)
            if (i < graph->adjList[i].arr[j].dest)
                edgeCount++;
        }
    }

    EdgeRecord *edges = malloc(edgeCount * sizeof(EdgeRecord));
    if (!edges)
    {
        printf("Memory alloc error");
        exit(1);
    }

    int k = 0;
    // creating a edge set
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < graph->adjList[i].deg; j++)
        {
            int dest = graph->adjList[i].arr[j].dest;
            if (i < dest)
            {
                edges[k].src = i;
                edges[k].dest = dest;
                edges[k].weight = graph->adjList[i].arr[j].weight;
                k++;
            }
        }
    }

    // sorting edges according to weight
    quicksort(edges, 0, edgeCount - 1);
    EdgeRecord *result = malloc((n - 1) * sizeof(EdgeRecord));
    if (!result)
    {
        printf("Result allocation error");
        exit(1);
    }

    UFNode **ufSets = malloc(n * sizeof(UFNode *));
    if (!ufSets)
    {
        printf("UFSet array alloc error");
        exit(1);
    }

    for (i = 0; i < n; i++)
        ufSets[i] = makeSet(i); // MAKESET creation

    *totalWeight = 0;
    int e = 0, idx = 0;

    // FINDSET comparison
    while (e < n - 1 && idx < edgeCount)
    {
        EdgeRecord curr = edges[idx++];
        printf("Trying to Union %d -- %d, weight = %d\n", curr.src, curr.dest, curr.weight);

        if (findSet(ufSets[curr.src]) != findSet(ufSets[curr.dest]))
        {
            result[e++] = curr;
            *totalWeight += curr.weight;
            unionSets(ufSets[curr.src], ufSets[curr.dest]); // UNION
        }
    }

    *mstSize = e;
    free(edges);
    free(ufSets);
    return result;
}

void printGraph(Graph *graph)
{
    int v, j, wt, dest;
    printf("Vertex\t\t(Destination | Weight)\n");
    for (v = 0; v < graph->numVertices; v++)
    {
        printf("%d:\t", v);
        for (j = 0; j < graph->adjList[v].deg; j++)
        {
            dest = graph->adjList[v].arr[j].dest;
            wt = graph->adjList[v].arr[j].weight;

            printf("(%d | %d)\t", dest, wt);
        }
        printf("\n");
    }
    printf("\n");
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

    printf("\nThe Graph\n");
    printGraph(graph);

    int mstSize, totalWeight;
    printf("Running the Kruskal Algorithm\n");
    EdgeRecord *mst = kruskalMST(graph, &mstSize, &totalWeight);

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