#pragma once
#include <iostream>
#include <string>
#include<vector>

class Quiz {
public:
	void createQuiz(const std::string& title, const std::string& description, std::int16_t score, bool isLogedIn, bool isAdmin);
	void updateQuiz(const std::string& title, const std::string& description, std::int16_t score, bool isLogedIn, bool isAdmin);
	void deleteQuiz(const int id);
	void getAllQuizes();
	void getQuizById(const int id);

private:
	std::string title;
	std::string description;
	std::vector<int> questions;
	std::int16_t score;
	bool isLogedIn;
	bool isAdmin;
};