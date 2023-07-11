#include "Communicator.h"
#include "RoomManager.h"
#include "SqliteDataBase.h"
#include <time.h>  
void Communicator::startHandleRequests(int port)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
	else
	{
		bindAndListen(port);
	}
}

void Communicator::bindAndListen(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		std::cout << WSAGetLastError() << std::endl;
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}

void Communicator::acceptClient()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	RequestHandlerFactory rh;
	m_client.emplace(client_socket, rh.createLoginRequestHandler());
	std::thread t(&Communicator::handleNewClient, this, client_socket);
	t.detach();
}
/// This function decides what to do with the client scoket and is the "main" of the server
void Communicator::handleNewClient(SOCKET clientSock)
{
	const int M_SIZE = 500;
	char buff[M_SIZE] = "";

	RequestInfo info;
	RequestResult result;
	auto handler = this->m_client.find(clientSock);

	RequestHandlerFactory factory;
	handler->second = factory.createLoginRequestHandler();
	try
	{
		while (true)
		{
			int id = Helper::getIntPartFromSocket(clientSock, 1);
			int size = Helper::getIntPartFromSocket(clientSock, 4);
			if (size > 0)
			{
				int res = recv(clientSock, buff, size, 0);

			}
			std::cout << "size" << size << std::endl;
			std::cout << "id" << id << std::endl;

			std::vector<unsigned char> data(buff, buff + size);
			info.buffer = data;
			for (int i = 0; i < data.size(); i++)
			{
				std::cout << data[i];
			}
			info.id = id;
			info.rawtime = time(NULL);
			result = handler->second->handleRequest(info);
			std::cout << "\n----"  << reinterpret_cast<char*>(result.response.data()) << "===" << result.response.size() << "----\n";
			send(clientSock, reinterpret_cast<char*>(result.response.data()), result.response.size(), 0);


			//check room
		/*	RoomManager rooms;
			LoggedUser user("Eli");
			LoggedUser user2("Other");

			RoomData dataRoom1;
			dataRoom1.id = 10;
			RoomData dataRoom2;
			dataRoom2.id = 11;
			rooms.createRoom(user, dataRoom1);
			rooms.createRoom(user2, dataRoom2);
			std::vector<RoomData> datas = rooms.getRooms();
			rooms.deleteRoom(10);*/

			//SqliteDataBase database;
			//database.setStatistics("Eli", 10, 1, 11, 4, 5.5);
			
			if (result.newHandler)
			{
				handler->second = result.newHandler;
			}
			
		}
	}
	catch (...)
	{
		
	}

	closesocket(clientSock);
}
