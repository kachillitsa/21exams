#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

int		sock_id[42*4242], next_id = 0, max_sock = 0;
fd_set	sfd_act, sfd_read, sfd_write;
char	buf_str[42*4242], buf_read[42*4242], buf_write[42*4242+42];

void fatal_error() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

void send_all(int except_sock) {
	int len = strlen(buf_write);
	for (int sel_sock = 0; sel_sock <= max_sock; sel_sock++)
		if (FD_ISSET(sel_sock, &sfd_write) && sel_sock != except_sock) { // FD_ISSET чекает есть ли sel_sock среди sfd_write
			send(sel_sock, buf_write, len, 0);
		}
}

int main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	bzero(&sock_id, sizeof(sock_id));
	FD_ZERO(&sfd_act);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) fatal_error();
	max_sock = sockfd;
	FD_SET(sockfd, &sfd_act);
	struct sockaddr_in servaddr;
	socklen_t addr_len = sizeof(servaddr);
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal_error();
	if (listen(sockfd, SOMAXCONN) < 0)
		fatal_error();
	while (1) {
		sfd_read = sfd_write = sfd_act;
		if (select(max_sock + 1, &sfd_read, &sfd_write, NULL, NULL) < 0)
			continue ;
		for (int sel_sock = 0; sel_sock <= max_sock; sel_sock++) {
			if (FD_ISSET(sel_sock, &sfd_read) && sel_sock == sockfd) {
				int client_sock = accept(sockfd, (struct sockaddr *)&servaddr, &addr_len);\
				if (client_sock < 0) continue ;
				max_sock = (client_sock > max_sock) ? client_sock : max_sock;
				sock_id[client_sock] = next_id++;
				FD_SET(client_sock, &sfd_act);
				sprintf(buf_write, "server: client %d just arrived\n", sock_id[client_sock]);
				send_all(client_sock);
				break ;
			}
			if (FD_ISSET(sel_sock, &sfd_read) && sel_sock != sockfd) {
				int read_res = recv(sel_sock, buf_read, 42*4096, 0);
				if (read_res <= 0) {
					sprintf(buf_write, "server: client %d just left\n", sock_id[sel_sock]);
					send_all(sel_sock);
					FD_CLR(sel_sock, &sfd_act);
					close(sel_sock);
					break ;
				}
				else {
					for (int i = 0, j = 0; i < read_res; i++, j++) {
						buf_str[j] = buf_read[i];
						if (buf_str[j] == '\n') {
							buf_str[j] = '\0';
							sprintf(buf_write, "client %d: %s\n", sock_id[sel_sock], buf_str);
							send_all(sel_sock);
							j = -1;
						}
					}
				}
			}
		}
	}
	return (0);
}
