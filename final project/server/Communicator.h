#pragma once
#include <exception>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <map>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include <bitset>
#include <vector>
#include "json-develop/json-develop/single_include/nlohmann/json.hpp"
#include "Helper.h"
using json = nlohmann::json;
class Communicator
{
public:
	void startHandleRequests(int port);
private:
	void bindAndListen(int port);
	void acceptClient();
	void handleNewClient(SOCKET clientSock);
	//void m_handler_factory();
	SOCKET _serverSocket; 
	std::map<SOCKET, IRequestHandler*> m_client;
};

