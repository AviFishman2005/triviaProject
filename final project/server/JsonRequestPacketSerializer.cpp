#include "JsonRequestPacketSerializer.h"
// For now codes are 1 2 3...


std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(LoginResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_LOG_IN, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(SignupResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_SIGN_UP, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(ErrorResponse response)
{
	
	json j;
	j["message"] = response.message;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_ERROR, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(LogoutResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_LOGOUT, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse response)
{
	
	json j;
	std::string roomsStr = "";
	RoomData currRoom;
	for (std::size_t i = 0; i < response.rooms.size(); ++i) {
		roomsStr += std::to_string(response.rooms[i].id); 
		roomsStr += ',';
		roomsStr += std::to_string(response.rooms[i].isActive);
		roomsStr += ',';
		roomsStr += std::to_string(response.rooms[i].maxPlayers);
		roomsStr += ','; 
		roomsStr += response.rooms[i].name;
		roomsStr += ',';
		roomsStr += std::to_string(response.rooms[i].numOfQuestionsInGame);
		roomsStr += ',';
		roomsStr += std::to_string(response.rooms[i].timePerQuestion);
		roomsStr += ',';

		

	}
	j["Rooms"] = roomsStr;
	j["status"] = response.status;

	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_GROOM, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json j;
	std::string playersStr;
	for (auto it = response.players.begin(); it != response.players.end(); it++)
	{

		playersStr += it->c_str();
		playersStr += ",";
	}	
	j["players"] = playersStr;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_PROOM, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_JROOM, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_CROOM, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(GetHighScoreResponse response)
{
	json j;
	j["status"] = response.status;
	//Maybe need to format diffarently later
	std::string statsStr;


	std::vector<std::string> stats = response.statistics;
	for (auto it = stats.begin(); it != stats.end(); it++)
	{
		
		statsStr += it->c_str();
		statsStr += ',';
	}
	j["statistics"] = statsStr;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_HSCORE, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(GetPersonalStatsResponse response)
{
	json j;
	j["status"] = response.status;
	//Maybe need to format diffarently later
	std::string statsStr;


	std::vector<std::string> stats = response.statistics;
	for (auto it = stats.begin(); it != stats.end(); it++)
	{

		statsStr += it->c_str();
		statsStr += ',';
	}
	j["statistics"] = statsStr;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_STATS, vector);
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(CloseRoomResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_CLOSE_ROOM, vector);
}
std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(StartGameResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_SGAME, vector);
}
std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(GetRoomStateResponse response)
{
	json j;
	j["status"] = response.status;
	j["answerTimeout"] = response.answerTimout;
	j["hasGameBegun"] = response.hasGameBegun;
	std::string playersStr;
	for (auto it = response.players.begin(); it != response.players.end(); it++)
	{

		playersStr += it->c_str();
		playersStr += ",";
	}
	j["players"] = playersStr;
	j["questionCount"] = response.questionCount;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_GSTATE, vector);
}
std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse response)
{
	json j;
	j["status"] = response.status;
	std::string strJ = j.dump();
	std::vector<unsigned char> vector(strJ.begin(), strJ.end());
	return Helper::toBinarySerialize(MT_SGAME, vector);
}