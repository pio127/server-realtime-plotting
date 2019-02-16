#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "matplotlibcpp.h"
#include <nlohmann/json.hpp>   

using json = nlohmann::json;
namespace plt = matplotlibcpp;
int main() {
	sockaddr_in server;
	char serverReply[200] = {0};
	// Parameters
	int serverPort = 90190;
	sockaddr_in  remote{};
    remote.sin_family = AF_INET; 
	remote.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	remote.sin_port = htons(serverPort); 
	// Socket creation
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if (socketClient == -1) {
		std::cerr << "Socket could not be created\n";
		return 1;
	}
	// Connecting with server
	int isConnected = connect(socketClient, 
			(sockaddr *)&remote,
			sizeof(sockaddr_in));
	if (isConnected < 0) {
		std::cerr << "Could not connect with server\n";
		return 1;
	}
	std::cout <<"Connected with server\n";

	// Receiving message from server
	timeval tv;
	tv.tv_sec = 10;
	tv.tv_usec = 0;

	int gettingMessage = setsockopt(socketClient, 
			SOL_SOCKET,
			SO_RCVTIMEO,
			(char *)&tv,
			sizeof(tv));
	if (gettingMessage < 0) {
		std::cerr << "Waiting to long for message\n";
		return 1;
	}
	int respondVal = recv(socketClient, serverReply, 200, 0);
	json jFile{json::parse(serverReply)};
  	auto message = jFile["message"].get<std::string>();
	std::cout << "Server response: " << message << '\n';
	close(socketClient);

    plt::plot({0,3,2,4});
    plt::show();
}

