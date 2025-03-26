#pragma once
#include <iostream>
#include <string>
#include<vector>

class Quiz {
public:

	Quiz() : title(""), description(""), isLogedIn(false), isAdmin(false) {}
	void createQuiz(bool isLogedIn, bool isAdmin);
	void updateQuiz(bool isLogedIn, bool isAdmin);
	void deleteQuizById(const int id, bool isLogedIn, bool isAdmin);
	void getAllQuizes(bool isLogedIn, bool isAdmin);
	void getQuizById(const int id,std::string username, bool isLogedIn, bool isAdmin);

private:
	std::string title;
	std::string description;
	bool isLogedIn;
	bool isAdmin;
};