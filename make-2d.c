#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char rows_A[10];
    char columns_A[10];
    int rows;
    int columns;

    // Checks to see if arguments are satisfied
    if (argc < 4 || argc > 4)
    {
        printf("usage: ./make-2d <rows> <columns> <output file> \n");
        exit(0);
    }

    // Take the data and then turn it into its proper formats
    strcpy(rows_A, argv[1]);
    strcpy(columns_A, argv[2]);
    rows = atoi(rows_A);
    columns = atoi(columns_A);
    double t = 1;
    double u = 0;

    // Create a file that with specified parameters
    fp = fopen(argv[3], "w");
    fwrite(&rows, 1, sizeof(rows), fp);
    fwrite(&columns, 1, sizeof(columns), fp);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (j == 0  || j == columns-1)
            {
                fwrite(&t, 1, sizeof(double), fp);
            } else {
                fwrite(&u, 1, sizeof(double), fp);
            }
            
        }
        
    }


    fclose(fp);

    return 0;
}