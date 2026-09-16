#pragma once

#include <iostream>
#include <unordered_map>

using namespace std;

class KVStore{

    public:
        KVStore();
        ~KVStore();
        int insertKey(string key, string value);
        int deleteKey(string key);
        string findKey(string key);

    private:
        unordered_map<string,string> kvs;

};