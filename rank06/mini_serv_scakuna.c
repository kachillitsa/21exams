#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

typedef struct		s_client {
	int				fd, id;
	struct s_client	*next;
}					t_client;

t_client			*g_clients;
fd_set				curr_sock, cpy_read, cpy_write; // event sets
int					sock_fd, g_id = 0;
char				str[42*4096], tmp[42*4096], buf[42*4096 + 42], msg[42];

void	fatal() {
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	close(sock_fd);
	exit(1);
}

void	send_all(int fd, char *str_req) {
	for (t_client *it = g_clients; it; it = it->next)
		if (FD_ISSET(it->fd, &cpy_write) && it->fd != fd) // send all in set but the fd owner (message autor)
			if (send(it->fd, str_req, strlen(str_req), 0) < 0)
				fatal();
}

int		get_id(int fd) {
	for (t_client *it = g_clients; it; it = it->next)
		if (it->fd == fd)
			return (it->id);
	return (-1);
}

int		get_max_fd() {
	int	max = sock_fd;

	for (t_client *it = g_clients; it; it = it->next) {
		if (it->fd > max)
			max = it->fd;
	}
	return (max);
}

void	ex_msg(int fd) { //extract message
	int		i = -1, j = 0;

	while (str[++i]) {
		tmp[j++] = str[i];
		if (str[i] == '\n') {
			sprintf(buf, "client %d: %s", get_id(fd), tmp);
			send_all(fd, buf);
			j = 0;
			bzero(&tmp, strlen(tmp));
			bzero(&buf, strlen(buf));
		}
	}
	bzero(&str, strlen(str));
}

int		add_client_to_list(int fd) {
	t_client	*it = g_clients, *new;

	if (!(new = calloc(1, sizeof(t_client))))
		fatal();
	new->id = g_id++;
	new->fd = fd;
	if (!g_clients) {
		g_clients = new;
	} else {
		while (it->next)
			it = it->next;
		it->next = new;
	}
	return (new->id);
}

void	add_client() {
	struct sockaddr_in	clientaddr;
	unsigned int		len = sizeof(clientaddr), client_fd;

	if ((client_fd = accept(sock_fd, (struct sockaddr *)&clientaddr, &len)) < 0) // from main
		fatal();
	sprintf(msg, "server: client %d just arrived\n", add_client_to_list(client_fd));
	send_all(client_fd, msg);
	FD_SET(client_fd, &curr_sock);
}

int		rm_client(int fd) {
	t_client	*it = g_clients, *del;
	int			id = get_id(fd);

	if (it->fd == fd) {
		g_clients = it->next;
		free(it);
	} else {
		while (it->next && it->next->fd != fd)
			it = it->next;
		del = it->next;
		it->next = it->next->next;
		free(del);
	}
	return (id);
}

int		main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	struct sockaddr_in	servaddr;

	bzero(&servaddr, sizeof(servaddr));				// from main
	servaddr.sin_family = AF_INET;					// adress from internet flag
	servaddr.sin_addr.s_addr = htonl(2130706433);	// 127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));			// change port to atoi

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		fatal();
	if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		fatal();
	if (listen(sock_fd, 128) < 0)						// how many clients?
		fatal();

	FD_ZERO(&curr_sock);			// free fd set
	FD_SET(sock_fd, &curr_sock);	// add to the set
	bzero(&tmp, sizeof(tmp));		// free arrays
	bzero(&buf, sizeof(buf));
	bzero(&str, sizeof(str));

	while (1) {
		cpy_write = cpy_read = curr_sock; // everything is equal to curr_sock
		if (select(get_max_fd() + 1, &cpy_read, &cpy_write, NULL, NULL) < 0)	// error, but continue
			continue ;
		for (int fd = 0; fd <= get_max_fd(); fd++) { // some socket works, check every from 0 to max_fd
			if (FD_ISSET(fd, &cpy_read)) {			// if read - read
				if (fd == sock_fd) {
					bzero(&msg, sizeof(msg));
					add_client();
					break ;
				} else {
					if (recv(fd, str, sizeof(str), 0) <= 0) {			// if read but < 0, non message
						bzero(&msg, sizeof(msg));
						sprintf(msg, "server: client %d just left\n", rm_client(fd)); // printf but to str
						send_all(fd, msg);
						FD_CLR(fd, &curr_sock); // delete socket from set
						close(fd);
						break ;
					} else
						ex_msg(fd);		// extract message
				}
			}
		}
	}
	return (0);
}
