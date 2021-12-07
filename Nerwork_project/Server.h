#pragma once


#ifndef SERVER_H_
#define SERVER_H_

#include "LoginAndSignUp.h"
#include "Common.h"

class Server : public MThread {

	TCPSoket* listen_sock; // listen socket
	LoginAndSignUp* loginAndSign; // all incoming connection are hhandle by this obhect
	bool status;

public:
	Server();
	void printAllUsers();
	void ptintUsers();
	void printSessions();
	void ptrintChatRooms();
	void printUsersInChatRoom();
	void close();

	virtual ~Server();
	void run();
};
#endif /* SERVER_H_*/   // !SERVER_H_
