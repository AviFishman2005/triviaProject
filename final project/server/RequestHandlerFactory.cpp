#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
    this->m_database = new SqliteDataBase;
    m_loginManeger.setDatabase(m_database);
    this->m_statManager = new StatisticsManager(m_database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
    //delete this->m_statManager;
    //delete this->m_database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* p = new LoginRequestHandler(m_loginManeger, *this);
    return p;
}
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
    LoggedUser user(username);
   
    MenuRequestHandler* m = new MenuRequestHandler(user, m_roomManager, *this, m_statManager);
    return m;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
    RoomAdminRequestHandler* adminRoom = new RoomAdminRequestHandler(user, m_roomManager, *this, room);

    return adminRoom;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
    RoomMemberRequestHandler* memberRoom = new RoomMemberRequestHandler(user, m_roomManager, *this, room);

    return memberRoom;
}



LoginManeger& RequestHandlerFactory::getLoginManeger()
{
    return m_loginManeger;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager* RequestHandlerFactory::getStatisticsManager()
{
    return m_statManager;
}
    