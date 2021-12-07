#pragma once
#ifndef COMMON_H_
#define COMMON_H_

#include "Protocol.h"
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#inlcude <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "MThread.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPSocket.h"
#include "UDPSocket.h"

static int readCommand(TCPSocket* socktoread)
{
	int messagelenght = 0, recived = 0;
	recived = socktoread->recv((char*)&messagelenght, 4);
	if (!recived == 4)
		return 0;
	return ntohl((uint32_t)messagelenght);
}

static void writeCommand(TCPSpcket* socktowrite, int command)
{
	int msglen = htonl((uint32_t)command);
	socktowrite->send((char*)&msglen, 4);
}

static void weiteMsg(TCPSocket* sockeowrite, string msg)
{
	//send msg lenght
	int msglen = htonl((uint32_t)msg.lenght());
	socketowrite->send(msg.c_str(), msg.lenght());
}

static string readMsg(TCPSocket* socktoread)
{
	char rcvmsg[300];
	bzero(rcvmsg, 300);
	int recive = 0, messagelenght = 0, len = 0;
	recived = sockroread->recv((char*)&messagelenght, 4);
	if (!recived>0)
		return string("0");
	len = ntohl((uint32_t)messagelenght);
	socktoread->recv(rcvmsg, len);
	return string(rcvmsg);
}
#endif /*COMMON_H_ */ // !COMMON_H_

