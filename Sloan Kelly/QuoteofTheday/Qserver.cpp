#include <Qserver.h>

Qserver::Qserver(string filename)
{
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        string line;
        string running = "";

        while (getline(file, line))
        {
            if (line != "%")
            {
                running = running + line + "\n";
            }
            else
            {
                quotes.push_back(running);
                running = "";
            }
        }
        
    }

}
        // Get random qoute
string Qserver::GetRandomQ()
{
    int r = rand() % quotes.size();

    return quotes[r];
}