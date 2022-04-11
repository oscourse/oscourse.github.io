#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFLEN 100

int main() {

	char buf[BUFLEN];

	int fd = open("/dev/chatroom", O_RDWR);
	if( fd < 0) {
		perror("Open failed: ");
		exit(1);
	}

	//read from the module
	if(read(fd, buf, BUFLEN) < 0) {
		perror("Read failed: ");
		exit(2);
	}

	printf("Got this from kernel: %s", buf);

	sprintf(buf, "Hello back to you, kernel!\n");
	printf("Sending %s", buf);
	if(write(fd, buf, strlen(buf)+1) < 0) {
		perror("write failed: ");
		exit(3);
	}

	return 0;
}

