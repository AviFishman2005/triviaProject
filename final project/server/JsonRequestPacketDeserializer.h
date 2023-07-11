#pragma once
#include <string>
#include <vector>
#include "json-develop/json-develop/single_include/nlohmann/json.hpp"
#include "Helper.h"
struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};
struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};
struct GetPlayerInRoomRequest
{
	unsigned int roomId;
};
struct JoinRoomRequest
{
	unsigned int roomId;
};
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);
	static GetPlayerInRoomRequest deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);
};



