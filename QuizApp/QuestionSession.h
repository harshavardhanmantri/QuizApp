#pragma once

#include <string>
#include "Database.h"

class QuestionSession {
public:
    QuestionSession() : score() {}
    int startQuiz(int user_id, int quiz_id, bool isLogedIn, bool isAdmin);
    void submitQuiz(int session_id, const int score, bool isLogedIn, bool isAdmin);
    void provideFeedback(bool isLogedIn, bool isAdmin);
	void provideHistory(std::string username, bool isLogedIn, bool isAdmin);
private:
    int score;
};
