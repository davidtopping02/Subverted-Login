#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "authlib.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#define n = 0

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
 * Gets user from keyboard
 */
string getUser()
{
    cout << "Enter you username: ";
    string User;
    cin >> User;
    return User;
}

/**
 * Gets password from keyboard
 */
string getPassword()
{
    cout << "Enter your password: ";
    string Pass;
    cin >> Pass;
    return Pass;
}

/**
 *
 */
string findUser(string user)
{
    ifstream file;
    string line;
    file.open("passwords.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.find(user) != string::npos)
            {
                return line.substr(line.find(':') + 1);
                ;
            }
        }
        return "User not found";
    }
    return 0;
}

int main(string test)
{

    cout << test << endl;

    string user, storedHash, pass, userLine;

    user = getUser();
    pass = getPassword();
    storedHash = findUser(user);

    if (sha256(pass) == storedHash)
    {
        authenticated(user);
    }
    else
    {
        rejected(user);
    }
}
