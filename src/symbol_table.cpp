#include "../headers/headers.hpp"
#include "../headers/symbol_table.hpp"

namespace hack {
	SymbolTable::SymbolTable() : _symbolTable(std::shared_ptr<std::map<std::string, int>>(new std::map<std::string, int>()))
	{
		// insert preset symbols
		_symbolTable->emplace(std::make_pair("SP", 0));
		_symbolTable->emplace(std::make_pair("LCL", 1));
		_symbolTable->emplace(std::make_pair("ARG", 2));
		_symbolTable->emplace(std::make_pair("THIS", 3));
		_symbolTable->emplace(std::make_pair("THAT", 4));
		_symbolTable->emplace(std::make_pair("R0", 0));
		_symbolTable->emplace(std::make_pair("R1", 1));
		_symbolTable->emplace(std::make_pair("R2", 2));
		_symbolTable->emplace(std::make_pair("R3", 3));
		_symbolTable->emplace(std::make_pair("R4", 4));
		_symbolTable->emplace(std::make_pair("R5", 5));
		_symbolTable->emplace(std::make_pair("R6", 6));
		_symbolTable->emplace(std::make_pair("R7", 7));
		_symbolTable->emplace(std::make_pair("R8", 8));
		_symbolTable->emplace(std::make_pair("R9", 9));
		_symbolTable->emplace(std::make_pair("R10", 10));
		_symbolTable->emplace(std::make_pair("R11", 11));
		_symbolTable->emplace(std::make_pair("R12", 12));
		_symbolTable->emplace(std::make_pair("R13", 13));
		_symbolTable->emplace(std::make_pair("R14", 14));
		_symbolTable->emplace(std::make_pair("R15", 15));
		_symbolTable->emplace(std::make_pair("SCREEN", 16384));
		_symbolTable->emplace(std::make_pair("KBD", 24576));
	}

	SymbolTable::~SymbolTable()
	{
		// do nothing
	}

	void SymbolTable::addSymbol(const std::string& symbol, int address)
	{
		_symbolTable->emplace(std::make_pair(symbol, address));
	}

	bool SymbolTable::contains(const std::string& symbol) const
	{
		auto result = _symbolTable->find(symbol);
		return result != _symbolTable->end();
	}

	int SymbolTable::retrieveSymbol(const std::string& key) const
	{
		if (contains(key)) {
			return _symbolTable->at(key);
		}

		return -1;
	}

	int SymbolTable::size() const
	{
		return _symbolTable->size();
	}
}
