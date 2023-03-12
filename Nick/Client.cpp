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
    int ClientServer = socket(AF_INET, SOCK_STREAM, 0);
    if (ClientServer == INVALID_SOCKET)
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
    int connectRes = connect(ClientServer, (sockaddr*)&clinet, sizeof(clinet));
    if (connectRes == INVALID_SOCKET)
    {
        cout << "Connection Failed\n\n";
        return INVALID_SOCKET;
    }
    else
    {
        cout << "Connection Successful\n\n";
    }

    //	While loop:
    /* char buf[4096];
    string userInput;


    do {
        //		Enter lines of text
        cout << "> ";
        getline(cin, userInput);

        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);

    //	Close the socket
    close(sock);
*/
    return 0;
} 