#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

void printTable(int n, int m[MAX][MAX])
{
    int i, j;
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            if (i > j)
            {
                printf("-    ");
            }
            else
            {
                printf("%d    ", m[i][j]);
            }
        }
        printf("\n");
    }
}

void printOptimalParen(int s[MAX][MAX], int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        printOptimalParen(s, i, s[i][j]);
        printOptimalParen(s, s[i][j] + 1, j);
        printf(")");
    }
}

int matrixChainMul(int n, int *p)
{
    int i, j, k, l, cost;
    int m[MAX][MAX], s[MAX][MAX];
    for (i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }

    for (l = 2; l < n; l++)
    {
        for (i = 1; i < n - l + 1; i++)
        {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++)
            {
                cost = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printTable(n, m);
    printf("Optimal Parenthesis: ");
    printOptimalParen(s, 1, n - 1);
    printf("\n");

    return m[1][n - 1];
}

int main()
{
    int n, i = 0, ch, res;
    FILE *file = fopen("matIp.txt", "r");
    if (!file)
    {
        printf("Error in reading file\n");
        exit(1);
    }

    fscanf(file, "%d", &n);
    int *p = (int *)malloc(n * sizeof(int));
    while (fscanf(file, "%d ", &ch) != EOF)
    {
        p[i++] = ch;
    }

    printf("Matrix order sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    res = matrixChainMul(n, p);
    printf("Min. no. of multiplications required = %d\n", res);

    fclose(file);
    return 0;
}