#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));


	string Message = "give me message.";
	send(ServerSocket, Message.c_str(), Message.length(), 0);
	
	cout << Message << endl;

	char Buffer[1024] = { 0, };
	recv(ServerSocket, Buffer, 1024, 0);

	cout << "Server Sended : " << Buffer << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}