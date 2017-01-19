#ifndef LIB_SOCKET_H_
#define LIB_SOCKET_H_


void client_init(int * cli_socket, char *ip, char *puerto);
void server_init(int *svr_socket, char *puerto);
void server_acept(int server_socket, int *cliente_socket);


#endif /* LIB_SOCKET_H_ */
