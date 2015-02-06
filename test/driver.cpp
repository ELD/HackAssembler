// #define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HACK_ASM
#include <boost/test/unit_test.hpp>
#include "../headers/parser.hpp"
#include "utility.hpp"

int unit_test_main(boost::unit_test::init_unit_test_func init_func, int argc, char* argv[])
{
    std::string fileName;
    if (argc > 1) {
        fileName = argv[1];
    } else {
        std::cout << "No file provided\nExample usage: ./tester [file]" << std::endl;
    }

    // Tests
}

BOOST_AUTO_TEST_CASE(Parser_Creation)
{
    hack::Parser parser(fileName);
    if (parser.hasMoreCommands()) {
        parser.advance();
        BOOST_CHECK_MESSAGE(parser.getCurrentCommand() == "@R2", "Should be '@R2' but was: " << parser.getCurrentCommand());
    }
}

BOOST_AUTO_TEST_CASE(Parser_Command_Type)
{
    hack::Parser parser(fileName);

    std::string aCommand = "@R0";
    parser.setCurrentCommand(aCommand);
    BOOST_CHECK_MESSAGE(parser.commandType() == 1, "Should be A_COMMAND but was: " << getCommandString(parser.commandType()));

    std::string cCommand = "D=D+A";
    parser.setCurrentCommand(cCommand);
    BOOST_CHECK_MESSAGE(parser.commandType() == 2, "Should be C_COMMAND but was: " << getCommandString(parser.commandType()));

    std::string lCommand = "(LABEL)";
    parser.setCurrentCommand(lCommand);
    BOOST_CHECK_MESSAGE(parser.commandType() == 0, "Should be L_COMMAND but was: " << getCommandString(parser.commandType()));
}
