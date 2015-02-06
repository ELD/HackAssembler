#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE HACK_ASM
#include <boost/test/unit_test.hpp>
#include "../headers/parser.hpp"
#include "utility.hpp"

using namespace boost::unit_test;

bool init_function();

/**
 * Test suite functions
*/

void parser_init_test_case();
void parser_command_type_test_case();

int main(int argc, char* argv[])
{
    return ::boost::unit_test::unit_test_main(&init_function, argc, argv);
}

bool init_function()
{
    if (framework::master_test_suite().argc < 2) {
        std::cout << "No test file supplied.\nExample usage: ./tester [file]" << std::endl;
        return false;
    }

    std::string fileName = framework::master_test_suite().argv[1];
    auto parser_suite = BOOST_TEST_SUITE("Parser_Test_Suite");
    parser_suite->add(BOOST_TEST_CASE(&parser_init_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_command_type_test_case));

    framework::master_test_suite().add(parser_suite);

    return true;
}

void parser_init_test_case()
{
    auto fileName = framework::master_test_suite().argv[1];
    hack::Parser parser(fileName);
    if (parser.hasMoreCommands()) {
        parser.advance();
        BOOST_CHECK_MESSAGE(parser.getCurrentCommand() == "@R2", "Should be '@R2' but was: " << parser.getCurrentCommand());
    }
}

void parser_command_type_test_case()
{
    auto fileName = framework::master_test_suite().argv[1];
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
