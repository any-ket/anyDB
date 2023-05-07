#include <cstdlib>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>
#include "tcp.h"
#include "../common.h"
#include <iomanip>

#define DB_PATH "dbfile"

using namespace std;


void createTable(CreateTableReq* tableData, mutex* mtx){
  mtx->lock();
  std::ofstream file(string(DB_PATH) + "_" + tableData->tableName);
  if (file.is_open()) {
    file.write(reinterpret_cast<const char*>(tableData), sizeof(CreateTableReq) + static_cast<int>(tableData->length));

    file.flush();
    file.close();
  } else {
    std::cerr << "Unable to open the file." << std::endl;
  }
  mtx->unlock();
  cout<<"Created table "<<tableData->tableName<<static_cast<int> (tableData->length)<<endl;
}

int main(int n, char** argv){
  int port = atoi(argv[1]) ? atoi(argv[1]) : SERVER_PORT;
  std::mutex dbLock;
  TcpServer server(port, [&dbLock](char* buff){
    ClientRequest* req = reinterpret_cast<ClientRequest*>(buff);
    switch(req->opcode){
      case 1:{
        CreateTableReq* tableData = reinterpret_cast<CreateTableReq*>(req->data);
        if (tableData != nullptr) {
          createTable(tableData, &dbLock);
        } else {
          std::cerr << "Invalid CreateTableReq data." << std::endl;
        }
        break;
      }
      default:
        break;
    }
  });
  return EXIT_SUCCESS;
}