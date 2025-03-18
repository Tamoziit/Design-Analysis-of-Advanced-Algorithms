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

    int ran[10] = {7, 3, 4, 2, 4, 6};
    int i;

    for (i = 0; i < 6; i++)
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