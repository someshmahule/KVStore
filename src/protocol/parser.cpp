#include "parser.h"

using namespace std;

Parser::Parser(char* buff)
{
    buff_ = buff;
}


vector<string> Parser::parseBuffer()
{
    stringstream message_(buff_);
    string intermediate_;

    while(std::getline(message_, intermediate_,' '))
    {
        tokens_.push_back(intermediate_);
    }

    return tokens_;

}

void Parser::parserStats(){

    cout<<"Buffer:" <<buff_<<"\n";
    cout<<"Tokens size:"<< tokens_.size()<<endl;
    cout<<"Command: "<< tokens_[0]<<endl;
}