// TODO: Extract parser and symbol tests into separate file

#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE HACK_ASM
#include <boost/test/unit_test.hpp>
#include "../headers/parser.hpp"
#include "../headers/symbol_table.hpp"
#include "utility.hpp"
// #include "parser_tests.hpp"
// #include "symbol_table_tests.hpp"

using namespace boost::unit_test;

bool init_function();

void parser_init_test_case();
void parser_command_type_test_case();
void parser_token_test_case();

void symbol_table_init_test_case();
void symbol_table_insert_test_case();
void symbol_table_retrieve_test_case();
void symbol_table_contains_test_case();

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
    parser_suite->add(BOOST_TEST_CASE(&parser_token_test_case));

    auto symbol_table_test_suite = BOOST_TEST_SUITE("Symbol_Table_Test_Suite");
    symbol_table_test_suite->add(BOOST_TEST_CASE(&symbol_table_init_test_case));
    symbol_table_test_suite->add(BOOST_TEST_CASE(&symbol_table_insert_test_case));
    symbol_table_test_suite->add(BOOST_TEST_CASE(&symbol_table_retrieve_test_case));
    symbol_table_test_suite->add(BOOST_TEST_CASE(&symbol_table_contains_test_case));

    framework::master_test_suite().add(parser_suite);
    framework::master_test_suite().add(symbol_table_test_suite);

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
    hack::Parser parser;

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

void parser_token_test_case()
{
    hack::Parser parser;
    std::string label = "(MY_LABEL)";
    parser.setCurrentCommand(label);
    BOOST_CHECK_MESSAGE(parser.symbol() == "MY_LABEL", "Should be MY_LABEL but was: " << parser.symbol());

    label = "@R0";
    parser.setCurrentCommand(label);
    BOOST_CHECK_MESSAGE(parser.symbol() == "R0", "Should be R0 but was: " << parser.symbol());

    label = "@SP";
    parser.setCurrentCommand(label);
    BOOST_CHECK_MESSAGE(parser.symbol() == "SP", "Should be SP but was: " << parser.symbol());
}

void symbol_table_init_test_case()
{
    hack::SymbolTable symbols;

    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("SP") == 0, "Should be 0 but was: " << symbols.retrieveSymbol("SP"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("LCL") == 1, "Should be 1 but was: " << symbols.retrieveSymbol("LCL"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("ARG") == 2, "Should be 2 but was: " << symbols.retrieveSymbol("ARG"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("THIS") == 3, "Should be 3 but was: " << symbols.retrieveSymbol("THIS"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("THAT") == 4, "Should be 4 but was: " << symbols.retrieveSymbol("THAT"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R0") == 0, "Should be 0 but was: " << symbols.retrieveSymbol("R0"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R1") == 1, "Should be 1 but was: " << symbols.retrieveSymbol("R1"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R2") == 2, "Should be 2 but was: " << symbols.retrieveSymbol("R2"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R3") == 3, "Should be 3 but was: " << symbols.retrieveSymbol("R3"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R4") == 4, "Should be 4 but was: " << symbols.retrieveSymbol("R4"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R5") == 5, "Should be 5 but was: " << symbols.retrieveSymbol("R5"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R6") == 6, "Should be 6 but was: " << symbols.retrieveSymbol("R6"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R7") == 7, "Should be 7 but was: " << symbols.retrieveSymbol("R7"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R8") == 8, "Should be 8 but was: " << symbols.retrieveSymbol("R8"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R9") == 9, "Should be 9 but was: " << symbols.retrieveSymbol("R9"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R10") == 10, "Should be 10 but was: " << symbols.retrieveSymbol("R10"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R11") == 11, "Should be 11 but was: " << symbols.retrieveSymbol("R11"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R12") == 12, "Should be 12 but was: " << symbols.retrieveSymbol("R12"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R13") == 13, "Should be 13 but was: " << symbols.retrieveSymbol("R13"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R14") == 14, "Should be 14 but was: " << symbols.retrieveSymbol("R14"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("R15") == 15, "Should be 15 but was: " << symbols.retrieveSymbol("R15"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("SCREEN") == 16384, "Should be 16384 but was: " << symbols.retrieveSymbol("SCREEN"));
    BOOST_CHECK_MESSAGE(symbols.retrieveSymbol("KBD") == 24576, "Should be 24576 but was: " << symbols.retrieveSymbol("KBD"));
}

void symbol_table_insert_test_case()
{

}

void symbol_table_retrieve_test_case()
{

}

void symbol_table_contains_test_case()
{

}
