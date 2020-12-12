﻿#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <limits>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd,
        n;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket";
        return 1;
    }

    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_port          = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr   = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR connecting";
        close(sockfd);
        return 1;
    }

    char command[1000];
    char answer[1000];
    int len = 0;
    while (true)
    {
        std::cout << ">";
        std::cin.getline(command, 64, '\n');
        if (strcmp(command, "exit") == 0)
        {
            len = strlen(command);
            write(sockfd, (char*)&len, sizeof(len));
            write(sockfd, (char*)&command, len * sizeof(char));
            break;
        }
        else
        {
            len = strlen(command);
            write(sockfd, (char*)&len, sizeof(len));
            write(sockfd, command, len * sizeof(char));
            read(sockfd, (char*)&len, sizeof(len));
            read(sockfd, answer, len * sizeof(char));
            answer[len] = '\0';
            std::cout << answer << std::endl;
        }
    }

    close(sockfd);
    return 0;
}