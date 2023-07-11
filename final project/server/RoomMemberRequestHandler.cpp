#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, Room& m_room) :
    m_user(loggedUser), m_roomManager(roomManager), m_handlerFactory(handlerFactory), m_room(m_room)
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{

}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (info.id == MT_LROOM) || (info.id == MT_GSTATE);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
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
    case(MT_LROOM):
        result = this->leaveRoom(info);
        break;
    case(MT_GSTATE):
        result = this->getRoomState(info);
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

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
;
    RequestResult result;
  
    GetRoomStateResponse response;
    RoomData* thisRoom = m_room.getRoomData();
    if (m_roomManager.getRoom(thisRoom->id))
    {
        response.players = m_roomManager.getAllUsers(thisRoom->id);
        response.status = OK;
        response.hasGameBegun = m_roomManager.getRoomState(thisRoom->id);
        response.questionCount = thisRoom->numOfQuestionsInGame;
        response.answerTimout = info.rawtime / 10000000000;// NOT SURE!!!!
        result.response = JsonRequestPacketSerializer::serializeResponse(response);
        result.newHandler = nullptr;
    }
    else
    {
        result.response = JsonRequestPacketSerializer::serializeResponse(response);
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
    }
  
    
    return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
    RequestResult result;
    CloseRoomResponse response;
    m_room.removeUser(this->m_user);
    response.status = OK;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
    return result;
}


