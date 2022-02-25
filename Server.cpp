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
    ServerAddr.sin_family = PF_INET;
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddr.sin_port = htons(5001);

    bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

    listen(ServerSocket, 0);

    SOCKADDR_IN ClientAddr;
    int ClientAddrSize = sizeof(ClientAddr);
    SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);

    string Message = "show me the money.";
    send(ClientSocket, Message.c_str(), Message.length(), 0);

    char Buffer[1024];
    recv(ClientSocket, Buffer, 1023, 0);

    cout << Buffer << endl;

    WSACleanup();

    return 0;
}