#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

void mockIstream(stringstream&);

int main(int argc, char* argv[])
{
    stringstream oss;
    mockIstream(oss);

    std::string line;
    while (!oss.eof()) {
        getline(oss, line);
        std::cout << "Line: " << line << "\tEOF?:" << oss.eof() << std::endl;
    }
}

void mockIstream(stringstream& mock)
{
    mock << "Test" << std::endl;
    mock << "Test 2" << std::endl;
    mock << "Test 3" << std::endl;
    mock << "Test 4" << std::endl;
    mock << "Test 5" << std::endl << std::endl;
}
