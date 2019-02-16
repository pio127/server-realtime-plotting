#include "matplotlibcpp.h"
#include <stdio.h>
#include <string.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>   
#include <iostream>
#include <nlohmann/json.hpp>   

using json = nlohmann::json;

int main() {
	
	int clientLen, socketConnection, sendStatus;
	sockaddr_in server, client;	
	json jFile;
	char message[100];
	// Parameters
	int iRetval=-1;
	int clientPort = 90190;
	sockaddr_in  remote{};
    remote.sin_family = AF_INET; /* Internet address family */
	remote.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	remote.sin_port = htons(clientPort); /* Local port */

	// Socket creation
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1) {
		std::cerr << "Socket could not be created\n";
		return 1;
	}
    // Socket binding    
	int socketBind = bind(socketServer,(sockaddr *) &remote, sizeof(remote));
	if (socketBind < 0) {
		std::cerr << "Socket bind failed\n";
		return 1;
	}
	// Listening
	listen(socketServer, 3);
	std::cout << "Searching for connection...\n";
	while(true) {
		clientLen = sizeof(sockaddr_in);
		socketConnection = accept(socketServer, 
				(sockaddr *)&client,
				(socklen_t *)&clientLen);
		if (socketConnection < 0) {
			std::cerr << "Connection not accepted\n";
			return 1;
		} else {
			std::cout << "Connection accepted\n";
		}
		// Sending message
		//strcpy(message, "Message from server!");
		jFile["message"] = "JSON message";
		std::string stringJSON{jFile.dump()};

		sendStatus = send(socketConnection,
				stringJSON.c_str(),
				stringJSON.size(),
				0);
		if (sendStatus < 0) {
			std::cerr << "Failed to send\n";
			return 1;
		}
		close(socketConnection);
		sleep(1);
	}
		

}
