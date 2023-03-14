#include "ServerClass.h"

#define max (49152)

ServerClass::ServerClass(string IP, int port, MessageRecHandler handler)
        : m_IP(IP), m_port(port), MessageReceived(handler)
{

}

//Send a message to the specified client
void ServerClass::Send(int clientSocket, string msg)
{
    send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

//Main loop
void ServerClass::Run()
{
    char buffer[max];

    while (true)
    {
        // create a listening socket
        int listening = CreateSocket();
        cout << "Connection Successful\n";

        int client = waitforconnection(listening);
        cout << "Listening Successful\n";
        
        int byteRec = 0;
        do
        {
            byteRec = recv(client,buffer, max, 0);
            MessageReceived(this, client, string(buffer, 0, byteRec));

        } while (byteRec > 0);
        
    }
    
}

//Create a socket
int ServerClass::CreateSocket()
{
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serveradd;
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(m_port);
    inet_pton(AF_INET, m_IP.c_str(), &serveradd.sin_addr);
    
    //bind
    bind(listening, (sockaddr*)&serveradd, sizeof(serveradd));

    int connectedSer = listen(listening, SOMAXCONN);

    return listening;
}   

//Wait for connection
int ServerClass::waitforconnection(int listening)
{
    int client = accept(listening, NULL, NULL);
    return client;
}