#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>

typedef struct		s_client {
	int				fd, id;
	struct s_client	*next;
}				t_client;
t_client	*g_client;
fd_set		sock_cur, sock_read, sock_write;
int			g_fd, g_id;
char		str[42*4242], tmp1[42*4242], tmp2[42*4242 + 42], msg[42];

void	fatal() {
	write (2, "Fatal error\n", strlen("Fatal error\n"));
	close(g_fd);
	exit(1);
}

void	send_all(int fd, char *str_req) {
	for (t_client *it = g_client; it; it = it->next)
		if (FD_ISSET(it->fd, &sock_write) && it->fd != fd) // send all in set but the fd owner (message autor)
			if (send(it->fd, str_req, strlen(str_req), 0) < 0)
				fatal();
}

int		get_id(int fd) {
	for (t_client *it = g_client; it; it = it->next)
		if (it->fd == fd)
			return (it->id);
	return (-1);
}

int		get_max_fd() {
	int	max = g_fd;

	for (t_client *it = g_client; it; it = it->next) {
		if (it->fd > max)
			max = it->fd;
	}
	return (max);
}

void	extract_msg(int fd) { //extract message
	int		i = -1, j = 0;

	while (str[++i]) {
		tmp1[j++] = str[i];
		if (str[i] == '\n') {
			sprintf(tmp2, "client %d: %s", get_id(fd), tmp1);
			send_all(fd, tmp2);
			j = 0;
			bzero(&tmp1, strlen(tmp1));
			bzero(&tmp2, strlen(tmp2));
		}
	}
	bzero(&str, strlen(str));
}

int		add_client_to_list(int fd) {
	t_client	*it = g_client, *new;

	if (!(new = calloc(1, sizeof(t_client))))
		fatal();
	new->id = g_id++;
	new->fd = fd;
	if (!g_client) {
		g_client = new;
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

	if ((client_fd = accept(g_fd, (struct sockaddr *)&clientaddr, &len)) < 0) // from main
		fatal();
	sprintf(msg, "server: client %d just arrived\n", add_client_to_list(client_fd));
	send_all(client_fd, msg);
	FD_SET(client_fd, &sock_cur);
}

int		rm_client(int fd) {
	t_client	*it = g_client, *del;
	int			id = get_id(fd);

	if (it->fd == fd) {
		g_client = it->next;
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
		write (2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}
	struct sockaddr_in		servaddr;

	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	if ((g_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		fatal();
	if ((bind(g_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal();
	if (listen(g_fd, 128) < 0)					//listen 128
		fatal();
	
	FD_ZERO(&sock_cur);
	FD_SET(g_fd, &sock_cur);
	bzero(&tmp1, sizeof(tmp1));
	bzero(&tmp2, sizeof(tmp2));
	bzero(&str, sizeof(str));
	while (1) {
		sock_write = sock_read = sock_cur;
		if (select(get_max_fd() + 1, &sock_read, &sock_write, NULL, NULL) < 0)
			continue;
		for (int fd = 0; fd <= get_max_fd(); fd++) {
			if (FD_ISSET(fd, &sock_read)) {
				if (fd == g_fd) {
					bzero (&msg, sizeof(msg));
					add_client();
					break;
				} else {
					if (recv(fd, str, sizeof(str), 0) <= 0) {
						bzero(&msg, sizeof(msg));
						sprintf(msg, "server: client %d just left\n", rm_client(fd));
						send_all(fd, msg);
						FD_CLR(fd, &sock_cur);
						close(fd);
						break;
					} else
						extract_msg(fd);
				}

			}
		}
	}
	return (0);
}