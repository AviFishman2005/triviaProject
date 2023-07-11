#pragma once
#include "LoginManeger.h"



struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool isActive;
};


class Room
{
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

public:
	Room(RoomData data, LoggedUser firstUser);
	~Room();
	RoomData* getRoomData();
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();

};

