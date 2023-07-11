#pragma once
#include <vector>
#include <string>
#include <bitset>
#include <iostream>
#include "json-develop/json-develop/single_include/nlohmann/json.hpp"
#include "Helper.h"
#include <list>
#include "Room.h"
using json = nlohmann::json;
struct LoginResponse
{
	unsigned int status;
};
struct LogoutResponse
{
	unsigned int status;
};
struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};
struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};
struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

};
struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

};
struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};
struct CloseRoomResponse
{
	unsigned int status;
};
struct ErrorResponse
{
	std::string message;
};
struct StartGameResponse
{
	unsigned int status;
};
struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	int answerTimout;//doesnt specify type so int for now
};
struct LeaveRoomResponse
{
	unsigned int status;


};
class JsonRequestPacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);
	static std::vector<unsigned char> serializeResponse(LogoutResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse response);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static std::vector<unsigned char> serializeResponse(GetHighScoreResponse response);
	static std::vector<unsigned char> serializeResponse(GetPersonalStatsResponse response);
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse response);
	static std::vector<unsigned char> serializeResponse(StartGameResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse response);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse response);

};


