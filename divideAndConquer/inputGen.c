#include <stdio.h>
#include <stdlib.h>

void createInp()
{
    FILE *file = fopen("input.txt", "w");
    if (file == NULL)
    {
        printf("Error in creating input file\n");
        exit(1);
    }

    int ran[10] = {6, 3, 9, 1, 8, 10, 2, 5, 4, 7};
    int i;

    for (i = 1; i <= 10; i++)
    {
        fprintf(file, "%d\n", i);
    }
    fprintf(file, "\n");

    for (i = 10; i >= 1; i--)
    {
        fprintf(file, "%d\n", i);
    }
    fprintf(file, "\n");

    for (i = 0; i < 10; i++)
    {
        fprintf(file, "%d\n", ran[i]);
    }
    fprintf(file, "\n");

    printf("Written input to file\n");
    fclose(file);
}

int main()
{
    createInp();
    return 0;
}