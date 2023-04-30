#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include "../common.h"

#define CREATE_TABLE_COMMAND 1

using namespace std;

int parseCommand(string str_command){
  if(str_command=="create table")
    return CREATE_TABLE_COMMAND;
  return 0;
}

int sendToServer(int sockId, char* buff){
  if (write(sockId, buff, sizeof(buff)) < 0) {
    std::cerr << "Failed to send data" << std::endl;
    return 1;
  }
  return 0;
}

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

  while(true){
    string command;
    getline(cin, command);
    int com = parseCommand(command);
    if(!com){
      cout<<"Invalid command!"<<endl;
      continue;
    }

    CLI_REQ req = {
      .opcode = com
    };

    switch(com){
      case 1:
        sendToServer(sockId, (char*)&req);
        break;
      default:
        break;
    }
  }

	return EXIT_SUCCESS;
}