#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomMemberRequestHandler :
    public IRequestHandler
{
public:
    RoomMemberRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, Room& m_room);
    ~RoomMemberRequestHandler();
    virtual bool isRequestRelevant(RequestInfo info) override;
    virtual RequestResult handleRequest(RequestInfo info) override;
    RequestResult getRoomState(RequestInfo info);
    RequestResult leaveRoom(RequestInfo info);
private:
    Room& m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};