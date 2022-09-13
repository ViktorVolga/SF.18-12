#pragma once
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include<sys/socket.h>
#include<netinet/in.h>



#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 65530 // Будем использовать этот номер порта



class net1 {
	struct sockaddr_in serveraddress, client; //socaddr_in - структура содержащая:
//sin_addr - ip адрес
//sin_port - используемый порт
//sin_family - IPv4 или IPv6
	int socket_descriptor;
	int bind_stat;
	int connection_status;
	
	size_t connection;
	char net_message[MESSAGE_LENGTH];
    socklen_t length;
public:
	
	
	void create_socket() {
		socket_descriptor = socket(AF_INET, SOCK_STREAM, 0); //AF_INET -IPv4 семейство SOCK_STREAM - using TCP; 0 - умолчанию.
		if (socket_descriptor == -1)
			std::cout << "Socked creation failed" << std::endl;		
	}
	void create_bind(){
		serveraddress.sin_addr.s_addr = htonl(INADDR_ANY); //htohl - конвертирует 32-битную беззнаковую величину из локального порядка байтов в сетевой;
		//INADDR_ANY - универсальный адрес -означающий что сервер будет принимать запросы от весх адресов.
		serveraddress.sin_port = htons(PORT); //htons конвертирует 16-битную беззнаковую величину из локального порядка байтов в сетевой;
		serveraddress.sin_family = AF_INET; //указываем что используем IPv4
		bind_stat = bind(socket_descriptor, (struct sockaddr*) & serveraddress, sizeof(serveraddress));
		if (bind_stat == -1) {
			std::cout << "Socket binding failed.!" << std::endl;			
		}
	}
	void listening() {
		connection_status = listen(socket_descriptor, 5);
		if (connection_status == -1) {
			std::cout << "Socket is unable to listen for new connections.!" << std::endl;			
		}
		else {
			std::cout << "Server is listening for new connection: " << std::endl;
		}
	}
	void connecting() {
		length = sizeof(client);
		connection = accept(socket_descriptor, (struct sockaddr*)&client, &length);
		if (connection == -1) {
			std::cout << "Server is unable to accept the data from client.!" << std::endl;			
		}
	}

	void server_work() {
		memset(net_message, '0', MESSAGE_LENGTH);
		size_t read_result = recv(connection, net_message, sizeof(net_message), 0);
	}

	
};