#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

class Client{

    public:
        Client();
        void connect_server();
        void send_msg(const char* message);
        void receive();
        std::string parseArgs(int argc, char* argv[]);

    private:
        int clientSocketFd_;
        sockaddr_in clientAddress_;

};