#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <thread>

#include "Command.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock.h>
#pragma comment(lib, "WS2_32.lib")

void work_with_client(int socketClient)
{
    int len = 0;
    char command[1000];
    auto com = Command();
    ModelUser* user = NULL;
    while (true)
    {
        recv(socketClient, (char*)&len, sizeof(len), 0);
        recv(socketClient, (char*)&command, len * sizeof(char), 0);
        command[len] = '\0';
        if (strcmp(command, "exit") == 0)
        {
            delete user;
            user = NULL;
            break;
        }
        if (user == NULL)
        {
            user = com.loginCommand(command);
        }
        else
        {
            com.simpleCommand(user, command);
        }
        len = com.get_answer().length();
        send(socketClient, (char*)&len, sizeof(len), 0);
        send(socketClient, com.get_answer().c_str(), len * sizeof(char), 0);
    }
    closesocket(socketClient);
}

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) == WSAVERNOTSUPPORTED)
    {
        std::cerr << "Version is not supported" << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKET socketServer, socketClient;
    socketServer = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress, clientAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(1280);

    if (bind(socketServer, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "ERROR on binding";
        WSACleanup();
        closesocket(socketServer);
        return 1;
    }
    const size_t numberUser = 5;
    listen(socketServer, numberUser);

    int lengthAdr = sizeof(clientAddress);

    int i = 0;
    std::thread threads[numberUser];
    while (i < 5)
    {
        socketClient = accept(socketServer, (sockaddr*)&clientAddress, &lengthAdr);
        threads[i] = std::thread(work_with_client, socketClient);
        ++i;
    }
    for (size_t i = 0; i < numberUser; ++i)
    {
        threads[i].join();
    }

    closesocket(socketServer);

    return 0;
}
