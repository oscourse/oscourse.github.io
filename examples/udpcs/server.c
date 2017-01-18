#include "aup.h"

#define REQ_LEN 1000

int main(int argc, char **argv)
{
	int sockfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
        char buff[MAXLINE], req[REQ_LEN];
        time_t ticks;
	int n;

        /* Create a  socket */
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* Initialize server's address and well-known port */
	bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(1024);   /* daytime server */

	/* Bind server's address and port to the socket */
        Bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	for ( ; ; ) {
		/* Wait for client request */
		clilen = sizeof(cliaddr); 
		n = Recvfrom( sockfd, req, REQ_LEN, 0, (struct sockaddr *)&cliaddr, &clilen);

		/* Retrieve the system time */
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		/* Send to client*/
		Sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&cliaddr, clilen);
	}
}

