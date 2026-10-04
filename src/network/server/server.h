#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <unordered_map>
#include <bits/stdc++.h>
#include "protocol/parser.h"
#include "db/kvstore.h"

using namespace std;


class Server{

    public:
        Server();
        ~Server();
        void create_connection();
        int accept_connection();
        int receive_msg(int clientSocket, char* buff, size_t bufferSize, int* end);
        void send_msg(const char* msg, int clientSocket);
        void respond(Parser parse, int clientSocket);

    private:
        int serverSocketFd_;
        sockaddr_in serverAddress_;
        KVStore kvs_;


};