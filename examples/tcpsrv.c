#include "aup.h"

int main(int argc, char **argv)
{
        int   listenfd, connfd;
	socklen_t clilen;
        struct sockaddr_in servaddr, cliaddr;
        char buff[MAXLINE];
        time_t ticks;

        /* Create a TCP socket */
        listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* Initialize server's address and well-known port */
	bzero((void *)&servaddr, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(1024);   /* daytime server */

	/* Bind server's address and port to the socket */
        Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	/* Convert socket to a listening socket  max 100 pending clients*/
        Listen(listenfd, 100); 

        for ( ; ; ) {
                /* Wait for client connections and accept them */
		clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		/* Now we ave a connected client */

                /* Retrieve system time */
                ticks = time(NULL);
                snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

                /* Write to socket */
                Writen(connfd, buff, strlen(buff));

                /* Close the connection */
                close(connfd);
        }
}

