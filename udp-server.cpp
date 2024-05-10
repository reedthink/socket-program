#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;

//TODO 使用多线程处理连接

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }
    struct sockaddr_in servaddr {};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(6868);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cerr << "Error on binding" << std::endl;
        return 1;
    }
    std::cout << "UDP server up and running on port 6868" << std::endl;

    char buffer[BUFFER_SIZE];
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    while(true)
    {
        ssize_t recvbytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientaddr, &len);
        if (recvbytes < 0)
        {
            std::cerr << "Error receiving message" << std::endl;
            return 1;
        }
        buffer[recvbytes] = '\0';
        std::cout << "Received message:" << buffer << " from " << inet_ntoa(clientaddr.sin_addr) << std::endl;

        if (sendto(sockfd, buffer, recvbytes, 0, (const struct sockaddr * )&clientaddr, len) < 0)
        {
            std::cerr << "Error sending message" << std::endl;
            return 1;
        }
    }
    close(sockfd);
}