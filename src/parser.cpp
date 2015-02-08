#include "../headers/parser.hpp"

namespace hack {

    // Parser::Parser()
    // {
    //     _currentCommand = "";
    //     lCommand.assign("\\((.*)\\)", std::regex_constants::icase);
    //     aCommand.assign("\\@([\\w*|\\d*]*)", std::regex_constants::icase);
    // }

    Parser::Parser(std::istream& file) : _file(file)
    {
        _currentCommand = "";
        _fileHead = _file.tellg();
        lCommand.assign("\\((.*)\\)", std::regex_constants::icase);
        aCommand.assign("\\@([\\w*|\\d*]*)", std::regex_constants::icase);
    }

    Parser::~Parser()
    {
        // do nothing
    }

    std::string Parser::nextLine() const
    {
        std::string line;
        std::getline(_file, line);
        return line;
    }

    bool Parser::hasMoreCommands()
    {
        bool moreCommands;
        std::string line;
        auto previousPos = _file.tellg();

        _file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(_file, line);

        if (line.substr(0,1) == "\n") {
            moreCommands = false;
        } else {
            moreCommands = !_file.eof();
        }

        _file.seekg(previousPos);
        return moreCommands;
    }

    void Parser::advance()
    {
        if (hasMoreCommands()) {
            std::string tempCommand;
            do {
                getline(_file, tempCommand);
                trimCommand(tempCommand);
            } while ((tempCommand == "" || tempCommand.substr(0,2) == "//") && !_file.eof());

            _currentCommand = tempCommand;
        } else {
            _currentCommand = "--ERROR--";
        }
    }

    COMMAND_TYPE Parser::commandType() const
    {
        if (std::regex_match(_currentCommand, lCommand)) {
            return L_COMMAND;
        } else if (std::regex_match(_currentCommand, aCommand)) {
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

    void Parser::trimCommand(std::string& commandToTrim)
    {
        if (commandToTrim.size() > 0) {
            auto firstPos = commandToTrim.find_first_not_of(' ');
            auto lastPos = commandToTrim.find_last_not_of(' ');
            commandToTrim = commandToTrim.substr(firstPos, (lastPos - firstPos + 1));
        }
    }

    void Parser::rewind()
    {
        _file.seekg(_fileHead);
    }

    // Accessor methods for testing
    void Parser::setCurrentCommand(std::string command)
    {
        _currentCommand = std::move(command);
    }
}
