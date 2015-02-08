#include "../headers/headers.hpp"

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::cout << "No target file specified!" << std::endl << "Example usage: ./hackasm [file]" << std::endl;
        return -1;
    }

    std::string file(argv[1]);
    std::ifstream fileHandle(file);

    // std::string noNumericValues("TEST");
    // try {
    //     auto number = stoi(noNumericValues);
    //     std::cout << number << std::endl;
    // } catch (std::invalid_argument exc) {
    //     std::cout << exc.what() << std::endl;
    // }

    std::string numericValues("10");
    std::cout << stoi(numericValues) << std::endl;

    hack::Parser parser(fileHandle);
    // hack::Parser parser(iss);
    while (parser.hasMoreCommands()) {
        parser.advance();
        std::string command = parser.getCurrentCommand();
        std::cout << "Current command: " << command << std::endl;
        std::cout << "Command type: " << parser.commandType() << std::endl;
    }

    return 0;
}
