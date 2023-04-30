#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <arpa/inet.h>
#include "tcp.h"
#include <unistd.h> // read(), write(), close()
#define SA struct sockaddr
#define MAX 25

TcpServer::TcpServer(int port){
  // socket create and verification
  sockId = socket(AF_INET, SOCK_STREAM, 0);
  if (sockId == -1) {
    printf("socket creation failed...\n");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  // Binding newly created socket to given IP and verification
  if ((bind(sockId, (SA*)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(EXIT_FAILURE);
  }

  // Now server is ready to listen and verification
  if ((listen(sockId, 5)) != 0) {
    printf("Listen failed...\n");
    exit(EXIT_FAILURE);
  }

  //have a thread running just to accept incoming client connections
  std::thread connectionThread([this](){
    while(true){
      TcpConnection connection;
      socklen_t cliAddrLen = sizeof(connection.cliAddr);
      int connId = accept(sockId, (SA*)&connection.cliAddr, (socklen_t*)&(cliAddrLen));
      if (connId < 0) {
       printf("server accept failed...\n");
       exit(0);
      }

      connection.init(connId);

      //TODO: use mutex to avoid race condition since connections is being shared by multiple threads
      this->connections.emplace_back(connection);
    }
  });
  connectionThread.detach();
}

void TcpConnection::init(int connId){
  printf("New client Connected..%s: %d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

  std::thread readerThread([this, connId](){
    char buff[MAX];
    // infinite loop for reading input from client
    while (true) {
      memset(buff, 0, sizeof(buff));
      // read the message from client and copy it into the buffer
      ssize_t bytesRead = read(connId, buff, sizeof(buff) - 1);

      if (bytesRead == -1) {
        perror("Error reading from client");
        break;
      } else if (bytesRead == 0) {
        printf("client disconnected...\n");
        close(connId);
        break;
      }

      printf("Client sent %s\n", buff);

      // if msg contains "exit" then disconnect the client
      if (strncmp("exit", buff, 4) == 0) {
        printf("client disconnected...\n");
        close(connId);
        break;
      }
    }
  });
  readerThread.detach();
}