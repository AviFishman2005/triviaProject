#include "MenuRequestHandler.h"

int MenuRequestHandler::roomNumber = 0;
MenuRequestHandler::MenuRequestHandler(LoggedUser loggedUser, RoomManager& roomManager, RequestHandlerFactory& handlerFactory, StatisticsManager* statManager) :
   m_user(loggedUser), m_roomManager(roomManager), m_handlerFactory(handlerFactory), m_statManager(statManager)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
    return  (info.id == MT_CROOM) || (info.id == MT_JROOM) || (info.id == MT_LOGOUT) || (info.id == MT_PROOM) || (info.id == MT_STATS) || (info.id == MT_GROOM);
}
/// <summary>
/// This function gets a request from client, sorts it, and decides what to do with it
/// </summary>
/// <param name="info"></param>
/// <returns></returns>
RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
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
    case(MT_CROOM):
        result = this->createRoom(info);
        break;
    case(MT_JROOM):
        result = this->joinRoom(info);
        break;
    case(MT_LOGOUT):
        result = this->signOut(info);
        break;
    case(MT_PROOM):
        result = this->getPlayersInRoom(info);
        break;
    case(MT_STATS):
        result = this->getPersonalStats(info);
        break;
    case(MT_HSCORE):
        result = this->getHighScore(info);
        break;
    case(MT_GROOM):
        result = this->getRooms(info);
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
/// <summary>
/// Sign client out and send message that returs him to login menu
/// </summary>
/// <param name="info"></param>
/// <returns></returns>
RequestResult MenuRequestHandler::signOut(RequestInfo info)
{
    RequestResult result;
    LogoutResponse response;
    std::string username;
    username = this->m_user.getUsername();
    LoginManeger manage = m_handlerFactory.getLoginManeger();
    manage.logout(username);
    response.status = OK;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = m_handlerFactory.createLoginRequestHandler();
    return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
    RequestResult result;
    GetRoomsResponse response;
    response.rooms = this->m_roomManager.getRooms();
    response.status = OK;
    std::vector<unsigned char> data = JsonRequestPacketSerializer::serializeResponse(response);
    result.response = data;
    result.newHandler = nullptr;
    return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{

    RequestResult result;
    GetPlayersInRoomResponse response;
    GetPlayerInRoomRequest pRoom;
    pRoom = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
    response.players = m_roomManager.getAllUsers(pRoom.roomId);
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = nullptr;
    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
    RequestResult result;
    GetPersonalStatsResponse response;
    Statistics stats = m_statManager->getUserStatistics(m_user.getUsername());
    std::vector<std::string> statsVector;
    statsVector.push_back(stats.username);
    statsVector.push_back(std::to_string(stats.highScore));
    statsVector.push_back(std::to_string(stats.gamesPlayed));
    statsVector.push_back(std::to_string(stats.correctAnswers));
    statsVector.push_back(std::to_string(stats.answers));
    statsVector.push_back(std::to_string(stats.avaregeTime));

    response.status = OK;
    response.statistics = statsVector;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = nullptr;
    return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
    RequestResult result;
    GetHighScoreResponse response;
    std::list<Statistics> stats = m_statManager->getHighScore();
    response.status = OK;
    for (Statistics& c : stats) {
        response.statistics.push_back(c.username);
        response.statistics.push_back(std::to_string(c.highScore));
        /*response.statistics.push_back(std::to_string(c.gamesPlayed));
        response.statistics.push_back(std::to_string(c.correctAnswers));
        response.statistics.push_back(std::to_string(c.avaregeTime));
        response.statistics.push_back(std::to_string(c.answers));*/
    }
    response.status = OK;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = nullptr;
    return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
    RequestResult result;
    JoinRoomResponse response;
    JoinRoomRequest jRoom;
    jRoom = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
    Room* m = m_roomManager.getRoom(jRoom.roomId);
    //m.addUser(this->m_user);
    if (m == nullptr)
    {
        ErrorResponse error;
        error.message = "error: room does not exist";
        result.response = JsonRequestPacketSerializer::serializeResponse(error);
        result.newHandler = nullptr;
        return result;
    }
    try
    {
        m->addUser(this->m_user);
        response.status = OK;
        result.response = JsonRequestPacketSerializer::serializeResponse(response);
        result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, *this->m_roomManager.getRoom(jRoom.roomId));
        return result;
    }
    catch (const std::exception&)
    {
        ErrorResponse error;
        error.message = "error: try again";
        result.response = JsonRequestPacketSerializer::serializeResponse(error);
        result.newHandler = nullptr;
    }
    
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
    RequestResult result;
    CreateRoomResponse response;
    CreateRoomRequest cRoom;
    cRoom = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
    RoomData data;
    MenuRequestHandler::roomNumber += 1;
    data.id = MenuRequestHandler::roomNumber;
    data.isActive = false;
    data.maxPlayers = cRoom.maxUsers;
    data.name = cRoom.roomName;
    data.timePerQuestion = cRoom.answerTimeOut;
    data.numOfQuestionsInGame = cRoom.questionCount;
    this->m_roomManager.createRoom(this->m_user.getUsername(), data);
    response.status = 1;
    result.response = JsonRequestPacketSerializer::serializeResponse(response);
    result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, *this->m_roomManager.getRoom(MenuRequestHandler::roomNumber));
    std::vector<RoomData> rooms= this->m_roomManager.getRooms();

    return result;
}
