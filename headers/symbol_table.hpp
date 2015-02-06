#include "headers.hpp"
#include <map>

namespace hack {
	class SymbolTable {
	public:
		SymbolTable();
		~SymbolTable();
		void addSymbol(const std::string&, int);
		bool contains(const std::string&) const;
		int retrieveSymbol(const std::string&) const;

	private:
		std::unique_ptr<std::map<std::string, int>> _symbolTable;
	};
}