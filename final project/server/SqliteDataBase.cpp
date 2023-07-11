#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	this->open();
}

SqliteDataBase::~SqliteDataBase()
{
	this->close();
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	std::list<User> users;
	std::string msg = "SELECT * FROM USERS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, msg.c_str(), callbackUser, &users, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
	if (users.size() != 0)//if there is a match
	{
		return true;
	}
	return false;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	std::list<User> users;
	std::string msg = "SELECT * FROM USERS WHERE USERNAME = \"" + username + "\";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, msg.c_str(), callbackUser, &users, &errMessage);
	if (users.size() != 0)//if there is a match
	{
		if (users.begin()->password == password)
		{
			return true;
		}
	}
	return false;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	std::string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	sendSqlStatement(sqlStatement);
}

std::list<Question> SqliteDataBase::getQuestions(int amount)
{
	 std::list<Question> questions;
	 std::string msg = "SELECT * FROM QUESTIONS LIMIT " + std::to_string(amount) + ';';
	 char* errMessage = nullptr;
	 int res = sqlite3_exec(_db, msg.c_str(), callbackQuestion, &questions, &errMessage);
	 if (res != SQLITE_OK)
	 {
		 std::cout << errMessage << std::endl;
	 }

	 return questions;
}
//
//float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
//{
//	std::list<Statistics> stats;
//	std::string msg = "SELECT ANSWER_TIME FROM STATISTICS WHERE  USERNAME = \"" + username + "\" LIMIT 1;";
//	char* errMessage = nullptr;
//	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
//	if (res != SQLITE_OK)
//	{
//		std::cout << errMessage << std::endl;
//	}
//	return stats.begin()->avaregeTime;
//}
//
//int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
//{
//	std::list<Statistics> stats;
//	std::string msg = "SELECT CORRECT_ANSWERS FROM STATISTICS WHERE  USERNAME = \"" + username + "\" LIMIT 1;";
//	char* errMessage = nullptr;
//	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
//	if (res != SQLITE_OK)
//	{
//		std::cout << errMessage << std::endl;
//	}
//	return stats.begin()->correctAnswers;
//}
//
//int SqliteDataBase::getNumOfTotalAnswers(std::string username)
//{
//	std::list<Statistics> stats;
//	std::string msg = "SELECT ANSWERS FROM STATISTICS WHERE  USERNAME = \"" + username + "\" LIMIT 1;";
//	char* errMessage = nullptr;
//	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
//	if (res != SQLITE_OK)
//	{
//		std::cout << errMessage << std::endl;
//	}
//	return stats.begin()->answers;
//}
//
//int SqliteDataBase::getNumOfPlayerGames(std::string username)
//{
//	std::list<Statistics> stats;
//	std::string msg = "SELECT GAMES FROM STATISTICS WHERE  USERNAME = \"" + username + "\" LIMIT 1;";
//	char* errMessage = nullptr;
//	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
//	if (res != SQLITE_OK)
//	{
//		std::cout << errMessage << std::endl;
//	}
//	return stats.begin()->gamesPlayed;
//}

Statistics SqliteDataBase::getUserStatistics(std::string username)
{
	std::list<Statistics> stats;
	std::string msg = "SELECT * FROM STATISTICS WHERE  USERNAME = \"" + username + "\" LIMIT 1;";
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
	if (stats.size() == 0)
	{
		Statistics stat;
		stat.username = "no stats";
		stats.push_back(stat);
	}
	return stats.front();
}

std::list<Statistics> SqliteDataBase::getTop5()
{
	std::list<Statistics> stats;
	std::string msg = "SELECT * FROM STATISTICS ORDER BY HIGH_SCORE LIMIT 5;";
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, msg.c_str(), callbackStatistics, &stats, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
	return stats;
}

void SqliteDataBase::updateStatistics(std::string username, int score, int gamesPlayed, int answers, int correctAnswers, float averegeTime)
{
	Statistics stats =  getUserStatistics(username);
	//update states
	if (stats.username != username)
	{
		std::string sqlStatement = "insert into STATISTICS (USERNAME, HIGH_SCORE, GAMES, ANSWERS, CORRECT_ANSWERS, ANSWER_TIME) VALUES (\"" + username + "\", " + std::to_string(score)
			+ ", " + std::to_string(gamesPlayed) + ", " + std::to_string(answers) + ", " + std::to_string(correctAnswers) + ", " + std::to_string(averegeTime) + "); ";
		sendSqlStatement(sqlStatement);
	}
	else
	{
		averegeTime = (stats.avaregeTime * stats.answers + averegeTime * answers) / (stats.answers + answers);
		gamesPlayed += stats.gamesPlayed;
		answers += stats.answers;
		correctAnswers += stats.correctAnswers;
		if (score < stats.highScore)
		{
			score = stats.highScore;
		}

		std::string sqlStatement = "UPDATE STATISTICS SET GAMES = " + std::to_string(gamesPlayed) + ", ANSWERS = " + std::to_string(answers) + ", HIGH_SCORE = " + std::to_string(score) +
			", CORRECT_ANSWERS = " + std::to_string(correctAnswers) + ", ANSWER_TIME = " + std::to_string(averegeTime) + " WHERE USERNAME = \"" + username + "\";";
		//add high
		sendSqlStatement(sqlStatement);
	}
}

//opens db
bool SqliteDataBase::open()
{
	std::string dbFileName = "TriviaDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &_db);
	if (res != SQLITE_OK)
	{
		_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (doesFileExist != 0)
	{
		//add table
		std::string sqlStatements[] = { "create table if not exists USERS (USERNAME TEXT PRIMARY KEY, PASSWORD TEXT, EMAIL TEXT);", 
		"create table if not exists QUESTIONS (ID INTEGER PRIMARY KEY, QUESTION TEXT, CORRECT_ANSWER TEXT, ANSWER2 TEXT, ANSWER3 TEXT, ANSWER4 TEXT);", 
		"create table if not exists STATISTICS (USERNAME TEXT PRIMARY KEY, HIGH_SCORE INTEGER, GAMES INTEGER, ANSWERS INTEGER, CORRECT_ANSWERS INTEGER, ANSWER_TIME FLOAT);", 
		"INSERT INTO QUESTIONS (QUESTION, CORRECT_ANSWER, ANSWER2, ANSWER3, ANSWER4) VALUES (\"How many manned moon landings have there been?\", \"6\", \"3\", \"8\", \"1\"),"
			"(\"When was Adolf Hitler appointed as Chancellor of Germany?\", \"January 30, 1933\", \"September 1, 1939\", \"February 27, 1934\", \"October 6, 1936\"),"
			"(\"What year was the United States Declaration of Independence signed?\", \"1776\", \"1767\", \"1812\", \"1744\"), "
			"(\"Which building was set aflame on August 24th, 1812?\", \"The White House\", \"Parliament Building\", \"Pentegon\", \"Capital\"),"
			"(\"In 1939, Britain and France declared war on Germany after it invaded which country?\", \"Poland\", \"Russia\", \"Czechoslovakia\", \"Ukraine\"),"
			"(\"What was the original name of New York City?\", \"New Amsterdam\", \"New Paris\", \"New Rome\", \"New Brussels\"),"
			"(\"In what year did the Wall Street Crash take place?\", \"1929\", \"1930\", \"1939\", \"1933\"), "
			"(\"When was Google founded?\", \"September 4, 1998\", \"October 9, 1997\", \"December 12, 1989\", \"Feburary 7th, 2000\"),"
			"(\"Who led the Communist Revolution of Russia?\", \"Vladimir Lenin\", \"Joseph Stalin\", \"Vladimir Putin\", \"Leon Trotsky\"), "
			"(\"What year did Christopher Columbus dicover the new world?\", \"1492\", \"1520\", \"1430\", \"1544\")"};
		for (int i = 0; i < 4; i++)
		{
			sendSqlStatement(sqlStatements[i]);
		}
	}
	return true;
}

void SqliteDataBase::close()
{
	sqlite3_close(this->_db);
	_db = nullptr;
}

void SqliteDataBase::sendSqlStatement(std::string statement)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, statement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
}

//returns list of users
int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	User user;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "USERNAME") {
			user.username = argv[i];
		}
		if (std::string(azColName[i]) == "PASSWORD") {
			user.password = argv[i];
		}
		if (std::string(azColName[i]) == "EMAIL") {
			user.email = argv[i];
		}
	}
	std::list<User>* p = (std::list<User>*)data;
	p->push_back(user);
	return 0;
}

int callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	Question question;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "ID") {
			question.id = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "QUESTION") {
			question.question = argv[i];
		}
		else if (std::string(azColName[i]) == "CORRECT_ANSWER") {
			question.correctAnswer = argv[i];
		}
		else if (std::string(azColName[i]) == "ANSWER2") {
			question.answer2 = argv[i];
		}
		else if (std::string(azColName[i]) == "ANSWER3") {
			question.answer3 = argv[i];
		}
		else if (std::string(azColName[i]) == "ANSWER4") {
			question.answer4 = argv[i];
		}
	}
	std::list<Question>* p = (std::list<Question>*)data;
	p->push_back(question);
	return 0;
}

int callbackStatistics(void* data, int argc, char** argv, char** azColName)
{

	Statistics statistics;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "USERNAME") {
			statistics.username = argv[i];
		}
		else if (std::string(azColName[i]) == "GAMES") {
			statistics.gamesPlayed = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "HIGH_SCORE") {
			statistics.highScore = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "ANSWERS") {
			statistics.answers = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "CORRECT_ANSWERS") {
			statistics.correctAnswers = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "ANSWER_TIME") {
			statistics.avaregeTime = atof(argv[i]);
		}
	}
	std::list<Statistics>* p = (std::list<Statistics>*)data;
	p->push_back(statistics);
	return 0;
}
