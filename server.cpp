#include "matplotlibcpp.h"
#include <arpa/inet.h>
#include <cmath>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using json = nlohmann::json;

int main() {

  int clientLen, socketConnection, sendStatus;
  sockaddr_in server, client;
  json jFile;
  int count{1};
  double x{0.1};

  // Parameters
  char message[100];
  int iRetval = -1;
  int clientPort = 90190;
  sockaddr_in remote{};
  remote.sin_family = AF_INET;
  remote.sin_addr.s_addr = htonl(INADDR_ANY);
  remote.sin_port = htons(clientPort);

  // Socket creation
  int socketServer = socket(AF_INET, SOCK_STREAM, 0);
  if (socketServer == -1) {
    std::cerr << "Socket could not be created\n";
    return 1;
  }
  // Socket binding
  int socketBind = bind(socketServer, (sockaddr*)&remote, sizeof(remote));
  if (socketBind < 0) {
    std::cerr << "Socket bind failed\n";
    return 1;
  }
  // Listening
  listen(socketServer, 3);
  std::cout << "Searching for connection...\n";

  
  clientLen = sizeof(sockaddr_in);
  socketConnection =
      accept(socketServer, (sockaddr*)&client, (socklen_t*)&clientLen);
  if (socketConnection < 0) {
    std::cerr << "Connection not accepted\n";
    return 1;
  } else {
    std::cout << "Connection accepted\n";
  }

  while (true) {

    double pi = 3.142;
    jFile["value1"] = sin(x);
    jFile["value2"] = cos(x);
    std::string stringJSON{jFile.dump()};

    sendStatus =
        send(socketConnection, stringJSON.c_str(), stringJSON.size(), 0);

    if (sendStatus < 0) {
      std::cerr << "Failed to send\n";
      close(socketConnection);
      return 1;
    } else {
      std::cout << count << ". Data sent: " << stringJSON << '\n';
    }

    usleep(150000);
    x += 0.1;
    count++;
  }
  close(socketConnection);
}
