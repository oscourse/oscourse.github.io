#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLEN 100

int main(int argc, char *argv[])
{

	int fd;
	char numstr[MAXLEN];
	int num_read;

	if( argc != 2) {
		printf("Usage: %s <numpipe_name>\n", argv[0]);
		exit(1);
	}

	if ( (fd = open(argv[1], O_RDONLY)) < 0) {
		perror(""); printf("error opening %s\n", argv[1]);
		exit(1);
	}

	while(1) {
		// read a line
		ssize_t ret = read(fd, &num_read, sizeof(int));
		if( ret > 0) {
			printf("Number read: %d ", num_read);
			printf("Bytes read: %ld\n", ret);
		} else {
			fprintf(stderr, "error reading ret=%ld errno=%d perror: ", ret, errno);
			perror("");
			sleep(1);
		}
	}
	close(fd);

	return 0;
}

