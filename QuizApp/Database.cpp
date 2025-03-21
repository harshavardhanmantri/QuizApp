#include<iostream>
#include<string>
#include "Database.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

//for demonstration only. never save your password in the code!


using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "Harsha@7676";


    Database::Database(){}

    sql::Connection* Database::useDatabase()
    {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        //sql::PreparedStatement* pstmt;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        //please create database "quickstartdb" ahead of time
        con->setSchema("quizapp");
        
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS users (id INT PRIMARY KEY AUTO_INCREMENT,username VARCHAR(50) NOT NULL UNIQUE,password VARCHAR(50) NOT NULL,isAdmin BOOLEAN NOT NULL,isLogedIn BOOLEAN NOT NULL);");
        cout << "Finished creating table" << endl;
        delete stmt;
        return con;

        //pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
        //pstmt->setString(1, "banana");
        //pstmt->setInt(2, 150);
        //pstmt->execute();
        //cout << "One row inserted." << endl;

        //pstmt->setString(1, "orange");
        //pstmt->setInt(2, 154);
        //pstmt->execute();
        //cout << "One row inserted." << endl;

        //pstmt->setString(1, "apple");
        //pstmt->setInt(2, 100);
        //pstmt->execute();
        //cout << "One row inserted." << endl;

        //delete pstmt;
        //delete con;

    }
