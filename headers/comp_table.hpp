#ifndef _COMP_TABLE_H_
#define _COMP_TABLE_H_

#include "headers.hpp"

namespace hack {
	class CompTable
	{
	public:
		typedef std::unordered_map<std::string, std::pair<std::string, std::string>> CompBits;
		static CompBits lookup;
	};
}

#endif
