
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>


int main(int argc, char *argv[])
{

	FILE *fp;
	char *line = NULL;
	size_t len = 0;

	if( argc != 2) {
		printf("Usage: %s <linepipe_name>\n", argv[0]);
		exit(1);
	}	

	if ( (fp = fopen(argv[1], "r")) == NULL) {
		perror(""); printf("error opening %s\n", argv[1]);
		exit(1);
	} 

	while(1) {
		// read a line
		ssize_t ret = getline(&line, &len, fp);
		if( ret < 0) {
			printf("error reading ret=%ld errno=%d\n", ret, errno);
			sleep(1);
		} else {
			printf("line: %s", line);
			printf("bytes read: %ld\n", ret);
		}

	}
	fclose(fp);

	return 0;
}

