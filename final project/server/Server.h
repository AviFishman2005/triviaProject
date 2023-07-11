#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class Server
{
public:
	Server();
	~Server();
	void run(int port);

private:
	SqliteDataBase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
	

	/*Server();
	~Server();
	void serve(int port);
	void queueHandler();
private:

	void acceptClient();
	void clientHandler(SOCKET clientSocket);
	std::string getUsers();
	std::set<std::string> users;
	std::queue<std::string> msgQueue;
	SOCKET _serverSocket;*/
};

//std::string filetostring(std::string path);

