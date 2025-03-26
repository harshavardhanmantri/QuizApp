#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {
public:
    User(const string& username, const string& password, const bool& isAdmin,const bool& isLogedIn);
    User();
    bool login(const string& username, const string& password, bool& isAdmin, bool& isLogedIn);
    void registerUser(const string &username, const string &password,  bool &isAdmin, bool& isLogedIn);
    string hashedPassword(const string &password);
    void logOut(const string& username, bool& isLogedIn);
private:
    string username;
    string password;
    bool isAdmin;
    bool isLogedIn;
};

// USER_H