#ifndef _ConnectionMaintainer_HG
#define _ConnectionMaintainer_HG

#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "Buffer.h"
#define UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "Ws2_32.lib")
#define PORT_NUMBER "5000"
#define BUFFER_LENGTH 512
#define ARRAY_SIZE 256
#define MSG_ID_JOIN_ROOM 1
#define MSG_ID_LEAVE_ROOM 2
#define MSG_ID_LEAVE_THE_MESSAGE 3


struct UserInfo {
	const char* ServerAdress;
	char* Room;
	char* Name;
	char* Message;
};

using namespace std;

class ConnectionMaintainer {
public:
	ConnectionMaintainer();
	~ConnectionMaintainer();
	WSADATA winsockData;
	SOCKET ConnectionSocket = INVALID_SOCKET;

	struct addrinfo* InfoResult =
		NULL;  // Holds the address information of our server
	struct addrinfo* Pointer = NULL;
	struct addrinfo Hints;
	int IResult;                  // code of the result of any command we use
	char recvbuf[BUFFER_LENGTH];  // The maximum buffer size of a message to send
	int recvbuflen = BUFFER_LENGTH;  // The length of the buffer we receive from the server

	// Is connetion still exist
	bool isAlive = 0;
	// Connection to the Server
	void Connect(UserInfo info);
	// Close the connection
	void closeConnection();
	// Send a message to the server
	void sendMessage(Buffer* connBuff, UserInfo info, char msgID,
		string message);
	// New Messeges
	string getMessages();
};

#endif