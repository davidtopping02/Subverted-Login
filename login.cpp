#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "authlib.h"
#include <openssl/sha.h>
#include <openssl/evp.h>

using namespace std;

//Using the openssl 3.0 function SHA256, because it takes const unsigned char[] arguments instead of strings, the pass string is typecasted
std::string sha256(string pass)
{
    unsigned int len = strlen ((const char *)pass.c_str());
    unsigned char hash [SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)pass.c_str(), len, hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string getUser()
{
    cout << "Enter you username: ";
    std::string User;
    cin >> User;
    return User;
}

string getPassword()
{
    cout << "Enter your password: ";
    string Pass;
    cin >> Pass;
    return Pass;
}

std::string findUser(string user){
    ifstream file;
    string line;
    file.open("passwords.txt");
    if(file.is_open()){
        while(getline(file, line)){
            if(line.find(user) != std::string::npos ){
                return line;
            }
        }
        return "User not found";

    }
    return 0;
}

int main()
{
    bool auth = false;
    string user,test,hash,pass;
    user = getUser();
    pass = getPassword();
    test = findUser(user);
    hash = test.substr(test.find(':')+1);
    if(sha256(pass) == hash){
        authenticated(user);
    }else{
        rejected(user);
    }


}
