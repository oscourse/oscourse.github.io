#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

main() {

	sem_t s;
	int i;

	if ( sem_init(&s, 1, 1) < 0) {
		perror("sem_init:");
		exit(1);
	}

	if( fork() == 0 ) {
		for( i=0; i<20; i++) {
			sem_wait(&s);
			printf("22\n");
			printf("222\n");
			sem_post(&s);
			sleep(1);
		}
		exit(0);
	}
	else {
		for( i=0; i<20; i++) {
			sem_wait(&s);
			printf("11\n");
			printf("111\n");
			sem_post(&s);
			sleep(1);
		}
	}

	sem_destroy(&s);

}

