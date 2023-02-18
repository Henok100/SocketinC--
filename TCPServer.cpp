#include <iostream>         // C++ library
#include <sys/types.h>      // C   library
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    // Create a socket
    int listening  = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Error";
        return -1;
    }
    
    // Bind a socket to IP and PORT
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);       // Big Endian
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening,(sockaddr*)&hint, sizeof(hint)) == -1)
    {
        cerr << "Cant bind to IP/PORT";
        return 2;
    }

    // Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == 1)
    {
        cerr << "Can't listen";
        return 3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientsize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientsocket

    // Close a listening socket
    // display and echo
    // Close

    return 0;
}