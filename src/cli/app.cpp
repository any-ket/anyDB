#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include "../common.h"

using namespace std;

int main(){
  //connect to server
  int sockId = socket(AF_INET, SOCK_STREAM, 0);
  if (sockId == -1) {
    cerr << "Failed to create socket" << endl;
    return 1;
  }

  string serverIP = "127.0.0.1";
  //TODO: take serverIP as argument

  struct sockaddr_in serverAddr = {
    .sin_family = AF_INET, //AF_INET is family used for ipv4
    .sin_port = htons(SERVER_PORT) //htons -> host to network converstion(Endianness convertion)
  };

  if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddr.sin_addr)) <= 0) {
    std::cerr << "Invalid address/Address not supported" << std::endl;
    return 1;
  }

  // Connect to the server
  if (connect(sockId, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Connection failed" << std::endl;
    return 1;
  }

	return EXIT_SUCCESS;
}