# IPK Project 1: IPK Calculator Protocol
**Title**: IPK Calculator Protocol\
**Author**: Elena Marochkina\
**Language**: en-US\
**Supported OS**: Linux\
**Gitea**: [xmaroc00](https://gitlab.fit.cvut.cz/emarochk/ipk-proj1)

# Brief Description
The program allows the user to send and receive messages to a server using either the TCP 
or UDP protocol. The program takes in the host name, port number, and mode (TCP or UDP) 
as command-line arguments. It validates the arguments to make sure they are valid, creates 
a socket based on the protocol mode, and then sends and receives messages to and from the server.

The program includes several functions that perform different tasks. 
The validate() function validates the command-line arguments to ensure that all required 
arguments are entered, the port is valid, the mode is either TCP or UDP, and the host is 
a valid IP address.

The create_socket() function creates a socket for the specified mode (TCP or UDP) and sets 
the global variable SOCKET to the socket file descriptor.

The timeout() function sets a timeout for the select() function to prevent the program from 
waiting indefinitely for a response.

The tcp_client() and udp_client() functions connect to the server and sends a message using TCP or UDP. 
The functions reads input from the user and sends it to the server using send(). 
It then waits for a response from the server using recv(). 

The program includes a main() function that parses the command-line arguments using the 
getopt() function, calls the validate() and create_socket() functions, and then calls either 
the tcp_client() or udp_client() function depending on the specified mode.

# Known Limitations
- Limited error handling: While the program does check for some invalid inputs and errors, 
such as invalid port numbers and host names, it does not handle all possible errors that 
could occur during runtime. For example, if the server is not running or if the connection 
is lost during the communication process, the program will terminate abruptly without 
providing a clear error message.
- Limited functionality: The program is designed to send and receive messages from a 
server using either TCP or UDP protocols. It does not provide any other functionality, 
such as file transfers or remote execution of commands.
- Limited platform compatibility: The program is written in C and relies on standard 
system libraries for socket communication. This means that it may not be compatible 
with all platforms or operating systems, especially those with non-standard networking 
stacks.
- Messages larger than 1024 bytes will be truncated