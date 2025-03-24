#pragma once
#include <iostream>
#include <string>

class Question {
public:
	Question() : questionText(""), quizId(0), options(""), correctAnswer(""), isLogedIn(false), isAdmin(false) {} // No-argument constructor
	void createQuestion(int quizId ,std::string questionText, std::string options, std::string correctAnswer, bool isLogedIn, bool isAdmin);
	//void updateQuiz(const std::string& title, const std::string& description, bool isLogedIn, bool isAdmin);
	void deleteQuestionById(const int id, bool isLogedIn, bool isAdmin);
	int getAllQuestionsByQuizId(int quizId,bool isLogedIn, bool isAdmin);
	void getQuestionById(const int id, bool isLogedIn, bool isAdmin);

private:
	std::string questionText="";
	int quizId=0;
	std::string options="";
	std::string correctAnswer="";
	bool isLogedIn;
	bool isAdmin;
};