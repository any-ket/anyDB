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

int parseCommand(string str_command, char*& payload, uint16_t& length){
  if(str_command=="create table"){
    string name;
    cout<<"Enter table name"<<endl;
    cin>>name;

    length = static_cast<uint16_t>(sizeof(CreateTableReq) + name.size());

    CreateTableReq* req = reinterpret_cast<CreateTableReq*>(new char[length]);
    req->length = static_cast<uint8_t>(name.size());

    strcpy(req->tableName, name.c_str());

    payload = (char*)req;

    return CREATE_TABLE_COMMAND;
  }
  return 0;
}


int sendToServer(int sockId, char* buff, uint16_t bufLen){
  if (write(sockId, buff, bufLen) < 0) {
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
    char * payload;
    uint16_t length = 0;
    uint8_t com = parseCommand(command, payload, length);
    if(!com){
      cout<<"Invalid command!"<<endl;
      continue;
    }

    uint16_t reqLen = sizeof(ClientRequest) + length;
    ClientRequest* req = reinterpret_cast<ClientRequest*>(new char[reqLen]);;

    req->opcode = com;
    memcpy(&req->data, payload, length);

    switch(com){
      case 1:
        sendToServer(sockId, (char*)req, reqLen);
        break;
      default:
        break;
    }

    delete req;
    delete payload;
  }

	return EXIT_SUCCESS;
}