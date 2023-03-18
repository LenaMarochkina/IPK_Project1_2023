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
//void tcp_client(char *host, int port) {
//}

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

void tcp()

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
