#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
        int fd, offset;
        char *data;
        struct stat sbuf;

        if (argc != 2) {
            fprintf(stderr, "usage: mmap offset\n");
            exit(1);
        }

        if ((fd = open("mmap.c", O_RDONLY)) == -1) {
            perror("open");
            exit(1);
        }

        if (stat("mmap.c", &sbuf) == -1) {
            perror("stat");
            exit(1);
        }

        offset = atoi(argv[1]);
        if (offset < 0 || offset > sbuf.st_size-1) {
            fprintf(stderr, "mmap: offset must be in the range 0-%d\n", sbuf.st_size-1);
            exit(1);
        }
        
        if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
            perror("mmap");
            exit(1);
        }

        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);
	++offset;
        printf("byte at offset %d is '%c'\n", offset, data[offset]);


	if( munmap(data, sbuf.st_size) < 0 ) {
		perror("munmap");
		exit(1);
	}

	close(fd);

        return 0;
}
