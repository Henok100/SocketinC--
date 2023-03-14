#include <iostream>         // C++ library
#include <fstream> 
#include <sstream> 
#include <string>
#include <unistd.h>

using namespace std;

unsigned int micro = 1000000;

int main()
{
    fstream myFile;

    /*Write Mode
        // myFile.open("Henok.txt", ios::out); // overwrite mode
        
        // if (myFile.is_open()){
        //     myFile << "Hello Henok \n";
        //     myFile << "Hello Tenaw \n";

        //     myFile.close();
        // }
        // myFile.open("Henok.txt", ios::app); // append mode
        
        // if (myFile.is_open()){
        //     myFile << "Hello Henok \n";

        //     myFile.close();
        // }
    */

    /*Read Mode*/
    ifstream inputfile;
    inputfile.open("path_test.csv", ios::in); // Read Mode
    if (inputfile.is_open())
    {
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
            //continue;
            string buf[5] = {x, y, z, zR, heading};
            cout << buf << endl;
            usleep(stod(time) * micro);
        }

        myFile.close();
    }
    else
    {
        cout << "Unable to open txt file.\n";
    } 

    /*CSV file*/

    /* ifstream inputfile;
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

        usleep(stod(time) * micro);
    }

    inputfile.close(); */

    return 0;
}