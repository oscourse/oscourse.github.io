    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <unistd.h>

    int main()
    {
        int pfds[2];
        char buf[30];

        pipe(pfds);

        if (!fork()) {
            printf("CHILD: writing to the pipe\n");
            write(pfds[1], "Hello from Child\n", 17);

            printf(" CHILD: reading from pipe\n");
            read(pfds[0], buf, 17);
            printf(" CHILD: read \"%s\"\n", buf);

            printf(" CHILD: exiting\n");
            exit(0);

        } else {

            printf("PARENT: reading from pipe\n");
            read(pfds[0], buf, 17);
            printf("PARENT: read \"%s\"\n", buf);

            printf("PARENT: writing to the pipe\n");
            write(pfds[1], "Hello from Parent\n", 17);

            wait(NULL);

            printf("PARENT: exiting\n");
        }
    }


