#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;

int main() {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Set up the server address structure
    struct sockaddr_in servaddr {};
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP
    servaddr.sin_port = htons(6868); // Port

    // Message to be sent
    std::string message = "Hello, Server!";

    // Send the message to the server
    if (sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Error sending message" << std::endl;
        return 1;
    }

    std::cout << "Message sent to server." << std::endl;

    // Receive the message from the server
    char buffer[BUFFER_SIZE];
    struct sockaddr_in fromaddr;
    socklen_t fromlen = sizeof(fromaddr);

    ssize_t recvbytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&fromaddr, &fromlen);
    if (recvbytes < 0) {
        std::cerr << "Error receiving message" << std::endl;
        return 1;
    }

    // Null-terminate the buffer
    buffer[recvbytes] = '\0';

    // Print the received message
    std::cout << "Received message: " << buffer << " from " << inet_ntoa(fromaddr.sin_addr) << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}