#ifndef AUP_H
#define AUP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <string.h>


#define MAXLINE 1000

/* function prototypes */
int	 Accept(int, struct sockaddr *, socklen_t *);
void	 Bind(int, const struct sockaddr *, socklen_t);
void	 Connect(int, const struct sockaddr *, socklen_t);
void	 Getpeername(int, struct sockaddr *, socklen_t *);
void	 Getsockname(int, struct sockaddr *, socklen_t *);
void	 Getsockopt(int, int, int, void *, socklen_t *);
int	 Isfdtype(int, int);
void	 Listen(int, int);
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
ssize_t	 Recv(int, void *, size_t, int);
ssize_t	 Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
ssize_t	 Recvmsg(int, struct msghdr *, int);
int	 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Send(int, const void *, size_t, int);
void	 Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
void	 Sendmsg(int, const struct msghdr *, int);
void	 Setsockopt(int, int, int, const void *, socklen_t);
void	 Shutdown(int, int);
int	 Sockatmark(int);
int	 Socket(int, int, int);
void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);

#define err_sys(str) do { \
	fprintf(stderr, str); \
	exit(1); \
} while(0)

#endif
