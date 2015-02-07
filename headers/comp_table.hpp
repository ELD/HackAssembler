#ifndef _COMP_TABLE_H_
#define _COMP_TABLE_H_

#include "../headers/headers.hpp"
#include <map>

namespace hack {
	class CompTable
	{
	public:
		typedef std::map<std::pair<int, std::string>, std::string> CompBits;
		static CompBits lookup;
	};
}

#endif