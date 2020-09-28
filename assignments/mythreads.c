#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num_threads; // number of threads
int test_interval; // seconds for which to run the experiment
int run = 0; // flag to control thread execution

void *thread_func(void * arg) 
{

	int tid = (int)arg;
	int pid = getpid();
	int ppid = getppid();

	printf("Thread %d:%d created. \n", getpid(), tid);

	while( !run )
		sleep(1); /* do nothing, just wait for run flag */ 
		/* Not a perfect way to synchronize -- can you find a better way? */

	printf("Thread %d:%d ready. \n", getpid(), tid);

	/* This is the actual run of all threads */
	while( run ) {
		/* do nothing - just yield each time */ 

		// enabling this print may interfere with your thread scheduling
		printf("Thread %d:%d yielding. \n", getpid(), tid); 

		// yield to another thread/process
		pthread_yield();
		//sleep(1);
	}

	printf("Thread %d:%d finished. \n", getpid(), tid);
}


void process(void)
{
	int i, ret;
	pthread_t *tid;

	if ((tid = malloc(num_threads*sizeof(pthread_t))) == NULL) {
		perror("malloc error:");
		exit(1);
	}

	printf("num_threads %d test_interval %d\n", num_threads, test_interval);

	// CALL YOUR SYSCALL TO START PROFILING HERE

	// create child threads
	for(i=0; i<num_threads; i++) {
		ret = pthread_create(&tid[i], NULL, thread_func, (void *)i);
		if( ret ) {
			printf("pthread creation error ret=%d\n", ret);
			exit(1);
		}
	}

	run = 1;

	sleep(test_interval);

	run = 0;

	// CALL YOUR SYSCALL TO STOP PROFILING HERE

	// wait for children
	for(i=0; i<num_threads; i++) {
		ret = pthread_join(tid[i], NULL);
		if( ret ) {
			printf("pthread join error ret=%d\n", ret);
			// no need to exit - continue
		}
	}

	free(tid);
}

int main(int argc, char * argv[])
{

	if( argc < 3 ){
		printf("Usage: %s <num_threads> <test_interval>\n", argv[0]);
		exit(1);
	}

	num_threads = atoi(argv[1]);
	test_interval = atoi(argv[2]);

	process();
}
