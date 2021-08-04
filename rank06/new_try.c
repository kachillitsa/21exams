#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

// 3 инта, фд_сета, чара
int		sock_id[42*4242], next_id = 0, max_sock = 0;
fd_set	sfd_act, sfd_read, sfd_write;
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
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal_error();
	if (listen(sockfd, 128) < 0)
		fatal_error();
	while (1) {
		sfd_read = sfd_write = sfd_act;
		if (select(max_sock + 1, &sfd_read, &sfd_write, NULL, NULL) < 0)
			continue;
		for (int sel_sock = 0; sel_sock <= max_sock; sel_sock++) {
			if (FD_ISSET(sel_sock, &sfd_read) && sel_sock == sockfd) {
				
			}
		}
	}
	return (0);
}
