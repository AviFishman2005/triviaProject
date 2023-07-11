#pragma once
#include "Room.h"
#include <map>
#include <vector>

class RoomManager
{
private:
	static std::map<int, Room*> m_rooms;

public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
	Room* getRoom(int id);
	std::vector<std::string> getAllUsers(int id);

};

