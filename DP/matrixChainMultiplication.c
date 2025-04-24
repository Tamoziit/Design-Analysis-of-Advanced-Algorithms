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
                printf(" - ");
            else
                printf("%d   ", m[i][j]);
        }
        printf("\n");
    }
}

void printOptimalParenthesis(int s[MAX][MAX], int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

int matrixChainMultiplication(int *p, int n)
{
    int m[MAX][MAX], s[MAX][MAX];
    int i, l, j, k, cost;

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
    printOptimalParenthesis(s, 1, n - 1);
    printf("\n");

    return m[1][n - 1];
}

int main()
{
    int arr[] = {30, 35, 15, 5, 10, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);

    int min = matrixChainMultiplication(arr, size);
    printf("Minimum no. of Multiplications = %d\n", min);
    return 0;
}