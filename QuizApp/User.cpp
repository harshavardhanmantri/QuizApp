#include "User.h"
#include "Database.h"
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;


bool User::login(const string& username, const string& password, bool& isAdmin, bool& isLogedIn) {
    try {
        sql::Connection* con;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        Database database;
        con = database.useDatabase();

        // Select data
        pstmt = con->prepareStatement("SELECT * FROM users WHERE username = ?");
        pstmt->setString(1, username);
      
        res = pstmt->executeQuery();
        bool isAdmin1,isPresent = false;
        while (res->next()) {
            if (res->getBoolean("isLogedIn") != true){
                if (hashedPassword(password) == res->getString("password")) {
                    pstmt = con->prepareStatement("UPDATE users SET isLogedIn = ? WHERE username = ?");
                    pstmt->setBoolean(1, true);
                    pstmt->setString(2, username);
                    pstmt->executeUpdate();
                    cout << "isLogedIn updated to true for user: " << username << std::endl;
					isLogedIn = true;
                }
                else {
                    cout << "Wrong password"<<endl;
                }
            }
            else {
                cout << "User is already Logged in" << endl;
                isLogedIn = true;
            }
            isAdmin1 = res->getBoolean("isAdmin");
            isPresent = true;
            break;
        }
        if (!isPresent) {
            cout << "User Not Found" << endl;
            return false;
        }
         
        if (isAdmin != isAdmin1 && isAdmin == false) {
            cout << "User is not an Admin" << endl;
            return false;
        }
		else if (isAdmin != isAdmin1 && isAdmin == true) {
			cout << "Admin is not an User" << endl;
			return false;
		}
        else {
			isAdmin = isAdmin1;
            cout << "User/Admin is Logged in" << endl;
            
        }

        // Update data

        delete res;
        delete pstmt;
		return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
    }
    return true;
}

void User::registerUser(const string& username, const string& password, bool& isAdmin, bool& isLogedIn)
{
    try {
        sql::Connection* con;
        sql::PreparedStatement* pstmt;
        Database database;
        con = database.useDatabase();
        cout << "Register as:"<<endl<<"1.User "<<endl<<"2.Admin"<<endl;
		int choice;
        cin >> choice;
		if (choice == 2) {
			isAdmin = true;
		}
		else {
			isAdmin = false;
		}
        pstmt = con->prepareStatement("INSERT INTO users(username, password, isAdmin,isLogedIn) VALUES(?,?,?,?)");
        pstmt->setString(1, username);
        pstmt->setString(2, hashedPassword(password));
        pstmt->setBoolean(3, isAdmin);
        pstmt->setBoolean(4, isLogedIn);
        pstmt->execute();
        cout << "One row inserted." << endl;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL error: " << e.what() << endl;
    }
    catch (std::runtime_error& e) {
        cerr << "Runtime error: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unexpected error occurred." << endl;
    }
}

string User::hashedPassword(const string& password)
{
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

void User::logOut(const string& username, bool& isLogedIn)
{
    try {
        sql::Connection* con;
        sql::PreparedStatement* pstmt, * pstmt1 = nullptr;

        sql::ResultSet* res;
        Database database;
        con = database.useDatabase();

        // Select data
        pstmt = con->prepareStatement("SELECT * FROM users WHERE username = ?");
        pstmt->setString(1, username);
        res = pstmt->executeQuery();
        delete pstmt;
        while (res->next()) {
            if (res->getBoolean("isLogedIn") == false) {
                cout << "User is already Logged out" << std::endl;
            }
            else {
                pstmt1 = con->prepareStatement("UPDATE users SET isLogedIn = ? WHERE username = ?");
                pstmt1->setBoolean(1, false);
                pstmt1->setString(2, username);
				isLogedIn = false;
                int rowsAffected = pstmt1->executeUpdate();

                if (rowsAffected > 0) {
                    std::cout << "User is Logged Out" << std::endl;
                }
                else {
                    std::cout << "No user found with the specified username" << std::endl;
                }
            }
            break;
        }

        // Update data

        delete res;
        if (pstmt1 != nullptr) {
            delete pstmt1;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
    }
    return;
}


User::User(const string& username, const string& password, const bool& isAdmin, const bool& isLogedIn)
{
    this->username = username;
    this->password = hashedPassword(password);
    this->isLogedIn = isLogedIn;
    this->isAdmin = isAdmin;
}

User::User() : username(""), password(""), isAdmin(false), isLogedIn(false) {}

//#include "User.h"

// Constructor with parameters
//User::User(const string& username, const string& password, const bool& isAdmin)
//    : username(username), password(password), isAdmin(isAdmin) {
//}
//
//// Default constructor
//User::User() : username(""), password(""), isAdmin(false) {}
//
//// Login function
//bool User::login(const string& username, const string& password, const bool& isAdmin) {
//    return (this->username == username && this->password == password && this->isAdmin == isAdmin);
//}