#include "kvstore.h"

KVStore::KVStore()
{

}

KVStore::~KVStore()
{


}

int KVStore::insertKey(string key, string value)
{
    if(kvs.find(key)!=kvs.end()){
        cout<<"Server : Updating key value from " << kvs[key]<<endl;
        cout<<"to : "<<value<<"\n"<<endl;
    }
    kvs[key] = value;
    if(kvs.find(key)!=kvs.end()){
        return 0;
    }
    return -1;
}

int KVStore::deleteKey(string key)
{
    kvs.erase(key);
    if(kvs.find(key)==kvs.end()){
        return 0;
    }
    return -1;
}

string KVStore::findKey(string key)
{
    if(kvs.find(key)!=kvs.end())
    {
        return kvs[key];
    }

    return "";
}



