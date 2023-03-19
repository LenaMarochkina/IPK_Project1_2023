#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUF_SIZE 1024

//Global variables
char buffer[BUF_SIZE];
int SOCKET = -1;

//Function to validate arguments
void validate(char* host, int port, char* mode){

    //check if all arguments are entered
    if (host == NULL || port == 0 || mode == NULL) {
        fprintf(stderr, "Usage: %s -h host -p port -m mode\n");
        exit(EXIT_FAILURE);
    }

    //check if port is valid
    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Invalid port number. Please enter a port number between 1024 and 65535\n");
        exit(EXIT_FAILURE);
    }

    //check if mode is valid
    if (strcmp(mode, "tcp") != 0 && strcmp(mode, "udp") != 0) {
        fprintf(stderr, "Invalid mode. Please enter tcp or udp\n");
        exit(EXIT_FAILURE);
    }

    //check if host is valid
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, host, &(sa.sin_addr));
    if (result == 0) {
        fprintf(stderr, "Invalid host. Please enter a valid host\n");
        exit(EXIT_FAILURE);
    }
}

//Function to create socket
void create_socket (char* mode) {

    if (strcmp(mode, "tcp") == 0) {
        SOCKET = socket(AF_INET, SOCK_STREAM, 0);
        if (SOCKET < 0) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

    }
    else if (strcmp(mode, "udp") == 0) {
        SOCKET = socket(AF_INET, SOCK_DGRAM, 0);
        if (SOCKET < 0) {
            perror("socket");
            exit(EXIT_FAILURE);
        }
    }
}

//Function to send message to server and receive answer using TCP
void tcp_client(const char* server_ip, int server_port) {
    struct sockaddr_in server_addr;

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(SOCKET, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    while(strcmp(buffer, "BYE\n") != 0) {
        bzero (buffer, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        if (send(SOCKET, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            exit(EXIT_FAILURE);
        }

        // Receive a response from the server
        memset(buffer, 0, sizeof(buffer));
        if (recv(SOCKET, buffer, sizeof(buffer), 0) < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        printf("%s\n", buffer);
    }
    // Close the socket
    close(SOCKET);

}

//Function to send message to server and receive answer using UDP
void udp_client(const char* server_ip, int server_port) {

    // Set up the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    // Prompt the user for a message
    while (strcmp(buffer, "BYE\n") != 0) {
        bzero (buffer, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);

        //add \0 to the start of buffer
        char new_buffer[BUF_SIZE];
        new_buffer[0] = 0;
        new_buffer[1] = strlen(buffer);
        memcpy(new_buffer + 2, buffer, strlen(buffer));

        // Send the message to the server
        int len = sendto(SOCKET, new_buffer, strlen(buffer) + 2, 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if (len < 0) {
            perror("Failed to send message");
            close(SOCKET);
            exit(1);
        }

        // Receive the server's response
        memset(buffer, 0, sizeof(buffer));
        len = recvfrom(SOCKET, buffer, BUF_SIZE, 0, NULL, NULL);
        if (len < 0) {
            perror("Failed to receive response");
            close(SOCKET);
            exit(1);
        }

        int status_code = (int) buffer[1];
        if(status_code == 0){
            printf("%s\n", buffer + 2);
        } else {
            exit(1);
        }

    }
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

    validate(host, port, mode);
    create_socket(mode);

    //check if mode is tcp or udp
    if (strcmp(mode, "tcp") == 0){
        tcp_client(host, port);
    }
    else if (strcmp(mode, "udp") == 0){
        udp_client(host, port);
    }
    else{
        printf("Invalid mode. Please enter tcp or udp");
    }

    return 0;
}
