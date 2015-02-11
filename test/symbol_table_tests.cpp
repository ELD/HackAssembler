#include "headers/symbol_table_tests.hpp"

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
