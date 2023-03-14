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
    //server ip adress and port
    string ip = "127.0.0.1";
    int port = 54000;

    //create socket
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);

    //fill in adress structure
    sockaddr_in clinetadd;
    clinetadd.sin_family = AF_INET;
    clinetadd.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &clinetadd.sin_addr);

    //connect to server
    connect(clientSock, (sockaddr*)&clinetadd, sizeof(clinetadd));

    //While loop to send and receive data
    char buffer[4096];
    string userinput;

    do
    {
        //Prompt the user
        cout << "Enter your message: ";
        getline(cin, userinput);

        //send the message
        send(clientSock, userinput.c_str(), userinput.size() + 1, 0); //+1 is for null character
        
        int byterec = recv(clientSock, buffer, 4096, 0);

        cout << "Server > " << string(buffer, 0, byterec) << endl;

    } while (userinput.size() > 0);
    
    close(clientSock);
    return 0;
}
