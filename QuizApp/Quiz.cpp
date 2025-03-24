#include "Quiz.h"
#include "Database.h"
#include "Question.h"
#include "QuestionSession.h"
#include<iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

void Quiz::createQuiz(const std::string& title, const std::string& description, bool isLogedIn, bool isAdmin)
{
    try {
        if (isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt;
            Database database;
            con = database.useDatabase();
            pstmt = con->prepareStatement("INSERT INTO quizes(title, description) VALUES(?,?)");
            pstmt->setString(1, title);
            pstmt->setString(2, description);
            pstmt->execute();
            cout << "One row inserted." << endl;
            delete pstmt;
        }
        else {
            cout << "Admin is not loged IN" << std::endl;
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

//void Quiz::updateQuiz(const std::string& title, const std::string& description, bool isLogedIn, bool isAdmin)
//{
//    try {
//        if (isAdmin && isLogedIn) {
//            sql::Connection* con;
//            sql::PreparedStatement* pstmt;
//            Database database;
//            con = database.useDatabase();
//            pstmt = con->prepareStatement("Update quizes set  INTO quizes(title, description) VALUES(?,?)");
//            pstmt->setString(1, title);
//            pstmt->setString(2, description);
//            pstmt->execute();
//            cout << "One row inserted." << endl;
//            delete pstmt;
//        }
//        else {
//            cout << "Admin is not loged IN" << std::endl;
//        }
//    }
//    catch (sql::SQLException& e) {
//        std::cerr << "SQL error: " << e.what() << std::endl;
//    }
//    catch (std::runtime_error& e) {
//        std::cerr << "Runtime error: " << e.what() << std::endl;
//    }
//    catch (...) {
//        cerr << "An unexpected error occurred." << endl;
//    }
//}

void Quiz::deleteQuizById(const int id, bool isLogedIn, bool isAdmin)
{
    return;
}

void Quiz::getAllQuizes(bool isLogedIn, bool isAdmin)
{
    try {
        if (isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt;
            sql::ResultSet* res;
            Database database;

            con = database.useDatabase();

            // Select data
            pstmt = con->prepareStatement("SELECT * FROM quizes");
            res = pstmt->executeQuery();
            bool isPresent = false;
            cout << "These are the quizes:" << endl;
            while (res->next()) {
                cout << "Id: "<<res->getInt("quiz_id");
                cout << " title: " << res->getString("title") << " description: " << res->getString("description") << endl;
                isPresent = true;
            }
            if (!isPresent) {
                cout << "No Quizes Available";
            }
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
        std::cerr << "An unexpected error occurred." << endl;
    }
}

void Quiz::getQuizById(const int id,string username, bool isLogedIn, bool isAdmin)
{
    try {
        if (!isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt;
            sql::ResultSet* res;
            Database database;
            QuestionSession session;
            Question question;
            con = database.useDatabase();
            pstmt = con->prepareStatement("SELECT * FROM users WHERE username = ?");

            pstmt->setString(1, username);

            pstmt->execute();
            res = pstmt->executeQuery();
            int user_id=0;
            while (res->next()) {
             user_id = res->getInt("id");
            break;
            }
            if (user_id) {
                int session_id = session.startQuiz(user_id, id, isLogedIn, isAdmin);
                int score = question.getAllQuestionsByQuizId(id, isLogedIn, isAdmin);
                session.submitQuiz(session_id, score, isLogedIn, isAdmin);
            }
            else {
                cout << "User not found";
            }
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
