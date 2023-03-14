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

class ServerClass;          //declaration of class

using namespace std;

// Callback to data received
typedef void(*MessageRecHandler)(ServerClass* listener, int socketId, string msg);

class ServerClass
{
    public:
        ServerClass(string IP, int port, MessageRecHandler handler);

        // send a message to the specified client
        void Send(int clientSocket, string msg);

        //Main loop
        void Run();
    
    private:
        //Create a socket
        int CreateSocket();

        //wait for connection
        int waitforconnection(int listening);

        string m_IP;
        int m_port;
        MessageRecHandler MessageReceived;


};