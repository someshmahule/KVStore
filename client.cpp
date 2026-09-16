#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

int main()
{
    int clientSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(5000);
    clientAddress.sin_addr.s_addr = INADDR_ANY;
    
    cout <<"Connect :" << connect(clientSocketFd, (struct sockaddr*)&clientAddress, sizeof(clientAddress));

    const char* message = "Hello, server!";
    send(clientSocketFd, message, strlen(message), 0);
    
}