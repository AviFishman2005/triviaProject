#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "StatisticsManager.h"
class RequestHandlerFactory;
class MenuRequestHandler :
    public IRequestHandler
{
public:
    static int roomNumber;
    MenuRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, StatisticsManager* statManager);
    ~MenuRequestHandler();
    virtual bool isRequestRelevant(RequestInfo info) override;
    virtual RequestResult handleRequest(RequestInfo info) override;
    virtual RequestResult signOut(RequestInfo info);
    RequestResult getRooms(RequestInfo info);
    RequestResult getPlayersInRoom(RequestInfo info);
    RequestResult getPersonalStats(RequestInfo info);
    RequestResult getHighScore(RequestInfo info);
    RequestResult joinRoom(RequestInfo info);
    RequestResult createRoom(RequestInfo info);
private:
    LoggedUser m_user;
    RoomManager& m_roomManager;
    StatisticsManager* m_statManager;
    RequestHandlerFactory& m_handlerFactory;
};