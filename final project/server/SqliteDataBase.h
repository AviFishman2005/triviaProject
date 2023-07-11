#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <iostream>
#include <list>
#include <vector>


class SqliteDataBase :
    public IDatabase
{
public:
    SqliteDataBase();
    ~SqliteDataBase();
    //users
    bool doesUserExist(std::string username) override;
    bool doesPasswordMatch(std::string username, std::string password) override;
    void addNewUser(std::string username, std::string password, std::string email) override;
    //questions
    std::list<Question> getQuestions(int amount) override;
    //statistics
    //float getPlayerAverageAnswerTime(std::string username) override;
    //int getNumOfCorrectAnswers(std::string username) override;
    //int getNumOfTotalAnswers(std::string username) override;
    //int getNumOfPlayerGames(std::string username) override;
    Statistics getUserStatistics(std::string username) override;
    std::list<Statistics> getTop5() override;
    void updateStatistics(std::string username, int score, int gamesPlayed, int answers, int correct_Answers, float averegeTime) override;


    //db
    bool open();
    void close();
    void sendSqlStatement(std::string statement);


private:
    sqlite3* _db;
};

static int callbackUser(void* data, int argc, char** argv, char** azColName);
static int callbackQuestion(void* data, int argc, char** argv, char** azColName);
static int callbackStatistics(void* data, int argc, char** argv, char** azColName);
