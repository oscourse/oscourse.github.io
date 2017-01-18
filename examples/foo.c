#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <linux/unistd.h>

#define __NR_foo 311

_syscall0(int,foo)

int main(void) 
{
	int ret;
	printf("EOF=%d\n", EOF);
	while(1) {
		// making the system call 
		ret = foo();
		printf("ret = %d errno = %d\n", ret, errno);
		sleep(1);
	}

	return 0;
}

