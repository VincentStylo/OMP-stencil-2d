/* Code by Jose Martinez Torres
 * This is stencil-2d
 * Outputs to screen the elapsed time in seconds, number-
 * of iterations, along with row and column
 */

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "utilities.h"

#define SWAP_PTR(xnew, xold, xtmp) (xtmp = xnew, xnew = xold, xold = xtmp)

// main program
int main(int argc, char *argv[])
{
  // Checks to see if arguments are satisfied
  if (argc != 5)
  {
    printf("usage: ./stencil-2d <num iterations> <input file> <output file> <thread_count> \n");
    exit(0);
  }

  //Gets the Thread count
  double thread_count = 0;
  thread_count = atoi(argv[4]);

  // Sets the threadcount
  omp_set_num_threads(thread_count);

  //Prints the Threadcount
  #pragma omp parallel
  #pragma omp master
  printf("Running with %d thread(s)\n", omp_get_num_threads());

  // Pointer, Row, Column and Iteration are created
  FILE *fp;
  int row = 0, column = 0, iteration = 0;
  char iteration_A[10];
  strcpy(iteration_A, argv[1]);
  iteration = atoi(iteration_A);

  // Opens <input file>, reads row and column from <Input File>
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
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      xnew[i][j] = x[i][j];
    }
  }

  clock_t begin = clock();

  // Sets the threadcount
  omp_set_num_threads(thread_count);

  // Does Stencil Operation
  for (int i = 0; i < iteration; i++)
  {
    calc2D(x, xnew, row, column);
    SWAP_PTR(xnew, x, xtmp);
  }

  //Opens Output File and reads x into it
  fp = fopen(argv[3], "w");
  fwrite(&row, 1, sizeof(int), fp);
  fwrite(&column, 1, sizeof(int), fp);
  fwrite(&x[0][0], row * column, sizeof(double), fp);
  fclose(fp);

  // Frees x and xnew, stops the timer, and Ends Program
  free(x);
  free(xnew);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time =  %f \nNumber of iterations = %d \nRows: %d, Columns: %d\n", time_spent, iteration, row, column);
  return 0;
}
