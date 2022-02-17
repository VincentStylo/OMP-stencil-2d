

// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Main Program
int main(int argc, char *argv[])
{

    
    //Creation of Variables
    FILE *fp;
    char rows_A[10], columns_A[10];
    int rows, columns;


    // Checks to see if arguments are satisfied
    if (argc != 4)
    {
        printf("usage: ./make-2d <rows> <columns> <output file> \n");
        exit(0);
    }


    // Takes input <rows> <columns> and converts them from string to int
    strcpy(rows_A, argv[1]);
    strcpy(columns_A, argv[2]);
    rows = atoi(rows_A);
    columns = atoi(columns_A);
    double t = 1;
    double u = 0;


    // Creates <output file> , and putting a stencil with the dimensions of <rows> <columns>
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
