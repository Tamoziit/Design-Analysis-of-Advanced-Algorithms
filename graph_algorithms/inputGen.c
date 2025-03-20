#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("graph.txt", "w");
    if (fp == NULL) {
        printf("Error opening graph.txt for writing\n");
        return 1;
    }
    
    int numVertices;
    printf("Enter the number of vertices: ");
    if (scanf("%d", &numVertices) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    for (int i = 0; i < numVertices; i++) {
        int degree;
        printf("Enter degree (number of edges) for vertex %d: ", i);
        if (scanf("%d", &degree) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        
        fprintf(fp, "%d %d", i, degree);
        
        for (int j = 0; j < degree; j++) {
            int adjVertex, weight;
            printf("Enter adjacent vertex and edge weight for edge %d of vertex %d: ", j+1, i);
            if (scanf("%d %d", &adjVertex, &weight) != 2) {
                printf("Invalid input.\n");
                return 1;
            }
            fprintf(fp, " %d %d", adjVertex, weight);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("Graph input has been generated in graph.txt\n");
    return 0;
}
