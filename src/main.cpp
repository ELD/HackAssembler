#include "../headers/headers.hpp"

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::cout << "No target file specified!" << std::endl << "Example usage: ./hackasm [file]" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::ifstream fileHandle(file);

    hack::Parser parser(fileHandle);
    while (parser.hasMoreCommands()) {
        parser.advance();
        std::string command = parser.getCurrentCommand();
        std::cout << "Current command: " << command << std::endl;
        std::cout << "Command type: " << parser.commandType() << std::endl;
    }

    parser.rewind();
    parser.translateAssembly(std::cout);

    return 0;
}
