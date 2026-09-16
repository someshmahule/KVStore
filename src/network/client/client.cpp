#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "client.h"

using namespace std;

Client::Client()
{
    clientSocketFd_ = socket(AF_INET, SOCK_STREAM, 0);
    clientAddress_.sin_family = AF_INET;
    clientAddress_.sin_port = htons(5000);
    clientAddress_.sin_addr.s_addr = INADDR_ANY;
}

void Client::connect_server()
{
    connect(clientSocketFd_, (struct sockaddr*)&clientAddress_, sizeof(clientAddress_));
}

void Client::send_msg(const char* m){

    send(clientSocketFd_, m, strlen(m), 0);
}

std::string Client::parseArgs(int argc, char* argv[])
{

    std::string message = "";
    std::string command = argv[1];
    cout<<command;
    if (command == "PUT")
    {
        std::string key = argv[2];
        std::string value = argv[3];
        message = command + " " + key + " " + value;
    }
    else if (command == "GET")
    {
        std::string key = argv[2];
        message = command+ " "+ key;
    }
    else
    {
        return "";
    }

    
    return message;

}

void Client::receive(){

    //recv();

}


int main(int argc, char* argv[])
{
    
    Client c1;
    std::string message = c1.parseArgs(argc, argv);
    if(message == ""){
        cout<<"Incorrect message should be either"<<endl;
        cout<<"1. PUT <KEY> <VALUE>"<<endl;
        cout<<"2. GET <KEY>"<<endl;
        exit(0);
    }
    c1.connect_server();
    c1.send_msg(message.c_str());

}