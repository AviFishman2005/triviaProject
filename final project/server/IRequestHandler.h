#pragma once
#include <time.h> 
#include <vector>
#include <string>
#include "json-develop/json-develop/single_include/nlohmann/json.hpp"
#include "Helper.h"
#include "JsonRequestPacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
class IRequestHandler;
struct RequestResult;
struct RequestInfo
{
	int id;
	time_t rawtime;
	std::vector<unsigned char> buffer;
};

struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};



