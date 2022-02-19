/* Code by Jose Martinez Torres
 *
 * This is: stencil-2d-stack
 * Just generates the raw image stack,
 * just like prior assignment
 * BUT PARALLEL
 */


// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>


// defined functions
double **malloc2D(int jmax, int imax);

int main(int argc, char *argv[])
{
    // Checks to see if argc matches
    if (argc != 4)
    {
        printf("usage: ./stencil-2d <num iterations> <input file> <raw stack> \n");
        exit(0);
    }
    // TIMER STARTS
    clock_t begin = clock(); 
    // Variables are created
    FILE *fp;
    int row = 0, column = 0, iteration = 0;
    char iteration_A[10];
    strcpy(iteration_A, argv[1]);
    iteration = atoi(iteration_A);
    // Opens <input file>, reads row and column
    fp = fopen(argv[2], "r");
    printf("reading in file: %s \n", argv[2]);
    fread(&row, sizeof(int), 1, fp);
    fread(&column, sizeof(int), 1, fp);
    // BRobey memory allocation
    double **x = malloc2D(row, column);
    // Loads values from <input file> to x, and closes <input file>
    fread(&x[0][0], row * column, sizeof(double), fp);
    fclose(fp);
    // Opens <Raw Stack>
    fp = fopen(argv[3], "w");
    // Does Stencil Operation but PARALLEL

    {
    for (int i = 0; i < iteration; i++)
    {
        for (int a = 1; a < row - 1; a++)
        {
            for (int b = 1; b < column - 1; b++)
            {
                x[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] +
                           x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] +
                           x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) /
                          9.0;
            }
        }
    }
    // Writes to <Raw Stack> after iteration is completed
        fwrite(&x[0][0], row * column, sizeof(double), fp);
    }
    fclose(fp);
    free(x);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time =  %f \nNumber of iterations = %d \nRows: %d, Columns: %d\n", time_spent, iteration, row, column);
    return 0;
}

// malloc2d code by SCROBEY, THIS IS NOT MINE
double **malloc2D(int jmax, int imax)
{
    // first allocate a block of memory for the row pointers and the 2D array
    double **x = (double **)malloc(jmax * sizeof(double *) + jmax * imax * sizeof(double));

    // Now assign the start of the block of memory for the 2D array after the row pointers
    x[0] = (double *)(x + jmax);

    // Last, assign the memory location to point to for each row pointer
    for (int j = 1; j < jmax; j++)
    {
        x[j] = x[j - 1] + imax;
    }

    return (x);
}