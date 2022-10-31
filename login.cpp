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

/**
 * Using the openssl 3.0 function SHA256, because it takes const unsigned char[] arguments instead of strings, the pass string is typecasted
 */
string sha256(string pass)
{
    unsigned int len = strlen((const char *)pass.c_str());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)pass.c_str(), len, hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

/**
 * Finds hash from password file based on user name
 */
string findUser(string user)
{
    // inits file stream
    ifstream file;
    string line;

    // opens password file
    file.open("passwords.txt");
    if (file.is_open())
    {
        // loops through each line looking for the user, then returns password if user found
        while (getline(file, line))
        {
            if (line.find(user) != string::npos)
            {
                return line.substr(line.find(':') + 1);
            }
        }
        return "User not found";
    }
    return 0;
}

/**
 * runs the main functionality of the secure login
 * note that the user and password are passed into the program through run time parameters, e.g ./login.o username password
 */
int main(int argc, char *argv[])
{

    // exit if username AND password are not entered
    if (argc != 3)
    {
        exit(0);
    }
    string user(argv[1]), storedHash, pass(argv[2]), userLine;

    // gets hash of password for user
    storedHash = findUser(user);

    // authentification process
    if (sha256(pass) == storedHash)
    {
        authenticated(user);
    }
    else
    {
        rejected(user);
    }
}