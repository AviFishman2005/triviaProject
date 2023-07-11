#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomAdminRequestHandler:
    public IRequestHandler
{
public:
    RoomAdminRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, Room& m_room);
    ~RoomAdminRequestHandler();
    virtual bool isRequestRelevant(RequestInfo info) override;
    virtual RequestResult handleRequest(RequestInfo info) override;
    RequestResult getRoomState(RequestInfo info);
    RequestResult closeRoom(RequestInfo info);
    RequestResult startGame(RequestInfo info);
private:
    Room& m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};