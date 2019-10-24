#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NUM 1000000

int ifPrime(int num){
	int i;
	if(num <= 1)
		return 0;

	for(i = 2; i < num; i++){
		if((num % i) == 0)
			return 0;
	}
	
	return 1;
}

void *get_prime_count(){
	int num, primeCount = 0;

	// How does increase in MAX_NUM value affect page allocation? 

	for(num = 0; num < MAX_NUM; num++){
		if(ifPrime(num))
			primeCount++;
	}
}

int main(){

	int primeCount, num_threads = 5, i;

	time_t start, end;

	pthread_t tid[num_threads];
	
	start = time(NULL);

	for(i = 0; i < num_threads; i++){
		pthread_create(&tid[i], NULL, get_prime_count, NULL);
	}

	for(i = 0; i < num_threads; i++){
		pthread_join(tid[i], NULL);
	}
 
	end = time(NULL);

	printf("Time taken to find prime numbers: %ld seconds\n", end - start);

	while(1);

	return 0;
}

