#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Parser{

    public:
        Parser(char *buff);
        vector<string> parseBuffer();
        void parserStats();

    private:
        vector<string> tokens_;
        char* buff_;
        int len_;
};
