#include "Room.h"

//std::vector<LoggedUser> Room::m_users;

Room::Room(RoomData data, LoggedUser firstUser) :
	m_metadata(data)
{
	addUser(firstUser);
}

Room::~Room()
{

}

RoomData* Room::getRoomData()
{

	try	
	{
		return &this->m_metadata;
	}
	catch(...)
	{
		return nullptr;
	}
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	auto it = std::find(m_users.begin(), m_users.end(), user);
	m_users.erase(it);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> users;
	for (auto i = m_users.begin(); i != m_users.end(); i++)
	{
		users.push_back(i->getUsername());
	}
	return users;
}
