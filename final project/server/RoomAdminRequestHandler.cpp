#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, Room& m_room) :
	m_user(loggedUser), m_roomManager(roomManager), m_handlerFactory(handlerFactory),m_room(m_room)
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
    
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.id == MT_CLOSE_ROOM) || (info.id == MT_GSTATE) || (info.id == MT_SGAME);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (!isRequestRelevant(info))
    {
        ErrorResponse error;
        error.message = "error: try again";
        result.response = JsonRequestPacketSerializer::serializeResponse(error);
        result.newHandler = nullptr;
    }
    /*   try
       {*/
    switch (info.id)
    {
    case(MT_CLOSE_ROOM):
        result = this->closeRoom(info);
        break;
    case(MT_GSTATE):
        result = this->getRoomState(info);
        break;
    case(MT_SGAME):
        result = this->startGame(info);
        break;
    }
    //Comment out for now for debugging
  /*  }
    catch (...)
    {
        ErrorResponse error;
        error.message = "error: try again";
        result.response = JsonRequestPacketSerializer::serializeResponse(error);
        result.newHandler = m_handlerFactory.createLoginRequestHandler();
    }*/
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
    RequestResult result;
    GetRoomStateResponse response;
    RoomData* thisRoom = m_room.getRoomData();
    response.players = m_roomManager.getAllUsers(thisRoom->id);
    response.status = OK;
    response.hasGameBegun = m_roomManager.getRoomState(thisRoom->id);
    response.questionCount = thisRoom->numOfQuestionsInGame;
    response.answerTimout = info.rawtime / 10000000000;// NOT SURE!!!!
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = nullptr;
    return result;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    RequestResult result;
    CloseRoomResponse response;
    m_roomManager.deleteRoom(m_room.getRoomData()->id);
    //this->m_handlerFactory.getStatisticsManager().updateStatistics();
    response.status = OK;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
   
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
    RequestResult result;
    StartGameResponse response;
    response.status = OK;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler =  nullptr;
	return result;
}
