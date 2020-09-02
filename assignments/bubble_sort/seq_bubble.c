/* Pure Sequential Bubble Sort
 * Author: Kartik Gopalan
 * Date: Aug 31 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_COUNT 1000000 // Max integers to sort
#define MAX_NUM 100 // Generate numbers between 0 and MAX_NUM

// Uncomment the following line to turn on debugging messages
//#define DEBUG

long number[MAX_COUNT];
int N; // Number of integers to sort

// generate N random numbers between 0 and MAX_NUM
void generate_numbers()
{
	int i;

	srandom(time(NULL));

	for(i=0; i<N; i++) 
		number[i] = random()%MAX_NUM;
}

void print_numbers() 
{
	int i;

	for(i=0; i<N; i++) 
		printf("%ld ", number[i]);
	printf("\n");
}

int compare_and_swap(int i, int j) 
{
	assert ( i<N );
	assert ( j<N );

	if( number[i] > number[j]) {
		long temp = number[i];
		number[i] = number[j];
		number[j] = temp;
		return 1;
	}

	return 0;
}

// single pass bubbling from start to start+n
int bubble(int start, int n) 
{

	int swap_count = 0;
	int next;

	assert (start<N );

	for( next = start; (next+1) < (start+n); next++ ) 
		swap_count += compare_and_swap(next, next+1);

	return swap_count;
}

void bubble_sort() 
{
	int swap_count = N;

#ifdef DEBUG
	print_numbers();
#endif

	do {
		swap_count = bubble(0,N); // 0 for single-process sorting
#ifdef DEBUG
		print_numbers();
		//fprintf(stderr,"swap_count %d\n", swap_count);
#endif
	} while(swap_count!=0);
}

int main(int argc, char *argv[])
{

	if( argc != 2) {
		fprintf(stderr, "Usage: %s N\n", argv[0]);
		return 1;
	}

	N = strtol(argv[1], (char **)NULL, 10);
	if( N == 0) {
		perror("Invalid N");
		return 2;
	}
	if( N > MAX_COUNT) {
		fprintf(stderr, "N larger than %d.\n", MAX_COUNT);
		return 3;
	}

	//fprintf(stderr, "Generating.\n");
	generate_numbers();

#ifdef DEBUG
	//fprintf(stdout, "Generated sequence is as follows:\n");
	//print_numbers();
#endif

	//fprintf(stderr, "Sorting.\n");
	bubble_sort();

	fprintf(stderr, "Sorted sequence is as follows:\n");
	print_numbers();
	fprintf(stderr, "Done.\n");

	return 0;
}


