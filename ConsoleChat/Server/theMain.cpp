#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>

//#include "BufferThing.h"

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

// #pragma comment (lib, "Mswsock.lib")
#define BUFFER_LENGTH 512  // Default buffer length of our buffer in characters
#define PORT_NUMBER "5000"  // The default port to listen on

typedef struct _SOCKET_INFORMATION {
	char Buffer[BUFFER_LENGTH];
	WSABUF WsaBuffer;
	SOCKET Socket;
	OVERLAPPED Overlapped;
	DWORD BytesSEND;
	DWORD BytesRECV;
	std::vector<std::string> rooms;  // Rooms
	std::string UserName;            // Name
	bool GotNewData = 0;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

LPSOCKET_INFORMATION SocketArray[FD_SETSIZE];
int iRes;
FD_SET WriteSet;
FD_SET ReadSet;
BOOL CreateSocketInformation(SOCKET s);
void FreeSocketInformation(DWORD Index);
void ReadSocket(LPSOCKET_INFORMATION sa);
void sendMsg(LPSOCKET_INFORMATION sa, std::string msg, std::string userName);
void TreatMessage(LPSOCKET_INFORMATION sa, std::string msg);
DWORD TotalSockets = 0;

int main(void)
{
	//Winsock
	WSADATA winsockData;
	SOCKET clientSocket;
	SOCKET listenSocket;
	SOCKADDR_IN InternetAddress;
	DWORD i, Total;
	ULONG NonBlock;
	DWORD Flags, SendBytes, RecvBytes;

	//address
	struct addrinfo* result = NULL; 
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));

	// Initialize Winsock
	iRes = WSAStartup(MAKEWORD(2, 2), &winsockData);
	if (iRes != 0)
	{
		printf("WSAStartip Fail: %d\n", iRes);
		return 1;
	}

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;


}