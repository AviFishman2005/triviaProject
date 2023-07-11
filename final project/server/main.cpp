#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#define EXIT_MSG "EXIT"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		std::thread threadConnections(&Server::run, &myServer, 4554);
		threadConnections.detach();
		while (true)//till exit
		{
			std::string msg = "";
			std::cin >> msg;
			if (msg == EXIT_MSG)
			{
				return 0;
				//threadConnections.~thread();
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}