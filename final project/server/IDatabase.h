#pragma once
#include <string>
#include <list>

struct User
{
    std::string username;
    std::string password;
    std::string email;
};
struct Question
{
    int id;
    std::string question;
    std::string correctAnswer;
    std::string answer2;
    std::string answer3;
    std::string answer4;
};
struct Statistics
{
    std::string username;
    int highScore;
    int gamesPlayed;
    int answers;
    int correctAnswers;
    float avaregeTime;
};


class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;

    virtual std::list<Question> getQuestions(int amount) = 0;

    //virtual float getPlayerAverageAnswerTime(std::string username) = 0;
    //virtual int getNumOfCorrectAnswers(std::string username) = 0;
    //virtual int getNumOfTotalAnswers(std::string username) = 0;
    //virtual int getNumOfPlayerGames(std::string username) = 0;
    virtual Statistics getUserStatistics(std::string username) = 0;
    virtual std::list<Statistics> getTop5() = 0;
    virtual void updateStatistics(std::string username, int score, int gamesPlayed, int answers, int correct_Answers, float averegeTime) = 0;
};
