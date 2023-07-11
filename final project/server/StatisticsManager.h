#pragma once
#include "SqliteDataBase.h"
class StatisticsManager
{
private: 
	IDatabase* m_database;

public:
	StatisticsManager(IDatabase* m_database);
	~StatisticsManager();
	std::list<Statistics> getHighScore();
	Statistics getUserStatistics(std::string username);
	void updateStatistics(std::string username, int score, int gamesPlayed, int answers, int correctAnswers, float averegeTime);
};

