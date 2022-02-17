//Code by Jose Martinez Torres
#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>

int main(int argc, char *argv[])
{
   FILE * fp;
   int row = 0;
   int column = 0;
   double temp = 0;
   //Checks to see if arguments are satisfied
   if (argc < 2 || argc > 2)
   {
      printf("usage: ./print-2d <input data file> \n");
      exit(0);
   }
   //opens the file, sets it to read
   fp = fopen(argv[1], "r");
   fread(&row, sizeof(int), 1, fp);
   fread(&column, sizeof(int), 1, fp);
   printf("reading in file: ./%s \n", argv[1]);

   //Prints out array
   for (size_t i = 0; i < row; i++)
   {
      for (size_t j = 0; j < column; j++){
         fread(&temp, sizeof(double),1, fp);
         printf("%.2f ", temp);
      }
      printf("\n");
   }
   
   //closes the file
   fclose(fp);

   return 0;
}
