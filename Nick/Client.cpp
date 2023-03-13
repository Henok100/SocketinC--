#include <iostream>         // C++ library
#include <sys/types.h>      // C   library // for socket function
#include <sys/socket.h>     // for socket function
#include <unistd.h>
#include <netdb.h>          // for getnameinfo function
#include <arpa/inet.h>      // for inet_pton function
#include <string.h>         // for memset function
#include <string>
#define INVALID_SOCKET -1

using namespace std;

int main()
{
    //	Create a socket
    int ClinetSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ClinetSocket == INVALID_SOCKET)
    {
        cout << "Socket creation Failed\n\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Socket creation Successful\n\n";
    }

    //	Create a hint structure for the server we're connecting with
    int port = 55555;
    string ipAddress = "127.0.0.1";

    sockaddr_in clinet;
    clinet.sin_family = AF_INET;
    clinet.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &clinet.sin_addr.s_addr);

    //	Connect to the server on the socket
    int connectRes = connect(ClinetSocket, (sockaddr*)&clinet, sizeof(clinet));
    if (connectRes == INVALID_SOCKET)
    {
        cout << "Connection Failed\n\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Connection Successful\n\n";
    }

    while (true)
    {
    
    char charBuffer[200];

    cout << "Client :";
    cin.getline(charBuffer, 200);
    send(ClinetSocket, charBuffer, 200, 0);

    /*  if (send(ClinetSocket, charBuffer, 200, 0) > 0)
    {
        cout << "Sent message: " << charBuffer << endl;
    }
    else 
    {
        cout << "Sending Failed\n";
        return -1;
    } */

    //Receving
    char recvBuffer[200];
    recv(ClinetSocket, recvBuffer, 200, 0);
    cout << "Server: " << recvBuffer << endl;
    if (recvBuffer == "Bye")
    {
        cout << "Exiting" << endl;
        break;
    }
    /* if (recv(ClinetSocket, recvBuffer, 200, 0) > 0)
    {
        cout << "Server: " << recvBuffer << endl;
    } */
    
    }   
    //	Close the socket
    close(ClinetSocket);

    return 0;
} 