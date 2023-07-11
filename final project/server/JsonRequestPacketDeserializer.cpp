#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
    LoginRequest request;
    
    json j = json::parse(buffer);

    request.password = j["password"].get<std::string>();
    request.username = j["username"].get<std::string>();

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
    SignupRequest request;
    json j = json::parse(buffer);
    request.password = j["password"].get<std::string>();
    request.username = j["username"].get<std::string>();
    request.email = j["email"].get<std::string>();
    
    return request;
}

GetPlayerInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer)
{
    GetPlayerInRoomRequest request;
    json j = json::parse(buffer);
    request.roomId = j["roomId"].get<unsigned int>();
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
    JoinRoomRequest request;
    json j = json::parse(buffer);
    request.roomId = j["roomId"].get<unsigned int>();
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
    CreateRoomRequest request;
    json j = json::parse(buffer);
    request.answerTimeOut = j["answerTimeOut"].get<unsigned int>();
    request.maxUsers = j["maxUsers"].get<unsigned int>();
    request.questionCount = j["questionCount"].get<unsigned int>();
    request.roomName = j["roomName"].get<std::string>();
    return request;
}
