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

// Inlucded Programs
#include "utilities.h"
#include "timer.h"

#define SWAP_PTR(xnew, xold, xtmp) (xtmp = xnew, xnew = xold, xold = xtmp)

int main(int argc, char *argv[])
{
    // Checks to see if argc matches
    if (argc != 5)
    {
        printf("usage: ./omp-stencil-2d-stack <num iterations> <input file> <raw stack> <num threads> \n");
        exit(0);
    }

    // Gets the Thread count
    double thread_count = 0;
    thread_count = atoi(argv[4]);

    // Sets the threadcount
    omp_set_num_threads(thread_count);

    // Prints the Threadcount
    #pragma omp parallel
    #pragma omp master
    printf("Running with %d thread(s)\n", omp_get_num_threads());

    // Pointer, Row, Column and Iteration are created
    FILE *fp;
    int row = 0, column = 0, iteration = 0;
    char iteration_A[10];
    strcpy(iteration_A, argv[1]);
    iteration = atoi(iteration_A);
    double Start, End, Elapsed;

    // Opens <input file>, reads row and column
    fp = fopen(argv[2], "r");
    printf("reading in file: %s \n", argv[2]);
    fread(&row, sizeof(int), 1, fp);
    fread(&column, sizeof(int), 1, fp);

    // Memory allocation
    double **xtmp;
    double **x = malloc2D(row, column);
    double **xnew = malloc2D(row, column);

    // Loads values from <input file> to x, and closes <input file>
    fread(&x[0][0], row * column, sizeof(double), fp);
    fclose(fp);

    // Copies Values from x and puts them into xnew, ready to double buffer
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            xnew[i][j] = x[i][j];
        }
    }

    // Opens the file that's going to be written to
    fp = fopen(argv[3], "w");
    GET_TIME(Start);

    // Does Stencil Operation and stores it in a .raw file!
    for (int i = 0; i < iteration; i++)
    {
    calc2D_Parallel(x, xnew, row, column);
    fwrite(&x[0][0], row * column, sizeof(double), fp);
    SWAP_PTR(xnew, x, xtmp);
    }
    fwrite(&x[0][0], row * column, sizeof(double), fp);
    fclose(fp);

    // Frees X, stops the timer, and Ends Program
    free(x);
    free(xnew);
    GET_TIME(End);
    Elapsed = End - Start;
    printf("Elapsed time =  %f Number of iterations = %d Rows: %d, Columns: %d\n", Elapsed, iteration, row, column);
    return 0;
}
