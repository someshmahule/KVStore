#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <unordered_map>
#include <bits/stdc++.h>
#include "protocol/parser.h"
#include "server.h"
#include "db/kvstore.h"

using namespace std;

Server::Server()
{
    serverSocketFd_ = socket(AF_INET, SOCK_STREAM,0);
    // AF_INET -> using IP, SOCK_STREAM -> stream oriented socket
    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(5000);
    serverAddress_.sin_addr.s_addr = INADDR_ANY;

}

Server::~Server(){
    close(serverSocketFd_);
}

void Server::create_connection()
{
    bind(serverSocketFd_, (struct sockaddr*)&serverAddress_, sizeof(serverAddress_));
    listen(serverSocketFd_, 5);
}

void Server::accept_connection()
{
        int clientSocket = accept(serverSocketFd_, nullptr, nullptr);
        receive_msg(clientSocket);
        close(clientSocket);
}

void Server::receive_msg(int clientSocket)
{
        char buffer[1024] = {0};
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesReceived] = '\0';
        cout<< "Client : " << buffer<< "\n";
        Parser clientMsg(buffer);
        respond(clientMsg);
        
}

void Server::send_msg()
{

}

void Server::respond(Parser msg)
{
    
    vector<string> toks = msg.parseBuffer();
    string command = toks[0];
    if (command == "PUT")
    {
        int ret = kvs_.insertKey(toks[1],toks[2]);
        if (ret != 0){
            cout<<"Server : Insert failed\n"<<endl;
        }
        else
        {
            cout<<"Server : Inserted key: "<< toks[1]<<endl;
        }
    }
    else if (command == "GET")
    {
        string value = kvs_.findKey(toks[1]);
        if(value != ""){
            cout<<"Server : Value: " << value<<endl;
        }
        else{
            cout<<"Server : Key not found"<<endl;
        }
    }
    else{
        cout<<"Server : UNKNOW command from Client\n"<<endl;
    }
}

int main()
{
    Server s1;
    s1.create_connection();
    cout << "Server is listening:.... \n";
    while(true){
        s1.accept_connection();
    }
    return 0;
}