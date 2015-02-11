#include "headers/lookup_table_tests.hpp"

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
