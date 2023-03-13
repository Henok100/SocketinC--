#include <iostream>         // C++ library
#include <sys/types.h>      // C   library // for socket function
#include <sys/socket.h>     // for socket function
#include <unistd.h>
#include <netdb.h>          // for getnameinfo function
#include <arpa/inet.h>      // for inet_pton function
#include <string.h>         // for memset function
#include <string>
#include <fstream> 
#define INVALID_SOCKET -1
 
using namespace std;
 
int main()
{
    int port = 55555;
    // Create a socket
    int ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerSocket == INVALID_SOCKET)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
    else
    {
        cout << "Socket creation went successful\n\n";
    }
 
    // Bind the ip address and port to a socket
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &server.sin_addr.s_addr);
 
    if (bind(ServerSocket, (sockaddr*)&server, sizeof(server)) == INVALID_SOCKET)
    {
        cout << "Binding failed\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Binding Successful\n\n";
    }
 
    // Listen
    if (listen(ServerSocket, SOMAXCONN) == INVALID_SOCKET)
    {
        cout << "Listening failed\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Listening succesful\n\n";
    }
 
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int acceptClient = accept(ServerSocket, (sockaddr*)&client, &clientSize);
    
    if (acceptClient == INVALID_SOCKET)
    {
        cout << "Accept failed\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Accept successful\n\n";
    }

    //Receving and send
    while(true)
    {
        char buffer[200];
        recv(acceptClient, buffer, 200, 0);
        cout << "Client: " << buffer << endl;
        if (buffer == "Bye")
        {
            cout << "Quiting\n";
            return -1;
        }

    /*  if (recv(acceptClient, buffer, 200, 0) > 0)
        {
            cout << "Message received: " << buffer << endl;
        }
        else
        {
            cout << "error" << endl;
            return -1;
        } */

        //Sending
        char SendBuffer[200];
        cout << "Server: ";
        cin.getline(SendBuffer, 200);
        send(acceptClient, SendBuffer, 200, 0);
        /* if (send(acceptClient, SendBuffer, 200, 0) > 0)
        {
            cout << "Message Sent: " << SendBuffer << endl;
        } */
    }

    // Close the socket
    close(acceptClient);
    return 0;
}