//#pragma once
#ifndef USER_H_
#define USER_H_

#include "ChatRoom.h"
#include "Common.h"

class ChatRoom;

class User {
	 
public:
	TCPSocket* socket;
	string name;
	bool connectionStatus;
	User* connectioToUser;
	ChahrRoom* connectedToChatRoom;

public:
	User();
	virtual ~User();
	
};
#endif // !USER_H_


