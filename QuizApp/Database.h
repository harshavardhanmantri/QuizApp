#include<iostream>
#include<string>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//for demonstration only. never save your password in the code!


using namespace std;


class Database {
public:
    Database();
    sql::Connection* useDatabase();
    
};