/* Code by Jose Martinez Torres
This is stencil-2d, but it accounts for time elapsed
of the creation of the program 
*/


//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//defined functions
#define SWAP_PTR(xnew, xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)
double **malloc2D(int jmax, int imax);


//main program
int main(int argc, char *argv[])
{

    // Variables are created
    FILE *fp;
    FILE *fp2;
    int row = 0, column = 0, iteration;
    double t = 0, u = 1, temp = 0;
    char iteration_A[10];


    // Checks to see if arguments are satisfied
    if (argc != 5)
    {
        printf("usage: ./stencil-2d <num iterations> <input file> <output file> <all-iterations> \n");
        exit(0);
    }


    // opens the file, sets it to read row and column
    fp = fopen(argv[2], "r");
    printf("reading in file: %s \n", argv[2]);
    fread(&row, sizeof(int), 1, fp);
    fread(&column, sizeof(int), 1, fp);
    strcpy(iteration_A, argv[1]);
    iteration = atoi(iteration_A);
    double **xtmp,**x = (double **)malloc2D(row, column);
    double **xnew = (double **)malloc2D(row, column);


    // Takes values from File Pointer 1 and stores it into variable x
    for (int a = 0; a < row; a++)
    {
        for (int b = 0; b < column; b++)
        {
            fread(&temp, sizeof(double), 1, fp);
            x[a][b] = temp;
        }
    }
    fclose(fp);


    // Does Stencil Operation, and then writes it to file pointer 2
    fp2 = fopen(argv[4], "w");
    for (int i = 0; i < iteration; i++)
    {
        for (int a = 1; a < row - 1; a++)
        {
            for (int b = 1; b < column - 1; b++)
            {
                fwrite(&x[a][b], 1, sizeof(double), fp2);
                xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] +
                              x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] +
                              x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) /
                             9.0;
                x[a][b] = xnew[a][b];
            }
        }
    }


    // Opens the file that is designated to be the RAW file using file pointer 1
    fp = fopen(argv[3], "w");
    fwrite(&row, 1, sizeof(row), fp);
    fwrite(&column, 1, sizeof(column), fp);
    
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            if (j == 0 || j == column - 1)
            {
                fwrite(&u, 1, sizeof(double), fp);
                
            }
            else if ((j > 0 && j < column - 1 && i == 0) || (j > 0 && j < column - 1 && i == row - 1))
            {
                fwrite(&t, 1, sizeof(double), fp);
            } else {
                fwrite(&xnew[i][j], 1, sizeof(double), fp);
                
            }
        }
        SWAP_PTR(xnew, x, xtmp);
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}


//malloc2d code by SCROBEY, THIS IS NOT MINE
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
