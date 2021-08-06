#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

int		all_socks[42*4059], nextid = 0, maxid = 0;
fd_set	fd_cur, fd_r, fd_w;
char	c_str[42*4059], c_r[42*4059], c_w[42*4059+42];

void	fatal() {
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

void send_all(int exc) {
	int len = strlen(c_w);
	for (int sels = 0; sels <= maxid; sels++)
		if (FD_ISSET(sels, &fd_w) && sels != exc)
			send(sels, c_w, len, 0);
}

int		main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	bzero(&all_socks, sizeof(all_socks));
	FD_ZERO(&fd_cur);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		fatal();
	maxid = sockfd;
	FD_SET(sockfd, &fd_cur);
	struct sockaddr_in servaddr;
	socklen_t len = sizeof(servaddr);
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal();
	if (listen(sockfd, 128) < 0)
		fatal();
	while (1) {
		fd_r = fd_w = fd_cur;
		if (select(maxid + 1, &fd_r, &fd_w, NULL, NULL) < 0)
			continue;
		for (int sels = 0; sels <= maxid; sels++) {
			if (FD_ISSET(sels, &fd_r) && sels == sockfd) {
				int cl_s = accept(sockfd, (struct sockaddr *)&servaddr, &len);
				if (cl_s < 0)
					continue;
				maxid = (cl_s > maxid) ? cl_s : maxid;
				all_socks[cl_s] = nextid++;
				FD_SET(cl_s, &fd_cur);
				sprintf(c_w, "server: client %d just arrived\n", all_socks[cl_s]);
				send_all(cl_s);
				break;
			}
			if (FD_ISSET(sels, &fd_r) && sels != sockfd) {
				int read_res = recv(sels, c_r, 42*4056, 0);
				if (read_res <= 0) {
					sprintf (c_w, "server: client %d just left\n", all_socks[sels]);
					send_all(sels);
					FD_CLR(sels, &fd_cur);
					close(sels);
					break;
				}
				else {
					for (int i = 0, j = 0; i < read_res; i++, j++) {
						c_str[j] = c_r[i];
						if (c_str[j] == '\n' || j == read_res - 1) {
							c_str[j] = '\0';
							sprintf (c_w, "client %d: %s\n", all_socks[sels], c_str);
							send_all(sels);
							j = -1;
						}
					}
				}
			}
		}
	}
	return (0);
}