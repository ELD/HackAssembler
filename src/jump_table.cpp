#include "../headers/jump_table.hpp"

namespace hack {
	JumpTable::JumpBits JumpTable::lookup = {
		{"", "000"},
		{"JGT", "001"},
		{"JEQ", "010"},
		{"JGE", "011"},
		{"JLT", "100"},
		{"JNE", "101"},
		{"JLE", "110"},
		{"JMP", "111"}
	};
}