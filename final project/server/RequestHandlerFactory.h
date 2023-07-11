#pragma once
#include "LoginManeger.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "SqliteDataBase.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room &room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room& room);
	LoginManeger& getLoginManeger();
	RoomManager& getRoomManager();
	StatisticsManager* getStatisticsManager();
private:
	RoomManager m_roomManager;
	StatisticsManager* m_statManager;
	LoginManeger m_loginManeger;
	IDatabase* m_database;
};
