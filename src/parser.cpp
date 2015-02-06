#include "../headers/parser.hpp"

namespace hack {

    Parser::Parser(const std::string fileName) : _file(std::unique_ptr<std::ifstream>(new std::ifstream(fileName)))
    {
        _currentCommand = "";
        _fileHead = _file->tellg();
        std::regex lCommand(R"(\(.*\))", std::regex_constants::icase);
        std::regex aCommand(R"(\@[\w*|\d*]*)", std::regex_constants::icase);
    }

    Parser::~Parser()
    {
        // do nothing
    }

    std::string Parser::nextLine() const
    {
        std::string line;
        std::getline(*_file, line);
        return line;
    }

    bool Parser::hasMoreCommands()
    {
        bool moreCommands;
        std::string line;
        auto previousPos = _file->tellg();

        _file->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(*_file, line);

        if (line.substr(0,1) == "\n") {
            moreCommands = false;
        } else {
            moreCommands = !_file->eof();
        }

        _file->seekg(previousPos);
        return moreCommands;
    }

    void Parser::advance()
    {
        if (hasMoreCommands()) {
            std::string tempCommand;
            do {
                getline(*_file, tempCommand);
                trimCommand(tempCommand);
            } while ((tempCommand == "" || tempCommand.substr(0,2) == "//") && !_file->eof());

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

    std::string Parser::symbol()
    {
        if (commandType() == L_COMMAND || commandType() == A_COMMAND) {

        }

        return "";
    }

    std::string Parser::dest()
    {
        return "";
    }

    std::string Parser::comp()
    {
        return "";
    }

    std::string Parser::jump()
    {
        return "";
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
        _file->seekg(_fileHead);
    }

    // Accessor methods for testing
    void Parser::setCurrentCommand(std::string command)
    {
        _currentCommand = std::move(command);
    }
}
