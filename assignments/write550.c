#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_LINE_LEN 10000

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[MAX_LINE_LEN];
	int linenum = 0;

	if( argc != 2) {
		printf("Usage: %s <linepipe_name>\n", argv[0]);
		exit(1);
	}	

	if ( (fp = fopen(argv[1], "w")) == NULL) {
		perror(""); printf("error opening %s\n", argv[1]);
		exit(1);
	} 
	
	while(1) {

		sprintf(line, "Producer %d Line %d\n", getpid(), linenum++);
		printf("%s", line);

		// write a line
		if ( fputs(line, fp) == -1) {
			perror("error writing line\n");
			//exit(2);
		}
		fflush(fp);
		sleep(1);
	}

	fclose(fp);

	return 0;
}

