#include <iostream>         // C++ library
#include <sys/types.h>      // C   library // for socket function
#include <sys/socket.h>     // for socket function
#include <unistd.h>
#include <netdb.h>          // for getnameinfo function
#include <arpa/inet.h>      // for inet_pton function
#include <string.h>         // for memset function
#include <string>

using namespace std;

int main()
{
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1"; // Local Machine

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    //char buf[4096];
    string buf[5] = {0};
    //string userInput;


    do {
        //	Enter lines of text
        //cout << "> ";
        //getline(cin, userInput);

        //	Send to server
        /* int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }
 */
        //	Wait for response
       // memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 5, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << buf << "\r\n";
        }
    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}