#include "headers/utility.hpp"
#include "headers/parser_tests.hpp"
#include "headers/symbol_table_tests.hpp"
#include "headers/lookup_table_tests.hpp"
#include "../headers/headers.hpp"

using namespace boost::unit_test;

bool init_function();

int main(int argc, char* argv[])
{
    return ::boost::unit_test::unit_test_main(&init_function, argc, argv);
}

bool init_function()
{
    auto parser_suite = BOOST_TEST_SUITE("Parser_Test_Suite");
    parser_suite->add(BOOST_TEST_CASE(&parser_init_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_command_type_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_token_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_dest_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_comp_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_jump_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_all_bits_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_pc_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_collect_symbols_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_assemble_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_assemble_with_symbols_test_case));

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
