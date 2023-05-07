#include <mutex>
#include <vector>
#include <netinet/in.h>

#define Callback std::function<void(char*)>

class TcpConnection {
  private:
    int connId;
    Callback msgCallback;
  public:
    struct sockaddr_in cliAddr;
    TcpConnection(Callback callback): msgCallback(callback){}
    void init(int connId);
};

class TcpServer {
  private:
    int sockId;
    struct sockaddr_in servaddr;
    std::vector<TcpConnection> connections;
  public:
    TcpServer(int port, Callback msgCallback);
};
