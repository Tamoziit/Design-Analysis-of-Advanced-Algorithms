#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

void printPrefixVector(char *pattern, int *pi)
{
    int i, m = strlen(pattern);
    for (i = 0; i < m; i++)
    {
        printf("%c:%d ", pattern[i], pi[i]);
    }
    printf("\n");
}

int *computePrefix(char *pattern, int *pi)
{
    int m = strlen(pattern);
    int i, k = 0;
    pi[0] = 0;

    for (i = 1; i < m; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }

        if (pattern[k] == pattern[i])
            k++;

        pi[i] = k;
    }

    printPrefixVector(pattern, pi);
    return pi;
}

void KMPMatcher(char *pattern, char *text)
{
    int m = strlen(pattern), n = strlen(text);
    int i, q = 0, flag = 0;
    int *pi = (int *)malloc(m * sizeof(int));
    pi = computePrefix(pattern, pi);

    for (i = 0; i < n; i++)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = pi[q - 1];
        }

        if (pattern[q] == text[i])
        {
            q++;
        }

        if (q == m)
        {
            printf("Pattern found with shift = %d\n", i - m + 1);
            flag++;
            q = pi[q - 1];
        }
    }

    if (!flag)
    {
        printf("Pattern not found\n");
    }
}

int main()
{
    char *text = (char *)malloc(MAX * sizeof(char));
    char *pattern = (char *)malloc(MAX * sizeof(char));

    FILE *file = fopen("string.txt", "r");
    if (!file)
    {
        printf("Error in reading file\n");
        exit(1);
    }

    fscanf(file, "%s", text);
    fscanf(file, "%s", pattern);

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    KMPMatcher(pattern, text);

    free(pattern);
    free(text);
    return 0;
}