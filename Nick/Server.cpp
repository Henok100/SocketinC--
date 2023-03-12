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

/*     char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
 
    // While loop: accept and echo message back to client
    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
 
        cout << string(buf, 0, bytesReceived) << endl;
 
        // Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
 
    // Close the socket
    close(clientSocket); */
 
    return 0;
}