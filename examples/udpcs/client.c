#include "aup.h"

#define GET_TIME 0

int main(int argc, char **argv)
{
        int  sockfd, n, servlen; 
        char req[10], recvline[MAXLINE + 1];
        struct sockaddr_in servaddr;

	if( argc != 2 ){
		printf("usage : gettime <IP address>");
		exit(0);
	}

        /* Create a UDP socket */
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	    
        /* Specify server's IP address and port */
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(1024); /* daytime server port */

        if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
                perror("inet_pton");
		exit(3);
	}

	/* Send message to server requesting date/time */
	strcpy(req, "GET_TIME");	
	Sendto(sockfd, req, strlen(req), 0, 
		(struct sockaddr *)&servaddr,
		sizeof(servaddr));

	/* Read date/time from the socket */
	servlen = sizeof(servaddr);
        n= Recvfrom(sockfd, recvline, MAXLINE, 0, 
			(struct sockaddr *)&servaddr, 
			&servlen);
	recvline[n] = '\0';
		
	printf("%s\n", recvline);            
        
        close(sockfd);

	return(0);
} 

