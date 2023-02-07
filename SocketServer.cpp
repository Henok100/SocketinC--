#include <iostream>
#include <sys/socket.h> // For socket function
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(){

    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufSize = 1024;
    char buffer[bufSize];
    
    struct sockaddr_in server_addr;
    socklen_t size;

    // init socket

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0){
        cout << "Error in establishing connecion." << endl;
        exit(1);
    }

    cout << "Server connection established!..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portNum);

    // binding socket

    if (bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        cout << "Error binding socket..." << endl;
        exit(1);
    }

    size = sizeof(server_addr);
    cout << "Looking for clients..." << endl;

    // Listeneing

    listen(client, 1);

    // Accept client

    server = accept(client, (struct sockaddr*)&server_addr, &size);

    if (server < 0){
        cout << "Error on accepting..." << endl;
        exit(1);
    }

    while (server > 0){
        strcpy(buffer, "Server connected... \n");
        send(server, buffer, bufSize, 0);

        cout << "Connected with client..." << endl;
        cout << "Enter # to end the connection" << endl;

        cout << "Client: ";
        do {
            recv(server, buffer, bufSize, 0);
            cout << "buffer ";
            if (*buffer == '#'){
                *buffer = '*';
                isExit = true;
            }
        }while (*buffer != '*');

        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server, buffer, bufSize, 0);
                if (*buffer == '#'){
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');
        cout << "Client: ";
        do {
            recv(server, buffer, bufSize, 0);
            cout << buffer << " ";
            if (*buffer == '#')
            {
                *buffer == '#';
                isExit = true;
            }
        }while (*buffer != '*');
    }while(!isExit);
    
    cout << "Connection terminated..." << endl;
    cout << "Bye..." << endl;
    isExit = false;
    exit(1);
}
    close(client);
    return 0;
}