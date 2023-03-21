# IPK Project 1: IPK Calculator Protocol
**Title**: IPK Calculator Protocol\
**Author**: Elena Marochkina\
**Language**: en-US\
**Supported OS**: Linux\
**Gitea**: [xmaroc00](https://gitlab.fit.cvut.cz/emarochk/ipk-proj1)

#Table of Contents
1. [Description](#description)
   1. [Compilation](#compilation)
   2. [Usage](#usage)
   3. [Included libraries](#included-libraries)
   4. [Defined constants](#defined-constants)
   5. [Global variables](#global-variables)
   6. [Defined functions](#defined-functions)
   7. [Main function](#main-function)
2. Testing
   1. [Testing the TCP client](#testing-the-tcp-client)
   2. [Testing the UDP client](#testing-the-udp-client)
3. [License](#license)

## Description

This repository contains an app which implement a client for the IPK Calculator
Protocol. The client is able to communicate with any server using IPKCP.

IPKCP is an application protocol for communicating with an Arithmetic as a Service (AaaS) provider.

## Compilation
### Linux
Before using the client, you need to compile the client.c file.\

To compile the client.c file, you can run **make build**, and to remove the ipkcpc executable 
file, you can run **make clean**.

### Windows
The program can be compiled for Windows.

## Usage
The client application requires three arguments to run:

- **-h host**: specifies the hostname of the server to connect to.\
- **-p port**: specifies the port number of the server to connect to.\
- **-m mode**: specifies the protocol to use for communication, either tcp or udp.


      Usage: ./ipkcpc -h host -p port -m mode

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

3. **void timeout()** - function to set a timeout value for the select() function when using UDP or TCP.\

*Input Parameters*
- SOCKET - an integer to the socket file descriptor.\

*Output*
- The function doesn't return anything, but it sets the timeout to 60 seconds and waits for incoming data on the socket using the select() function.
  If no data is received within the timeout period, it prints an error message and exits
  the program.

4.**void tcp_client(char\* host, int port)** - function to communicate with the server using TCP.\

*Input Parameters*
- host - a character pointer to the server hostname.
- port - an integer to the server port number.\

*Output*
- The function doesn't return anything, but it connects to the server using the connect() function and sends a message to the server using the send() function.\
  It then waits for a response from the server using the recv() function and prints the
  response to the console.\
This loop continues until the user types "BYE\n". Finally, it closes the socket using the close() function.

5. **void udp_client(const char\* server_ip, int server_port)** - function to communicate with the server using UDP.\

*Input Parameters*
- host - a character pointer to the server hostname.
- port - an integer to the server port number.\

*Output*
- The function doesn't return anything, but it sends a message to the server using the sendto() function and waits for a response from the server using the recvfrom() function.\
  This loop continues until the user terminates the program with Ctrl-C.\
  Finally, it closes the socket using the close() function.

6. **void sigint_handler(int signum)** - function to handle the SIGINT signal.\

*Input Parameters*
- signum - an integer to the signal number.\

- *Output*
- The function doesn't return anything, but it checks if the buffer is not empty, 
it clears the buffer using the memset function .\
If the MODE is "tcp", it sends the string "BYE\n" and waits for a response from the
server using the recvfrom function. \
Finally, the function closes the socket using the close function and exits the program 
with an exit code of 0.

## Main function
The main function takes two arguments **argc and argv[]**.

The main function *registers a signal handler* for SIGINT signal, which is generated when 
the user presses **Ctrl-C** on the terminal to stop the execution of the program.

It also **parses the command line arguments** using the **getopt** function. The arguments 
that it looks for are **-h** for host, **-p** for port, and **-m** for mode.\
These arguments are 
optional, but if they are specified, their values are stored in the **host, port, and MODE** 
variables respectively.

If any invalid argument is provided or any required argument is missing, the program 
will print an error message and exit.

Then, the program calls the **validate function** with **host** and **port** as arguments to validate 
if they are valid. After that, the program creates a socket using the **create_socket function**.

Finally, depending on the MODE, the program calls either the **tcp_client** or **udp_client** 
function with host and port as arguments to create a client connection.

The main function returns 0 to indicate successful execution of the program.

## Testing
### Testing for TCP client
The program was tested on the FIT VUT Linux server using the following commands:
[IMAGE_DESCRIPTION](https://git.fit.vutbr.cz/xmaroc00/IPK_Project1_2023/src/branch/master/TSP_1.png)
[IMAGE_DESCRIPTION](https://git.fit.vutbr.cz/xmaroc00/IPK_Project1_2023/src/branch/master/TSP_2.png)

### Testing for UDP client
The program was tested on the FIT VUT Linux server using the following commands:
[IMAGE_DESCRIPTION](https://git.fit.vutbr.cz/xmaroc00/IPK_Project1_2023/src/branch/master/UDP_1.png)

# License
This project is licensed under the GNU General Public License - see the 
[LICENSE](https://git.fit.vutbr.cz/xmaroc00/IPK_Project1_2023/src/branch/master/LICENSE.md)
file for details.

## References

1. [sys/socket.h - Internet Protocol family](https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html)
2. [netinet/in.h - Internet Protocol family](https://pubs.opengroup.org/onlinepubs/7908799/xns/netinetin.h.html)
3. [arpa/inet.h - Internet Protocol family](https://pubs.opengroup.org/onlinepubs/7908799/xns/arpainet.h.html)
4. [NESFIT - Stubs](https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Stubs)
5. [Wikipedia: Markdown](http://wikipedia.org/wiki/Markdown)