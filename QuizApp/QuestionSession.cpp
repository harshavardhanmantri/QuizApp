#include "QuestionSession.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include<vector>

int QuestionSession::startQuiz(int user_id, int quiz_id, bool isLogedIn, bool isAdmin)
{
    try {
        if (!isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt;
            Database database;
            con = database.useDatabase();
            pstmt = con->prepareStatement("INSERT INTO quiz_session(user_id, quiz_id, score) VALUES(?,?,?)");
            pstmt->setInt(1, user_id);
            pstmt->setInt(2, quiz_id);
            pstmt->setInt(3, 0);
            pstmt->execute();
            pstmt = con->prepareStatement("select * FROM quiz_session WHERE user_id=? and quiz_id=?");
            pstmt->setInt(1, user_id);
            pstmt->setInt(2, quiz_id);
            sql::ResultSet* res = pstmt->executeQuery();
            while (res->next()) {
                return res->getInt("session_id");
            }

        }
        else {
            cout << "User is not loged IN" << std::endl;
        }
    }
    catch (sql::SQLException& e) {
        cout << "hello";
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        cerr << "An unexpected error occurred." << endl;
    }
}

void QuestionSession::submitQuiz(int session_id, const int score, bool isLogedIn, bool isAdmin)
{
    try {
        if (!isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt;
            Database database;
            con = database.useDatabase();
            cout << "hello";
            cout << session_id <<score;
            pstmt = con->prepareStatement("UPDATE quiz_session SET score = ? WHERE session_id = ?;");
            pstmt->setInt(1, score);
            pstmt->setInt(2, session_id);
            pstmt->execute();
            cout << "One row inserted." << endl;
            delete pstmt;
        }
        else {
            cout << "User is not loged IN" << std::endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        cerr << "An unexpected error occurred." << endl;
    }
}

void QuestionSession::provideFeedback(int session_id, bool isLogedIn, bool isAdmin)
{
}
