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

int Server::accept_connection()
{
        int clientSocket = accept(serverSocketFd_, nullptr, nullptr);
        return clientSocket;
}

char* Server::receive_msg(int clientSocket, char* buffer, size_t bufferSize)
{
        ssize_t bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
        buffer[bytesReceived] = '\0';
        cout<< "Client : " << buffer<< "\n";
        return buffer;
}

void Server::send_msg(const char* msg, int clientSocket)
{
    send(clientSocket, msg, strlen(msg), 0);
}

void Server::respond(Parser msg, int clientSocket)
{
    
    vector<string> toks = msg.parseBuffer();
    string command = toks[0];
    if (command == "PUT")
    {
        int ret = kvs_.insertKey(toks[1],toks[2]);
        if (ret != 0){
            const char* res = "Server : Insert failed\n";
            send_msg(res, clientSocket);
        }
        else
        {
            string res = "OK"; //successful insert
            send_msg(res.c_str(), clientSocket);
        }
    }
    else if (command == "GET")
    {
        string res;
        string value = kvs_.findKey(toks[1]);
        if(value != ""){
            res = value;
            send_msg(res.c_str(), clientSocket);
        }
        else{
            res = "NOT_FOUND";
            send_msg(res.c_str(), clientSocket);
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
    int clientSocketFD_ = s1.accept_connection();
    while(true){
        char buff[1024] = {0};
        s1.receive_msg(clientSocketFD_, buff, sizeof(buff));
        Parser clientMsg(buff);
        s1.respond(clientMsg, clientSocketFD_);
    }
    close(clientSocketFD_);
    return 0;
}