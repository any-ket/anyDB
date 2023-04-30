#include <cstdlib>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>
#include "tcp.h"
#include "../common.h"
#define DB_PATH "db_file"

#define CREATE_TABLE_COMMAND 1

typedef struct {
  std::string name;
} table;

using namespace std;

int parseCommand(string str_command){
  if(str_command=="create table")
    return CREATE_TABLE_COMMAND;
  return 0;
}

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
  TcpServer server(SERVER_PORT);
  cout<<"Started DB server listening on port: "<<SERVER_PORT<<endl;

  while(true){
    string command;
    getline(cin, command);
    int com = parseCommand(command);
    if(!com){
      cout<<"Invalid command!"<<endl;
      continue;
    }
    switch(com){
      case 1:
        createTable();
        break;
      default:
        break;
    }
  }
  return EXIT_SUCCESS;
}