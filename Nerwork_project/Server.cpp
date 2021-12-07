#include "Server.h"
#include "Protocol.h"
#include <iostream>
void print_instructions();

int main()
{
	Server server;
	std::string command;

	std::cout << "*** WELCOME TO THE SERVER APPLICATION ***" << std::endl;

	print_instructions();

	do
	{
		std::cin >> command;

		if (command == "lcu") //list all connected users
		{
			server.printUsers();
		}
		else if (command == "lu") // list all users
		{
			server.printAllUsers();
		}
		else if (command == "ls") // list all sessions
		{
			server.printSessions();
		}
		else if (command == "lr") // list all chatrooms
		{
			server.printChatRooms();
		}
		else if (command == "lru") // list all users in a chatroom
		{
			server.printUsersInChatRooms();
		}
		else if (command == "p") // instruction
		{
			print_instructions();
		}
		else
		{
			std::cout << "** BAD COMMAND **" << std::endl;
		}
	}
		while (command != "x");

		return 0;
}

	void print_instructions()
	{
		std::cout << std::endl;
		std::cout << "Your commands:" << std::endl;
		std::cout << "lu	-	list all users" << std::endl;
		std::cout << "lcu	-	list all conncted users" << std::endl;
		std::cout << "ls	-	list all sessions" << std::endl;
		std::cout << "lr	-	list all chatrooms" << std::endl;
		std::cout << "lru <Room Name>	- list all users in a chatrooms" << std::endl;
		std::cout << "p		-	print commands" << std::endl;
		std::cout << "x		-	close the app" << std::endl;
		std::cout << std::endl;
	}

	Server::Server() :loginAndSign(new LoginAndSignUp) {

		listen_sock = NULL;

		status = false;
		this->start();
	}

	void Server::printAllUsers()
	{
		std::vector<string> names = liginAndSign->getAllUsers();
		std::cout << "*** All users list ***" << std::endl;
		for (unsigned int i = 0; i < names.size; i++)
		{
			std::cout << "User #" << i + 1 << ": " << names[i] << std::endl;
		}
	}

	void Server::printUsers()
	{
		loginAndSign->ptinyUsers();

	}
	void Server::ptintSessions()
	{
		loginAndSign->printSessions();
	}
	void Server::ptintChatRooms()
	{
		loginAndSign->printChatRooms();
	}

	void Server::run()
	{

		status = true;
		listen_sock = new TCPSocket(SERVER_PORT);
		sleep(2);				// uncnow 
		std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

		while (status == true)
		{
			TCPSocket* temp_sock = listen_sock->listenAndAccept();

			if (!temp_sock)
				continue;
			else
			{
				loginAndSign->addPeer(temp_sock);
			}
		}
		std::cout << "Server stopped running" << std::endl;
	}

	void Server::close()
	{
		std::cout << "Server application in closing ..." << std::endl;
		status = false;
		loginAndSign->close();
		loginAndSign->waitForThread();
		listen_sock->cclose();
		// listen_sock_waitForThread();
		delete(loginAndSign);
		if (listen_sock != NULL)
			delete (listen_sock);
	}

	Server::~Server() {

	}