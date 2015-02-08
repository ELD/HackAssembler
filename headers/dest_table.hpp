#ifndef _DEST_TABLE_H_
#define _DEST_TABLE_H_

#include "headers.hpp"

namespace hack {
	class DestTable {
	public:
		typedef std::map<std::string, std::string> DestBits;
		static DestBits lookup;
	};
}

#endif