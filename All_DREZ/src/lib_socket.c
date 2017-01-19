#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<stdbool.h>



void client_init(int * cli_socket, char *ip, char *puerto){

	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	/*carga en serverInfo los datos de la conexion*/
	getaddrinfo(ip, puerto, &hints, &server_info);


	/*creamos el socket*/
	*cli_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	/*conectamos al servidor*/
	connect(*cli_socket, server_info->ai_addr, server_info->ai_addrlen);

	/*liberamos*/
	freeaddrinfo(server_info);

}

void server_init(int *svr_socket, char *puerto){

	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	/*carga en serverInfo los datos de la conexion*/
	getaddrinfo(NULL, puerto, &hints, &server_info);

	/*creamos el socket*/
	*svr_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

        int option = 1;
        setsockopt(*svr_socket,SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),&option,sizeof(option));

	bind(*svr_socket,server_info->ai_addr, server_info->ai_addrlen);

	/*liberamos*/
	freeaddrinfo(server_info);

	listen(*svr_socket, SOMAXCONN);
}

void server_acept(int serverSocket, int *cliente_socket){

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);

	*cliente_socket = accept(serverSocket, (struct sockaddr *) &addr, &addrlen);
}

