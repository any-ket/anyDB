#include <vector>
#include <netinet/in.h>

class TcpConnection {
  private:
    int connId;
  public:
    struct sockaddr_in cliAddr;
    void init(int connId);
};

class TcpServer {
  private:
    int sockId;
    struct sockaddr_in servaddr;
    std::vector<TcpConnection> connections;
  public:
    TcpServer(int port);
};
