#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUF_SIZE 1024

//Function to send message to server and receive answer using TCP
void tcp_client(const char* server_ip, int server_port) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }


    // Send a message to the server
    while(strcmp(buffer, "BYE\n") != 0) {
        bzero (buffer, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            exit(EXIT_FAILURE);
        }

        // Receive a response from the server
        memset(buffer, 0, sizeof(buffer));
        if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        printf("Server response: %s\n", buffer);
    }
    // Close the socket
    close(sockfd);

}

//Function to send message to server using UDP

void udp_client(const char* server_ip, int server_port) {
    // Create a UDP socket
    // TODO: Change bite shift
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // Set up the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    // Prompt the user for a message
    char message[BUF_SIZE];
    printf("Enter a message: ");
    fgets(message, BUF_SIZE, stdin);
    printf("Message: %d\n", strlen(message));

    // Send the message to the server
    int len = sendto(sock, message, strlen(message), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (len < 0) {
        perror("Failed to send message");
        close(sock);
        exit(1);
    }

    // Receive the server's response
    char buffer[1024];
    memset(buffer, 0, BUF_SIZE);
    len = recvfrom(sock, buffer, BUF_SIZE, 0, NULL, NULL);
    if (len < 0) {
        perror("Failed to receive response");
        close(sock);
        exit(1);
    }

    printf("Received response: %s\n", buffer);

    close(sock);
}

int main(int argc, char *argv[]) {
    int opt;
    char *host = NULL;
    int port = 0;
    char *mode = NULL;

    // parsing arguments from command line
    while ((opt = getopt(argc, argv, "h:p:m:")) != -1) {
        switch (opt) {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'm':
                mode = optarg;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s -h host -p port -m mode\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (host == NULL || port == 0 || mode == NULL) {
        fprintf(stderr, "Usage: %s -h host -p port -m mode\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("host=%s, port=%d, mode=%s\n", host, port, mode);
    if (strcmp(mode, "tcp") == 0){
        //tcp_client(host, port);
    }
    else if (strcmp(mode, "udp") == 0){
        printf("here\n");
        udp_client(host, port);
    }
    else{
        printf("Invalid mode. Please enter tcp or udp");
    }

    return 0;
}
