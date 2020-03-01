#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define NS 1e9

struct timer_values {
	unsigned long start_time_ns;
	unsigned long expected_exp_time_ns;
	unsigned long exp_time_ns;
	unsigned long diff_ns;
};

int main(){
	struct timespec currtime, exptime;
	struct timer_values t[1000];
	int i;

	for(i = 0; i < 1000; i++){
		clock_gettime(CLOCK_MONOTONIC, &currtime);
		usleep(1000);				// sleep for 1000us or 1ms
		clock_gettime(CLOCK_MONOTONIC, &exptime);
		t[i].start_time_ns = (currtime.tv_sec * NS) + currtime.tv_nsec;
		t[i].expected_exp_time_ns = (currtime.tv_sec * NS) + currtime.tv_nsec + 1000000;
		t[i].exp_time_ns = (exptime.tv_sec * NS) + exptime.tv_nsec;
		t[i].diff_ns = t[i].exp_time_ns - t[i].expected_exp_time_ns; 
	}
	for(i = 0; i < 1000; i++){
		printf("start %lu ns", t[i].start_time_ns);
		printf(" end %lu ns", t[i].exp_time_ns);
		printf(" expected %lu ns", t[i].expected_exp_time_ns);
		printf(" diff %lu ns\n", t[i].diff_ns);
	}
}
