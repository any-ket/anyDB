#include <cstdlib>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>
#include "tcp.h"
#include "../common.h"

#define DB_PATH "db_file"

typedef struct {
  std::string name;
} table;

using namespace std;


void createTable(){
  cout<<"Enter Table Name: "<<endl;
  table newTable;
  cin>>newTable.name;

  std::ofstream file(DB_PATH);
  if (file.is_open()) {
    file.write(reinterpret_cast<const char*>(&newTable), sizeof(table));

    file.close();
  } else {
    std::cerr << "Unable to open the file." << std::endl;
  }
  cout<<"Created table "<<newTable.name<<endl;
}

int main(){
  TcpServer server(SERVER_PORT, [](char* buff){
    CLI_REQ* req = (CLI_REQ*)buff;
    switch(req->opcode){
      case 1:
        createTable();
        break;
      default:
        break;
    }
  });
  return EXIT_SUCCESS;
}