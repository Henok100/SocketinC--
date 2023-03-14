#include "ServerClass.h"
#include "../QuoteofTheday/Qserver.h"

void Listener_MessageReceived(ServerClass* listener, int client, string msg);

Qserver quotes("quote.txt");

int main()
{
    ServerClass server("127.0.0.1", 54000, Listener_MessageReceived);

    server.Run();

    return 0;

    system("pause");
}
void Listener_MessageReceived(ServerClass* listener, int client, string msg)
{
    //listener->Send(client, msg);
    listener->Send(client, quotes.GetRandomQ());
}