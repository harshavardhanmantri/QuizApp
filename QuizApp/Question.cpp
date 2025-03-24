#include "Question.h"
#include "Database.h"
#include<iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include<vector>
using namespace std;
void Question::createQuestion(int quizId, std::string questionText, std::string options, std::string correctAnswer, bool isLogedIn, bool isAdmin)
{
    try {
        if (isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt,* pstmt1;
            Database database;
            sql::ResultSet* res;
            con = database.useDatabase();

            pstmt1 = con->prepareStatement("SELECT * FROM quizes WHERE quiz_id = ?");
            pstmt1->setInt(1, quizId);
            res = pstmt1->executeQuery();
            bool isPresent = false;
            while (res->next()) {
               isPresent = true;
            }
            if (!isPresent) {
                cout << "No Quizes Available";
                return;
            }

            pstmt = con->prepareStatement("INSERT INTO question(quiz_id,question_text,options,correct_answer) VALUES(?,?,?,?)");
            pstmt->setInt(1, quizId);
            pstmt->setString(2, questionText);
            pstmt->setString(3, options);
            pstmt->setString(4, correctAnswer);

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

void Question::deleteQuestionById(const int id, bool isLogedIn, bool isAdmin)
{

}

int Question::getAllQuestionsByQuizId(int quizId,bool isLogedIn, bool isAdmin)
{
    int score = 0; // Initialize score to 0
    try {
        if (!isAdmin && isLogedIn) {
            sql::Connection* con;
            sql::PreparedStatement* pstmt, * pstmt1;
            Database database;
            sql::ResultSet* res;
            con = database.useDatabase();
            score = 0;
            pstmt1 = con->prepareStatement("SELECT * FROM quizes WHERE quiz_id = ?");
            pstmt1->setInt(1, quizId);
            res = pstmt1->executeQuery();
            bool isPresent = false;
            while (res->next()) {
                isPresent = true;
            }
            if (!isPresent) {
                cout << "That Quiz is not Available";
                return -1;
            }

            pstmt = con->prepareStatement("SELECT * FROM question where quiz_id = ?");
            pstmt->setInt(1, quizId);

            res = pstmt->executeQuery();
            isPresent = false;
            score = 0;
            while (res->next()) {
                cout << "Q.> " << res->getString("question_text")<<std::endl<<"options>"<<std::endl<<res->getString("options")<<endl;
                string answer;
                cout << "Enter the option number: ";
                cin >> answer;
                if (answer == res->getString("correct_answer")) {
                    score++;
                }
                isPresent = true;
                
            }
            if (!isPresent) {
                cout << "No Questions available";
            }
            delete pstmt;
            return score;
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
    return 0;
}

void Question::getQuestionById(const int id, bool isLogedIn, bool isAdmin)
{
    return;
}
