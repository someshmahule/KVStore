#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{

    int serverSocketFd = socket(AF_INET, SOCK_STREAM,0);
    // AF_INET -> using IP, SOCK_STREAM -> stream oriented socket

    cout<< "Socket code: " <<serverSocketFd<<"\n";

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    bind(serverSocketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(serverSocketFd, 5);

    cout << "Server is listening:.... \n";

    while(true){

        int clientSocket = accept(serverSocketFd, nullptr, nullptr);

        char buffer[1024] = {0};

        recv(clientSocket, buffer, sizeof(buffer), 0);

        cout<< "Message from client: " << buffer<< "\n";

        close(clientSocket);
    }

    close(serverSocketFd);

    return 0;


}