#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "authlib.h"
#include <openssl/sha.h>

// unsigned char text[] = "Test String";
// unsigned int len = std::strlen((const char *)text);
// unsigned char hash[SHA256_DIGEST_LENGTH];
using namespace std;

std::string sha256(const std::string str)
{
    // This is deprecated but the other method doesnt work
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
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

std::string getPassword()
{
    cout << "Enter your password: ";
    std::string Pass;
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
    // unsigned char text[] = "Test String";
    // unsigned int len = strlen((const char *)text);
    // unsigned char hash[SHA256_DIGEST_LENGTH];
    // cout << SHA256(text, len, hash) << endl;
    bool auth = false;
    string storedPass = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";
    string user;
    string pass;
    string test;
    user = getUser();
    test = findUser(user);
    cout << test << endl;
    pass = getPassword();
    cout << sha256(pass) << endl;
    
    if(storedPass == sha256(pass)){
        authenticated(user);
    }else{
        rejected(user);
    }


}
