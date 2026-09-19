#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "client.h"
#include <vector>
#include <sstream>

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

bool Client::validArgs(const std::string& input)
{
    std::stringstream stream(input);
    std::vector<std::string> args;
    std::string token;

    while(stream >> token)
    {
        args.push_back(token);
    }

    if(args.size() == 2 && args[0] == "GET")
    {
        return true;
    } 

    if(args.size() == 3 && args[0] == "PUT")
    {
        return true;
    }
    
    return false;

}

void Client::receive(){

    char buff[1024] = {0};
    recv(clientSocketFd_,buff, sizeof(buff), 0);
    cout<<"Received from server: " << buff <<endl;

}


int main(int argc, char* argv[])
{
    std::string input;
    Client c;
    c.connect_server();
    while(true)
    {
        cout<<"KVStore > ";
        if (!std::getline(std::cin, input))
        {
            break;
        }

        if (input == "exit")
        {
            exit(0);
        }
        if (!c.validArgs(input)) {
            cout<<"Incorrect message should be either"<<endl;
            cout<<"1. PUT <KEY> <VALUE>"<<endl;
            cout<<"2. GET <KEY>"<<endl;
            continue;
        }
        c.send_msg(input.c_str());
        c.receive();
    }

}