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
        void accept_connection();
        void receive_msg(int clientSocket);
        void send_msg();
        void respond(Parser parse);

    private:
        int serverSocketFd_;
        sockaddr_in serverAddress_;
        KVStore kvs_;


};