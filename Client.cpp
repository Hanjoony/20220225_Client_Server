#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData WsaData;

	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "connect Error : " << GetLastError() << endl;
		exit(-1);
	}

	char Message[] = "give me message.";
	send(ServerSocket, Message, strlen(Message)+1, 0);
	
	cout << Message << endl;

	char Result[1024] = { 0, };
	recv(ServerSocket, Result, 1024, 0);

	cout << "Server Sended : " << Result << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}