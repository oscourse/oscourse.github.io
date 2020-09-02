/* Even-Odd Sequential Bubble Sort
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
#ifdef DEBUG
	fprintf(stderr,"i %d j %d\n", i, j);
#endif
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

// even-odd pass bubbling from start to start+n
int bubble(int start, int n, int pass) 
{
#ifdef DEBUG
	fprintf(stderr, "start %d n %d pass %d\n", start, n, pass);
#endif

	int swap_count = 0;
	int next = start;

	assert (start < N-1); // bug if we start at the end of array

	if (pass) { // sort odd-even index pairs
		if ( !(next % 2) ) 
			next = next + 1;
	} else  { // sort even-odd index pairs
		if (next % 2) 
			next = next + 1;
	}

	while ( (next+1) < (start+n) ) {
		swap_count += compare_and_swap(next, next+1);
		next+=2;
	}

	return swap_count;
}

void bubble_sort() 
{
	int last_count, swap_count = N;
	int pass = 0;

#ifdef DEBUG
	print_numbers();
#endif

	do {
		last_count = swap_count;
		swap_count = bubble(0, N, pass); // 0 for single-process sorting
#ifdef DEBUG
		print_numbers();
		fprintf(stderr,"last_count %d swap_count %d\n", last_count, swap_count);
#endif
		pass = 1-pass;
	} while((swap_count!=0) || (last_count != 0));
}

int main(int argc, char *argv[])
{

	if( argc != 2) {
		fprintf(stderr, "Usage: %s N\n", argv[0]);
		return 1;
	}

	N = strtol(argv[1], (char **)NULL, 10);
	if( (N < 2) || (N > MAX_COUNT) ) {
		fprintf(stderr, "Invalid N. N should be between 2 and %d.\n", MAX_COUNT);
		return 2;
	}

	//fprintf(stderr, "Generating.\n");
	generate_numbers();

	//fprintf(stdout, "Generated sequence is as follows:\n");
	print_numbers();

	//fprintf(stderr, "Sorting.\n");
	bubble_sort();

	//fprintf(stdout, "Sorted sequence is as follows:\n");
	print_numbers();
	fprintf(stderr, "Done.\n");

	return 0;
}


