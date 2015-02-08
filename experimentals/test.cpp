#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

void istream_inject(std::istream&);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "No arguments passed in." << endl;
        return -1;
    }

    ifstream inFile(argv[1]);
    istream_inject(inFile);

    istringstream inString("This is a test");
    istream_inject(inString);
}

void istream_inject(std::istream& streamIn)
{
    string line;
    getline(streamIn, line);
    cout << line << endl;
}
