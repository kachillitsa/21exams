#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>

// 3 инта, фд_сета, чара
int		sock_id[65536], next_id = 0, max_sock = 0;
fd_set	active_socks, sock_read, sock_write;
char	buf_str[42*4096], buf_read[42*4096], buf_write[42*4096+42];

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

}
