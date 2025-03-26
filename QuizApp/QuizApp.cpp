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
    quiz.createQuiz(isLogedIn, isAdmin);
    
}
static void updateQuiz(bool isLogedIn, bool isAdmin) {
    Quiz quiz;
    quiz.updateQuiz(isLogedIn, isAdmin);

}

static void addQuestionForAQuiz(bool isLogedIn, bool isAdmin) {
    Quiz quiz;
    Question question;
    string questionText="", options="", correctAnswer="";
    int quiz_id=0;
    quiz.getAllQuizes(isLogedIn,isAdmin);
    if (isLogedIn && isAdmin) {
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
        question.createQuestion(quiz_id, questionText, options, correctAnswer, isLogedIn, isAdmin);
    }
}

static void getQuizById(bool isLogedIn, bool isAdmin) {
    Quiz quiz;
    Question question;
    string questionText="", options="", correctAnswer="";
    int quiz_id;
    quiz.getAllQuizes(isLogedIn, isAdmin);
    cout << isAdmin;
    if (isLogedIn && !isAdmin) {
        cout << "Choose the quiz by entering the id of quiz ";
        cin >> quiz_id;
        quiz.getQuizById(quiz_id, username, isLogedIn, isAdmin);
    }
}

static void mainMenuUser(bool isLogedIn, bool isAdmin) {
    int choice;
    User user;
    QuestionSession session;
   
    while (true) {
        cout << "\n=============================" << endl;
        cout << "       Welcome to the Quiz App" << endl;
        cout << "=============================" << endl;

        cout << "1. Start a Quiz" << endl;
        cout << "2. User's History" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
                getQuizById(isLogedIn, isAdmin);
                break;
        case 2:
            session.provideHistory(username,isLogedIn, isAdmin);
            break;
        case 3:
            user.logOut(username, isLogedIn);
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}


static void mainMenuAdmin(bool isLogedIn, bool isAdmin) {
    int choice;
    User user;
	Quiz quiz;
    QuestionSession session;
    
    while (true) {
        cout << "\n=============================" << endl;
        cout << "       Welcome to the Quiz App" << endl;
        cout << "=============================" << endl;
        cout << "1. Add Quiz" << endl;
		cout << "2. Get All Quizes" << endl;
		cout << "3. Update Quiz" << endl;
		cout << "4. Delete Quiz" << endl;
        cout << "5. Add Question for Quiz" << endl;
        cout << "6. Admin's Feedback" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {

        case 5: {
            addQuestionForAQuiz(isLogedIn, isAdmin);
            break;
        }
		case 4: {
			int id;
			cout << "Enter the id of the quiz you want to delete: ";
			cin >> id;
			quiz.deleteQuizById(id, isLogedIn, isAdmin);
			break;
		}
        case 1:
             addQuiz(isLogedIn, isAdmin);
        case 2:
			quiz.getAllQuizes(isLogedIn, isAdmin);
            break;
        case 3:
			updateQuiz(isLogedIn, isAdmin);
            break;
        case 6:
            session.provideFeedback(isLogedIn, isAdmin);
            break;
		case 7:
			user.logOut(username, isLogedIn);
			return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}
int main() {
    int choice;
    bool isLogedIn = false, isAdmin = false;
    Quiz quiz;
    User user;
    QuestionSession session;

    while (true) {
        cout << "\n=============================" << endl;
        cout << "       Welcome to the Quiz App" << endl;
        cout << "=============================" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Login as User" << endl;
        cout << "3. Login as Admin" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addUser(isLogedIn, isAdmin);
            break;
        case 2:
        {
            string password;
			isAdmin = false;
            bool check;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            check = user.login(username, password, isAdmin, isLogedIn);
            if (check) {
				mainMenuUser(isLogedIn,isAdmin);
            }
            break;
        }
        case 3: {
            string password;
			isAdmin = true;
            bool check;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            check = user.login(username, password, isAdmin, isLogedIn);
            if (check) {
                mainMenuAdmin(isLogedIn, isAdmin);
            }
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }      
    }
	return 0;
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


