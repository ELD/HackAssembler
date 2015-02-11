#ifndef _UTILITY_H_
#define _UTILITY_H_

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>
#include "utility.hpp"
#include "../../headers/headers.hpp"

void mockInputStream(std::stringstream&);
void mockInputStreamNoSymbols(std::stringstream&);
void mockInputStreamWithSymbols(std::stringstream&);
std::string getCommandString(int commandType);

#endif
