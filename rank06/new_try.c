#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

// 3 инта, фд_сета, чара
int		sock_id[42*4242], next_id = 0, max_sock = 0;
fd_set	sfd_act, afd_read, sfd_write;
char	buf_str[42*4242], buf_read[42*4242], buf_write[42*4242+42];

void fatal_error() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

int		main(int ac, char **av) {
	// 1. проверить аргументы
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	bzero(&sock_id, sizeof(sock_id));
	FD_ZERO(&sfd_act);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) fatal();
	max_sock = sockfd;
	FD_SET(sockfd, &sfd_act);
	struct sockaddr_in servaddr;
	socklen_t len = sizeof(servaddr);
	

}
