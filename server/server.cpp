#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Command.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS
// #include <WinSock.h>
// #pragma comment(lib, "WS2_32.lib")

void work_with_client(int clientSocket)
{
    int len = 0;
    char command[1000];
    auto com = Command();
    ModelUser* user = NULL;
    while (true)
    {
        read(clientSocket, (char*)&len, sizeof(len));
        read(clientSocket, (char*)&command, len * sizeof(char));
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
        write(clientSocket, (char*)&len, sizeof(len));
        write(clientSocket, com.get_answer().c_str(), len * sizeof(char));
    }
    close(clientSocket);
}

int main(int argc, char *argv[])
{
    // WORD wVersionRequested;
    // WSADATA wsaData;
    // wVersionRequested = MAKEWORD(2, 2);
    // if (WSAStartup(wVersionRequested, &wsaData) == WSAVERNOTSUPPORTED)
    // {
    //     std::cerr << "Version is not supported" << std::endl;
    //     WSACleanup();
    //     return 1;
    // }

    // SOCKET serverSocket, clientSocket;
    int serverSocket;
    int clientSocket;
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress, clientAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(atoi(argv[1]));

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "ERROR on binding";
        // WSACleanup();
        // closesocket(serverSocket);
        return 1;
    }
    const size_t numberUser = 5;
    listen(serverSocket, numberUser);

    socklen_t lengthAdr = sizeof(clientAddress);

    int i = 0;
    std::thread threads[numberUser];
    while (i < 5)
    {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &lengthAdr);
        threads[i] = std::thread(work_with_client, clientSocket);
        ++i;
    }
    for (size_t i = 0; i < numberUser; ++i)
    {
        threads[i].join();
    }

    close(serverSocket);

    return 0;
}
