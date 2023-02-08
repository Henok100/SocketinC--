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
#define PORT 9909

using namespace std;

int main()
{
    int nSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in srv; //Server address
    fd_set fr, fw, fe;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (nSocket < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << nSocket <<endl;

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htons(INADDR_ANY);
    srv.sin_port = htons(PORT); // host to network byte order
    memset(&(srv.sin_zero), 0, 8);

    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */

    int nRet = 0;

    nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
    if (nRet < 0){
        cout << "Failed at binding" << endl;
        exit(1);
    }
    else {
        cout << "Successfully bind to local port" << endl;
    }

    ////////////////// Listen //////////////////////
    nRet = listen(nSocket, 5);

    if (nRet < 0){
        cout << "Failed at listen to local port" << endl;
        exit(1);
    }
    else {
        cout << endl << "Started listening to local port" << endl;
    }
    ///////////////////////////////////////////////



    return 0;
}