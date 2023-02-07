/*!
 * Simple chat program (server side).cpp - https://github.com/Henok100
 *
 * Copyright (c) 2023 Henok Gashaw
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
    int nSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    socklen_t size;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (nSocket < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }


    cout << "\n=> Socket server has been created..." << endl;


    /*server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);


    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */


    return 0;
}