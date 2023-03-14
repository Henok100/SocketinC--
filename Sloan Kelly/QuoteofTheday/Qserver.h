#include <iostream>         // C++ library
#include <sys/types.h>      // C   library // for socket function
#include <sys/socket.h>     // for socket function
#include <unistd.h>
#include <netdb.h>          // for getnameinfo function
#include <arpa/inet.h>      // for inet_pton function
#include <string.h>         // for memset function
#include <string>
#include <fstream> 
#include <vector>

#define INVALID_SOCKET -1

using namespace std;

class Qserver
{
    public:
        // Constructor
        Qserver(string filename);
        // Get random qoute
        string GetRandomQ();

    private:
        vector<string> quotes;
};