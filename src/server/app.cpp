#include <cstdlib>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>
#include "tcp.h"
#include "../common.h"
#include <iomanip>

#define DB_PATH "db_file"

using namespace std;


void createTable(CreateTableReq* tableData){
  std::ofstream file(DB_PATH);
  if (file.is_open()) {
    file.write(reinterpret_cast<const char*>(tableData), sizeof(CreateTableReq));

    file.close();
  } else {
    std::cerr << "Unable to open the file." << std::endl;
  }
  cout<<"Created table "<<tableData->tableName<<endl;
}

int main(){
  TcpServer server(SERVER_PORT, [](char* buff){
    ClientRequest* req = reinterpret_cast<ClientRequest*>(buff);
    switch(req->opcode){
      case 1:{
        CreateTableReq* tableData = reinterpret_cast<CreateTableReq*>(req->data);
        if (tableData != nullptr) {
          createTable(tableData);
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