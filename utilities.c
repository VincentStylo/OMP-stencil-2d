#include <stdlib.h>
#include "utilities.h"
#include <omp.h>

double **malloc2D(int jmax, int imax)
{
   // first allocate a block of memory for the row pointers and the 2D array
   double **x = (double **)malloc(jmax*sizeof(double *) + jmax*imax*sizeof(double));

   // Now assign the start of the block of memory for the 2D array after the row pointers
   x[0] = (double *)(x + jmax);

   // Last, assign the memory location to point to for each row pointer
   for (int j = 1; j < jmax; j++) {
      x[j] = x[j-1] + imax;
   }

   return(x);
}

double **calc2D_Parallel(double **x, double **xnew, int row, int column)
{
   #pragma omp parallel for 
   for (int a = 1; a < row - 1; a++){
      for (int b = 1; b < column -1; b++){
         xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] + x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] + x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) / 9.0;
      }
   }
   return (xnew);
}

double **calc2D_Serial(double **x, double **xnew, int row, int column)
{
   for (int a = 1; a < row - 1; a++){
      for (int b = 1; b < column -1; b++){
         xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] + x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] + x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) / 9.0;
      }
   }
   return (xnew);
}