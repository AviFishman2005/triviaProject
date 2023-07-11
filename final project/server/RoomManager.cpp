#include "RoomManager.h"


std::map<int, Room*> RoomManager::m_rooms;

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room* newRoom = new Room(data, user);//create
	m_rooms.emplace(data.id, newRoom);
}

void RoomManager::deleteRoom(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if (i->first == id)//find correct room
		{
			//Room* room = i->second;
			delete i->second;
			m_rooms.erase(i);
			break;
		}
	}

}

unsigned int RoomManager::getRoomState(int id)
{
	int state = 0;
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if (i->first == id)//find correct room
		{
			state = i->second->getRoomData()->isActive;
			return state;
		}
	}
	return -1;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		rooms.push_back(*i->second->getRoomData());
	}
	return rooms;
}

Room* RoomManager::getRoom(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if (i->first == id)//find correct room
		{
			//Room* room = i->second;
			return i->second;
		}
	}
	return nullptr;
}

std::vector<std::string> RoomManager::getAllUsers(int id)
{
	std::vector<std::string> users;
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if (i->first == id)//find correct room
		{
			users = i->second->getAllUsers();
			return users;

		}
	}
	return users;
}


