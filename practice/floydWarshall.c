#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct graph
{
    int numVertices;
    int **dist;
    int **pred;
} Graph;

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory alloc error\n");
        exit(1);
    }

    graph->numVertices = numVertices;
    graph->dist = (int **)malloc(numVertices * sizeof(int *));
    graph->pred = (int **)malloc(numVertices * sizeof(int *));
    if (!graph->dist || !graph->pred)
    {
        printf("Memory alloc error\n");
        exit(1);
    }

    int i, j;
    for (i = 0; i < numVertices; i++)
    {
        graph->dist[i] = (int *)malloc(numVertices * sizeof(int));
        graph->pred[i] = (int *)malloc(numVertices * sizeof(int));
    }

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
            graph->pred[i][j] = -1;
        }
    }

    return graph;
}

void readFromFile(Graph *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
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
            printf("Invalid source vertex %d\n", vertex);
            continue;
        }

        for (i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);
            if (neighbor < 0 || neighbor >= graph->numVertices)
            {
                printf("Invalid neighbor vertex\n");
                continue;
            }

            graph->dist[vertex][neighbor] = weight;
            graph->pred[vertex][neighbor] = vertex;
        }
    }

    fclose(file);
}

void printDistMat(Graph *graph)
{
    int i, j, n = graph->numVertices;
    printf("Distance Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph->dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", graph->dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPredMat(Graph *graph)
{
    int i, j, n = graph->numVertices;
    printf("Predecessor Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph->pred[i][j] == -1)
                printf("nil\t");
            else
                printf("%d\t", graph->pred[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
                else if (graph->dist[i][k] + graph->dist[k][j] < graph->dist[i][j])
                {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                    graph->pred[i][j] = graph->pred[k][j];
                }
            }
        }

        printDistMat(graph);
        printPredMat(graph);
    }
}

void printPath(Graph *graph, int u, int v)
{
    if (u == v)
    {
        printf("%d", u);
    }
    else if (graph->pred[u][v] == -1)
    {
        printf("No path exists btw %d-%d", u, v);
    }
    else
    {
        printPath(graph, u, graph->pred[u][v]);
        printf("->%d", v);
    }
}

int main()
{
    int numVertices, i, j;
    Graph *graph = NULL;
    char *filename = (char *)malloc(50 * sizeof(char));

    printf("Enter filename\n");
    scanf("%s", filename);
    printf("Enter no. of vertices\n");
    scanf("%d", &numVertices);
    graph = createGraph(numVertices);
    readFromFile(graph, filename);

    printf("\nInitially\n");
    printDistMat(graph);
    printPredMat(graph);

    printf("Running Floyd Warshall Algo:\n");
    floydWarshall(graph);

    printf("All pair shortest paths:\n");
    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
        {
            if (i != j)
            {
                printf("%d -- %d: ", i, j);
                if (graph->dist[i][j] == INT_MAX)
                {
                    printf("No Path");
                }
                else
                {
                    printf("Cost = %d; ", graph->dist[i][j]);
                    printPath(graph, i, j);
                    printf("\n");
                }
            }
        }
    }

    for (i = 0; i < numVertices; i++)
    {
        free(graph->dist[i]);
        free(graph->pred[i]);
    }
    free(graph->dist);
    free(graph->pred);
    free(filename);
    free(graph);
    return 0;
}