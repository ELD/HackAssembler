#include "headers/utility.hpp"

std::string getCommandString(int commandType)
{
    switch (commandType) {
        case 0:
            return "L_COMMAND";
        break;
        case 1:
            return "A_COMMAND";
        break;
        case 2:
            return "C_COMMAND";
        break;
    }

    return "NO_COMMAND";
}

void mockInputStream(std::stringstream& in)
{
    in << "@R2" << std::endl;
    in << "M=0" << std::endl;
    in << std::endl << "@R0" << std::endl;
    in << std::endl << "D=M" << std::endl;
}

void mockInputStreamNoSymbols(std::stringstream& in)
{
    in << "@2" << std::endl;
    in << "D=A" << std::endl;
    in << "@3" << std::endl;
    in << "D=D+A" << std::endl;
    in << "@0" << std::endl;
    in << "M=D" << std::endl << std::endl;
}

void mockInputStreamWithSymbols(std::stringstream& in)
{
    in << "@R0" << std::endl;
    in << "D=M" << std::endl;
    in << "@R1" << std::endl;
    in << "D=D-M" << std::endl;
    in << "@OUTPUT_FIRST" << std::endl;
    in << "D;JGT" << std::endl;
    in << "@R1" << std::endl;
    in << "D=M" << std::endl;
    in << "@OUTPUT_D" << std::endl;
    in << "0;JMP" << std::endl;
    in << "(OUTPUT_FIRST)" << std::endl;
    in << "@R0" << std::endl;
    in << "D=M" << std::endl;
    in << "(OUTPUT_D)" << std::endl;
    in << "@R2" << std::endl;
    in << "M=D" << std::endl;
    in << "(INFINITE_LOOP)" << std::endl;
    in << "@INFINITE_LOOP" << std::endl;
    in << "0;JMP" << std::endl << std::endl;
}
