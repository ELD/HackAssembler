#include "../headers/parser.hpp"

// TODO: Rewrite first pass for optimization; only collect labels

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

    bool Parser::hasMoreCommands()
    {
        return !_file.eof();
    }

    bool Parser::advance()
    {
        if (hasMoreCommands()) {
            if (commandType() != L_COMMAND) {
                _pc += 1;
            }
            std::string tempCommand;
            do {
                getline(_file, tempCommand);
                trimCommand(tempCommand);
            } while ((isWhitespace(tempCommand) || tempCommand.substr(0,2) == "//") && hasMoreCommands());
            if (tempCommand != "") {
                trimComments(tempCommand);
                trimCommand(tempCommand);
                _currentCommand = tempCommand;
                return true;
            } else {
                _currentCommand = "GARBAGE";
                return false;
            }
        }

        return false;
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


        auto index = _currentCommand.find("=");

        if (index == std::string::npos) {
            return DestTable::lookup[""];
        }

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

    void Parser::collectLabels()
    {
        while (advance()) {
            if (commandType() == L_COMMAND) {
                if (_symbols.contains(getSymbol())) {
                    continue;
                }

                _symbols.addSymbol(getSymbol(), _pc);
            }
        }

        rewind();
    }

    void Parser::translateAssembly(std::ostream& oss)
    {
        collectLabels();
        while (advance()) {
            if (_currentCommand == "GARBAGE") {
                return;
            }

            if (commandType() == A_COMMAND) {
                int value;

                try {
                    value = stoi(getSymbol());
                } catch (std::invalid_argument exc) {
                    if (_symbols.contains(getSymbol())) {
                        value = _symbols.retrieveSymbol(getSymbol());
                    } else {
                        value = _mem;
                        _symbols.addSymbol(getSymbol(), _mem);
                        ++_mem;
                    }
                }

                oss << "0" + translateACode(value) << std::endl;
            } else if (commandType() == C_COMMAND) {
                oss << "111" + getCompBits() + getDestBits() + getJumpBits() << std::endl;
            }
        }
    }

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

    void Parser::trimComments(std::string& commandToTrim)
    {
        auto commentPos = commandToTrim.find_first_of("//");
        if (commentPos != std::string::npos) {
            commandToTrim = commandToTrim.substr(0, commentPos);
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
