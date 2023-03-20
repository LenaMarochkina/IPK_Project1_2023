# IPK Project 1: IPK Calculator Protocol
**title**: IPK Calculator Protocol\
**author**: Elena Marochkina\
**language**: en-US\
**gitea**: [xmaroc00](https://gitlab.fit.cvut.cz/emarochk/ipk-proj1)

#Table of Contents
1. [Description](#description)
2. [Usage](#usage)
3. [Included libraries](#included-libraries)
4. [Defined constants](#defined-constants)
5. [Global variables](#global-variables)
6. 

## Description

This repository contains an app which implement a client for the IPK Calculator
Protocol. The client is able to communicate with any server using IPKCP.

IPKCP is an application protocol for communicating with an Arithmetic as a Service (AaaS) provider.

## Usage
The client application requires three arguments to run:

- **-h host**: specifies the hostname of the server to connect to.\
- **-p port**: specifies the port number of the server to connect to.\
- **-m mode**: specifies the protocol to use for communication, either tcp or udp.

## Included libraries
The code uses the following libraries:

- stdio.h - for standard input/output operations.
- stdlib.h - for general purpose functions such as memory allocation and string conversions.
- unistd.h - for POSIX API functions like close().
- getopt.h - for parsing command-line arguments.
- string.h - for string manipulation functions such as strcmp().
- sys/socket.h - for socket related functions.
- netinet/in.h - for Internet address family (IPv4 and IPv6) related functions.
- arpa/inet.h - for IP address conversion functions.
- signal.h - for signal handling functions.

## Defined Constants
**BUF_SIZE** - an integer value to specify the maximum size of the message buffer.
## Global Variables
**buffer** - a character array used to store the message buffer.\
**SOCKET** - an integer value used to store the socket file descriptor\
**MODE** - a character pointer used to store the communication protocol mode

## Defined functions
1. **void validate(char\* host, int port)** - function to validate the command-line 
arguments.\

*Input Parameters*
- host - a character pointer to the server hostname.
- port - an integer to the server port number.\
    *Output*
- The function doesn't return anything, but it terminates the program with an error message if any of the arguments is invalid.

2. **void create_socket()** - function to create a socket and connect to the server.\
    *Input Parameters*
- MODE - a character pointer to the communication protocol mode.\
- SOCKET - an integer to the socket file descriptor.\
    *Output*
- The function doesn't return anything, but it creates a TCP socket using the socket function with the AF_INET domain, SOCK_STREAM type, and protocol value of 0 or
 a UDP socket using the socket function with the AF_INET domain, SOCK_DGRAM type, and protocol value of 0. 
- If the socket creation fails for either case, the function prints an error message using the perror function and exits the program with a failure status code using the exit function

3. **void tcp_client(char\* host, int port)** - function to communicate with the server using TCP.\
    *Input Parameters*
- host - a character pointer to the server hostname.
- port - an integer to the server port number.\
    *Output*
- 











## References

- [Pandoc](http://pandoc.org/)
- [Pandoc Manual](http://pandoc.org/MANUAL.html)
- [Wikipedia: Markdown](http://wikipedia.org/wiki/Markdown)