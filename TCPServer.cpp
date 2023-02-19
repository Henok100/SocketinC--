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
        return -2;
    }

    // Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1)
    {
        cerr << "Can't listen";
        return -3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    int clientSocket = accept(listening, 
                              (sockaddr*) &client,
                               &clientSize);

    if (clientSocket == -1)
    {
        cerr << "Problem with client connecting";
        return -4;
    }


    // Close a listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,
                              sizeof(client),
                              host,
                              NI_MAXHOST,
                              service,
                              NI_MAXSERV,
                              0);
    if (result)
    {
        cout << host << " connected on " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on " << ntohs(client.sin_port) << endl;
    }

    // display and echo
    char buf[4096];
    while (true)
    {
        // Clear the buffer
        memset(buf, 0, 4096);
        // Wait for message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1)
        {
            cerr << "There is a connection proble.\n";
            break;
        }
        if (bytesRecv == 0)
        {
            cerr << "The client disconnected.\n";
            break;
        }
        // display message
        cout << "Received: " << string(buf, 0, bytesRecv) << endl;
        
        // Resend message
        send(clientSocket, buf, bytesRecv + 1, 0);
        
    }

    // Close
    close (clientSocket); 

    return 0;
}