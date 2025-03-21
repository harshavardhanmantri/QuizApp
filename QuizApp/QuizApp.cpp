#include <stdlib.h>
#include <iostream>
#include<string>
#include "User.h"
#include "Database.h"/*
#include "Database.cpp"*/

using namespace std;


int main()
{
    Database database;
    database.useDatabase();
    User user;
    //user.registerUser("harsha", "kjadh0", false,false);
    /*if (user.login("harsha", "kjadh0", false, false)) {
        std::cout << "Login successful!" << std::endl;
    }
    else {
        std::cout << "Login failed!" << std::endl;
    }*/

    user.logOut("harsha", false);

    return 0;
}


