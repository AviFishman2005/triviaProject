#include "Server.h"
#include "WSAInitializer.h"


Server::Server()
{
	this->m_database = new SqliteDataBase();
	

}

Server::~Server()
{


	delete m_database;
	m_database = nullptr;
}

void Server::run(int port)
{
	WSAInitializer wsaInit;
	m_communicator.startHandleRequests(port);
}
