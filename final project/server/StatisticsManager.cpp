#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* m_database)
{
    this->m_database = m_database;
}

StatisticsManager::~StatisticsManager()
{
}

std::list<Statistics> StatisticsManager::getHighScore()
{
    return m_database->getTop5();;
}

Statistics StatisticsManager::getUserStatistics(std::string username)
{
    return m_database->getUserStatistics(username);
}

void StatisticsManager::updateStatistics(std::string username, int score, int gamesPlayed, int answers, int correct_Answers, float averegeTime)
{
    m_database->updateStatistics(username, score, gamesPlayed, answers, correct_Answers, averegeTime);
}
