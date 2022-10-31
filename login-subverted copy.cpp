#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "authlib.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <stdexcept>

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
 * Returns the user's hashed password if they exist in the list
 */
string findUser(string user)
{
    // opens file and stream etc...
    ifstream file;
    string line;
    file.open("passwords.txt");

    if (file.is_open())
    {
        // loops through each line looking for the user, then returns password
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

int main(int argc, char *argv[])
{
    // initial variables and pointers for program
    string user, storedHash, pass, userLine, *user_ptr = &user, *pass_ptr = &pass;

    storedHash = findUser(user);

    printf("User:");
    printf(argv[1]);
    printf("attempting to log in...");

    // reject if wrong password entered
    if (sha256(pass) != storedHash)
    {
        rejected(user);
    }
    else
    {
        // authenticate user
        authenticated(user);
    }
}