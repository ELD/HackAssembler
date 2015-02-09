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
    std::string outFileName = file.substr(0, file.find_first_of('.'));
    std::ofstream oss(outFileName + ".hack");
    parser.translateAssembly(oss);
    oss.close();

    return 0;
}
