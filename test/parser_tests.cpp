#include "headers/parser_tests.hpp"

void parser_init_test_case()
{
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);
    if (parser.hasMoreCommands()) {
        parser.advance();
        BOOST_CHECK_MESSAGE(parser.getCurrentCommand() == "@R2", "Should be '@R2' but was: " << parser.getCurrentCommand());
    }
}

void parser_command_type_test_case()
{
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);

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
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);
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
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);

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
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);

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
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);

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
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);
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

void parser_pc_test_case()
{
    std::stringstream mockStream;
    mockInputStream(mockStream);
    hack::Parser parser(mockStream);

    for (int pc = 0; parser.hasMoreCommands(); pc++) {
        parser.advance();
        BOOST_CHECK_MESSAGE(parser.getPC() == pc, "Should be 0 but was " << parser.getPC());
    }
}

void parser_collect_symbols_test_case()
{
    std::stringstream mockStream;
    mockInputStreamWithSymbols(mockStream);
    hack::Parser parser(mockStream);
    parser.collectSymbols();

    auto table = parser.getSymbolTable();

    BOOST_CHECK_MESSAGE(table.size() == 26, "Should be '26' but was " << table.size());
    BOOST_CHECK_MESSAGE(table.contains("OUTPUT_FIRST") && table.retrieveSymbol("OUTPUT_FIRST") == 10,
        "Should be '10' but was " << table.retrieveSymbol("OUTPUT_FIRST"));

    BOOST_CHECK_MESSAGE(table.contains("OUTPUT_D") && table.retrieveSymbol("OUTPUT_D") == 12,
        "Should be '13' but was " << table.retrieveSymbol("OUTPUT_D"));

    BOOST_CHECK_MESSAGE(table.contains("INFINITE_LOOP") && table.retrieveSymbol("INFINITE_LOOP") == 14,
        "Should be '16' but was " << table.retrieveSymbol("INFINITE_LOOP"));
}

void parser_assemble_test_case()
{
    std::stringstream mockStream;
    mockInputStreamNoSymbols(mockStream);
    hack::Parser parser(mockStream);
    std::vector<std::string> expectedBinary {
        "0000000000000010",
        "1110110000010000",
        "0000000000000011",
        "1110000010010000",
        "0000000000000000",
        "1110001100001000",
        ""
    };

    std::stringstream oss;
    parser.translateAssembly(oss);

    std::string line;
    std::vector<std::string> actualBinary;
    while (!oss.eof()) {
        getline(oss, line);
        actualBinary.emplace_back(line);
    }

    BOOST_CHECK_MESSAGE(actualBinary.size() == expectedBinary.size(), "Should be '6' but was " << actualBinary.size());
    for (int i = 0; i < actualBinary.size(); ++i) {
        BOOST_CHECK_MESSAGE(expectedBinary[i] == actualBinary[i],
            "Should be '" << expectedBinary[i] << "' but was '" << actualBinary[i] << "'");
    }
}

void parser_assemble_with_symbols_test_case()
{
    std::stringstream mockStream;
    mockInputStreamWithSymbols(mockStream);
    hack::Parser parser(mockStream);
    std::vector<std::string> expectedBinary {
        "0000000000000000",
        "1111110000010000",
        "0000000000000001",
        "1111010011010000",
        "0000000000001010",
        "1110001100000001",
        "0000000000000001",
        "1111110000010000",
        "0000000000001100",
        "1110101010000111",
        "0000000000000000",
        "1111110000010000",
        "0000000000000010",
        "1110001100001000",
        "0000000000001110",
        "1110101010000111",
        ""
    };

    std::stringstream oss;
    parser.translateAssembly(oss);

    std::string line;
    std::vector<std::string> actualBinary;
    while (!oss.eof()) {
        getline(oss, line);
        actualBinary.emplace_back(line);
    }

    BOOST_CHECK_MESSAGE(actualBinary.size() == expectedBinary.size(), "Should be '17' but was " << actualBinary.size());
    for (int i = 0; i < actualBinary.size(); ++i) {
        BOOST_CHECK_MESSAGE(expectedBinary[i] == actualBinary[i],
            "Should be '" << expectedBinary[i] << "' but was '" << actualBinary[i] << "'");
    }
}
