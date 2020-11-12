#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned long **matrix;
	int rows = 100, columns = 512;
	int i, j;

	printf("size of unsigned long %zu\n", sizeof(unsigned long));
	
	matrix = (unsigned long**)malloc(rows * sizeof(unsigned long*));
	if(!matrix)
		perror("malloc() failed\n");

	for(i = 0; i < rows; i++){
		matrix[i] = (unsigned long*)malloc(sizeof(unsigned long) * columns);
		if(!matrix[i])
			perror("malloc() failed\n");
	}

	// First for loop
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			matrix[i][j] = 0;
		}
	}

	// Second for loop
	for(j = 0; j < columns; j++){
		for(i = 0; i < rows; i++){
			matrix[i][j] = 5;
		}
	}

	// What is the difference between first and second for loop?
	// How many pages are allocated for the matrix?
	// Which loop performs better?
	// What happens if the number of rows increase?
	// What happens if the number of columns increase?
	
	// while(1);

	for(i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);

	return 0;
}
