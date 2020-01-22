
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

// this code assumes a maximum line length of 100 bytes.
#define MAXLEN 100

int main(int argc, char *argv[])
{

	int fd;
	char line[MAXLEN];
	size_t len = 0;

	if( argc != 2) {
		printf("Usage: %s <linepipe_name>\n", argv[0]);
		exit(1);
	}

	if ( (fd = open(argv[1], O_RDONLY)) < 0) {
		perror(""); printf("error opening %s\n", argv[1]);
		exit(1);
	}

	while(1) {
		// read a line
		ssize_t ret = read(fd, line, MAXLEN);
		if( ret > 0) {
			printf("Line read: %s", line);
			printf("Bytes read: %ld\n", ret);
		} else {
			fprintf(stderr, "error reading ret=%ld errno=%d perror: ", ret, errno);
			perror("");
		}
		sleep(1);
	}
	close(fd);

	return 0;
}

