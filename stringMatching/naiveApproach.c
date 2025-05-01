#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

void naiveStringMatcher(char *text, char *pattern)
{
    int n = strlen(text), m = strlen(pattern);
    int s, i, c, flag = 0;

    for (s = 0; s <= (n - m); s++)
    {
        c = 0;
        for (i = 0; i < m; i++)
        {
            if (pattern[i] == text[s + i])
                c++;
        }

        if (c == m)
        {
            flag++;
            printf("Pattern occurs with shift %d\n", s);
        }
    }

    if (!flag)
    {
        printf("Pattern not present in the string\n");
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

    naiveStringMatcher(text, pattern);

    free(text);
    free(pattern);
    return 0;
}