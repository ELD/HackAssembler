#ifndef _JUMP_TABLE_H_
#define _JUMP_TABLE_H_

#include "headers.hpp"

namespace hack {
	class JumpTable {
	public:
		typedef std::map<std::string, std::string> JumpBits;
		static JumpBits lookup;
	};
}

#endif