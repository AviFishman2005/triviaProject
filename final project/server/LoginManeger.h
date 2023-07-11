#pragma once
#include <iostream>
#include "SqliteDataBase.h"
#include <vector>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	LoggedUser();
	~LoggedUser();
	std::string getUsername() const;
	bool isEqual(LoggedUser& other) const;
	bool operator==(const LoggedUser& other) const;

private:
	std::string m_username;
};


class LoginManeger
{
private:
	IDatabase* m_database;
	static std::vector<LoggedUser> m_loggedUsers;

public:
	void setDatabase(IDatabase* database);
	LoginManeger();
	~LoginManeger();
	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	void logout(std::string username);

};
