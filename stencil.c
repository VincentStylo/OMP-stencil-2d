#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "malloc2D.h"
#include "timer.h"

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)

int main(int argc, char *argv[])
{
   
   int imax=2002, jmax = 2002;

   double **xtmp, *xnew1d, *x1d;
   double **x = malloc2D(jmax, imax);
   double **xnew = malloc2D(jmax, imax);
   int *flush = (int *)malloc(jmax*imax*sizeof(int)*10);

   xnew1d = xnew[0]; x1d = x[0];
   for (int i = 0; i < imax*jmax; i++){
      xnew1d[i] = 0.0; x1d[i] = 5.0;
   }   
   for (int j = jmax/2 - 5; j < jmax/2 + 5; j++){
      for (int i = imax/2 - 5; i < imax/2 -1; i++){
         x[j][i] = 400.0;
      }   
   }   

   for (int iter = 0; iter < 10000; iter++){
      for (int l = 1; l < jmax*imax*10; l++){
          flush[l] = 1.0;
      }   
      
      for (int j = 1; j < jmax-1; j++){
         for (int i = 1; i < imax-1; i++){
            xnew[j][i] = ( x[j][i] + x[j][i-1] + x[j][i+1] + x[j-1][i] + x[j+1][i] )/5.0;
         }   
      }   

      SWAP_PTR(xnew, x, xtmp);
      if (iter%100 == 0) printf("Iter %d\n",iter);
   }   


   free(x);
   free(xnew);
   free(flush);

}
