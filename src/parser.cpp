#include "../headers/parser.hpp"

namespace hack {

    Parser::Parser(std::istream& file) : _file(file)
    {
        _pc = -1;
        _mem = 16;
        _currentCommand = "";
        _fileHead = _file.tellg();
        _lCommand.assign("\\((.*)\\)", std::regex_constants::icase);
        _aCommand.assign("\\@([\\w*|\\d*]*).*", std::regex_constants::icase);
    }

    Parser::~Parser()
    {
        // do nothing
    }

    bool Parser::hasMoreCommands()
    {
        bool moreCommands = false;
        std::string line;
        auto prevPos = _file.tellg();
        do {
            getline(_file, line);
            if (!isWhitespace(line)) {
                moreCommands = true;
                break;
            }
        } while (!_file.eof());

        _file.seekg(prevPos);

        return moreCommands;
    }

    void Parser::advance()
    {
        if (hasMoreCommands()) {
            std::string tempCommand;
            do {
                getline(_file, tempCommand);
                trimCommand(tempCommand);
            } while ((isWhitespace(tempCommand) || tempCommand.substr(0,2) == "//") && hasMoreCommands());
            _currentCommand = tempCommand;
            _pc += 1;
        } else {
            _currentCommand = "--ERROR--";
        }
    }

    COMMAND_TYPE Parser::commandType() const
    {
        if (std::regex_match(_currentCommand, _lCommand)) {
            return L_COMMAND;
        } else if (std::regex_match(_currentCommand, _aCommand)) {
            return A_COMMAND;
        }

        return C_COMMAND;
    }

    std::string Parser::getCurrentCommand() const
    {
        return _currentCommand;
    }

    std::string Parser::getSymbol()
    {
        if (commandType() == A_COMMAND) {
            auto first = _currentCommand.find_first_not_of("@");
            return _currentCommand.substr(first);
        } else if (commandType() == L_COMMAND) {
            auto first = _currentCommand.find_first_not_of("(");
            auto second = _currentCommand.find_last_not_of(")");
            return _currentCommand.substr(first, second - first + 1);
        }

        return "";
    }

    std::string Parser::getDestBits()
    {
        if (commandType() != C_COMMAND) {
            return "";
        }

        // Check for equal sign
        auto index = _currentCommand.find("=");
        // if no equal sign, return null entry
        if (index == std::string::npos) {
            return DestTable::lookup[""];
        }
        // get substr and find key from dest table
        auto dest = _currentCommand.substr(0, index);

        return DestTable::lookup[dest];
    }

    std::string Parser::getCompBits()
    {
        if (commandType() != C_COMMAND) {
            return "";
        }

        auto equalPos = _currentCommand.find("=");
        auto semiColonPos = _currentCommand.find(";");

        if (equalPos == std::string::npos && semiColonPos == std::string::npos) {
            return "";
        }

        std::string comp;
        if (equalPos != std::string::npos) {
            comp = _currentCommand.substr(equalPos + 1);
            auto bitPair = CompTable::lookup[comp];
            return bitPair.first + bitPair.second;
        } else if (semiColonPos != std::string::npos) {
            comp = _currentCommand.substr(0, semiColonPos);
            auto bitPair = CompTable::lookup[comp];
            return bitPair.first + bitPair.second;
        }

        return "";
    }

    std::string Parser::getJumpBits()
    {
        if (commandType() != C_COMMAND) {
            return "";
        }

        auto semiColonPos = _currentCommand.find(";");

        if (semiColonPos == std::string::npos) {
            return JumpTable::lookup[""];
        }

        auto jump = _currentCommand.substr(semiColonPos + 1);

        return JumpTable::lookup[jump];
    }

    std::string Parser::translateACode(int value)
    {
        std::string encoded = std::bitset<15>(value).to_string();

        return encoded;
    }

    void Parser::rewind()
    {
        _file.clear();
        _file.seekg(_fileHead);
    }

    void Parser::collectSymbols()
    {
        while (hasMoreCommands()) {
            advance();
            if (commandType() == L_COMMAND || commandType() == A_COMMAND) {
                int value;
                try {
                    value = stoi(getSymbol());
                } catch (std::invalid_argument exc) {
                    std::string symbol = getSymbol();
                    if (!_symbols.contains(symbol)) {
                        if (commandType() == L_COMMAND) {
                            _symbols.addSymbol(symbol, _pc);
                        } else {
                            _symbols.addSymbol(symbol, _mem);
                            ++_mem;
                        }
                    }
                }
            }
        }
    }

    void Parser::translateAssembly(std::ostream& oss)
    {
        while (hasMoreCommands()) {
            advance();
            if (commandType() == L_COMMAND) {
                // Nothing for now
            } else if (commandType() == A_COMMAND) {
                int value;
                try {
                    value = stoi(getSymbol());
                } catch (std::invalid_argument exc) {
                    std::cout << "Error on symbol: " << getSymbol() << std::endl;
                }

                oss << "0" + translateACode(value) << std::endl;
            } else {
                oss << "111" + getCompBits() + getDestBits() + getJumpBits() << std::endl;
            }
        }
    }

    // Accessor methods for testing
    void Parser::setCurrentCommand(std::string command)
    {
        _currentCommand = std::move(command);
    }

    int Parser::getPC() const
    {
        return _pc;
    }

    SymbolTable Parser::getSymbolTable() const
    {
        return _symbols;
    }

    void Parser::trimCommand(std::string& commandToTrim)
    {
        if (commandToTrim.size() > 0) {
            auto firstPos = commandToTrim.find_first_not_of(' ');
            auto lastPos = commandToTrim.find_last_not_of(' ');
            commandToTrim = commandToTrim.substr(firstPos, (lastPos - firstPos + 1));

            commandToTrim.erase(std::remove(commandToTrim.begin(), commandToTrim.end(), '\r'), commandToTrim.end());
        }
    }

    bool Parser::isWhitespace(std::string& line)
    {
        for (char c : line) {
            if (!std::isspace(c)) {
                return false;
            }
        }

        return true;
    }
}
