// TODO: Extract parser and symbol tests into separate file

#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE HACK_ASM
#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../headers/headers.hpp"
#include "headers/utility.hpp"
// #include "parser_tests.hpp"
// #include "symbol_table_tests.hpp"

using namespace boost::unit_test;

bool init_function();

void parser_init_test_case();
void parser_command_type_test_case();
void parser_token_test_case();
void parser_dest_test_case();
void parser_comp_test_case();
void parser_jump_test_case();
void parser_all_bits_test_case();

void symbol_table_init_test_case();
void symbol_table_insert_test_case();
void symbol_table_contains_test_case();

void comp_table_init_test_case();
void comp_table_retrieve_test_case();

void dest_table_init_test_case();
void dest_table_retrieve_test_case();

void jump_table_init_test_case();
void jump_table_retrieve_test_case();

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
    parser_suite->add(BOOST_TEST_CASE(&parser_dest_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_comp_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_jump_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_all_bits_test_case));

    auto symbol_table_suite = BOOST_TEST_SUITE("Symbol_Table_Test_Suite");
    symbol_table_suite->add(BOOST_TEST_CASE(&symbol_table_init_test_case));
    symbol_table_suite->add(BOOST_TEST_CASE(&symbol_table_insert_test_case));
    symbol_table_suite->add(BOOST_TEST_CASE(&symbol_table_contains_test_case));

    auto comp_table_suite = BOOST_TEST_SUITE("Comp_Table_Test_Suite");
    comp_table_suite->add(BOOST_TEST_CASE(&comp_table_init_test_case));
    comp_table_suite->add(BOOST_TEST_CASE(&comp_table_retrieve_test_case));

    auto dest_table_suite = BOOST_TEST_SUITE("Dest_Table_Test_Suite");
    dest_table_suite->add(BOOST_TEST_CASE(&dest_table_init_test_case));
    dest_table_suite->add(BOOST_TEST_CASE(&dest_table_retrieve_test_case));

    auto jump_table_suite = BOOST_TEST_SUITE("Jump_Table_Test_Suite");
    jump_table_suite->add(BOOST_TEST_CASE(&jump_table_init_test_case));
    jump_table_suite->add(BOOST_TEST_CASE(&jump_table_retrieve_test_case));

    framework::master_test_suite().add(parser_suite);
    framework::master_test_suite().add(symbol_table_suite);
    framework::master_test_suite().add(comp_table_suite);
    framework::master_test_suite().add(dest_table_suite);
    framework::master_test_suite().add(jump_table_suite);

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
    BOOST_CHECK_MESSAGE(parser.getSymbol() == "MY_LABEL", "Should be MY_LABEL but was: " << parser.getSymbol());

    label = "@R0";
    parser.setCurrentCommand(label);
    BOOST_CHECK_MESSAGE(parser.getSymbol() == "R0", "Should be R0 but was: " << parser.getSymbol());

    label = "@SP";
    parser.setCurrentCommand(label);
    BOOST_CHECK_MESSAGE(parser.getSymbol() == "SP", "Should be SP but was: " << parser.getSymbol());
}

void parser_dest_test_case()
{
    hack::Parser parser;

    std::string command = "D;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "000", "Should be '000' but was " << parser.getDestBits());

    command = "M=1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "001", "Should be '001' but was " << parser.getDestBits());

    command = "D=D+1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "010", "Should be '010' but was " << parser.getDestBits());

    command = "MD=D+1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "011", "Should be '011' but was " << parser.getDestBits());

    command = "A=10";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "100", "Should be '100' but was " << parser.getDestBits());

    command = "AM=10";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "101", "Should be '101' but was " << parser.getDestBits());

    command = "AD=10";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "110", "Should be '110' but was " << parser.getDestBits());

    command = "AMD=D+1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getDestBits() == "111", "Should be '111' but was " << parser.getDestBits());
}

void parser_comp_test_case()
{
    hack::Parser parser;

    std::string command = "0;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "0101010", "Should be '0101010' but was " << parser.getCompBits());

    command = "1;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "0111111", "Should be '0111111' but was " << parser.getCompBits());

    command = "-1;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "0111010", "should be '0111010' but was " << parser.getCompBits());

    command = "D;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "0001100", "should be '0001100' but was " << parser.getCompBits());

    command = "D=D+A";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "0000010", "should be '0000010' but was " << parser.getCompBits());

    command = "M=M+1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getCompBits() == "1110111", "should be '1110111' but was " << parser.getCompBits());
}

void parser_jump_test_case()
{
    hack::Parser parser;

    std::string command = "D=D+1";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "000", "Should be '000' but was " << parser.getJumpBits());

    command = "D;JGT";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "001", "Should be '001' but was " << parser.getJumpBits());

    command = "D;JEQ";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "010", "Should be '010' but was " << parser.getJumpBits());

    command = "D;JGE";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "011", "Should be '011' but was " << parser.getJumpBits());

    command = "D;JLT";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "100", "Should be '100' but was " << parser.getJumpBits());

    command = "D;JNE";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "101", "Should be '101' but was " << parser.getJumpBits());

    command = "D;JLE";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "110", "Should be '110' but was " << parser.getJumpBits());

    command = "D;JMP";
    parser.setCurrentCommand(command);
    BOOST_CHECK_MESSAGE(parser.getJumpBits() == "111", "Should be '111' but was " << parser.getJumpBits());
}

void parser_all_bits_test_case()
{
    hack::Parser parser;
    std::string command;
    std::string allBits;

    command = "D=D+1";
    parser.setCurrentCommand(command);
    allBits = parser.getCompBits() + parser.getDestBits() + parser.getJumpBits();
    BOOST_CHECK_MESSAGE(allBits == "0011111010000", "Should be '0011111010000' but was " << allBits);

    command = "D;JGE";
    parser.setCurrentCommand(command);
    allBits = parser.getCompBits() + parser.getDestBits() + parser.getJumpBits();
    BOOST_CHECK_MESSAGE(allBits == "0001100000011", "Should be '0001100000011' but was " << allBits);
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
    hack::SymbolTable symbols;

    for (int i = 0; i < 15; ++i) {
        std::ostringstream oss;
        oss << "test" << i;
        symbols.addSymbol(oss.str(), i);
        BOOST_CHECK_MESSAGE(symbols.retrieveSymbol(oss.str()) == i,
            "Should be " << i << " but was: " << symbols.retrieveSymbol(oss.str()));
    }
}

void symbol_table_contains_test_case()
{
    hack::SymbolTable symbols;

    BOOST_CHECK_MESSAGE(symbols.contains("SP") == true, "Should have contained 'SP' but it didn't.");
    BOOST_CHECK_MESSAGE(symbols.contains("SCREEN") == true, "Should have contained 'SCREEN'");
    BOOST_CHECK_MESSAGE(symbols.contains("GABAGE_SYMBOL") == false, "Should not have contained 'GARBAGE_SYMBOL'");
}

void comp_table_init_test_case()
{
    BOOST_CHECK_MESSAGE(hack::CompTable::lookup.size() == 28, "Should have size 28 but had size " << hack::CompTable::lookup.size());
}

void comp_table_retrieve_test_case()
{
    auto value_pair = hack::CompTable::lookup["D-A"];
    BOOST_CHECK_MESSAGE(value_pair.first == "0" && value_pair.second == "010011", "Should be 0 and 010011 but was " << value_pair.first << " and " << value_pair.second);
}

void dest_table_init_test_case()
{
    BOOST_CHECK_MESSAGE(hack::DestTable::lookup.size() == 8, "Should have size 8 but had size " << hack::DestTable::lookup.size());
}

void dest_table_retrieve_test_case()
{
    BOOST_CHECK_MESSAGE(hack::DestTable::lookup["MD"] == "011", "Should be 011 but was " << hack::DestTable::lookup["MD"]);
}

void jump_table_init_test_case()
{
    BOOST_CHECK_MESSAGE(hack::JumpTable::lookup.size() == 8, "Should have size 8 but had size " << hack::JumpTable::lookup.size());
}

void jump_table_retrieve_test_case()
{
    BOOST_CHECK_MESSAGE(hack::JumpTable::lookup["JLE"] == "110", "Should be '110' but was " << hack::JumpTable::lookup["JLE"]);
}
