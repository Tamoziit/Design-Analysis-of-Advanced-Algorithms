/* KNUTH MORRIS PRATT APPROACH */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

void printPrefixVector(int *pi, char *pattern, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        printf("%c:%d ", pattern[i], pi[i]);
    }
    printf("\n");
}

int *computePrefix(char *pattern, int *pi)
{
    int m = strlen(pattern);

    int k = 0, i;
    pi[0] = 0;

    for (i = 1; i < m; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }

        if (pattern[k] == pattern[i])
        {
            k++;
        }

        pi[i] = k;
    }
    printPrefixVector(pi, pattern, m);

    return pi;
}

void KMPMatcher(char *text, char *pattern)
{
    int n = strlen(text), m = strlen(pattern);
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
            printf("Pattern occurs with shift = %d\n", i - m + 1);
            flag++;
            q = pi[q - 1];
        }
    }

    if (!flag)
    {
        printf("Pattern not present in the string i/p\n");
    }
}

int main()
{
    char *text = (char *)malloc(MAX * sizeof(char));
    char *pattern = (char *)malloc(MAX * sizeof(char));

    printf("Enter input string\n");
    scanf("%s", text);
    printf("Enter pattern to be found\n");
    scanf("%s", pattern);

    KMPMatcher(text, pattern);

    free(text);
    free(pattern);
    return 0;
}