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
    std::string outFileName = file.substr(0, file.find_last_of('.'));
    std::ofstream ofs(outFileName + ".hack");
    parser.translateAssembly(ofs);
    ofs.close();

    return 0;
}
