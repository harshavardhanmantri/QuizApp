#include <stdlib.h>
#include <iostream>
#include<string>
#include "Question.h"
#include "QuestionSession.h"
#include "User.h"
#include "Quiz.h"
#include "Database.h"

using namespace std;
string username;
static void mainMenu() {
    cout << "Welcome to the Quiz App" << endl;
    cout << "1. Add User" << endl;
    cout << "2. Add Quiz" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

static void addUser(bool isLogedIn,bool isAdmin) {
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    //cout << "User added: " << user_id << ", " << username << ", " << password << endl;
    User user;
    user.registerUser(username, password, isAdmin ,isLogedIn);
}

static void addQuiz(bool isLogedIn,bool isAdmin) {
    Quiz quiz;
    string title, description;
    cout << "Enter quiz title: ";
    cin >> title;
    cout << "Enter quiz description: ";
    cin.ignore(); // To ignore the newline character left in the buffer
    getline(cin, description);
    quiz.createQuiz(title,description,isLogedIn, isAdmin);
    
}

static void addQuestionForAQuiz(bool isLogedIn, bool isAdmin) {
    Quiz quiz;
    Question question;
    string questionText="", options="", correctAnswer="";
    int quiz_id=0;
    quiz.getAllQuizes(isLogedIn,isAdmin);
    cout << "Enter the id for adding question to particular quiz";
    cin >> quiz_id;
    cin.ignore();
    cout << "Enter the question : " << endl;
    std::getline(std::cin, questionText);
    cout << "Enter the options in this format : " << endl;
    cout << "(1)..... (2)...... (3)...... (4)....." << endl;
    std::getline(std::cin, options);
    cout << "Enter option number of correct Answer :" << endl;
    cin >> correctAnswer;
    question.createQuestion(quiz_id,questionText,options,correctAnswer,isLogedIn,isAdmin);
}

static void getQuizById(bool isLogedIn, bool isAdmin) {
    Quiz quiz;
    Question question;
    string questionText="", options="", correctAnswer="";
    int quiz_id;
    quiz.getAllQuizes(isLogedIn, isAdmin);
    cout << "Choose the quiz by entering the id of quiz ";
    cin >> quiz_id;
    quiz.getQuizById(quiz_id, "harsha", isLogedIn, isAdmin);
}

int main() {
    int choice;
    bool isLogedIn=true, isAdmin=false;
    Quiz quiz;
	QuestionSession session;
    while (true) {
        mainMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            addUser(isLogedIn, isAdmin);
            break;
        case 2:
            addQuiz(isLogedIn, isAdmin);
            break;
        case 3:
            addQuestionForAQuiz(isLogedIn, isAdmin);
        case 4:
            cout << "Exiting..." << endl;
            return 0;
        case 5:
            getQuizById(isLogedIn,isAdmin);
            break;
        case 6:
            session.provideFeedback(isLogedIn,isAdmin);
            break;
		case 7:
            session.provideHistory("harsha", isLogedIn, isAdmin);
			break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

//int main()
//{
//    Database database;
//    database.useDatabase();
//    User user;
//    //user.registerUser("harsha", "kjadh0", false,false);
//    if (user.login("admin", "password123", true,false)) {
//        std::cout << "Login successful!" << std::endl;
//    }
//    else {
//        std::cout << "Login failed!" << std::endl;
//    }
//
//    return 0;
//}


