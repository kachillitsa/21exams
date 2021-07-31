#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>

void fatal_error()
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

// 3 инта, фд_сета, чара
int sock_id[65536], max_sock = 0, next_id = 0;
fd_set active_socks, sock_read, sock_write;
char buf_for_read[42*4096], buf_str[42*4096], buf_for_write[42*4096+42];

int		main(int ac, char **av) {
	// 1. проверить аргументы
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// 2. задать порт
	int port = atoi(av[1]); (void) port;

	// 3. обнулить
	bzero(&sock_id, sizeof(sock_id)); //заполнить пространство 0
	FD_ZERO(&active_socks); // initializes a descriptor set fdset to the null set

	// 4. задать и проверить сокет
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) fatal_error();

	// 5.
	max_sock = 


}


    max_sock = server_sock;
    FD_SET(server_sock, &active_socks);
    
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = (1 << 24) | 127;
	addr.sin_port = (port >> 8) | (port << 8);

    if ((bind(server_sock, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
        fatal_error();
    if (listen(server_sock, SOMAXCONN) < 0)
        fatal_error();

    while (1) {
        ready_for_read = ready_for_write = active_socks;
        if (select(max_sock + 1, &ready_for_read, &ready_for_write, NULL, NULL) < 0)
            continue ;

        for (int sel_sock = 0; sel_sock <= max_sock; sel_sock++) {

            if (FD_ISSET(sel_sock, &ready_for_read) && sel_sock == server_sock) {
                int client_sock = accept(server_sock, (struct sockaddr *)&addr, &addr_len);\
                if (client_sock < 0) continue ;

                max_sock = (client_sock > max_sock) ? client_sock : max_sock;
                id_by_sock[client_sock] = next_id++;
                FD_SET(client_sock, &active_socks);

                sprintf(buf_for_write, "server: client %d just arrived\n", id_by_sock[client_sock]);
                send_all(client_sock);
                break ;
            }

            if (FD_ISSET(sel_sock, &ready_for_read) && sel_sock != server_sock) {

                int read_res = recv(sel_sock, buf_for_read, 42*4096, 0);

                if (read_res <= 0) {
                    sprintf(buf_for_write, "server: client %d just left\n", id_by_sock[sel_sock]);
                    send_all(sel_sock);
                    FD_CLR(sel_sock, &active_socks);
                    close(sel_sock);
                    break ;
                }
                else {
                    for (int i = 0, j = 0; i < read_res; i++, j++) {
                        buf_str[j] = buf_for_read[i];
                        if (buf_str[j] == '\n') {
                            buf_str[j] = '\0';
                            sprintf(buf_for_write, "client %d: %s\n", id_by_sock[sel_sock], buf_str);
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
