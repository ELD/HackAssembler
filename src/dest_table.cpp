#include "../headers/dest_table.hpp"

namespace hack {
	DestTable::DestBits DestTable::lookup = {
			{"", "000"},
			{"M", "001"},
			{"D", "010"},
			{"MD", "011"},
			{"A", "100"},
			{"AM", "101"},
			{"AD", "110"},
			{"AMD", "111"}
		};
}