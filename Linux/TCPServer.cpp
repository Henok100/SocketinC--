#include <iostream>         // C++ library
#include <sys/types.h>      // C   library // for socket function
#include <sys/socket.h>     // for socket function
#include <unistd.h>
#include <netdb.h>          // for getnameinfo function
#include <arpa/inet.h>      // for inet_pton function
#include <string.h>         // for memset function
#include <string>
#include <fstream> 

using namespace std;

unsigned int micro = 1000000;


using namespace std;

int main()
{
    // Create a socket
    int listening  = socket(AF_INET, SOCK_STREAM, 0);   // IPv4, TCP, Default 
    if (listening == -1)
    {
        cerr << "Error";
        return -1;
    }
    
    // Bind a socket to a IP and PORT
    sockaddr_in hint;                   // Specifies trans. add. and port for AF_INET AddFam
    hint.sin_family = AF_INET;          // Address family for the trans.add
    hint.sin_port = htons(54000);       // Big Endian HostByte to NetworkByte
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);  // conv. "0.0.0.0" to net. add. and copies to hint.sin_addr

    if (bind(listening,(sockaddr*)&hint, sizeof(hint)) == -1)
    {
        cerr << "Cant bind to IP/PORT";
        return -2;
    }

    // Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1)     // Maximum queue length specified by listen function
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

    memset(host, 0, NI_MAXHOST);            // clean host
    memset(service, 0, NI_MAXSERV);         // clean service

   /* int result = getnameinfo((sockaddr*)&client,        // address to name translation   
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
    */

    // display and echo
    char buf[4096];
    while (true)
    {
        // // Clear the buffer
         memset(buf, 0, 4096);
        // // Wait for message
        // int bytesRecv = recv(clientSocket, buf, 4096, 0);
        // if (bytesRecv == -1)
        // {
        //     cerr << "There is a connection problem.\n";
        //     break;
        // }
        // if (bytesRecv == 0)
        // {
        //     cerr << "The client disconnected.\n";
        //     break;
        // }
        // // display message
        // cout << "Received: " << string(buf, 0, bytesRecv) << endl;
        
    ifstream inputfile;
    inputfile.open("path_test.csv");
    string line;

    while (getline(inputfile, line))
    {
        string x;
        string y;
        string z;
        string zR;
        string heading;
        string time;

        getline(inputfile, x, ',');
        getline(inputfile, y, ',');
        getline(inputfile, z, ',');
        getline(inputfile, zR, ',');
        getline(inputfile, heading, ',');
        getline(inputfile, time, ',');

        cout << "X = " << x << endl;
        cout << "Y = " << y << endl;
        cout << "Z = " << z << endl;
        cout << "zR = " << zR << endl;
        cout << "heading = " << heading << endl;
        cout << "Time = " << time << endl;
        cout << "---------------------" << endl;

        send(clientSocket, buf, sizeof(buf), 0);

        usleep(stod(time) * micro);
    }

    inputfile.close();

        // Resend message
         
    }

    // Close
    close (clientSocket); 

    return 0;
}