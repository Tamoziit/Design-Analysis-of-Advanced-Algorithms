#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 50

typedef struct graph
{
    int numVertices;
    int **dist;
    int **pi;
} Graph;

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory allocation failed for graph\n");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->dist = (int **)malloc(numVertices * sizeof(int *));
    graph->pi = (int **)malloc(numVertices * sizeof(int *));

    if (!graph->dist || !graph->pi)
    {
        printf("Memory allocation failed for graph components\n");
        exit(1);
    }

    int i, j;
    for (i = 0; i < numVertices; i++)
    {
        graph->dist[i] = (int *)malloc(numVertices * sizeof(int));
        graph->pi[i] = (int *)malloc(numVertices * sizeof(int));
    }

    // Graph initialization
    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
        {
            if (i == j)
            {
                graph->dist[i][j] = 0;
            }
            else
            {
                graph->dist[i][j] = INT_MAX;
            }

            graph->pi[i][j] = -1;
        }
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

        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);

            if (neighbor < 0 || neighbor >= graph->numVertices)
            {
                printf("Invalid neighbor index: %d\n", neighbor);
                continue;
            }

            graph->dist[vertex][neighbor] = weight;
            graph->pi[vertex][neighbor] = vertex;
        }
    }

    fclose(file);
}

void printDistances(Graph *graph)
{
    printf("\nShortest Distance Matrix (d[i][j]):\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", graph->dist[i][j]);
        }
        printf("\n");
    }
}

void printPredecessors(Graph *graph)
{
    printf("\nPredecessor Matrix (π[i][j]):\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->pi[i][j] == -1)
                printf("nil\t");
            else
                printf("%d\t", graph->pi[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(Graph *graph)
{
    int i, j, k, n = graph->numVertices;

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (graph->dist[i][k] == INT_MAX || graph->dist[k][j] == INT_MAX)
                    continue;
                else if ((graph->dist[i][k] + graph->dist[k][j]) < graph->dist[i][j])
                {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                    graph->pi[i][j] = graph->pi[k][j];
                }
            }
        }

        printDistances(graph);
        printPredecessors(graph);
    }
}

void printPath(Graph *graph, int u, int v)
{
    if (u == v)
    {
        printf("%d", u);
    }
    else if (graph->pi[u][v] == -1)
    {
        printf("No path from %d to %d exists.", u, v);
    }
    else
    {
        printPath(graph, u, graph->pi[u][v]);
        printf("->%d", v);
    }
}

int main()
{
    int numVertices, i, j;
    char *fileName = (char *)malloc(MAX * sizeof(char));
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    printf("Enter no. of. vertices\n");
    scanf("%d", &numVertices);
    printf("Enter filename\n");
    scanf("%s", fileName);

    graph = createGraph(numVertices);
    readGraphFromFile(graph, fileName);

    printf("Initially:\n");
    printDistances(graph);
    printPredecessors(graph);

    printf("\nRunning Floyd-Warshall Algorithm:\n");
    floydWarshall(graph);

    printf("\nShortest Paths:\n");
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i != j)
            {
                printf("From %d to %d: ", i, j);
                if (graph->dist[i][j] == INT_MAX)
                    printf("No path\n");
                else
                {
                    printf("Cost = %d, ", graph->dist[i][j]);
                    printPath(graph, i, j);
                    printf("\n");
                }
            }
        }
    }

    for (i = 0; i < numVertices; i++)
    {
        free(graph->dist[i]);
        free(graph->pi[i]);
    }
    free(graph);
    return 0;
}